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

#include "SCFSMBuilder.h"

NAMESPACE_SPEEDCC_BEGIN

SCFSMBuilder::SCFSMBuilder()
{
}

void SCFSMBuilder::end()
{
    _stateStack.pop_front();
    SCASSERT(_stateStack.empty());
    _ptrRunner->setActive(true);
}

void SCFSMBuilder::beginState(const int nStateID)
{
//    SCASSERT(nStateID>0);
    _stateStack.push_front(nStateID);
    _ptrRunner->addState(nStateID);
}

void SCFSMBuilder::endState()
{
    _stateStack.pop_front();
}

void SCFSMBuilder::insertBehaviorWithMsg(const SCFSMBuilder::MessagePurifier& msgPurifier,const StateArgPurifier& bvrPurifier)
{
    SCASSERT(!_stateStack.empty());
    
    int nCurrentStateID = _stateStack.front();
    
    for(auto it : msgPurifier.msgList)
    {
        _ptrRunner->addBehavior2State(nCurrentStateID,it.nMsg, bvrPurifier.ptrBehavior,it.ptrMatcher);
    }
}

void SCFSMBuilder::insertBehaviorWithCmd(const SCString& strCmd,const StateArgPurifier& bvrPurifier)
{
    SCASSERT(!strCmd.isEmpty());
    SCASSERT(bvrPurifier.ptrBehavior!=nullptr);
    SCASSERT(!_stateStack.empty());
    
    int nParentStateID = _stateStack.front();
    _ptrRunner->addBehavior2State(nParentStateID, strCmd, bvrPurifier.ptrBehavior);
}

void SCFSMBuilder::insertEnterBehavior(const StateArgPurifier& bvrPurifier)
{
    SCASSERT(bvrPurifier.ptrBehavior!=nullptr);
    SCASSERT(!_stateStack.empty());
    
    int nParentStateID = _stateStack.front();
    _ptrRunner->addEnterBehavior2State(nParentStateID, bvrPurifier.ptrBehavior);
}

void SCFSMBuilder::insertExitBehavior(const StateArgPurifier& bvrPurifier)
{
    SCASSERT(bvrPurifier.ptrBehavior!=nullptr);
    SCASSERT(!_stateStack.empty());
    
    int nParentStateID = _stateStack.front();
    _ptrRunner->addExitBehavior2State(nParentStateID, bvrPurifier.ptrBehavior);
}

///--------------- utils

SCFSMBuilder::StateArgPurifier::StateArgPurifier(const std::function<void(const SCDictionary& par)>& func)
{
    ptrBehavior = SCBehaviorCallFunc::create([func](const SCDictionary& par)
                                             {
                                                 func(par);
                                             });
}

SCFSMBuilder::StateArgPurifier::StateArgPurifier(const std::function<void()>& func)
{
    ptrBehavior = SCBehaviorCallFunc::create([func](const SCDictionary& par)
                                             {
                                                 func();
                                             });
}

SCFSMBuilder::MessagePurifier::MessagePurifier(const int nMsgID)
{
    SMsgListInfo mli;
    mli.nMsg = nMsgID;
    mli.ptrMatcher = nullptr;
    
    msgList.push_back(mli);
}

SCFSMBuilder::MessagePurifier::MessagePurifier(SCMessageMatcher::Ptr ptrMatcher)
{
    SMsgListInfo mli;
    mli.nMsg = ptrMatcher->getMessageID();
    mli.ptrMatcher = ptrMatcher;
    
    msgList.push_back(mli);
}

SCFSMBuilder::MessagePurifier::MessagePurifier(SCMessageGroup::Ptr ptrGroup)
{
    auto ls = ptrGroup->getMessageList();
    for(auto it : ls)
    {
        SMsgListInfo mli;
        
        mli.nMsg = it->nMsgID;
        mli.ptrMatcher = nullptr;
        
        msgList.push_back(mli);
    }
}

NAMESPACE_SPEEDCC_END
