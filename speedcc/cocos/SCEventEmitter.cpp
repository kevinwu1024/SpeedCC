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

#include "SCEventEmitter.h"

NAMESPACE_SPEEDCC_BEGIN

SCEventEmitter::SCEventEmitter()
:_pReceiveNode(nullptr)
,_bActive(true)
,_pTouchListener(nullptr)
,_listenFunc(nullptr)
{}
    
SCEventEmitter::SCEventEmitter(EEventType type,cocos2d::Node* pNode)
:_pReceiveNode(pNode)
,_eventType(type)
,_bActive(true)
,_pTouchListener(nullptr)
,_listenFunc(nullptr)
{
    this->setEventType(type);
}
    
SCEventEmitter::SCEventEmitter(EEventType type,cocos2d::Node* pNode,SCMessageListener* pMsgListener)
:_pReceiveNode(pNode)
,_eventType(type)
,_bActive(true)
,_pTouchListener(nullptr)
,_listenFunc(nullptr)
{
    if(pMsgListener!=nullptr)
    {
        _listenFunc = [pMsgListener](SCMessage::Ptr ptrMsg)
        {
            return pMsgListener->onSCMessageProcess(ptrMsg);
        };
    }
        
    this->setEventType(type);
}
    
SCEventEmitter::SCEventEmitter(EEventType type,cocos2d::Node* pNode,const ListenFunc_t& listenFunc)
:_listenFunc(listenFunc)
,_pReceiveNode(pNode)
,_eventType(type)
,_bActive(true)
,_pTouchListener(nullptr)
{
    this->setEventType(type);
}
    
SCEventEmitter::~SCEventEmitter()
{
    if(_pTouchListener!=nullptr)
    {
        SCCCDirector()->getEventDispatcher()->removeEventListener(_pTouchListener);
        _pTouchListener = nullptr;
    }
}
    
void SCEventEmitter::setListenFunc(const ListenFunc_t& listenFunc)
{
    _listenFunc = listenFunc;
}
    
void SCEventEmitter::setMessageListener(SCMessageListener* pMsgListener)
{
    _listenFunc = nullptr;
        
    if(pMsgListener!=nullptr)
    {
        _listenFunc = [pMsgListener](SCMessage::Ptr ptrMsg) -> bool
        {
            return pMsgListener->onSCMessageProcess(ptrMsg);
        };
    }
}
    
void SCEventEmitter::setEventType(EEventType type)
{
    if(_pTouchListener!=nullptr)
    {
        SCCCDirector()->getEventDispatcher()->removeEventListener(_pTouchListener);
        _pTouchListener = nullptr;
    }
        
    switch(type)
    {
        case EEventType::kSingleTouch:
        {
            auto pListener = cocos2d::EventListenerTouchOneByOne::create();
            pListener->setSwallowTouches(true);
            pListener->onTouchBegan = SC_MAKE_FUNC(onSingleTouchBegan, this);
            pListener->onTouchMoved = SC_MAKE_FUNC(onSingleTouchMoved, this);
            pListener->onTouchEnded = SC_MAKE_FUNC(onSingleTouchEnded, this);
            pListener->onTouchCancelled = SC_MAKE_FUNC(onSingleTouchCancelled, this);
                
            _pTouchListener = pListener;
        }
            break;
                
        case EEventType::kMultipleTouch:
        {
            auto pListener = cocos2d::EventListenerTouchAllAtOnce::create();
            pListener->onTouchesBegan = SC_MAKE_FUNC(onMultipleTouchBegan, this);
            pListener->onTouchesMoved = SC_MAKE_FUNC(onMultipleTouchMoved, this);
            pListener->onTouchesEnded = SC_MAKE_FUNC(onMultipleTouchEnded, this);
            pListener->onTouchesCancelled = SC_MAKE_FUNC(onMultipleTouchCancelled, this);
                
            _pTouchListener = pListener;
        }
            break;
                
        case EEventType::kAcceleration:
        {
            auto pListener = cocos2d::EventListenerAcceleration::create(SC_MAKE_FUNC(onAcceleration, this));
            _pTouchListener = pListener;
        }
            break;
                
        case EEventType::kKeyboard:
        {
            auto pListener = cocos2d::EventListenerKeyboard::create();
            pListener->onKeyPressed = SC_MAKE_FUNC(onKeyboardPressed, this);
            pListener->onKeyReleased = SC_MAKE_FUNC(onKeyboardPressed, this);
            _pTouchListener = pListener;
        }
            break;
                
        default:
            SCASSERT(false);
            break;
    }
        
    if(_pTouchListener!=nullptr)
    {
        SCCCDirector()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_pTouchListener, _pReceiveNode);
    }
}
    

bool SCEventEmitter::onSingleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    SC_RETURN_IF(!this->getActive(), true);
        
    SCDictionary::SKVPair pair[] =
    {
        {SC_KEY_TOUCH,pTouch},
        {SC_KEY_RESULT,false}, // by default, it doens't consume touch and doesn't pass Move event
    };
        
    SCDictionary dic(pair,SC_ARRAY_LENGTH(pair));
        
    auto result = this->sendEventMessage(SCID::Msg::kMsgTouchBegan,dic);
    return result.getValue(SC_KEY_RESULT).getBool();
}
    
void SCEventEmitter::onSingleTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    SC_RETURN_V_IF(!this->getActive());
    this->sendTouchMessage(SCID::Msg::kMsgTouchMoved,pTouch,pEvent);
}
    
void SCEventEmitter::onSingleTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    SC_RETURN_V_IF(!this->getActive());
    this->sendTouchMessage(SCID::Msg::kMsgTouchEnded,pTouch,pEvent);
}
    
void SCEventEmitter::onSingleTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    SC_RETURN_V_IF(!this->getActive());
    this->sendTouchMessage(SCID::Msg::kMsgTouchCancelled,pTouch,pEvent);
}
    
void SCEventEmitter::onMultipleTouchBegan(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
{
    SC_RETURN_V_IF(!this->getActive());
    this->sendTouchMessage(SCID::Msg::kMsgTouchBegan,touchVtr,pEvent);
}
    
void SCEventEmitter::onMultipleTouchMoved(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
{
    SC_RETURN_V_IF(!this->getActive());
    this->sendTouchMessage(SCID::Msg::kMsgTouchMoved,touchVtr,pEvent);
}
    
void SCEventEmitter::onMultipleTouchEnded(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
{
    SC_RETURN_V_IF(!this->getActive());
    this->sendTouchMessage(SCID::Msg::kMsgTouchEnded,touchVtr,pEvent);
}
    
void SCEventEmitter::onMultipleTouchCancelled(const std::vector<cocos2d::Touch*>& touchVtr,
                                                cocos2d::Event* pEvent)
{
    SC_RETURN_V_IF(!this->getActive());
    this->sendTouchMessage(SCID::Msg::kMsgTouchCancelled,touchVtr,pEvent);
}
    
void SCEventEmitter::onAcceleration(cocos2d::Acceleration* pAcc, cocos2d::Event* pEvent)
{
    SC_RETURN_V_IF(!this->getActive());
    SCDictionary::SKVPair pairArray[] =
    {
        {SC_KEY_X,pAcc->x},
        {SC_KEY_Y,pAcc->y},
        {SC_KEY_Z,pAcc->z},
        {SC_KEY_TIMESTAMP,pAcc->timestamp},
        {SC_KEY_CCEVENT,pEvent}
    };
        
    SCDictionary dic(pairArray,SC_ARRAY_LENGTH(pairArray));
        
    this->sendEventMessage(SCID::Msg::kMsgAcceleration,dic);
}
    
void SCEventEmitter::onKeyboardPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* pEvent)
{
    SC_RETURN_V_IF(!this->getActive());
    SCDictionary::SKVPair pairArray[] =
    {
        {SC_KEY_KEYBOARDCODE,code},
        {SC_KEY_CCEVENT,pEvent}
    };
        
    SCDictionary dic(pairArray,SC_ARRAY_LENGTH(pairArray));
        
    this->sendEventMessage(SCID::Msg::kMsgKeyboardKeyDown,dic);
}
    
SCDictionary SCEventEmitter::sendEventMessage(const int nMsg,SCDictionary dic)
{
    SCMessage::Ptr ptrMsg = SCMessage::create();
    ptrMsg->nMsgID = nMsg;
    ptrMsg->parameters = dic;
        
    if(_listenFunc==nullptr)
    {
        SCMsgDisp()->sendMessage(ptrMsg);
    }
    else
    {
        _listenFunc(ptrMsg);
    }
        
    return ptrMsg->parameters;
}

NAMESPACE_SPEEDCC_END
