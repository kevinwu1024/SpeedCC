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

#include "SCBehaviorCommon.h"
#include "../cocos/SCCocosDef.h"
#include "../system/SCSystem.h"

NAMESPACE_SPEEDCC_BEGIN

///----------- SCBehaviorCallFunc
    
void SCBehaviorCallFunc::execute(const SCDictionary& par)
{
    SC_RETURN_V_IF(!this->getActive());
    
    if(_startFunc!=nullptr)
    {
        _startFunc(par);
    }
    else if(_startFunc2!=nullptr)
    {
        _startFunc2();
    }
}
    
void SCBehaviorCallFunc::setOnStartFunc(const std::function<void(const SCDictionary& par)>& func)
{
    _startFunc = func;
    _startFunc2 = nullptr;
}
    
void SCBehaviorCallFunc::setOnStartFunc(const std::function<void()>& func)
{
    _startFunc2 = func;
    _startFunc = nullptr;
}
    
    
///----------- SCBehaviorMultiple
    
SCBehaviorMultiple::SCBehaviorMultiple(SCBehavior::Ptr ptrBvr)
{
    SCASSERT(ptrBvr!=nullptr);
    this->addBehavior(ptrBvr);
}
    
void SCBehaviorMultiple::execute(const SCDictionary& par)
{
    SC_RETURN_V_IF(!this->getActive());
    
    for(auto it : _behaviorList)
    {
        it->execute(par);
    }
}
    
void SCBehaviorMultiple::addBehavior(const SCBehavior::Ptr& ptrBvr)
{
    SC_RETURN_V_IF(ptrBvr==nullptr);
    _behaviorList.push_back(ptrBvr);
}
    
void SCBehaviorMultiple::removeBehavior(const int nID)
{
    SC_RETURN_V_IF(nID==0);
    _behaviorList.remove_if([nID](const SCBehavior::Ptr& ptrBvr)
                            {
                                return (ptrBvr->getID()==nID);
                            });
}
    
///------------- SCBehaviorDelayExecute
SCBehaviorDelayExecute::~SCBehaviorDelayExecute()
{
    SCCCScheduler()->unschedule(SCF(onDelayExecute), dynamic_cast<cocos2d::Ref*>(this));
}
    
void SCBehaviorDelayExecute::execute(const SCDictionary& par)
{
    SC_RETURN_V_IF(!this->getActive());
    
    if(!_bPost && _ptrBvr!=nullptr)
    {
        _bPost = true;
        SCCCScheduler()->schedule(SCF(onDelayExecute),dynamic_cast<cocos2d::Ref*>(this),_fDelay,false);
    }
}
    
void SCBehaviorDelayExecute::onDelayExecute(float fDelta)
{
	SCCCScheduler()->unschedule(SCF(onDelayExecute), dynamic_cast<cocos2d::Ref*>(this));
    _bPost = false;
    if(_ptrBvr!=nullptr)
    {
        _ptrBvr->execute();
    }
}
    
bool SCBehaviorDelayExecute::setBehavior(SCBehavior::Ptr ptrBvr)
{
    SC_RETURN_IF(_bPost, false);
    _ptrBvr = ptrBvr;
    return true;
}
    
bool SCBehaviorDelayExecute::setDelayTime(const float fDelay)
{
    SC_RETURN_IF(_bPost, false);
    _fDelay = fDelay;
    _fDelay = _fDelay<0 ? 0 : _fDelay;
    return true;
}
    
///------------ SCBehaviorBoolInvert
SCBehaviorBoolInvert::SCBehaviorBoolInvert()
{
    _ptrWatch = SCWatchBool::create();
}
    
SCBehaviorBoolInvert::SCBehaviorBoolInvert(const bool bInit)
{
    _ptrWatch = SCWatchBool::create();
    (*_ptrWatch) = bInit;
}
    
SCBehaviorBoolInvert::SCBehaviorBoolInvert(SCWatchBool::Ptr ptrWatch):
_ptrWatch(ptrWatch)
{
}
    
void SCBehaviorBoolInvert::execute(const SCDictionary& par)
{
    SC_RETURN_V_IF(!this->getActive());
    
    if(_ptrWatch!=nullptr)
    {
        (*_ptrWatch) = !(*_ptrWatch);
    }
}

///------------ SCBehaviorLog
SCBehaviorLog::SCBehaviorLog()
:_bRelease(false)
{
}

SCBehaviorLog::SCBehaviorLog(const SCString strLog)
: _bRelease(false)
, _strText(strLog)
{
}

SCBehaviorLog::SCBehaviorLog(const SCString strLog, const bool bReleaseLog)
: _bRelease(bReleaseLog)
, _strText(strLog)
{
}

void SCBehaviorLog::setText(const SCString strText)
{
	_strText = strText;
}

void SCBehaviorLog::setReleaseLog(const bool bRelease)
{
	_bRelease = bRelease;
}

void SCBehaviorLog::execute(const SCDictionary& par)
{
	SC_RETURN_V_IF(!this->getActive());

	if (_bRelease)
	{
		SCLogR(_strText);
	}
	else
	{
		SCLog(_strText);
	}
}

NAMESPACE_SPEEDCC_END


