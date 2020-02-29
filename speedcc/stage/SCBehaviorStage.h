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

#ifndef __SPEEDCC__SCBEHAVIORSTAGE_H__
#define __SPEEDCC__SCBEHAVIORSTAGE_H__

#include "SCEntity.h"
#include "SCFSMRunner.h"

NAMESPACE_SPEEDCC_BEGIN

///---------------- SCBehaviorSwitchFSMStateT
template<typename T>
class SCBehaviorSwitchFSMStateT : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorSwitchFSMStateT)
    SC_DEFINE_CLASS_PTR(SCBehaviorSwitchFSMStateT)
    
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorSwitchFSMStateT,const int)
    
    virtual void execute(const SCDictionary& par) override
    {
        static_assert(std::is_base_of<SFSMStateComponent,T>::value,
                      "FSM state Component must derive from SFSMStateComponent");
        
        SC_RETURN_V_IF(!this->getActive());
        SC_RETURN_V_IF(_nStateID == SCID::State::kStateInvalid);
        
        auto entityVal = par.getValue(SC_KEY_ENTITY);
        SC_RETURN_V_IF(!entityVal.isValidObject<SCEntity::Ptr>());
        
        auto runnerVal = par.getValue(SC_KEY_FSMRUNNER);
        SC_RETURN_V_IF(!runnerVal.isValidObject<SCFSMRunner::Ptr>());
        
        auto ptrEntity = entityVal.getObject<SCEntity::Ptr>();
        auto ptrRunner = runnerVal.getObject<SCFSMRunner::Ptr>();
        SC_RETURN_V_IF(!ptrRunner->getActive());
        
        auto ptrStateComponent = ptrEntity->getComponent<T>();
        SC_RETURN_V_IF(ptrStateComponent->nCurrentState == _nStateID);

        auto oldState = ptrStateComponent->nCurrentState;
        
        auto ptrExitBvr = ptrRunner->getStateExitBehavior(ptrStateComponent->nCurrentState);
        if(ptrExitBvr != nullptr)
        {
            ptrExitBvr->execute(par);
        }
        
        ptrStateComponent->nCurrentState = _nStateID;
        ptrStateComponent->nPreviousState = oldState;
        
        auto ptrEnterBvr = ptrRunner->getStateEnterBehavior(_nStateID);
        if(ptrEnterBvr != nullptr)
        {
            ptrEnterBvr->execute(par);
        }
        
        if(ptrStateComponent->stateChangedFunc)
        {
            ptrStateComponent->stateChangedFunc(oldState,_nStateID);
        }

		// generate state changed message
		if (ptrStateComponent->bGenerateMsg)
		{
			SCDictionary paraDic = { { SC_KEY_FSMSTATECOMP ,ptrStateComponent } };
			auto ptrMsg = SCMessage::create(SCID::Msg::kMsgFSMStateChanged, paraDic);
			SCMsgDisp()->postMessage(ptrMsg);
		}
    }
    
protected:
    SCBehaviorSwitchFSMStateT(const int nState)
    :_nStateID(nState)
    {}
    
private:
    int                         _nStateID;
};

///----------- SCBehaviorEntityActive
class SCBehaviorEntityActive : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorEntityActive)
    SC_DEFINE_CLASS_PTR(SCBehaviorEntityActive)
    
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorEntityActive,const int,bool) // single id
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorEntityActive,std::list<int>*,bool) // dynamic list
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorEntityActive,std::list<int>,bool) // fixed list
    
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
    
protected:
    SCBehaviorEntityActive()
    {}
    
    SCBehaviorEntityActive(const int nActorID,const bool bActive)
    :_bActive(bActive)
    {
        _entIDList.push_back(nActorID);
    }
    
    SCBehaviorEntityActive(const std::list<int>& actorIDList,const bool bActive)
    :_entIDList(actorIDList)
    , _pEntIDList(nullptr)
    ,_bActive(bActive)
    {
    }
    
    SCBehaviorEntityActive(std::list<int>* pActorIDList,const bool bActive)
    :_pEntIDList(pActorIDList)
    ,_bActive(bActive)
    {
    }
    
private:
    std::list<int>      _entIDList;
    std::list<int>*     _pEntIDList;
    bool                _bActive;
};

///------------- SCBehaviorStrategyActive
class SCBehaviorStrategyActive : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorStrategyActive)
    SC_DEFINE_CLASS_PTR(SCBehaviorStrategyActive)
    
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorStrategyActive,const int,bool) // single id
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorStrategyActive,std::list<int>*,bool) // dynamic list
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorStrategyActive,const std::list<int>,bool) // static list
		SC_DEFINE_CREATE_FUNC_2(SCBehaviorStrategyActive, const std::vector<int>, bool) // static list
    
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
    
protected:
    SCBehaviorStrategyActive()
    {}
    
    SCBehaviorStrategyActive(const int nStrategyID,const bool bActive)
    :_bActive(bActive)
    {
        _strategyIDList.push_back(nStrategyID);
    }
    
    SCBehaviorStrategyActive(const std::list<int>& actorIDList,const bool bActive)
    :_strategyIDList(actorIDList)
    ,_pStrategyIDList(nullptr)
    ,_bActive(bActive)
    {
    }

	SCBehaviorStrategyActive(const std::vector<int>& actorIDVet, const bool bActive)
	:_strategyIDList(std::begin(actorIDVet), std::end(actorIDVet))
	, _pStrategyIDList(nullptr)
	, _bActive(bActive)
	{
	}
    
    SCBehaviorStrategyActive(std::list<int>* pActorIDList,const bool bActive)
    :_pStrategyIDList(pActorIDList)
    ,_bActive(bActive)
    {
    }
    
private:
    std::list<int>      _strategyIDList;
    std::list<int>*     _pStrategyIDList;
    bool                _bActive;
};

///------------- SCBehaviorDeliverMessage
class SCBehaviorDeliverMessage : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorDeliverMessage)
    SC_DEFINE_CLASS_PTR(SCBehaviorDeliverMessage)
        
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorDeliverMessage,const bool,SCMessage::Ptr)
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorDeliverMessage,const bool,const int)
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorDeliverMessage,const bool,const SCString&)
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
protected:
    SCBehaviorDeliverMessage(const bool bSend,SCMessage::Ptr ptrMsg);
    SCBehaviorDeliverMessage(const bool bSend,const int nMsgID);
    SCBehaviorDeliverMessage(const bool bSend,const SCString& strCmd);
        
private:
    SCMessage::Ptr      _ptrMsg;
    bool                _bSend;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCBEHAVIORSTAGE_H__
