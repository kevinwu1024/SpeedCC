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


#include "SCNodeUtils.h"
#include "../base/SCBaseMacros.h"
#include "SCCocosDef.h"
#include "SCNodeClickable.h"
#include "SCRefHolder.h"

using namespace cocos2d;

NAMESPACE_SPEEDCC_BEGIN

Vec2 SCNodeUtils::posA2P(const Vec2& ptAbs,const Size& frameSize=SCWinSize())
{
    return Vec2(ptAbs.x/frameSize.width,ptAbs.y/frameSize.height);
}
    
Vec2 SCNodeUtils::posP2A(const Vec2& ptPer,const Size& frameSize=SCWinSize())
{
    return Vec2(ptPer.x*frameSize.width,ptPer.y*frameSize.height);
}
    
bool SCNodeUtils::setPositionPer(cocos2d::Node* pNode,const cocos2d::Vec2& ptPer)
{
    SC_RETURN_IF(pNode==nullptr || pNode->getParent()==nullptr,false);
        
    const auto frameSize = pNode->getParent()->getContentSize();
    const auto pos = SCNodeUtils::posP2A(ptPer,frameSize);
        
    if(ptPer.x!=kSCPositionIgnore && ptPer.y!=kSCPositionIgnore)
    {
        pNode->setPosition(pos);
    }
    else if(ptPer.x!=kSCPositionIgnore)
    {
        pNode->setPositionX(pos.x);
    }
    else if(ptPer.y!=kSCPositionIgnore)
    {
        pNode->setPositionY(pos.y);
    }
        
    return true;
}
    
void SCNodeUtils::setPositionBy(cocos2d::Node* pNode,float fXBy,float fYBy)
{
    SC_RETURN_V_IF(pNode==nullptr);
        
    auto pos = pNode->getPosition();
    pos.x += fXBy;
    pos.y += fYBy;
    pNode->setPosition(pos);
}
    
cocos2d::Vec2 SCNodeUtils::getDockPosition(cocos2d::Node* pNode,const int nDockFlag)
{
    SC_RETURN_IF(pNode==nullptr || pNode->getParent()==nullptr,cocos2d::Vec2::ZERO);
        
    auto ptPos = pNode->getPosition();
        
    if(SC_BIT_HAS_OR(nDockFlag, kDockLeft|kDockRight|kDockMiddleX))
    {// x axis
        if(SC_BIT_HAS_AND(nDockFlag,kDockMiddleX))
        {
            ptPos.x = SCNodeUtils::getDockPosition(pNode,0,true);
        }
        else if(SC_BIT_HAS_AND(nDockFlag,kDockLeft))
        {
            ptPos.x = SCNodeUtils::getDockPosition(pNode,-1,true);
        }
        else if(SC_BIT_HAS_AND(nDockFlag,kDockRight))
        {
            ptPos.x = SCNodeUtils::getDockPosition(pNode,1,true);
        }
    }
        
    if(SC_BIT_HAS_OR(nDockFlag, kDockTop|kDockBottom|kDockMiddleY))
    {// y axis
        if(SC_BIT_HAS_AND(nDockFlag,kDockMiddleY))
        {
            ptPos.y = SCNodeUtils::getDockPosition(pNode,0,false);
        }
        else if(SC_BIT_HAS_AND(nDockFlag,kDockTop))
        {
            ptPos.y = SCNodeUtils::getDockPosition(pNode,1,false);
        }
        else if(SC_BIT_HAS_AND(nDockFlag,kDockBottom))
        {
            ptPos.y = SCNodeUtils::getDockPosition(pNode,-1,false);
        }
    }
        
    return ptPos;
}
    
bool SCNodeUtils::setDock(cocos2d::Node* pNode,const int nDockFlag)
{
    SC_RETURN_IF(pNode==nullptr || pNode->getParent()==nullptr,false);
    auto ptPos = SCNodeUtils::getDockPosition(pNode,nDockFlag);
    pNode->setPosition(ptPos);
        
    return true;
}
    
float SCNodeUtils::getDockPosition(cocos2d::Node* pNode,int nPark,const bool bIsX)
{
    SC_RETURN_IF(pNode==nullptr || pNode->getParent()==nullptr,-999);
    float fRet = 0;
        
    const auto& frameSize = pNode->getParent()->getContentSize();
    const auto& nodeSize = pNode->getContentSize();
        
    const auto& ptAnchor = pNode->isIgnoreAnchorPointForPosition() ? Vec2::ZERO : pNode->getAnchorPoint();
        
    if(bIsX)
    {// x
        const float fScaleX = pNode->getScaleX();
        // anchor offset by (0.5,0.5)
        float fAnchorOffset = (ptAnchor.x-0.5f)*nodeSize.width*fScaleX;
            
        if(nPark>0)
        {// right
            fRet = (frameSize.width - nodeSize.width*fScaleX/2) + fAnchorOffset;
        }
        else if(nPark<0)
        {// left
            fRet = (nodeSize.width * fScaleX/2) + fAnchorOffset;
        }
        else
        {// mid-x
            fRet = frameSize.width/2 + fAnchorOffset;
        }
    }
    else
    {// y
        const float fScaleY = pNode->getScaleY();
        // anchor offset by (0.5,0.5)
        float fAnchorOffset = (ptAnchor.y-0.5f)*nodeSize.height*fScaleY;
        if(nPark>0)
        {// top
            fRet = (frameSize.height - nodeSize.height*fScaleY/2) + fAnchorOffset;
        }
        else if(nPark<0)
        {// bottom
            fRet = (nodeSize.height * fScaleY/2) + fAnchorOffset;
        }
        else
        {// mid-y
            fRet = frameSize.height/2 + fAnchorOffset;
        }
    }
        
    return fRet;
}
    
    
cocos2d::Sprite* SCNodeUtils::createSprite(const SCString& strName)
{
    // find in sprite frame cache
    auto pSpriteFrame = SCCCSpriteFrameCache()->getSpriteFrameByName(strName.c_str());
    SC_RETURN_IF(pSpriteFrame!=nullptr, cocos2d::Sprite::createWithSpriteFrame(pSpriteFrame));
        
    // find in file
    auto strFile = SCCCFileUtils()->fullPathForFilename(strName.c_str());
    SC_RETURN_IF(!strFile.empty(), cocos2d::Sprite::create(strFile.c_str()));
        
    CCLOG("Can't Found Match Name: %s",strName.c_str());
    SCASSERT(false);
    return nullptr;
}
    
cocos2d::Size SCNodeUtils::getImageSize(const SCString& strImage)
{
    SCASSERT(!strImage.isEmpty());
    auto pSprite = SCNodeUtils::createSprite(strImage);
    SCASSERT(pSprite!=nullptr);
        
    return pSprite->getContentSize();
}
    
cocos2d::Sprite* SCNodeUtils::setSpriteImage(cocos2d::Sprite* pSprite, const SCString& strImage)
{
    SCASSERT(pSprite!=NULL);
    SCASSERT(!strImage.isEmpty());
        
    auto pRet = SCNodeUtils::createSprite(strImage);
    pSprite->setSpriteFrame(pRet->getSpriteFrame());
        
    return pRet;
}
NAMESPACE_SPEEDCC_END
