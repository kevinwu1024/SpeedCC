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

#ifndef __SPEEDCC__SCBEHAVIORCOMMON_H__
#define __SPEEDCC__SCBEHAVIORCOMMON_H__

#include "cocos2d.h"
#include "SCPlayObject.h"
#include "../base/SCWatchNumberT.h"

NAMESPACE_SPEEDCC_BEGIN

///-------------- SCBehaviorNull
class SCBehaviorNull : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorNull)
    SC_DEFINE_CLASS_PTR(SCBehaviorNull)
        
    SC_DEFINE_CREATE_FUNC_0(SCBehaviorNull)
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override {}
        
protected:
    SCBehaviorNull(){}
};
    
///-------------- SCBehaviroCallFunc
class SCBehaviorCallFunc : public SCBehavior
{
protected:
    SCBehaviorCallFunc()
    {}
        
    SCBehaviorCallFunc(const std::function<void(const SCDictionary& par)>& startFunc)
    {
        this->setOnStartFunc(startFunc);
    }
        
    SCBehaviorCallFunc(const std::function<void()>& startFunc)
    {
        this->setOnStartFunc(startFunc);
    }
        
public:
    SC_AVOID_CLASS_COPY(SCBehaviorCallFunc)
    SC_DEFINE_CLASS_PTR(SCBehaviorCallFunc)
        
    SC_DEFINE_CREATE_FUNC_0(SCBehaviorCallFunc)
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorCallFunc,const std::function<void(const SCDictionary& par)>&)
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorCallFunc,const std::function<void()>&)
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
    void setOnStartFunc(const std::function<void(const SCDictionary& par)>& func);
    void setOnStartFunc(const std::function<void()>& func);
        
private:
    std::function<void(const SCDictionary& par)>  _startFunc;
    std::function<void()>  _startFunc2;
};
    
///-------------- SCBehaviorMultiple
class SCBehaviorMultiple : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorMultiple)
    SC_DEFINE_CLASS_PTR(SCBehaviorMultiple)
        
    SC_DEFINE_CREATE_FUNC_0(SCBehaviorMultiple)
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorMultiple,SCBehavior::Ptr)
        
    template<typename ...Ts>
    static Ptr create(SCBehavior::Ptr ptrBvr1,SCBehavior::Ptr ptrBvr2,Ts... ts)
    {
        SCASSERT(ptrBvr1!=nullptr);
        SCASSERT(ptrBvr2!=nullptr);
        auto ptr2 = SCBehaviorMultiple::create(ptrBvr2,ts...);
            
        auto ptrRet = SCBehaviorMultiple::create();
            
        ptrRet->_behaviorList.push_back(ptrBvr1);
        for(auto it : ptr2->_behaviorList)
        {
            ptrRet->_behaviorList.push_back(it);
        }
            
        return ptrRet;
    }
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
    void addBehavior(const SCBehavior::Ptr& ptrBvr);
    void removeBehavior(const int nID);
        
protected:
    SCBehaviorMultiple()
    {}
        
    SCBehaviorMultiple(SCBehavior::Ptr ptrBvr);
        
private:
    std::list<SCBehavior::Ptr> _behaviorList;
};
    
///------------- SCBehaviorDelayExecute
class SCBehaviorDelayExecute :
public cocos2d::Ref,
public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorDelayExecute)
    SC_DEFINE_CLASS_PTR(SCBehaviorDelayExecute)
        
    virtual ~SCBehaviorDelayExecute();
        
    SC_DEFINE_CREATE_FUNC_0(SCBehaviorDelayExecute)
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorDelayExecute,const float,SCBehavior::Ptr)
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
    bool setBehavior(SCBehavior::Ptr ptrBvr);
    bool setDelayTime(const float fDelay);
    inline bool isRunning() const { return _bPost; }
        
protected:
    SCBehaviorDelayExecute()
    :_fDelay(0)
    ,_bPost(false)
    {}
        
    SCBehaviorDelayExecute(const float fDelay,SCBehavior::Ptr ptrBvr)
    :_fDelay(fDelay)
    ,_ptrBvr(ptrBvr)
    ,_bPost(false)
    {}
        
    void onDelayExecute(float fDelta);
        
private:
    bool                _bPost;
    float               _fDelay;
    SCBehavior::Ptr     _ptrBvr;
};
    
///--------------- SCBehaviorCaseT
template<typename T>
class SCBehaviorCaseT : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorCaseT)
    SC_DEFINE_CLASS_PTR(SCBehaviorCaseT)
        
    SC_DEFINE_CREATE_FUNC_0(SCBehaviorCaseT)
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorCaseT,typename T::Ptr)
        
    void setCase(const typename T::type value, SCBehavior::Ptr ptrBvr)
    {
        _watchValue2BvrMap[value] = ptrBvr;
    }
        
    inline typename T::Ptr getWatch() const {return _ptrWatch;}
    inline int getCaseCount() const { return (int)_watchValue2BvrMap.size();}
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override
    {
        auto it = _watchValue2BvrMap.find((*_ptrWatch));
        if(it!=_watchValue2BvrMap.end())
        {
            (*it).second->execute(par);
        }
    }
        
protected:
    SCBehaviorCaseT()
    {
        _ptrWatch = T::create();
    }
        
    SCBehaviorCaseT(typename T::Ptr ptrWatch):
    _ptrWatch(ptrWatch)
    {
    }
        
private:
    typename T::Ptr     _ptrWatch;
    std::map<typename T::type, SCBehavior::Ptr>     _watchValue2BvrMap;
};
    
typedef SCBehaviorCaseT<SCWatchUInt>                SCBehaviorCaseUInt;
typedef SCBehaviorCaseT<SCWatchFloat>               SCBehaviorCaseFloat;
typedef SCBehaviorCaseT<SCWatchDouble>              SCBehaviorCaseDouble;
typedef SCBehaviorCaseT<SCWatchInt>                 SCBehaviorCaseInt;
typedef SCBehaviorCaseT<SCWatchLong>                SCBehaviorCaseLong;
typedef SCBehaviorCaseT<SCWatchULong>               SCBehaviorCaseULong;
typedef SCBehaviorCaseT<SCWatchByte>                SCBehaviorCaseByte;
typedef SCBehaviorCaseT<SCWatchBool>                SCBehaviorCaseBool;
typedef SCBehaviorCaseT<SCWatchString>              SCBehaviorCaseString;
    
    
///------------ SCBehaviorAddNumberT
template<typename T>
class SCBehaviorAddNumberT : public SCBehavior
{
private:
    typedef typename T::type    NumberType_t;
    typedef typename T::Ptr     PtrType_t;
        
public:
    SC_AVOID_CLASS_COPY(SCBehaviorAddNumberT)
    SC_DEFINE_CLASS_PTR(SCBehaviorAddNumberT)
        
    SC_DEFINE_CREATE_FUNC_0(SCBehaviorAddNumberT)
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorAddNumberT,const NumberType_t)
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorAddNumberT,PtrType_t)
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorAddNumberT,PtrType_t,const NumberType_t)
        
    inline SCWatchInt::Ptr getWatch() const { return _ptrWatch; }
    void setWatch(SCWatchInt::Ptr ptrWatch) { _ptrWatch = ptrWatch;}
        
    inline NumberType_t getStep() const {return _step;}
    void setStep(const NumberType_t step) { _step = step;}
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override
    {
        if(_ptrWatch!=nullptr && _step!=0)
        {
            (*_ptrWatch) += _step;
        }
    }
        
protected:
    SCBehaviorAddNumberT()
    :_step((NumberType_t)0)
    {
        _ptrWatch = T::create();
    }
        
    SCBehaviorAddNumberT(const NumberType_t step)
    :_step(step)
    {
        _ptrWatch = T::create();
    }
        
    SCBehaviorAddNumberT(PtrType_t ptrWatch)
    :_step(0)
    ,_ptrWatch(ptrWatch)
    {
    }
        
    SCBehaviorAddNumberT(PtrType_t ptrWatch,const NumberType_t step)
    :_step(step)
    ,_ptrWatch(ptrWatch)
    {
    }
        
private:
    NumberType_t        _step;
    typename T::Ptr     _ptrWatch;
};
    
typedef SCBehaviorAddNumberT<SCWatchUInt>                SCBehaviorAddUInt;
typedef SCBehaviorAddNumberT<SCWatchFloat>               SCBehaviorAddFloat;
typedef SCBehaviorAddNumberT<SCWatchDouble>              SCBehaviorAddDouble;
typedef SCBehaviorAddNumberT<SCWatchInt>                 SCBehaviorAddInt;
typedef SCBehaviorAddNumberT<SCWatchLong>                SCBehaviorAddLong;
typedef SCBehaviorAddNumberT<SCWatchULong>               SCBehaviorAddULong;
typedef SCBehaviorAddNumberT<SCWatchByte>                SCBehaviorAddByte;
typedef SCBehaviorAddNumberT<SCWatchString>              SCBehaviorAddString;
    
///------------ SCBehaviorBoolInvert
class SCBehaviorBoolInvert : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorBoolInvert)
    SC_DEFINE_CLASS_PTR(SCBehaviorBoolInvert)
        
    SC_DEFINE_CREATE_FUNC_0(SCBehaviorBoolInvert)
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorBoolInvert,const bool)
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorBoolInvert,SCWatchBool::Ptr)
        
    inline SCWatchBool::Ptr getWatch() const { return _ptrWatch; }
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
protected:
    SCBehaviorBoolInvert();
    SCBehaviorBoolInvert(const bool bInit);
    SCBehaviorBoolInvert(SCWatchBool::Ptr ptrWatch);
        
private:
    SCWatchBool::Ptr        _ptrWatch;
};

///------------ SCBehaviorLog
class SCBehaviorLog : public SCBehavior
{
public:
	SC_AVOID_CLASS_COPY(SCBehaviorLog)
	SC_DEFINE_CLASS_PTR(SCBehaviorLog)

	SC_DEFINE_CREATE_FUNC_1(SCBehaviorLog, const SCString)
	SC_DEFINE_CREATE_FUNC_2(SCBehaviorLog, const SCString,const bool)

	virtual void execute(const SCDictionary& par = SCDictionary()) override;

	void setText(const SCString strText);
	void setReleaseLog(const bool bRelease);

	inline SCString getText() const { return _strText; }
	inline bool getIsReleaseLog() const { return _bRelease; }

protected:
	SCBehaviorLog();
	SCBehaviorLog(const SCString strLog);
	SCBehaviorLog(const SCString strLog,const bool bReleaseLog);

private:
	SCString	_strText;
	bool		_bRelease;
};
    
NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCBEHAVIORCOMMON_H__
