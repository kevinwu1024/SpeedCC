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


#ifndef __SPEEDCC__SCNODEUTILS_H__
#define __SPEEDCC__SCNODEUTILS_H__

#include "cocos2d.h"
#include "../stage/SCPlayObject.h"
#include "SCRefHolder.h"

NAMESPACE_SPEEDCC_BEGIN

class SCNodeUtils
{
public:
    enum EDockType
    {
        kDockLeft           = (1<<0),
        kDockRight          = (1<<1),
        kDockMiddleX        = (kDockLeft | kDockRight),
        kDockTop            = (1<<2),
        kDockBottom         = (1<<3),
        kDockMiddleY        = (kDockTop | kDockBottom),
        kDockCenter         = (kDockMiddleX | kDockMiddleY)
    };
        
       
public:
    static cocos2d::Vec2 posA2P(const cocos2d::Vec2& ptA,const cocos2d::Size& frameSize);
    static cocos2d::Vec2 posP2A(const cocos2d::Vec2& ptP,const cocos2d::Size& frameSize);
    static bool setPositionPer(cocos2d::Node* pNode,const cocos2d::Vec2& ptPer);
    static void setPositionBy(cocos2d::Node* pNode,float fXBy,float fYBy);
    static bool setDock(cocos2d::Node* pNode,const int nDockFlag);
    static cocos2d::Vec2 getDockPosition(cocos2d::Node* pNode,const int nDockFlag);
        
    static cocos2d::Sprite* createSprite(const SCString& strName);
    static cocos2d::Size getImageSize(const SCString& strImage);
    static cocos2d::Sprite* setSpriteImage(cocos2d::Sprite* pSprite, const SCString& strImage);
        
private:
    // nPark. <0:(left or bottom); 0:center; >0:(right or top)
    static float getDockPosition(cocos2d::Node* pNode,int nPark,const bool bIsX);
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCNODEUTILS_H__
