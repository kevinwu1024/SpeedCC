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

#ifndef __SPEEDCC__SCFSMBUILDER_H__
#define __SPEEDCC__SCFSMBUILDER_H__

#include "SCPlayObject.h"
#include "SCMessage.h"
#include "SCBehaviorCommon.h"
#include "SCFSMRunner.h"

NAMESPACE_SPEEDCC_BEGIN

class SCFSMBuilder : public SCObject
{
private:
    struct SMsgListInfo
    {
        int                     nMsg;
        SCString                strCmd;
        SCMessageMatcher::Ptr   ptrMatcher;
    };
    
public:
    struct StateArgPurifier
    {
        template<typename T,
        typename = typename std::enable_if<std::is_convertible<T,SCBehavior::Ptr>::value,T>::type >
        StateArgPurifier(T bvr)
        :ptrBehavior(bvr)
        {}
        
        StateArgPurifier(const std::function<void(const SCDictionary& par)>& func);
        StateArgPurifier(const std::function<void()>& func);
        StateArgPurifier(void*) {}
        
        SCBehavior::Ptr     ptrBehavior;
    };
    
    struct MessagePurifier
    {
        MessagePurifier(const int nMsgID);
        MessagePurifier(SCMessageMatcher::Ptr ptrMatcher);
        MessagePurifier(SCMessageGroup::Ptr ptrGroup);
        MessagePurifier(...) {}
        
        std::list<SMsgListInfo> msgList;
    };
    
public:
    SC_AVOID_CLASS_COPY(SCFSMBuilder)
    SC_DEFINE_CLASS_PTR(SCFSMBuilder)
        
    SC_DEFINE_CREATE_FUNC_0(SCFSMBuilder);
    
    template<typename T>
    SCFSMRunner::Ptr begin(const int nInitStateID)
    {
        SCASSERT(_stateStack.empty());
//        SCASSERT(nInitStateID>0);
        
        _ptrRunner = SCFSMRunnerT<T>::create();
        _ptrRunner->setActive(false);
        this->beginState(nInitStateID);
        
        return _ptrRunner;
    }
    
    
    SCFSMRunner::Ptr beginSingle()
    {
        SCASSERT(_stateStack.empty());
        
        _ptrRunner = SCFSMRunnerSingle::create();
        _ptrRunner->setActive(false);
        this->beginState(0); // default state value is 0
        
        return _ptrRunner;
    }
    
    void end();
    
    void beginState(const int nStateID);
    void endState();
    
    void insertBehaviorWithMsg(const MessagePurifier& msgPurifier,const StateArgPurifier& ptrBvr);
    void insertBehaviorWithCmd(const SCString& strCmd,const StateArgPurifier& ptrBvr);
    void insertEnterBehavior(const StateArgPurifier& ptrBvr);
    void insertExitBehavior(const StateArgPurifier& ptrBvr);
    
    SCFSMRunner::Ptr getRunner() const {return _ptrRunner;}
    
protected:
    SCFSMBuilder();
    
private:
    std::list<int>              _stateStack;
    SCFSMRunner::Ptr            _ptrRunner;
};
	
NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCFSMBUILDER_H__
