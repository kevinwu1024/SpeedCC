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

#ifndef __SPEEDCC__SCUIBUILDER_H__
#define __SPEEDCC__SCUIBUILDER_H__

#include "../base/SCObject.h"
#include "SCUIArg.h"

NAMESPACE_SPEEDCC_BEGIN

class SCViewController;
    
class SCViewBuilder : public SCObject
{
public:
    SC_AVOID_CLASS_COPY(SCViewBuilder)
    SC_DEFINE_CLASS_PTR(SCViewBuilder)
        
    SC_DEFINE_CREATE_FUNC_0(SCViewBuilder)
    SC_DEFINE_CREATE_FUNC_1(SCViewBuilder,cocos2d::Node*)
    SC_DEFINE_CREATE_FUNC_2(SCViewBuilder,cocos2d::Node*,cocos2d::Ref*)
        
    ///------------- root container
    void beginParentRoot(const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style,
                            const SCUIArg::SizePurifier& sizePurifier,
                            const SCUIArg::NodePurifier& parentNode,
                            cocos2d::Ref* pRef);
        
    void pushParentStack(cocos2d::Node* pNode);
    void popParentStack();
    cocos2d::Node* getContextParent() const;
        
    ///------------ layer
        
    cocos2d::LayerColor* insertLayerColor(SCUIArg::NodeAssignment<cocos2d::LayerColor> assignLayer,
                                            const float fPosX,
                                            const float fPosY,
                                            const SCUIArg::StringPurifier& style,
                                            const cocos2d::Size& size,
                                            const cocos2d::Color4B& crBackground);
        
    cocos2d::Layer* insertLayer(SCUIArg::NodeAssignment<cocos2d::Layer> assignLayer,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& style,
                                const cocos2d::Size& size);
        
    ///-------------- user node
    cocos2d::Node* insertUserNode(const SCUIArg::NodePurifier& userNode,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::StringPurifier& style);
    ///-------------- node
    cocos2d::Node* insertNode(SCUIArg::NodeAssignment<cocos2d::Node> assignNode,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& style,
                                const cocos2d::Size& size);
        
    ///-------------- sprite
    cocos2d::Sprite* insertSprite(SCUIArg::NodeAssignment<cocos2d::Sprite> assignSprite,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::StringPurifier& style,
                                    const SCString& strImage);
        
    ///--------------- label
        
    cocos2d::Label* insertLabel(SCUIArg::NodeAssignment<cocos2d::Label> assignLabel,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& style,
                                const SCUIArg::LabelStringPurifier& labelString,
                                const SCString& strFont,
                                const float fFontSize);
        
    cocos2d::Label* insertLabelTTF(SCUIArg::NodeAssignment<cocos2d::Label> assignLabel,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::StringPurifier& style,
                                    const SCUIArg::LabelStringPurifier& labelString,
                                    const SCString& strFont,
                                    const float fFontSize);
        
    cocos2d::Label* insertLabelBMFont(SCUIArg::NodeAssignment<cocos2d::Label> assignLabel,
                                        const float fPosX,
                                        const float fPosY,
                                        const SCUIArg::StringPurifier& style,
                                        const SCUIArg::LabelStringPurifier& labelString,
                                        const SCString& strFile);
        
        
    ///-------------- button
    cocos2d::MenuItemSprite* insertButton(SCUIArg::NodeAssignment<cocos2d::MenuItemSprite> assignMenuItemSprite,
                                            const float fPosX,
                                            const float fPosY,
                                            const SCUIArg::StringPurifier& style,
                                            const SCString& strImageNormal,
                                            const SCString& strSelect,
                                            const SCString& strDisable,
                                            SCUIArg::BehaviorPurifier bvrPurifier);
        
    cocos2d::MenuItemLabel* insertButtonLabel(SCUIArg::NodeAssignment<cocos2d::MenuItemLabel> assignMenuItemLabel,
                                                const float fPosX,
                                                const float fPosY,
                                                const SCUIArg::StringPurifier& style,
                                                const SCUIArg::LabelStringPurifier& labelString,
                                                const SCString& strFont,
                                                const float fFontSize,
                                                SCUIArg::BehaviorPurifier bvrPurifier);
        
    cocos2d::MenuItemLabel* insertButtonLabelTTF(SCUIArg::NodeAssignment<cocos2d::MenuItemLabel> assignMenuItemLabel,
                                                    const float fPosX,
                                                    const float fPosY,
                                                    const SCUIArg::StringPurifier& style,
                                                    const SCUIArg::LabelStringPurifier& labelString,
                                                    const SCString& strFont,
                                                    const float fFontSize,
                                                    SCUIArg::BehaviorPurifier bvrPurifier);
        
        
    cocos2d::MenuItemLabel* insertButtonLabelBMFont(SCUIArg::NodeAssignment<cocos2d::MenuItemLabel> assignMenuItemLabel,
                                                    const float fPosX,
                                                    const float fPosY,
                                                    const SCUIArg::StringPurifier& style,
                                                    const SCUIArg::LabelStringPurifier& labelString,
                                                    const SCString& strFile,
                                                    SCUIArg::BehaviorPurifier bvrPurifier);
        
    cocos2d::MenuItemToggle* insertButtonSwitch(SCUIArg::NodeAssignment<cocos2d::MenuItemToggle> assignMenuItemToggle,
                                                const float fPosX,
                                                const float fPosY,
                                                const SCUIArg::StringPurifier& style,
                                                const SCUIArg::MenuItemPurifier& itemOn,
                                                const SCUIArg::MenuItemPurifier& itemOff,
                                                const SCUIArg::BoolPurifier& value,
                                                SCUIArg::BehaviorPurifier bvrPurifier);
        
    cocos2d::MenuItemToggle* insertButtonRadio(SCUIArg::NodeAssignment<cocos2d::MenuItemToggle> assignMenuItemToggle,
                                                const float fPosX,
                                                const float fPosY,
                                                const SCUIArg::StringPurifier& style,
                                                const SCUIArg::MenuItemPurifier& itemOn,
                                                const SCUIArg::MenuItemPurifier& itemOff,
                                                SCRadioGroup::Ptr ptrRadioGroup,
                                                const int nID,
                                                SCUIArg::BehaviorPurifier bvrPurifier);
        
        
    cocos2d::ProgressTimer* insertProgressBar(SCUIArg::NodeAssignment<cocos2d::ProgressTimer> assignProgress,
                                                const float fPosX,
                                                const float fPosY,
                                                const SCUIArg::StringPurifier& style,
                                                const SCString& strBackgroundImage,
                                                const SCString& strFrontgroundImage,
                                                SCUIArg::PTNumberPurifier value,
                                                const bool bHorizontal,
                                                const bool bBaseLB = true);
        
    cocos2d::ProgressTimer* insertProgressRadial(SCUIArg::NodeAssignment<cocos2d::ProgressTimer> assignProgress,
                                                    const float fPosX,
                                                    const float fPosY,
                                                    const SCUIArg::StringPurifier& style,
                                                    const SCString& strBackgroundImage,
                                                    const SCString& strFrontgroundImage,
                                                    SCUIArg::PTNumberPurifier value,
                                                    const bool bCCW);
        
    void parentAlignment(SCUIArg::NodeAssignment<cocos2d::Node> assignNode,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style,
                            const bool bHorizontal,
                            const float fPadding,
                            const SCUIArg::DockPurifier& dockPurifier);
        
        
    void parentCrop(SCUIArg::NodeAssignment<cocos2d::ClippingNode> assignNode,
                                        const float fPosX,
                                        const float fPosY,
                                        const SCUIArg::StringPurifier& style,
                                        const cocos2d::Size& size);
        
    // must use with parentCrop()
    cocos2d::Sprite* insertCropStencil(SCUIArg::NodeAssignment<cocos2d::Sprite> assignNode,
                                        const float fPosX,
                                        const float fPosY,
                                        const SCUIArg::StringPurifier& style,
                                        const SCString& strImage,
                                        const bool bInverted,
                                        const GLfloat fAlphaThreshold);
        
        
    ///---------------- cocos2d-x extension UI
    void parentScrollView(SCUIArg::NodeAssignment<cocos2d::ui::ScrollView> assignScrollView,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& style,
                                const SCUIArg::ScrollViewDirectionPurifier& direction,
                                const cocos2d::Size& viewSize,
                                const cocos2d::Size& containerSize,
                                const std::function<void(cocos2d::Ref*, cocos2d::ui::ScrollView::EventType)>& funcCallback);
        
    void parentPageView(SCUIArg::NodeAssignment<cocos2d::ui::PageView> assignPageView,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style,
                            const bool bHorizontal,
                            const cocos2d::Size& size,
                            int nPageIndex,
                            const std::function<void(cocos2d::Ref*, cocos2d::ui::PageView::EventType)>& funcCallback);
        
    void parentPage(SCUIArg::NodeAssignment<cocos2d::ui::Widget> assignWidget,
                        const cocos2d::Size& size);
        
    cocos2d::ui::EditBox* insertEditBox(SCUIArg::NodeAssignment<cocos2d::ui::EditBox> assignEditBox,
                                        const float fPosX,
                                        const float fPosY,
                                        const SCUIArg::StringPurifier& style,
                                        const cocos2d::Size& size,
                                        const SCString& strImage,
                                        cocos2d::ui::EditBoxDelegate* pCallback);
        
    cocos2d::ui::Slider* insertSlider(SCUIArg::NodeAssignment<cocos2d::ui::Slider> assignSlider,
                                        const float fPosX,
                                        const float fPosY,
                                        const SCUIArg::StringPurifier& style,
                                        const SCString& strBackgroundImage,
                                        const SCString& strFrontImage,
                                        const SCString& strHandleImage,
                                        SCUIArg::SliderNumberPurifier value);
        
    cocos2d::ui::Scale9Sprite* insertScale9Sprite(SCUIArg::NodeAssignment<cocos2d::ui::Scale9Sprite> assignScale9Sprite,
                                                    const float fPosX,
                                                    const float fPosY,
                                                    const SCUIArg::StringPurifier& style,
                                                    const SCString& strImage,
                                                    const cocos2d::Size& size);
    
    cocos2d::Node* getNodeByID(const int nID) const;
    bool removeNodeByID(const int nID);
public:
    static void assign(SCViewBuilder::Ptr* ptrToBuilder, SCViewBuilder::Ptr ptrFromBuilder)
    {
        if(ptrToBuilder)
        {
            *ptrToBuilder = ptrFromBuilder;
        }
    }
    
protected:
    SCViewBuilder()
    :_pCurrentBedNode(nullptr)
    ,_pCurrentRefCaller(nullptr)
    ,_pDefaultBedNode(nullptr)
    ,_pDefaultRefCaller(nullptr)
    {
    }
        
    SCViewBuilder(cocos2d::Node* pBedNode,cocos2d::Ref* pRef)
    :_pCurrentBedNode(nullptr)
    ,_pCurrentRefCaller(nullptr)
    ,_pDefaultBedNode(pBedNode)
    ,_pDefaultRefCaller(pRef)
    {
    }
        
    SCViewBuilder(cocos2d::Node* pBedNode)
    :_pCurrentBedNode(nullptr)
    ,_pCurrentRefCaller(nullptr)
    ,_pDefaultBedNode(pBedNode)
    ,_pDefaultRefCaller(nullptr)
    {
    }
        
private:
    void addLayer(const SCUIArg::NodePurifier& layerNode,
                    const float fPosX,
                    const float fPosY,
                    const SCUIArg::StringPurifier& style,
                    const cocos2d::Size& size);
        
    void addLabel(const SCUIArg::NodePurifier& labelNode,
                    const float fPosX,
                    const float fPosY,
                    const SCUIArg::StringPurifier& style,
                    const SCUIArg::LabelStringPurifier& labelString);
        
    void addButton(const SCUIArg::NodePurifier& itemNode,
                    const float fPosX,
                    const float fPosY,
                    const SCUIArg::StringPurifier& style,
                    SCUIArg::BehaviorPurifier bvrPurifier);
        
    cocos2d::MenuItemLabel* addButtonLabel(cocos2d::Label* pLabel,
                                            const float fPosX,
                                            const float fPosY,
                                            const SCUIArg::StringPurifier& style,
                                            const SCUIArg::LabelStringPurifier& labelString,
                                            SCUIArg::BehaviorPurifier bvrPurifier);
        
    void bindLabel(const SCUIArg::NodePurifier& labelNode,
                    const SCUIArg::LabelStringPurifier& labelString);
        
private:
    cocos2d::Node*                          _pCurrentBedNode;
    cocos2d::Ref*                           _pCurrentRefCaller;
        
    cocos2d::Node*                          _pDefaultBedNode;
    cocos2d::Ref*                           _pDefaultRefCaller;
    std::list<SCUITypeDef::SUIContext>      _contextStack;
    std::map<int,cocos2d::Node*>            _id2NodeMap;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCUIBUILDER_H__

