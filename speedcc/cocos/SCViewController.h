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

#ifndef __SPEEDCC__SCVIEWCONTROLLERT_H__
#define __SPEEDCC__SCVIEWCONTROLLERT_H__

#include "cocos2d.h"

#include "SCRefHolder.h"
#include "SCCocosDef.h"
#include "SCBinderCocos.h"
#include "SCViewBuilder.h"
#include "SCEventEmitter.h"

#include "../base/SCObjPtrT.h"
#include "../base/SCObject.h"

#include "../stage/SCMessageDispatch.h"


NAMESPACE_SPEEDCC_BEGIN

class SCViewController;

extern "C"
{
	typedef bool(*scScriptCBViewController_onSCMessageProcess_t)(void* pContainer,SCMessage::Ptr ptrMsg);
	typedef void(*scScriptCBViewController_onCreate_t)(void* pContainer, SCDictionary parameters);
}

struct SScriptCBViewControllerInfo
{
	scScriptCBViewController_onSCMessageProcess_t	pfunOnMessageProcess;
	scScriptCBViewController_onCreate_t				pfunOnCreate;

	SScriptCBViewControllerInfo() 
	:pfunOnMessageProcess(nullptr)
	,pfunOnCreate(nullptr)
	{}
};

class SCView;
class SCScene;
class SCLayerDisableTouch;
    
// SCViewController lifecycle is owned by it's view,
// controller will be destroyed once view deleted
class SCViewController
:public cocos2d::Ref
,public SCMessageListener
,public SCObject
{
public:
    SC_DEFINE_CLASS_PTR(SCViewController)
    SC_AVOID_CLASS_COPY(SCViewController)
        
	SC_DEFINE_CREATE_FUNC_0(SCViewController)

    friend class SCView;
    friend class SCViewNavigator;
    template<typename> friend class SCVCCreatorT;
        
    typedef std::function<bool(SCMessage::Ptr ptrMsg)>      MsgFunc_t;
    typedef std::function<void(void*)>                      FinishFunc_t;
        
    virtual ~SCViewController();
        
    inline bool isAllTouchEnabled() const  {return (_pDisableTouchLayer==nullptr);}
    inline bool isBlackMaskForModal() const  {return _bBlackMaskForModal;}
    inline SCView* getView() const {return _pView;}
    inline SCScene* getScene() const  {return _pScene;}
        
    void setTouchAcceptable(const bool bEnabled);
    void showBlackMask(const bool bShow);

    // modal related
    void pushModalController(SCViewController* controllerPtr);
    SCViewController* popModalFromParent();
    
    // lifecycle related
    inline void ownLifecycle(SCObject::Ptr ptr) { _ownLifecycleList.push_back(ptr);}
    void ownLifecycle(cocos2d::Ref* pObject);
        
    void delayExecute(float fDelay,const std::function<void ()>& fun);
    void delayExecute(float fDelay,const std::function<void(SCDictionary dic)>& func,SCDictionary dic);
    void listenMessage(const int nMsg,MsgFunc_t func);
        
    void schedule(cocos2d::SEL_SCHEDULE selector);
    void schedule(cocos2d::SEL_SCHEDULE selector, float interval);
    void schedule(cocos2d::SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);
    void scheduleOnce(cocos2d::SEL_SCHEDULE selector, float delay);
    void unschedule(cocos2d::SEL_SCHEDULE selector);
        
    virtual bool onSCMessageProcess(SCMessage::Ptr ptrMsg) override;
        
    void finish(void* pResult=nullptr);
    
    void setFilterTransitionMsg(const bool bFilter);
    inline bool getOwnTransitionMsg() const { return _bFilterTransitionMsg; }
        
    void setBackButtonSceneEnabled(const bool bEnabled);
    inline bool getBackButtonSceneEnabled() const { return _ptrKeyboardEventEmtr!=nullptr; }
    
    // for lua
	void setScriptCBInfo(const SScriptCBViewControllerInfo& cbInfo) { _scriptCBInfo = cbInfo; }

protected:
    SCViewController();
        
    virtual void onCreate(SCDictionary parameters);
        
private:
    void setView(SCView* pLayer);
    inline void setScene(SCScene* pScene)  {_pScene = pScene;}
    inline void setModalParentController(SCViewController* pController)
    { _pParentModalController = pController; }
        
private:
    SCView*			                            _pView;
    SCScene*                                    _pScene;
    SCViewController*                           _pParentModalController; // weak pointer
    SCLayerDisableTouch*                        _pDisableTouchLayer;
    cocos2d::Layer*                             _pBlackMaskLayer;
    bool                                        _bBlackMaskForModal;
    bool                                        _bFilterTransitionMsg;
    std::list<SCObject::Ptr>                    _ownLifecycleList;
    std::map<int,MsgFunc_t>                     _msg2FuncMap;
    FinishFunc_t                                _finishFunc;
    SCEventEmitter::Ptr                         _ptrKeyboardEventEmtr;

	SScriptCBViewControllerInfo					_scriptCBInfo;
};
    

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCVIEWCONTROLLERT_H__
