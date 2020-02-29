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

#ifndef __SPEEDCC__SCEVENTEMITTER_H__
#define __SPEEDCC__SCEVENTEMITTER_H__

#include "cocos2d.h"
#include "../base/SCObject.h"
#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStageMacros.h"
#include "SCCocosDef.h"

NAMESPACE_SPEEDCC_BEGIN

class SCEventEmitter : public SCObject
{
public:
    enum class EEventType
    {
        kSingleTouch,
        kMultipleTouch,
        kAcceleration,
        kKeyboard,
    };
        
public:
    SC_AVOID_CLASS_COPY(SCEventEmitter)
    SC_DEFINE_CLASS_PTR(SCEventEmitter)
        
    virtual ~SCEventEmitter();
        
    typedef std::function<bool(SCMessage::Ptr)>     ListenFunc_t;
        
    SC_DEFINE_CREATE_FUNC_2(SCEventEmitter,EEventType,cocos2d::Node*)
    SC_DEFINE_CREATE_FUNC_3(SCEventEmitter,EEventType,cocos2d::Node*,SCMessageListener*)
    SC_DEFINE_CREATE_FUNC_3(SCEventEmitter,EEventType,cocos2d::Node*,const ListenFunc_t&)
        
    inline void setActive(const bool bActive) {_bActive = bActive;}
    inline bool getActive() const {return _bActive;}
        
    inline cocos2d::EventListener* getEventListener() const { return _pTouchListener; }
    void setEventType(EEventType type);
        
    void setListenFunc(const ListenFunc_t& listenFunc);
    void setMessageListener(SCMessageListener* pMsgListener);
        
protected:
    SCEventEmitter();
    SCEventEmitter(EEventType type,cocos2d::Node* pNode);
    SCEventEmitter(EEventType type,cocos2d::Node* pNode,SCMessageListener* pMsgListener);
    SCEventEmitter(EEventType type,cocos2d::Node* pNode,const ListenFunc_t& listenFunc);
        
private:
    bool onSingleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    void onSingleTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    void onSingleTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    void onSingleTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        
    void onMultipleTouchBegan(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
    void onMultipleTouchMoved(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
    void onMultipleTouchEnded(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
    void onMultipleTouchCancelled(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        
    void onAcceleration(cocos2d::Acceleration* pAcc, cocos2d::Event* pEvent);
    void onKeyboardPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* pEvent);

    template<typename T>
    void sendTouchMessage(const int nMsg, T touch,cocos2d::Event* pEvent)
    {
        SCDictionary::SKVPair pairArray[] =
        {
            {std::is_same<T,cocos2d::Touch*>::value ? SC_KEY_TOUCH : SC_KEY_TOUCHES,touch},
            {SC_KEY_CCEVENT,pEvent}
        };
            
        SCDictionary dic(pairArray,SC_ARRAY_LENGTH(pairArray));

        this->sendEventMessage(nMsg,dic);
    }
        
    SCDictionary sendEventMessage(const int nMsg,SCDictionary dic);
        
private:
    bool                                    _bActive;
    ListenFunc_t                            _listenFunc;
    cocos2d::Node*                          _pReceiveNode;
    EEventType                              _eventType;
    cocos2d::EventListener*                 _pTouchListener; // no need to remove from event dispatch
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCEVENTEMITTER_H__
