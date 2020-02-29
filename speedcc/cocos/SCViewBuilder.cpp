/****************************************************************************
 
 Copyright (c) 2017-2020 Kevin Wu (Wu Feng)
 
 github: http://github.com/kevinwu1024
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include "SCViewBuilder.h"
#include "SCViewController.h"
#include "SCNodeUtils.h"
#include "SCNodeAttachment.h"

#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStageMacros.h"

#include "../system/SCSystem.h"

using namespace cocos2d;

NAMESPACE_SPEEDCC_BEGIN

///------------ root container

void SCViewBuilder::beginParentRoot(const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& style,
                                const SCUIArg::SizePurifier& sizePurifier,
                                const SCUIArg::NodePurifier& parentNode,
                                cocos2d::Ref* pRef)
{
    Node* pParentNode = dynamic_cast<Node*>(parentNode.ptrNodeHolder->getRef());
    SCASSERT(pParentNode!=nullptr);
    _pCurrentRefCaller = pRef;
    _pCurrentBedNode = pParentNode;
    SCASSERT(_pCurrentBedNode!=nullptr);
    SCASSERT(_pCurrentRefCaller!=nullptr);
        
    cocos2d::Size size = (sizePurifier.size.equals(Size::ZERO)) ? pParentNode->getContentSize() : sizePurifier.size;
        
    _pCurrentBedNode->setContentSize(size);
        
    _pCurrentBedNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _pCurrentBedNode->setIgnoreAnchorPointForPosition(false);
        
    if(fPosX!=kSCPositionIgnore && fPosY!=kSCPositionIgnore)
    {
        _pCurrentBedNode->setPosition(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2(fPosX,fPosY),size));
    }
    else if(fPosX!=kSCPositionIgnore)
    {
        _pCurrentBedNode->setPositionX(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2(fPosX,fPosY),size).x);
    }
    else if(fPosY!=kSCPositionIgnore)
    {
        _pCurrentBedNode->setPositionY(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2(fPosX,fPosY),size).y);
    }
        
    SCNodeStyle::SFilterConfig config;
    config.setupPosition(true);
    parentNode.pfunSetStyle(pParentNode,style.strResult,&config);
        
    this->pushParentStack(pParentNode);
}
    
void SCViewBuilder::popParentStack()
{
    SCASSERT(!_contextStack.empty());
    auto& front = _contextStack.front();
        
    if(front.endFunc!=nullptr)
    {
        front.endFunc(front);
    }
        
    _contextStack.pop_front();
}
    
cocos2d::Node* SCViewBuilder::getContextParent() const
{
    SCASSERT(!_contextStack.empty());
    const auto& top = _contextStack.front();
    return top.pContainerNode;
}
    
///------------ user node
cocos2d::Node* SCViewBuilder::insertUserNode(const SCUIArg::NodePurifier& userNode,
                                            const float fPosX,
                                            const float fPosY,
                                            const SCUIArg::StringPurifier& style)
{
    Node* pNode = dynamic_cast<Node*>(userNode.ptrNodeHolder->getRef());
    SCASSERT(pNode!=nullptr);
    auto& top = _contextStack.front();
    top.pContainerNode->addChild(pNode);
    SCNodeUtils::setPositionPer(pNode, Vec2(fPosX,fPosY));
        
    if(top.containerType==SCUITypeDef::EContainerType::kAlignment)
    {// for padding layout container, all of children position are ignored
    // it's position is handled by layout container while container context pops.
        SCNodeStyle::SFilterConfig config;
        config.setupPosition(true);
        userNode.pfunSetStyle(pNode,style.strResult,&config);
    }
    else
    {
        userNode.pfunSetStyle(pNode,style.strResult,nullptr);
    }
        
    return pNode;
}
    
cocos2d::Node* SCViewBuilder::insertNode(SCUIArg::NodeAssignment<cocos2d::Node> assignNode,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style,
                                            const cocos2d::Size& size)
{
    auto pNode = cocos2d::Node::create();
    pNode->setContentSize(size);
    pNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    pNode->setIgnoreAnchorPointForPosition(false);
    this->insertUserNode(pNode,fPosX,fPosY,style);
    assignNode.assign(pNode);
    
    if(assignNode.nID)
    {
        _id2NodeMap[assignNode.nID] = pNode;
    }
    
    return pNode;
}
    
///---------------- sprite
cocos2d::Sprite* SCViewBuilder::insertSprite(SCUIArg::NodeAssignment<cocos2d::Sprite> assignSprite,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& style,
                                const SCString& strImage)
{
    auto pSprite = SCNodeUtils::createSprite(strImage);
    this->insertUserNode(pSprite,fPosX,fPosY,style);
    assignSprite.assign(pSprite);
    
    if(assignSprite.nID)
    {
        _id2NodeMap[assignSprite.nID] = pSprite;
    }
    
    return pSprite;
}
    
///------------ label
    
Label* SCViewBuilder::insertLabel(SCUIArg::NodeAssignment<cocos2d::Label> assignLabel,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style,
                            const SCUIArg::LabelStringPurifier& labelString,
                            const SCString& strFont,
                            const float fFontSize)
{
    SCString strLabelText = labelString.strResult;
        
    auto pLabel = Label::createWithSystemFont(strLabelText.c_str(),strFont.c_str(),fFontSize);
    this->addLabel(pLabel,fPosX,fPosY,style,labelString);
    assignLabel.assign(pLabel);
    
    if(assignLabel.nID)
    {
        _id2NodeMap[assignLabel.nID] = pLabel;
    }
    
    return pLabel;
}
    
Label* SCViewBuilder::insertLabelTTF(SCUIArg::NodeAssignment<cocos2d::Label> assignLabel,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& style,
                                const SCUIArg::LabelStringPurifier& labelString,
                                const SCString& strFont,
                                const float fFontSize)
{
    SCString strLabelText = labelString.strResult;
        
    auto pLabel = Label::createWithTTF(strLabelText.c_str(),strFont.c_str(),fFontSize);
    this->addLabel(pLabel,fPosX,fPosY,style,labelString);
    assignLabel.assign(pLabel);
    
    if(assignLabel.nID)
    {
        _id2NodeMap[assignLabel.nID] = pLabel;
    }
    
    return pLabel;
}
    
cocos2d::Label* SCViewBuilder::insertLabelBMFont(SCUIArg::NodeAssignment<cocos2d::Label> assignLabel,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::StringPurifier& style,
                                    const SCUIArg::LabelStringPurifier& labelString,
                                    const SCString& strFile)
{
    SCString strLabelText = labelString.strResult;
        
    auto pLabel = Label::createWithBMFont(strFile.c_str(),strLabelText.c_str());
    this->addLabel(pLabel,fPosX,fPosY,style,labelString);
    assignLabel.assign(pLabel);
    
    if(assignLabel.nID)
    {
        _id2NodeMap[assignLabel.nID] = pLabel;
    }
    
    return pLabel;
}
    
void SCViewBuilder::addLabel(const SCUIArg::NodePurifier& labelNode,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style,
                            const SCUIArg::LabelStringPurifier& labelString)
{
    this->bindLabel(labelNode,labelString);
    this->insertUserNode(labelNode, fPosX, fPosY, style);
}
    
void SCViewBuilder::bindLabel(const SCUIArg::NodePurifier& labelNode,
                const SCUIArg::LabelStringPurifier& labelString)
{
    auto ptrBinder = labelString.ptrLabelBinder;
    cocos2d::Label* pLabel = dynamic_cast<Label*>(labelNode.ptrNodeHolder->getRef());
    SCASSERT(pLabel!=nullptr);
        
    if(ptrBinder!=nullptr && pLabel!=nullptr)
    {
        ptrBinder->setLabel(pLabel);
        SCNodeAttach(pLabel)->addUserObj(ptrBinder);
    }
}
///---------------- button
cocos2d::MenuItemSprite* SCViewBuilder::insertButton(SCUIArg::NodeAssignment<cocos2d::MenuItemSprite> assignMenuItemSprite,
                                                    const float fPosX,
                                                    const float fPosY,
                                                    const SCUIArg::StringPurifier& style,
                                                    const SCString& strImageNormal,
                                                    const SCString& strSelect,
                                                    const SCString& strDisable,
                                                    SCUIArg::BehaviorPurifier bvrPurifier)
{
    cocos2d::Sprite* pSpriteArray[3] = {nullptr};
    pSpriteArray[0] = SCNodeUtils::createSprite(strImageNormal);
    pSpriteArray[1] = SCNodeUtils::createSprite(strSelect);
    pSpriteArray[2] = SCNodeUtils::createSprite(strDisable);
        
    auto pItemImage = MenuItemSprite::create(pSpriteArray[0],
                                                pSpriteArray[1],
                                                pSpriteArray[2]);
        
    this->addButton(pItemImage,fPosX,fPosY,style,bvrPurifier);
    assignMenuItemSprite.assign(pItemImage);
    
    if(assignMenuItemSprite.nID)
    {
        _id2NodeMap[assignMenuItemSprite.nID] = pItemImage;
    }
        
    return pItemImage;
}
    
MenuItemLabel* SCViewBuilder::insertButtonLabel(SCUIArg::NodeAssignment<cocos2d::MenuItemLabel> assignMenuItemLabel,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::StringPurifier& style,
                                    const SCUIArg::LabelStringPurifier& labelString,
                                    const SCString& strFont,
                                    const float fFontSize,
                                    SCUIArg::BehaviorPurifier bvrPurifier)
{
    SCString strLabelText = labelString.strResult;
        
    auto pLabel = Label::createWithSystemFont(strLabelText.c_str(),strFont.c_str(),fFontSize);
        
    auto ret = this->addButtonLabel(pLabel,fPosX,fPosY,style,labelString,bvrPurifier);
    assignMenuItemLabel.assign(ret);
    
    if(assignMenuItemLabel.nID)
    {
        _id2NodeMap[assignMenuItemLabel.nID] = ret;
    }
    
    return ret;
}
    
MenuItemLabel* SCViewBuilder::insertButtonLabelTTF(SCUIArg::NodeAssignment<cocos2d::MenuItemLabel> assignMenuItemLabel,
                                                const float fPosX,
                                                const float fPosY,
                                                const SCUIArg::StringPurifier& style,
                                                const SCUIArg::LabelStringPurifier& labelString,
                                                const SCString& strFont,
                                                const float fFontSize,
                                                SCUIArg::BehaviorPurifier bvrPurifier)
{
    SCString strLabelText = labelString.strResult;
    auto pLabel = Label::createWithTTF(strLabelText.c_str(),strFont.c_str(),fFontSize);
    auto ret = this->addButtonLabel(pLabel,fPosX,fPosY,style,labelString,bvrPurifier);
    assignMenuItemLabel.assign(ret);
    
    if(assignMenuItemLabel.nID)
    {
        _id2NodeMap[assignMenuItemLabel.nID] = ret;
    }
    
    return ret;
}
    
MenuItemLabel* SCViewBuilder::insertButtonLabelBMFont(SCUIArg::NodeAssignment<cocos2d::MenuItemLabel> assignMenuItemLabel,
                                                const float fPosX,
                                                const float fPosY,
                                                const SCUIArg::StringPurifier& style,
                                                const SCUIArg::LabelStringPurifier& labelString,
                                                const SCString& strFile,
                                                SCUIArg::BehaviorPurifier bvrPurifier)
{
    SCString strLabelText = labelString.strResult;
    auto pLabel = Label::createWithBMFont(strFile.c_str(),strLabelText.c_str());
    auto ret = this->addButtonLabel(pLabel,fPosX,fPosY,style,labelString,bvrPurifier);
    assignMenuItemLabel.assign(ret);
    
    if(assignMenuItemLabel.nID)
    {
        _id2NodeMap[assignMenuItemLabel.nID] = ret;
    }
    
    return ret;
}
    
MenuItemToggle* SCViewBuilder::insertButtonSwitch(SCUIArg::NodeAssignment<cocos2d::MenuItemToggle> assignMenuItemToggle,
                                            const float fPosX,
                                            const float fPosY,
                                            const SCUIArg::StringPurifier& style,
                                            const SCUIArg::MenuItemPurifier& itemOn,
                                            const SCUIArg::MenuItemPurifier& itemOff,
                                            const SCUIArg::BoolPurifier& value,
                                            SCUIArg::BehaviorPurifier bvrPurifier)
{
    MenuItem* pOnItem = (MenuItem*)itemOn.ptrHolder->getRef();
    MenuItem* pOffItem = (MenuItem*)itemOff.ptrHolder->getRef();
        
    SCASSERT(pOnItem!=nullptr);
    SCASSERT(pOffItem!=nullptr);
        
    bvrPurifier.setupBehavior(_pCurrentRefCaller,pOnItem);
    bvrPurifier.setupBehavior(_pCurrentRefCaller,pOffItem);
        
    auto pToggleItem = MenuItemToggle::createWithCallback(nullptr,pOnItem,pOffItem,nullptr);
    pToggleItem->setSelectedIndex(value.bResult ? 0 : 1);
        
    if(value.ptrWatch!=nullptr)
    {
        auto ptrLabelBinder = SCBinderUISwitch::create();
            
        ptrLabelBinder->setWatch(value.ptrWatch);
        ptrLabelBinder->setToggle(pToggleItem);
        SCNodeAttach(pToggleItem)->addUserObj(ptrLabelBinder);
    }

    // add clickable 
    bvrPurifier.setupBehavior(_pCurrentRefCaller, pToggleItem);
    SCNodeAttach(pToggleItem)->addClickable(bvrPurifier.ptrResultBvr);
        
    this->insertUserNode(pToggleItem, fPosX, fPosY, style);
        
    assignMenuItemToggle.assign(pToggleItem);
    
    if(assignMenuItemToggle.nID)
    {
        _id2NodeMap[assignMenuItemToggle.nID] = pToggleItem;
    }
        
    return pToggleItem;
}
    
cocos2d::MenuItemToggle* SCViewBuilder::insertButtonRadio(SCUIArg::NodeAssignment<cocos2d::MenuItemToggle> assignMenuItemToggle,
                                            const float fPosX,
                                            const float fPosY,
                                            const SCUIArg::StringPurifier& style,
                                            const SCUIArg::MenuItemPurifier& itemOn,
                                            const SCUIArg::MenuItemPurifier& itemOff,
                                            SCRadioGroup::Ptr ptrRadioGroup,
                                            const int nID,
                                            SCUIArg::BehaviorPurifier bvrPurifier)
{
    SCASSERT(ptrRadioGroup!=nullptr);
    SCString strStyle = style.strResult + SCString(0,"radio=%d;",nID);
    auto pMenuItemToggle = this->insertButtonSwitch(assignMenuItemToggle,fPosX,fPosY,strStyle,itemOn,itemOff,true,bvrPurifier);
    ptrRadioGroup->addRadio(pMenuItemToggle);
    
    if(assignMenuItemToggle.nID)
    {
        _id2NodeMap[assignMenuItemToggle.nID] = pMenuItemToggle;
    }
    
    return pMenuItemToggle;
}

cocos2d::ProgressTimer* SCViewBuilder::insertProgressBar(SCUIArg::NodeAssignment<cocos2d::ProgressTimer> assignProgress,
                                            const float fPosX,
                                            const float fPosY,
                                            const SCUIArg::StringPurifier& style,
                                            const SCString& strBackgroundImage,
                                            const SCString& strFrontgroundImage,
                                            SCUIArg::PTNumberPurifier value,
                                            const bool bHorizontal,
                                            const bool bBaseLB)
{
    SCASSERT(!strFrontgroundImage.isEmpty());
        
    Sprite* pSpriteBar = SCNodeUtils::createSprite(strFrontgroundImage);
        
    auto pProgressBar =  ProgressTimer::create(pSpriteBar);
    pProgressBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    pProgressBar->setIgnoreAnchorPointForPosition(false);
    if(bHorizontal)
    {
        pProgressBar->setBarChangeRate(Vec2(1,0));
        pProgressBar->setMidpoint(Vec2((bBaseLB)?0.0f:1.0f,0.5f));
    }
    else
    {
        pProgressBar->setBarChangeRate(Vec2(0,1)) ;
        pProgressBar->setMidpoint(Vec2(0.5,(bBaseLB)?0.0f:1.0f));
    }

    pProgressBar->setType(ProgressTimer::Type::BAR);
        
    if(!strBackgroundImage.isEmpty())
    {
        Sprite* pSpriteBack = SCNodeUtils::createSprite(strBackgroundImage);
        pProgressBar->addChild(pSpriteBack,-1);
        pSpriteBack->setPosition(Vec2(pSpriteBar->getContentSize().width/2,pSpriteBar->getContentSize().height/2));
        pProgressBar->setContentSize(pSpriteBack->getContentSize()); // content size from background image
    }
        
    this->insertUserNode(pProgressBar, fPosX, fPosY, style);
        
    if(value.ptrBinderProgress!=nullptr)
    {
        value.ptrBinderProgress->setProgressTimer(pProgressBar);
        SCNodeAttach(pProgressBar)->addUserObj(value.ptrBinderProgress);
    }
    else
    {
        pProgressBar->setPercentage((float)value.nPercentage);
    }
    assignProgress.assign(pProgressBar);
    
    if(assignProgress.nID)
    {
        _id2NodeMap[assignProgress.nID] = pProgressBar;
    }
        
    return pProgressBar;
}
    
ProgressTimer* SCViewBuilder::insertProgressRadial(SCUIArg::NodeAssignment<cocos2d::ProgressTimer> assignProgress,
                                                    const float fPosX,
                                                    const float fPosY,
                                                    const SCUIArg::StringPurifier& style,
                                                    const SCString& strBackgroundImage,
                                                    const SCString& strFrontgroundImage,
                                                    SCUIArg::PTNumberPurifier value,
                                                    const bool bCCW)
{
    SCASSERT(!strFrontgroundImage.isEmpty());
        
    Sprite* pSpriteBar = SCNodeUtils::createSprite(strFrontgroundImage);
        
    auto pProgressBar =  ProgressTimer::create(pSpriteBar);
    pProgressBar->setType(ProgressTimer::Type::RADIAL);
        
    if(!strBackgroundImage.isEmpty())
    {
        Sprite* pSpriteBack = SCNodeUtils::createSprite(strBackgroundImage);
        pProgressBar->addChild(pSpriteBack,-1);
        SCNodeUtils::setPositionPer(pSpriteBack, Vec2(0.5,0.5));
    }
        
    pProgressBar->setReverseDirection(!bCCW);
        
    this->insertUserNode(pProgressBar, fPosX, fPosY, style);
        
    if(value.ptrBinderProgress!=nullptr)
    {
        value.ptrBinderProgress->setProgressTimer(pProgressBar);
        SCNodeAttach(pProgressBar)->addUserObj(value.ptrBinderProgress);
    }
    else
    {
        pProgressBar->setPercentage((float)value.nPercentage);
    }
    assignProgress.assign(pProgressBar);
    
    if(assignProgress.nID)
    {
        _id2NodeMap[assignProgress.nID] = pProgressBar;
    }
        
    return pProgressBar;
}
    
void SCViewBuilder::parentAlignment(SCUIArg::NodeAssignment<cocos2d::Node> assignNode,
                                            const float fPosX,
                                            const float fPosY,
                                            const SCUIArg::StringPurifier& style,
                                            const bool bHorizontal,
                                            const float fPadding,
                                            const SCUIArg::DockPurifier& dockPurifier)
{
    Node* pNode = Node::create();
    pNode->setIgnoreAnchorPointForPosition(false);
    pNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        
    SCString strDockStyle = SCNodeStyle::extractKey(SC_STYLE_DOCK, style.strResult);
    SCString strXByStyle = SCNodeStyle::extractKey(SC_STYLE_X_BY, style.strResult);
    SCString strYByStyle = SCNodeStyle::extractKey(SC_STYLE_Y_BY, style.strResult);
        
    SCString strNewStyle = style.strResult;
    if(!strDockStyle.isEmpty())
    {
        strNewStyle = SCNodeStyle::removeKey(SC_STYLE_DOCK,strNewStyle);
    }
        
    if(!strXByStyle.isEmpty())
    {
        strNewStyle = SCNodeStyle::removeKey(SC_STYLE_X_BY,strNewStyle);
    }
        
    if(!strYByStyle.isEmpty())
    {
        strNewStyle = SCNodeStyle::removeKey(SC_STYLE_Y_BY,strNewStyle);
    }
        
    SCString strDelayStyle = strDockStyle + strXByStyle + strYByStyle;
        
    SCUITypeDef::SUIContext context;
    context.pContainerNode = pNode;
    context.containerType = SCUITypeDef::EContainerType::kAlignment;
        
    int nDock = dockPurifier.nDock;
    if(nDock==0)
    {
        nDock = SCNodeUtils::EDockType::kDockCenter;
    }
        
    context.endFunc = [bHorizontal,
                        fPadding,
                        nDock,
                        strDelayStyle](SCUITypeDef::SUIContext& context)
    {
        Node* pNode = context.pContainerNode;
        auto childrenVec = pNode->getChildren();
        SC_RETURN_V_IF(childrenVec.empty());
            
        if(bHorizontal)
        {// x
            float fWidth = 0;
            int nDock2 = SC_BIT_REMOVE(nDock,SCNodeUtils::kDockMiddleX);
            const bool bApplyDock = SC_BIT_HAS_OR(nDock2, SCNodeUtils::kDockMiddleY);
                
            float fMaxHeight = 0;
            for(const auto& child : childrenVec)
            {
                fWidth += child->getContentSize().width * child->getScaleX() + fPadding;
                    
                const float fRealHeight = child->getContentSize().height * child->getScaleY();
                fMaxHeight = MAX(fMaxHeight,fRealHeight);
            }
                
            fWidth -= fPadding;
            pNode->setContentSize(Size(fWidth,fMaxHeight));
                
            float fOffset = (pNode->getContentSize().width-fWidth)/2;
                
            for(const auto& child : childrenVec)
            {
                const float fRealWidth = child->getContentSize().width * child->getScaleX();
                const auto& ptAnchor = child->isIgnoreAnchorPointForPosition() ? Vec2::ZERO : child->getAnchorPoint();
                float fAnchorOffset = (ptAnchor.x-0.5f)*fRealWidth;
                    
                child->setPositionX(fOffset + fRealWidth/2 + fAnchorOffset);
                fOffset += fRealWidth + fPadding;
                    
                if(bApplyDock)
                {
                    SCNodeUtils::setDock(child, nDock2);
                }
            }
        }
        else
        {// y
            float fHeight = 0;
            int nDock2 = SC_BIT_REMOVE(nDock,SCNodeUtils::kDockMiddleY);
            const bool bApplyDock = SC_BIT_HAS_OR(nDock2, SCNodeUtils::kDockMiddleX);
                
            float fMaxWidth = 0;
            for(const auto& child : childrenVec)
            {
                fHeight += child->getContentSize().height * child->getScaleY() + fPadding;
                const float fRealWidth = child->getContentSize().width * child->getScaleX();
                fMaxWidth = MAX(fMaxWidth,fRealWidth);
            }
                
            fHeight -= fPadding;
            pNode->setContentSize(Size(fMaxWidth,fHeight));
            float fOffset = fHeight + (pNode->getContentSize().height-fHeight)/2;
                
            for(const auto& child : childrenVec)
            {
                const float fRealHeight = child->getContentSize().height * child->getScaleY();
                const auto& ptAnchor = child->isIgnoreAnchorPointForPosition() ? Vec2::ZERO : child->getAnchorPoint();
                float fAnchorOffset = (ptAnchor.y-0.5f)*fRealHeight;
                    
                child->setPositionY(fOffset - fRealHeight/2 + fAnchorOffset);
                fOffset -= fRealHeight + fPadding;
                    
                if(bApplyDock)
                {
                    SCNodeUtils::setDock(child, nDock2);
                }
            }
        }
            
        if(!strDelayStyle.isEmpty())
        {
            SCNodeStyle::setStyle<Node>(pNode, strDelayStyle);
        }
    };
        
    this->insertUserNode(pNode, fPosX, fPosY, strNewStyle);
    _contextStack.push_front(context);
    assignNode.assign(pNode);
    
    if(assignNode.nID)
    {
        _id2NodeMap[assignNode.nID] = pNode;
    }
}
    
void SCViewBuilder::parentCrop(SCUIArg::NodeAssignment<cocos2d::ClippingNode> assignNode,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style,
                            const cocos2d::Size& size)
{
    auto pClippingNode = cocos2d::ClippingNode::create();
    pClippingNode->setContentSize(size);
    pClippingNode->setIgnoreAnchorPointForPosition(false);
        
    SCUITypeDef::SUIContext context;
    context.pContainerNode = pClippingNode;
    context.endFunc = [](SCUITypeDef::SUIContext& context)
    {
        cocos2d::ClippingNode* pClipper = dynamic_cast<cocos2d::ClippingNode*>(context.pContainerNode);
        SCASSERT(pClipper!=nullptr);
            
        auto pStencil = pClipper->getStencil();
            
        if(pStencil==nullptr)
        {// by default, create hollow rectangle
            const auto contentSize = pClipper->getContentSize();
            auto pRenderTexture = cocos2d::RenderTexture::create(contentSize.width, contentSize.height);
            pRenderTexture->beginWithClear(1, 1, 1, 1);
            pRenderTexture->end();
            auto pSprite = Sprite::createWithTexture(pRenderTexture->getSprite()->getTexture());
            pSprite->setPosition(Vec2(contentSize.width/2,contentSize.height/2));
            pClipper->setStencil(pSprite);
            pClipper->setAlphaThreshold(0.05);
        }
    };
        
    this->insertUserNode(pClippingNode, fPosX, fPosY, style);
    _contextStack.push_front(context);
    assignNode.assign(pClippingNode);
    
    if(assignNode.nID)
    {
        _id2NodeMap[assignNode.nID] = pClippingNode;
    }
}
    
cocos2d::Sprite* SCViewBuilder::insertCropStencil(SCUIArg::NodeAssignment<cocos2d::Sprite> assignNode,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::StringPurifier& style,
                                    const SCString& strImage,
                                    const bool bInverted,
                                    const GLfloat fAlphaThreshold)
{
    auto& top = _contextStack.front();
    SCASSERT(top.pContainerNode!=nullptr);
    auto pClipper = dynamic_cast<cocos2d::ClippingNode*>(top.pContainerNode);
    SCASSERT(pClipper!=nullptr);
    SCASSERT(!strImage.isEmpty());
    auto pSprite = SCNodeUtils::createSprite(strImage);
        
    pClipper->setStencil(pSprite);
    pClipper->setAlphaThreshold(fAlphaThreshold);
    pClipper->setInverted(bInverted);
        
    const auto parentContentSize = pClipper->getContentSize();
        
    auto pos = SCNodeUtils::posP2A(Vec2(fPosX,fPosY), parentContentSize);
    pSprite->setPosition(pos);
        
    {   // because stencil node has no parent,
        //so it can't apply position style,
        // below code simulates parent-child node in position
        // and copy simulate position to stencil node as result
        auto pParentNode = Node::create();
        pParentNode->setContentSize(parentContentSize);
            
        auto pChildNode = Node::create();
        pChildNode->setContentSize(pSprite->getContentSize());
        pChildNode->setIgnoreAnchorPointForPosition(false);
        pChildNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        pParentNode->addChild(pChildNode);
            
        SCNodeStyle::SFilterConfig config;
        config.setupPosition(false);
        SCNodeStyle::setStyle<cocos2d::Node>(pChildNode, style.strResult);
        pSprite->setPosition(pChildNode->getPosition());
    }
        
    SCNodeStyle::SFilterConfig config;
    config.setupPosition(true);
    SCNodeStyle::setStyle<cocos2d::Sprite>(pSprite, style.strResult);
        
    assignNode.assign(pSprite);
    
    if(assignNode.nID)
    {
        _id2NodeMap[assignNode.nID] = pSprite;
    }
    
    return pSprite;
}
    
///------------- cocos2d-x extension UI
void SCViewBuilder::parentScrollView(SCUIArg::NodeAssignment<cocos2d::ui::ScrollView> assignScrollView,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style,
                            const SCUIArg::ScrollViewDirectionPurifier& direction,
                            const cocos2d::Size& viewSize,
                            const cocos2d::Size& containerSize,
                            const std::function<void(cocos2d::Ref*, cocos2d::ui::ScrollView::EventType)>& funcCallback)
{
    auto pScrollView = ui::ScrollView::create();
        
    pScrollView->setIgnoreAnchorPointForPosition(false);
    pScrollView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    pScrollView->setBounceEnabled(true);
    pScrollView->setDirection(direction.direction);
        
    pScrollView->setContentSize(viewSize);
    pScrollView->setInnerContainerSize(containerSize);
    pScrollView->addEventListener(funcCallback);
        
    SCUITypeDef::SUIContext context;
    context.pContainerNode = pScrollView;
    context.containerType = SCUITypeDef::EContainerType::kNormal;
        
    this->insertUserNode(pScrollView, fPosX, fPosY, style);
    _contextStack.push_front(context);
        
    assignScrollView.assign(pScrollView);
    
    if(assignScrollView.nID)
    {
        _id2NodeMap[assignScrollView.nID] = pScrollView;
    }
}
    
void SCViewBuilder::parentPageView(SCUIArg::NodeAssignment<cocos2d::ui::PageView> assignPageView,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::StringPurifier& style,
                                    const bool bHorizontal,
                                    const cocos2d::Size& size,
                                    int nPageIndex,
                                    const std::function<void(cocos2d::Ref*, cocos2d::ui::PageView::EventType)>& funcCallback)
{
    auto pPageView = ui::PageView::create();
    pPageView->setContentSize(size);
    pPageView->setDirection(bHorizontal ? ui::PageView::Direction::HORIZONTAL
                            : ui::PageView::Direction::VERTICAL);
    pPageView->setIgnoreAnchorPointForPosition(false);
    pPageView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    pPageView->addEventListener(funcCallback);
        
    nPageIndex = (nPageIndex<0) ? 0 : nPageIndex;
        
    SCUITypeDef::SUIContext context;
    context.pContainerNode = pPageView;
    context.containerType = SCUITypeDef::EContainerType::kNormal;
    context.endFunc = [nPageIndex,pPageView](SCUITypeDef::SUIContext& context)
    {
        const auto nCount = pPageView->getItems().size();
        if(nCount>nPageIndex && nCount<nPageIndex)
        {
            pPageView->setCurrentPageIndex(nPageIndex);
        }
    };
        
    this->insertUserNode(pPageView, fPosX, fPosY, style);
    _contextStack.push_front(context);
        
    assignPageView.assign(pPageView);
    
    if(assignPageView.nID)
    {
        _id2NodeMap[assignPageView.nID] = pPageView;
    }
}
    
void SCViewBuilder::parentPage(SCUIArg::NodeAssignment<cocos2d::ui::Widget> assignWidget,
                    const cocos2d::Size& size)
{
    auto& top = _contextStack.front();
    auto pPageView = dynamic_cast<ui::PageView*>(top.pContainerNode);
    SCASSERT(pPageView!=nullptr);
    auto pWidget = ui::Widget::create();
        
    pPageView->addPage(pWidget);
        
    SCUITypeDef::SUIContext context;
    context.pContainerNode = pWidget;
    context.containerType = SCUITypeDef::EContainerType::kNormal;
        
    _contextStack.push_front(context);
        
    assignWidget.assign(pWidget);
    
    if(assignWidget.nID)
    {
        _id2NodeMap[assignWidget.nID] = pWidget;
    }
}
    
cocos2d::ui::EditBox* SCViewBuilder::insertEditBox(SCUIArg::NodeAssignment<cocos2d::ui::EditBox> assignEditBox,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::StringPurifier& style,
                                    const cocos2d::Size& size,
                                    const SCString& strImage,
                                    cocos2d::ui::EditBoxDelegate* pCallback)
{
    auto size1 = size;
    if(size.equals(Size::ZERO))
    {
        size1 = SCNodeUtils::getImageSize(strImage);
        size1.width -= 4;
        size1.height -= 2;
    }
        
    auto pSpriteFrame = SCCCSpriteFrameCache()->getSpriteFrameByName(strImage.c_str());
    auto type = pSpriteFrame==nullptr ? ui::Widget::TextureResType::LOCAL : ui::Widget::TextureResType::PLIST;
        
    auto pEditBox = cocos2d::ui::EditBox::create(size1, strImage.c_str(),type);
    pEditBox->setDelegate(pCallback);
    pEditBox->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
        
    this->insertUserNode(pEditBox, fPosX, fPosY, style);
    assignEditBox.assign(pEditBox);
    
    if(assignEditBox.nID)
    {
        _id2NodeMap[assignEditBox.nID] = pEditBox;
    }
    
    return pEditBox;
}
    
cocos2d::ui::Slider* SCViewBuilder::insertSlider(SCUIArg::NodeAssignment<cocos2d::ui::Slider> assignSlider,
                                                    const float fPosX,
                                                    const float fPosY,
                                                    const SCUIArg::StringPurifier& style,
                                                    const SCString& strBackgroundImage,
                                                    const SCString& strFrontImage,
                                                    const SCString& strHandleImage,
                                                    SCUIArg::SliderNumberPurifier value)
{
    auto pSlider = ui::Slider::create();
        
    {
        auto pFrame = SCCCSpriteFrameCache()->getSpriteFrameByName(strBackgroundImage.c_str());
        auto type = pFrame==nullptr ? ui::Widget::TextureResType::LOCAL : ui::Widget::TextureResType::PLIST;
        pSlider->loadBarTexture(strBackgroundImage.c_str(),type);
    }
        
    {
        auto pFrame = SCCCSpriteFrameCache()->getSpriteFrameByName(strFrontImage.c_str());
        auto type = pFrame==nullptr ? ui::Widget::TextureResType::LOCAL : ui::Widget::TextureResType::PLIST;
        pSlider->loadProgressBarTexture(strFrontImage.c_str(),type);
    }
        
    {
        auto pFrame = SCCCSpriteFrameCache()->getSpriteFrameByName(strHandleImage.c_str());
        auto type = pFrame==nullptr ? ui::Widget::TextureResType::LOCAL : ui::Widget::TextureResType::PLIST;
        pSlider->loadSlidBallTextureNormal(strHandleImage.c_str(),type);
    }
        
    this->insertUserNode(pSlider, fPosX, fPosY, style);
        
    if(value.ptrBinderSlider!=nullptr)
    {
        value.ptrBinderSlider->setSlider(pSlider);
        SCNodeAttach(pSlider)->addUserObj(value.ptrBinderSlider);
    }
    else
    {
        pSlider->setPercent(value.nPercentage);
    }
    assignSlider.assign(pSlider);
    
    if(assignSlider.nID)
    {
        _id2NodeMap[assignSlider.nID] = pSlider;
    }
        
    return pSlider;
}
    
cocos2d::ui::Scale9Sprite* SCViewBuilder::insertScale9Sprite(SCUIArg::NodeAssignment<cocos2d::ui::Scale9Sprite> assignScale9Sprite,
                                                                const float fPosX,
                                                                const float fPosY,
                                                                const SCUIArg::StringPurifier& style,
                                                                const SCString& strImage,
                                                                const cocos2d::Size& size)
{
    auto pSprite = SCNodeUtils::createSprite(strImage);
    auto pScale9Sprite = ui::Scale9Sprite::createWithSpriteFrame(pSprite->getSpriteFrame());
    pScale9Sprite->setContentSize(size);
        
    this->insertUserNode(pScale9Sprite, fPosX, fPosY, style);
        
    assignScale9Sprite.assign(pScale9Sprite);
    
    if(assignScale9Sprite.nID)
    {
        _id2NodeMap[assignScale9Sprite.nID] = pScale9Sprite;
    }
    
    return pScale9Sprite;
}
    
///-------------- internal methods
MenuItemLabel* SCViewBuilder::addButtonLabel(Label* pLabel,
                                        const float fPosX,
                                            const float fPosY,
                                            const SCUIArg::StringPurifier& style,
                                            const SCUIArg::LabelStringPurifier& labelString,
                                            SCUIArg::BehaviorPurifier bvrPurifier)
{
    this->bindLabel(pLabel,labelString);
    auto pItemLabel = MenuItemLabel::create(pLabel);
        
    SpeedCC::SCNodeStyle::SFilterConfig scTemFilterConfig;
    scTemFilterConfig.bExclude = false;
    scTemFilterConfig.keyVtr.push_back(SC_STYLE_TEXT_COLOR);
    scTemFilterConfig.keyVtr.push_back(SC_STYLE_FONT_SIZE);
    scTemFilterConfig.keyVtr.push_back(SC_STYLE_FONT_NAME);
    scTemFilterConfig.keyVtr.push_back(SC_STYLE_TEXT);
        
    SCNodeStyle::setStyle<Label>(pLabel, style.strResult,&scTemFilterConfig);
        
    this->addButton(pItemLabel,fPosX,fPosY,style,bvrPurifier);
    return pItemLabel;
}
    
void SCViewBuilder::addButton(const SCUIArg::NodePurifier& itemNode,
                const float fPosX,
                const float fPosY,
                const SCUIArg::StringPurifier& style,
                SCUIArg::BehaviorPurifier bvrPurifier)
{
    auto pMenuItem = dynamic_cast<MenuItem*>(itemNode.ptrNodeHolder->getRef());
        
    bvrPurifier.setupBehavior(_pCurrentRefCaller,pMenuItem);
//        SCNodeUtils::addClickable(pMenuItem, bvrPurifier.ptrResultBvr);
    auto ptrAtt = SCNodeAttachment::create(pMenuItem);
    ptrAtt->addClickable(bvrPurifier.ptrResultBvr);
        
    this->insertUserNode(pMenuItem, fPosX, fPosY, style);
}
    
///------------ layer
    
LayerColor* SCViewBuilder::insertLayerColor(SCUIArg::NodeAssignment<cocos2d::LayerColor> assignLayer,
                                            const float fPosX,
                                            const float fPosY,
                                            const SCUIArg::StringPurifier& style,
                                            const cocos2d::Size& size,
                                            const cocos2d::Color4B& crBackground)
{
    auto pLayer = LayerColor::create(crBackground);
    this->addLayer(pLayer,fPosX,fPosY,style,size);
        
    assignLayer.assign(pLayer);
    
    if(assignLayer.nID)
    {
        _id2NodeMap[assignLayer.nID] = pLayer;
    }
    
    return pLayer;
}
    
cocos2d::Layer* SCViewBuilder::insertLayer(SCUIArg::NodeAssignment<cocos2d::Layer> assignLayer,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style,
                            const cocos2d::Size& size)
{
    auto pLayer = Layer::create();
    this->addLayer(pLayer,fPosX,fPosY,style,size);
    assignLayer.assign(pLayer);
    
    if(assignLayer.nID)
    {
        _id2NodeMap[assignLayer.nID] = pLayer;
    }
    
    return pLayer;
}
    
void SCViewBuilder::addLayer(const SCUIArg::NodePurifier& layerNode,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style,
                            const cocos2d::Size& size)
{
    cocos2d::Layer* pLayer = dynamic_cast<cocos2d::Layer*>(layerNode.ptrNodeHolder->getRef());
    SCASSERT(pLayer!=nullptr);
        
    pLayer->setContentSize(size);
    pLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    pLayer->setIgnoreAnchorPointForPosition(false);
        
    this->insertUserNode(layerNode, fPosX, fPosY, style);
}
    
void SCViewBuilder::pushParentStack(cocos2d::Node* pNode)
{
    SCUITypeDef::SUIContext context;
    context.pContainerNode = pNode;
    context.containerType = SCUITypeDef::EContainerType::kNormal;
    _contextStack.push_front(context);
}

cocos2d::Node* SCViewBuilder::getNodeByID(const int nID) const
{
    SC_RETURN_IF(nID == 0, nullptr);
    auto it = _id2NodeMap.find(nID);
    return (it == _id2NodeMap.end()) ? nullptr : (*it).second;
}

bool SCViewBuilder::removeNodeByID(const int nID)
{
    SC_RETURN_IF(nID == 0, false);
    
    auto it = _id2NodeMap.find(nID);
    SC_RETURN_IF(it == _id2NodeMap.end(), false);
    _id2NodeMap.erase(it);
    
    return true;
}

NAMESPACE_SPEEDCC_END
