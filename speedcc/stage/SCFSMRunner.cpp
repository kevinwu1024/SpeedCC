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

#include "SCFSMRunner.h"
#include "SCStage.h"

NAMESPACE_SPEEDCC_BEGIN

void SCFSMRunner::markCaptureMsg(const int nMsgID)
{
    auto it = _msgID2FilterCounterMap.find(nMsgID);
    if(it!=_msgID2FilterCounterMap.end())
    {
        ++(*it).second;
    }
    else
    {
        SCMapInsert(_msgID2FilterCounterMap, nMsgID, 1);
    }
}

void SCFSMRunner::markCmdUnfilter(const SCString& strCmd)
{
    this->markCaptureMsg(SCID::Msg::kMsgCommand);
    
    auto it = _cmd2FilterCounterMap.find(strCmd);
    if(it!=_cmd2FilterCounterMap.end())
    {
        ++(*it).second;
    }
    else
    {
        SCMapInsert(_cmd2FilterCounterMap, strCmd, 1);
    }
}

void SCFSMRunner::unmarkCaptureMsg(const int nMsgID)
{
    auto it = _msgID2FilterCounterMap.find(nMsgID);
    if(it!=_msgID2FilterCounterMap.end())
    {
        if(--(*it).second == 0)
        {
            _msgID2FilterCounterMap.erase(nMsgID);
        }
    }
}

void SCFSMRunner::unmarkCmdUnfilter(const SCString& strCmd)
{
    this->unmarkCaptureMsg(SCID::Msg::kMsgCommand);
    
    auto it = _cmd2FilterCounterMap.find(strCmd);
    if(it!=_cmd2FilterCounterMap.end())
    {
        if(--(*it).second == 0)
        {
            _cmd2FilterCounterMap.erase(strCmd);
        }
    }
}

bool SCFSMRunner::isCaptureMsg(SCMessage::Ptr ptrMsg)
{
    SC_RETURN_IF(_msgID2FilterCounterMap.empty(), false);
    
    if(ptrMsg->nMsgID==SCID::Msg::kMsgCommand)
    {
        SC_RETURN_IF(_cmd2FilterCounterMap.empty(), false);
        bool bResult = false;
        auto strCommand = ptrMsg->parameters.getValue(SC_KEY_COMMAND).getString(&bResult);
        if(bResult && !strCommand.isEmpty())
        {
            return (_cmd2FilterCounterMap.find(strCommand)!=_cmd2FilterCounterMap.end());
        }
        
        return true;
    }
    
    auto it = _msgID2FilterCounterMap.find(ptrMsg->nMsgID);
    return (_msgID2FilterCounterMap.end()!=it);
}

bool SCFSMRunner::addBehavior2State(const int nStateID,
                                     const int nMsgID,
                                     SCBehavior::Ptr bvrPtr,
                                     SCMessageMatcher::Ptr ptrMatcher)
{
    auto ptrSI = this->getStateInfo(nStateID);
    SC_RETURN_IF(ptrSI==nullptr, false);

    auto it = ptrSI->msgID2BehaviorMap.find(nMsgID);

    if(it==ptrSI->msgID2BehaviorMap.end())
    {
         SCStateInfo::SBehaviorInfo bi;
         bi.ptrBehaviorGroup = SCBehaviorMultiple::create();
         bi.ptrBehaviorGroup->addBehavior(bvrPtr);
         bi.ptrMatcher = ptrMatcher;
        
         ptrSI->msgID2BehaviorMap[nMsgID] = bi;
    }
    else
    {
         (*it).second.ptrBehaviorGroup->addBehavior(bvrPtr);
    }

    this->markCaptureMsg(nMsgID);

    return true;
}

bool SCFSMRunner::addBehavior2State(const int nStateID,
                                     const SCString& strCommand,
                                     SCBehavior::Ptr bvrPtr,
                                     SCMessageMatcher::Ptr ptrMatcher)
{
    SCASSERT(!strCommand.isEmpty());

    auto ptrSI =  this->getStateInfo(nStateID);
    SC_RETURN_IF(ptrSI==nullptr, false);

    auto it = ptrSI->command2BehaviorMap.find(strCommand);
    if(it==ptrSI->command2BehaviorMap.end())
    {
         SCStateInfo::SBehaviorInfo bi;
         bi.ptrBehaviorGroup = SCBehaviorMultiple::create();
         bi.ptrBehaviorGroup->addBehavior(bvrPtr);
         bi.ptrMatcher = ptrMatcher;
        
         ptrSI->command2BehaviorMap[strCommand] = bi;
    }
    else
    {
         (*it).second.ptrBehaviorGroup->addBehavior(bvrPtr);
    }

    this->markCmdUnfilter(strCommand);
    
    return true;
}

bool SCFSMRunner::addBehavior2State(const int nStateID,
                                     SCMessageMatcher::Ptr ptrMatcher,
                                     SCBehavior::Ptr bvrPtr)
{
    bool bRet = false;
    if(ptrMatcher->getMessageID()==SCID::Msg::kMsgCommand)
    {
        SC_RETURN_IF(ptrMatcher->getCommand()=="",false);
        bRet = this->addBehavior2State(nStateID,ptrMatcher->getCommand(),bvrPtr,ptrMatcher);
    }
    else
    {
        bRet = this->addBehavior2State(nStateID,ptrMatcher->getMessageID(),bvrPtr,ptrMatcher);
    }
    
    return bRet;
}

bool SCFSMRunner::addEnterBehavior2State(const int nStateID,SCBehavior::Ptr bvrPtr)
{
    auto ptrSI = this->getStateInfo(nStateID);
    SC_RETURN_IF(ptrSI==nullptr, false);

    if(ptrSI->ptrEnterBehavior==nullptr)
    {
        ptrSI->ptrEnterBehavior = SCBehaviorMultiple::create();
    }

    ptrSI->ptrEnterBehavior->addBehavior(bvrPtr);

    return true;
}

bool SCFSMRunner::addExitBehavior2State(const int nStateID,SCBehavior::Ptr bvrPtr)
{
    auto ptrSI = this->getStateInfo(nStateID);
    SC_RETURN_IF(ptrSI==nullptr, false);

    if(ptrSI->ptrExitBehavior==nullptr)
    {
        ptrSI->ptrExitBehavior = SCBehaviorMultiple::create();
    }

    ptrSI->ptrExitBehavior->addBehavior(bvrPtr);
    
    return true;
}

SCBehavior::Ptr SCFSMRunner::getStateEnterBehavior(const int nState) const
{
    auto it = _stateID2StateInfoMap.find(nState);
    SC_RETURN_IF(it == _stateID2StateInfoMap.end(), nullptr);
    
    return (*it).second->ptrEnterBehavior;
}

SCBehavior::Ptr SCFSMRunner::getStateExitBehavior(const int nState) const
{
    auto it = _stateID2StateInfoMap.find(nState);
    SC_RETURN_IF(it == _stateID2StateInfoMap.end(), nullptr);
    
    return (*it).second->ptrExitBehavior;
}

SCFSMRunner::SCStateInfo::Ptr SCFSMRunner::getStateInfo(const int nStateID) const
{
    SC_RETURN_IF(_stateID2StateInfoMap.empty(), nullptr);
    
    auto it = _stateID2StateInfoMap.find(nStateID);
    SC_RETURN_IF(it==_stateID2StateInfoMap.end(), nullptr);
    
    return (*it).second;
}

void SCFSMRunner::addState(int nStateID)
{
    auto ptrSI = SCStateInfo::create();
    ptrSI->nState = nStateID;
    _stateID2StateInfoMap[nStateID] = ptrSI;
}

SCDictionary SCFSMRunner::makeParameter(SCEntity::Ptr ptrEntity,SCMessage::Ptr ptrMsg)
{
    SCStage* pStage = ptrEntity->getStage();
    SCStage::Ptr ptrStage = pStage->makeObjPtr<SCStage::Ptr>();
    
    SCDictionary dic = ptrMsg->parameters;
    dic[SC_KEY_FSMRUNNER] = this->makeObjPtr<SCFSMRunner::Ptr>();
    dic[SC_KEY_ENTITY] = ptrEntity;
    dic[SC_KEY_MESSAGE] = ptrMsg;
    dic[SC_KEY_STAGE] =  ptrStage;
    
    return dic;
}

NAMESPACE_SPEEDCC_END
