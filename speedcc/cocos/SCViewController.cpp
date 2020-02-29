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


#include "cocos2d.h"

#include "SCViewController.h"
#include "SCViewNavigator.h"
#include "../base/SCTemplateUtils.h"
#include "../stage/SCStageMacros.h"
#include "../stage/SCBehaviorCocos.h"

NAMESPACE_SPEEDCC_BEGIN

////-------------- member methods
SCViewController::SCViewController()
:_pView(nullptr)
,_pScene(nullptr)
,_pDisableTouchLayer(nullptr)
,_pBlackMaskLayer(nullptr)
,_bBlackMaskForModal(true)
,_bFilterTransitionMsg(true)
{
	SCMessageDispatch::getInstance()->addListener(this);
}
    
SCViewController::~SCViewController()
{
    SCCCScheduler()->unscheduleAllForTarget(static_cast<cocos2d::Ref*>(this));
	SCMessageDispatch::getInstance()->removeListener(this);
}
    
void SCViewController::onCreate(SCDictionary parameters)
{
    bool bResult = false;
    auto finishFunc = parameters.getValue(SC_KEY_FINISHFUNC).getObject<FinishFunc_t>(&bResult);
        
    if(bResult && finishFunc!=nullptr)
    {
        _finishFunc = finishFunc;
    }

	if (_scriptCBInfo.pfunOnCreate)
	{
		_scriptCBInfo.pfunOnCreate(this->getScriptContainer(),parameters);
	}
}
    
void SCViewController::setView(SCView* pLayer)
{
    _pView = pLayer;
}
    
void SCViewController::ownLifecycle(cocos2d::Ref* pObject)
{
    SC_RETURN_V_IF(pObject==nullptr);
        
    auto ptr = SCRef2Ptr::create(pObject);
    this->ownLifecycle(ptr);
}
    
void SCViewController::pushModalController(SCViewController* pController)
{
    pController->setModalParentController(this);
    pController->setScene(_pScene);
        
    if(_bBlackMaskForModal)
    {
        this->showBlackMask(true);
    }
        
    _pScene->addChild(pController->getView());
    this->setTouchAcceptable(false);
        
    // generate modal mssage
    SCMessage::Ptr ptrMsg = SCMessage::create();
        
    ptrMsg->nMsgID = SCID::Msg::kMsgModalSceneLostFocus;
    ptrMsg->parameters.setValue(SC_KEY_CONTROLLER,this);
    SCMessageDispatch::getInstance()->postMessage(ptrMsg);
        
    ptrMsg->nMsgID = SCID::Msg::kMsgModalSceneGotFocus;
    ptrMsg->parameters.setValue(SC_KEY_CONTROLLER,pController);
    SCMessageDispatch::getInstance()->postMessage(ptrMsg);
}
    
SCViewController* SCViewController::popModalFromParent()
{
    SCASSERT(_pParentModalController!=nullptr);
    auto pRet = _pParentModalController;
        
    _pParentModalController->setTouchAcceptable(true);
    if(_pParentModalController->isBlackMaskForModal())
    {
        _pParentModalController->showBlackMask(false);
    }
        
    _pParentModalController = nullptr;
    _pView->removeFromParent();
        
    // generate modal mssage
    SCMessage::Ptr ptrMsg = SCMessage::create();
    ptrMsg->nMsgID = SCID::Msg::kMsgModalSceneGotFocus;
    ptrMsg->parameters.setValue(SC_KEY_CONTROLLER,_pParentModalController);
    SCMessageDispatch::getInstance()->postMessage(ptrMsg);
        
    return pRet;
}
    
void SCViewController::setTouchAcceptable(const bool bEnable)
{
    if(_pDisableTouchLayer==nullptr && !bEnable)
    {// turn to no touch
        auto pLayer = SCLayerDisableTouch::create();
        _pView->addChild(pLayer);
        pLayer->setPosition(cocos2d::Vec2(0,0));
            
        _pDisableTouchLayer = pLayer;
    }
    else if(_pDisableTouchLayer!=nullptr && bEnable)
    {// turn to touchable
        _pDisableTouchLayer->removeFromParentAndCleanup(true);
        _pDisableTouchLayer = nullptr;
    }
}
    
    
void SCViewController::showBlackMask(const bool bShow)
{
    if(bShow)
    {
        if(_pBlackMaskLayer==nullptr)
        {
            _pBlackMaskLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 200));
            _pView->addChild(_pBlackMaskLayer);
        }
    }
    else
    {
        if(_pBlackMaskLayer!=nullptr)
        {
            _pBlackMaskLayer->removeFromParentAndCleanup(true);
            _pBlackMaskLayer = nullptr;
        }
    }
}

void SCViewController::setFilterTransitionMsg(const bool bFilter)
{
    _bFilterTransitionMsg = bFilter;
}
    
void SCViewController::schedule(cocos2d::SEL_SCHEDULE selector)
{
    this->schedule(selector, 0.0f, CC_REPEAT_FOREVER, 0.0f);
}
    
void SCViewController::schedule(cocos2d::SEL_SCHEDULE selector, float interval)
{
    this->schedule(selector, interval, CC_REPEAT_FOREVER, 0.0f);
}
    
void SCViewController::schedule(cocos2d::SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
{
    SCCCScheduler()->schedule(selector, dynamic_cast<cocos2d::Ref*>(this), interval , repeat, delay, !_pView->isRunning());
}
    
void SCViewController::scheduleOnce(cocos2d::SEL_SCHEDULE selector, float delay)
{
    this->schedule(selector, 0.0f, 0, delay);
}
    
void SCViewController::unschedule(cocos2d::SEL_SCHEDULE selector)
{
    SCCCScheduler()->unschedule(selector, dynamic_cast<cocos2d::Ref*>(this));
}
    
void SCViewController::finish(void* pResult)
{
    if(_finishFunc!=nullptr)
    {
        _finishFunc(pResult);
    }
}
    
void SCViewController::delayExecute(float fDelay,const std::function<void ()>& fun)
{
    fDelay = (fDelay<0) ? 0 : fDelay;
        
    auto pSeqAction = ASequence(ADelayTime(fDelay),
                                ACallFunc(fun),
                                nullptr);
        
    this->getView()->runAction(pSeqAction);
}
    
void SCViewController::delayExecute(float fDelay,const std::function<void(SCDictionary dic)>& func,SCDictionary dic)
{
    this->delayExecute(fDelay,[func,dic]()
                        {
                            func(dic);
                        });
}
    
void SCViewController::setBackButtonSceneEnabled(const bool bEnabled)
{
    if(bEnabled)
    {
        const auto call = [](SCMessage::Ptr ptrMsg) -> bool
        {
            SC_RETURN_IF(ptrMsg->nMsgID!=SCID::Msg::kMsgKeyboardKeyDown,true);
                
            auto value = ptrMsg->parameters.getValue(SC_KEY_KEYBOARDCODE);
            auto code = value.getObject<cocos2d::EventKeyboard::KeyCode>();
            SC_RETURN_IF(code!=cocos2d::EventKeyboard::KeyCode::KEY_BACK,true);
            SCBehaviorViewBack::create()->execute();
            return true;
        };
            
        _ptrKeyboardEventEmtr = SCEventEmitter::create(SCEventEmitter::EEventType::kKeyboard,
                                                        _pView,
                                                        call);
    }
    else
    {
        _ptrKeyboardEventEmtr = nullptr;
    }
}
    
void SCViewController::listenMessage(const int nMsg,MsgFunc_t func)
{
    SC_RETURN_V_IF(nMsg<=0);
        
    if(func==nullptr)
    {// remove mapping
        _msg2FuncMap.erase(nMsg);
    }
    else
    {
        _msg2FuncMap[nMsg] = func;
    }
}
    
bool SCViewController::onSCMessageProcess(SCMessage::Ptr ptrMsg)
{
    SCASSERT(ptrMsg!=nullptr);
    
    // filter view transition message which is not belong to current controller
    if(_bFilterTransitionMsg)
    {
        switch(ptrMsg->nMsgID)
        {
            case SCID::Msg::kMsgViewEnter:
            case SCID::Msg::kMsgViewEnterTransitionDidFinish:
            case SCID::Msg::kMsgViewExit:
            case SCID::Msg::kMsgViewExitTransitionDidStart:
            {
                SCViewController* p = ptrMsg->getController();
                SCASSERT(p!=nullptr);
                SC_RETURN_IF(p!=this, true);
            }
                break;
        }
    }
    
    // lua callback
	if (_scriptCBInfo.pfunOnMessageProcess)
	{
		SC_RETURN_IF(!_scriptCBInfo.pfunOnMessageProcess(this->getScriptContainer(), ptrMsg), false);
	}
        
    auto it = _msg2FuncMap.find(ptrMsg->nMsgID);
        
    if(it!=_msg2FuncMap.end() && (*it).second!=nullptr)
    {
        (*it).second(ptrMsg);
        SC_RETURN_IF(!(*it).second(ptrMsg),false);
    }
        
	return true;
}
    
NAMESPACE_SPEEDCC_END

