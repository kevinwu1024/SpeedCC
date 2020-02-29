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

#include "SCMessageDispatch.h"
#include "../base/SCTemplateDef.h"
#include "../cocos/SCCocosDef.h"
#include "../stage/SCStageMacros.h"

using namespace std;

NAMESPACE_SPEEDCC_BEGIN

///----------- SCMessageListener
    
SCMessageDispatch* SCMessageDispatch::_pInstance = nullptr;
    
SCMessageDispatch* SCMessageDispatch::getInstance()
{
    if(_pInstance==nullptr)
    {
        _pInstance = new SCMessageDispatch();
        SCCCScheduler()->schedule(SC_FUNC(SCMessageDispatch::onFrameMessagePump),_pInstance,0,false);
    }
        
    return _pInstance;
}
    
SCMessageDispatch::SCMessageDispatch()
:_nPostMsgCallStackCounter(0)
,_nSendMsgCallStackCounter(0)
,_bMessageQueFlag(true)
,_bFrameMessageEnabled(true)
{
}
    
void SCMessageDispatch::addListener(SCMessageListener* pListener,const unsigned char nPriority)
{
    SCASSERT(pListener!=nullptr);
        
    SMutabelListenerInfo info;
        
    info.bAdd = true;
    info.listener.pListener = pListener;
    info.listener.byPriority = nPriority;
        
    auto it = std::find(_mutableListenerList.begin(),_mutableListenerList.end(),info);
        
    if(it!=_mutableListenerList.end())
    {
        _mutableListenerList.erase(it);
    }
        
    _mutableListenerList.push_back(info);
        
    // if no message dispatch in call stack, then updating mutable listener immediately
    if(_nPostMsgCallStackCounter==0 && _nSendMsgCallStackCounter==0)
    {
        this->updateMutableListener();
    }
}
    
void SCMessageDispatch::removeListener(SCMessageListener* pListener)
{
    SCASSERT(pListener!=nullptr);
        
    SMutabelListenerInfo info;
        
    info.bAdd = false;
    info.listener.pListener = pListener;
        
    auto it = std::find(_mutableListenerList.begin(),_mutableListenerList.end(),info);
        
    if(it!=_mutableListenerList.end())
    {
        _mutableListenerList.erase(it);
    }
        
    _mutableListenerList.push_back(info);
        
    if(_nPostMsgCallStackCounter==0 && _nSendMsgCallStackCounter==0)
    {
        this->updateMutableListener();
    }
}
    
void SCMessageDispatch::sendMessage(SCMessage::Ptr ptrMsg)
{
    if(_nPostMsgCallStackCounter==0 && _nSendMsgCallStackCounter==0)
    {
        this->updateMutableListener();
    }
        
    ++_nSendMsgCallStackCounter;
        
    auto it = _listenerList.begin();
    for(;it!=_listenerList.end();++it)
    {
        SCASSERT((*it).pListener!=nullptr);
            
        if((*it).pListener!=nullptr)
        {
            SC_BREAK_IF(!(*it).pListener->onSCMessageProcess(ptrMsg));
        }
            
        _defaultProc.processMessage(ptrMsg);
    }
        
    --_nSendMsgCallStackCounter;
}
    
void SCMessageDispatch::sendMessage(const int nMsgID)
{
    SCMessage::Ptr ptrMsg = SCMessage::create();
    ptrMsg->nMsgID = nMsgID;
    this->sendMessage(ptrMsg);
}
    
void SCMessageDispatch::sendMessage(const int nMsgID,const SCDictionary& dic)
{
    SCMessage::Ptr ptrMsg = SCMessage::create();
    ptrMsg->nMsgID = nMsgID;
    ptrMsg->parameters = dic;
    this->sendMessage(ptrMsg);
}
    
void SCMessageDispatch::postMessage(SCMessage::Ptr ptrMsg)
{
    this->getMsgQueRecive().push_back(ptrMsg);
}
    
void SCMessageDispatch::postMessage(const int nMsgID)
{
    SCMessage::Ptr ptrMsg = SCMessage::create();
    ptrMsg->nMsgID = nMsgID;
    this->postMessage(ptrMsg);
}
    
void SCMessageDispatch::postMessage(const int nMsgID,const SCDictionary& dic)
{
    SCMessage::Ptr ptrMsg = SCMessage::create();
    ptrMsg->nMsgID = nMsgID;
    ptrMsg->parameters = dic;
    this->postMessage(ptrMsg);
}
    
void SCMessageDispatch::updateMutableListener()
{
    SCASSERT(_nSendMsgCallStackCounter==0);
    SCASSERT(_nPostMsgCallStackCounter==0);
        
    SC_RETURN_V_IF(_mutableListenerList.empty());
        
	bool bAdded = false;
    std::for_each(_mutableListenerList.begin(),_mutableListenerList.end(),
                    [this,&bAdded](const SMutabelListenerInfo& info)-> void
                    {
                        SC_RETURN_V_IF(info.listener.pListener==nullptr);
                          
                        if(info.bAdd)
                        {// add listener
                            _listenerList.remove_if([&info](const SListenerInfo& it) -> bool
                                                    {
                                                        return (it.pListener==info.listener.pListener);
                                                    });
                              
                            SListenerInfo listenerInfo = info.listener;
                            _listenerList.push_back(listenerInfo);
							bAdded = true;
                        }
                        else
                        {// remove listener
                            _listenerList.remove_if([&info](const SListenerInfo& it) -> bool
                                                    {
                                                        return (it.pListener==info.listener.pListener);
                                                    });
                        }
                    });
        
	if (bAdded)
	{
		_listenerList.sort(std::greater<SListenerInfo>());
	}
    
    _mutableListenerList.clear();
}
    
    
void SCMessageDispatch::onFrameMessagePump(float fDelta)
{
    std::list<SCMessage::Ptr>& workingQue = this->getMsgQueRecive();
    this->swapMsgQue();
        
    // update mutable listener first before message loop
    this->updateMutableListener();
    
    // free retain pool
    SCObject::freeFrameRetainPool();
    
    // send frame message
    if(_bFrameMessageEnabled)
    {
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kMsgFrame;
        ptrMsg->parameters.setValue(SC_KEY_DELTA, SCValue(fDelta));
        SCMsgDisp()->sendMessage(ptrMsg);
            
//            if(!ptrMsg->bContinue)
//            {
//                workingQue.clear();
//                return;
//            }
    }
        
    ++_nPostMsgCallStackCounter;
    bool bContinue = true;
    while(!workingQue.empty())
    {
        auto& msg = workingQue.front();
		
		if (msg->pTargetListener)
		{// for specific listener
			msg->pTargetListener->onSCMessageProcess(msg);
		}
		else
		{// for all of listeners
			auto it = _listenerList.begin();
			for (; it != _listenerList.end() && bContinue; ++it)
			{
				SCASSERT((*it).pListener != nullptr);
				SC_CONTINUE_IF((*it).pListener == nullptr);
				bContinue = (*it).pListener->onSCMessageProcess(msg);
			}
		}
         
        if(bContinue)
        {
            _defaultProc.processMessage(msg);
        }
        workingQue.pop_front();
    }
        
    --_nPostMsgCallStackCounter;
        
    workingQue.clear();
}

NAMESPACE_SPEEDCC_END





