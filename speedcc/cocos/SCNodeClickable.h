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

#ifndef __SPEEDCC__SCNODECLICKABLE_H__
#define __SPEEDCC__SCNODECLICKABLE_H__

#include "cocos2d.h"

#include "SCEventEmitter.h"

#include "../base/SCObject.h"
#include "../stage/SCMessageDispatch.h"
#include "../stage/SCPlayObject.h"

NAMESPACE_SPEEDCC_BEGIN

class SCNodeClickable
:public SCObject
,public SCMessageListener
{
public:
    SC_AVOID_CLASS_COPY(SCNodeClickable)
    SC_DEFINE_CLASS_PTR(SCNodeClickable)
        
    SC_DEFINE_CREATE_FUNC_0(SCNodeClickable)
    SC_DEFINE_CREATE_FUNC_1(SCNodeClickable,cocos2d::Node*)
    SC_DEFINE_CREATE_FUNC_2(SCNodeClickable,cocos2d::Node*,SCBehavior::Ptr)
        
    virtual ~SCNodeClickable();
        
    void setActive(const bool bActive);
    inline bool getActive() const { return _bActive; }
        
    void setNode(cocos2d::Node* pNode);
    void setBehavior(SCBehavior::Ptr ptrBvr);
        
    inline SCEventEmitter::Ptr getEventEmitter() const { return _ptrEventEmitter;}
        
private:
    virtual bool onSCMessageProcess(SCMessage::Ptr ptrMsg) override;
    bool isNodeInTouch(cocos2d::Touch* pTouch, const cocos2d::Camera* pCamera);
        
protected:
    SCNodeClickable();
    SCNodeClickable(cocos2d::Node* pNode);
    SCNodeClickable(cocos2d::Node* pNode,SCBehavior::Ptr ptrBvr);
        
protected:
    bool                        _bActive;
    bool                        _bTrack;
    bool                        _bSelected;
    cocos2d::Node*              _pNode;
    cocos2d::MenuItem*          _pMenuItem;
    SCEventEmitter::Ptr         _ptrEventEmitter;
    const cocos2d::Camera*      _pSelectedCamera;
    SCBehavior::Ptr             _ptrBvr;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCNODECLICKABLE_H__
