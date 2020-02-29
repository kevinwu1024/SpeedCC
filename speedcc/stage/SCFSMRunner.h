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

#ifndef __SPEEDCC__SCFSMRUNNER_H__
#define __SPEEDCC__SCFSMRUNNER_H__

#include "SCEntity.h"
#include "SCMessage.h"
#include "SCBehaviorCommon.h"

NAMESPACE_SPEEDCC_BEGIN

class SCFSMBuilder;

struct SFSMStateComponent : public SCComponent
{   
	SC_DEFINE_CLASS_PTR(SFSMStateComponent)

    int nPreviousState;
    int nCurrentState;
	bool bGenerateMsg; // whether generate kMsgFSMStateChanged message
    std::function<void(int,int)> stateChangedFunc; // (int nOldState, int nNewState)
    
    SFSMStateComponent()
    :nCurrentState(SCID::State::kStateInvalid)
    ,stateChangedFunc(nullptr)
	,bGenerateMsg(true)
    {}
};

class SCFSMRunner : public SCObject
{
    friend SCFSMBuilder;
    
private:
    struct SCStateInfo : public SCObject
    {
        SC_AVOID_CLASS_COPY(SCStateInfo)
        SC_DEFINE_CLASS_PTR(SCStateInfo)
        
        SC_DEFINE_CREATE_FUNC_0(SCStateInfo);
        
        struct SBehaviorInfo
        {
            SCMessageMatcher::Ptr       ptrMatcher;
            SCBehaviorMultiple::Ptr     ptrBehaviorGroup;
        };
        
        int                                     nState;
        SCBehaviorMultiple::Ptr                 ptrEnterBehavior;
        SCBehaviorMultiple::Ptr                 ptrExitBehavior;
        
        std::map<int,SBehaviorInfo>             msgID2BehaviorMap;
        std::map<SCString,SBehaviorInfo>        command2BehaviorMap;
        
    protected:
        SCStateInfo() {}
    };
    
public:
    SC_AVOID_CLASS_COPY(SCFSMRunner)
    SC_DEFINE_CLASS_PTR(SCFSMRunner)
    
    virtual bool execute(SCEntity::Ptr ptrEntity,SCMessage::Ptr ptrMsg) = 0;
    
    inline bool getActive() const {return _bActive;}
    inline void setActive(const bool bActive) {_bActive = bActive;}
    
    SCBehavior::Ptr getStateEnterBehavior(const int nState) const;
    SCBehavior::Ptr getStateExitBehavior(const int nState) const;
    
    void addState(int nStateID);
    
protected:
    SCFSMRunner()
    :_bActive(true)
    {}
    
protected:
    SCStateInfo::Ptr getStateInfo(const int nState) const;
    bool addBehavior2State(const int nStateID,
                           const int nMsgID,
                           SCBehavior::Ptr ptrBvr,
                           SCMessageMatcher::Ptr ptrMatcher=nullptr);
    bool addBehavior2State(const int nStateID,
                           const SCString& strCommand,
                           SCBehavior::Ptr bvrPtr,
                           SCMessageMatcher::Ptr ptrMatcher=nullptr);
    bool addBehavior2State(const int nStateID,
                           SCMessageMatcher::Ptr ptrMatcher,
                           SCBehavior::Ptr bvrPtr);
    
    bool addEnterBehavior2State(const int nStateID,SCBehavior::Ptr ptrBvr);
    bool addExitBehavior2State(const int nStateID,SCBehavior::Ptr ptrBvr);
    
    void markCaptureMsg(const int nMsgID);
    void markCmdUnfilter(const SCString& strCmd);
    void unmarkCaptureMsg(const int nMsgID);
    void unmarkCmdUnfilter(const SCString& strCmd);
    
    bool isCaptureMsg(SCMessage::Ptr ptrMsg);
    void updateVariationEntity();
    
    SCDictionary makeParameter(SCEntity::Ptr ptrEntity,SCMessage::Ptr ptrMsg);
    
protected:
    bool                            _bActive;
    std::map<int,int>               _msgID2FilterCounterMap;
    std::map<SCString,int>          _cmd2FilterCounterMap;
    
    std::map<int,SCStateInfo::Ptr>  _stateID2StateInfoMap;
};


template<typename T>
class SCFSMRunnerT : public SCFSMRunner
{
public:
    SC_AVOID_CLASS_COPY(SCFSMRunnerT)
    SC_DEFINE_CLASS_PTR(SCFSMRunnerT)
    
    SC_DEFINE_CREATE_FUNC_0(SCFSMRunnerT);
    
public:
    virtual bool execute(SCEntity::Ptr ptrEntity,SCMessage::Ptr ptrMsg) override
    {
        static_assert(std::is_base_of<SFSMStateComponent,T>::value,
                      "FSM state property must derive from SFSMStateComponent");
        
        SC_RETURN_IF(!_bActive, false);
        SC_RETURN_IF(ptrEntity == nullptr || ptrMsg == nullptr, false);
        SC_RETURN_IF(!this->isCaptureMsg(ptrMsg),false);
        SC_RETURN_IF(!ptrEntity->hasComponent<T>(), false);
        
        auto ptrProperty = ptrEntity->getComponent<T>();
        auto ptrStateInfo = this->getStateInfo(ptrProperty->nCurrentState);
        
        SC_RETURN_IF(ptrStateInfo == nullptr, false);
        
        if(ptrMsg->nMsgID == SCID::Msg::kMsgCommand)
        {
            auto it = ptrStateInfo->command2BehaviorMap.find(ptrMsg->getCommand());
            SC_RETURN_IF(it == ptrStateInfo->command2BehaviorMap.end(),false);
            SC_RETURN_IF((*it).second.ptrMatcher != nullptr && !(*it).second.ptrMatcher->isMatch(ptrMsg),false);
            
            auto dic = this->makeParameter(ptrEntity,ptrMsg);
            (*it).second.ptrBehaviorGroup->execute(dic);
        }
        else
        {
            auto it = ptrStateInfo->msgID2BehaviorMap.find(ptrMsg->nMsgID);
            SC_RETURN_IF(it == ptrStateInfo->msgID2BehaviorMap.end(), false);
            SC_RETURN_IF((*it).second.ptrMatcher != nullptr && !(*it).second.ptrMatcher->isMatch(ptrMsg),false);
            
            auto dic = this->makeParameter(ptrEntity,ptrMsg);
            (*it).second.ptrBehaviorGroup->execute(dic);
        }
        
        return true;
    }
    
protected:
    SCFSMRunnerT(){}
};


class SCFSMRunnerSingle : public SCFSMRunner
{
public:
    SC_AVOID_CLASS_COPY(SCFSMRunnerSingle)
    SC_DEFINE_CLASS_PTR(SCFSMRunnerSingle)
    
    SC_DEFINE_CREATE_FUNC_0(SCFSMRunnerSingle);
    
public:
    virtual bool execute(SCEntity::Ptr ptrEntity,SCMessage::Ptr ptrMsg) override
    {
        SC_RETURN_IF(!_bActive, false);
        SC_RETURN_IF(ptrEntity == nullptr || ptrMsg == nullptr, false);
        SC_RETURN_IF(!this->isCaptureMsg(ptrMsg),false);
        
        auto ptrStateInfo = this->getStateInfo(0); // default state value is 0
        
        SC_RETURN_IF(ptrStateInfo == nullptr, false);
        SCFSMRunner::Ptr ptrRunner = this->makeObjPtr<SCFSMRunner::Ptr>();
        
        if(ptrMsg->nMsgID == SCID::Msg::kMsgCommand)
        {
            auto it = ptrStateInfo->command2BehaviorMap.find(ptrMsg->getCommand());
            SC_RETURN_IF(it == ptrStateInfo->command2BehaviorMap.end(),false);
            SC_RETURN_IF((*it).second.ptrMatcher != nullptr && !(*it).second.ptrMatcher->isMatch(ptrMsg),false);
            
            auto dic = this->makeParameter(ptrEntity,ptrMsg);
            (*it).second.ptrBehaviorGroup->execute(dic);
        }
        else
        {
            auto it = ptrStateInfo->msgID2BehaviorMap.find(ptrMsg->nMsgID);
            SC_RETURN_IF(it == ptrStateInfo->msgID2BehaviorMap.end(), false);
            SC_RETURN_IF((*it).second.ptrMatcher != nullptr && !(*it).second.ptrMatcher->isMatch(ptrMsg),false);
            
            auto dic = this->makeParameter(ptrEntity,ptrMsg);
            (*it).second.ptrBehaviorGroup->execute(dic);
        }
        
        return true;
    }
    
protected:
    SCFSMRunnerSingle(){}
};
	
NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCFSMRUNNER_H__
