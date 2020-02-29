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

#ifndef __SPEEDCC__SCSTRATEGY_H__
#define __SPEEDCC__SCSTRATEGY_H__

#include "SCMessage.h"
#include "SCBehaviorCommon.h"
#include "SCFSMRunner.h"


NAMESPACE_SPEEDCC_BEGIN


#define SC_STRATEGY_COMMON_DEF(_class_) \
public:\
	SC_DEFINE_CREATE_FUNC_1(_class_, SpeedCC::SCStage*) \
	SC_DEFINE_CREATE_FUNC_2(_class_, SpeedCC::SCStage*, const int) \
protected:\
	_class_(SpeedCC::SCStage* pStage,int nID):SpeedCC::SCStrategy(pStage,nID) { this->onInit(); } \
	_class_(SpeedCC::SCStage* pStage):SpeedCC::SCStrategy(pStage) { this->onInit(); } \
private:\

class SCStage;
    
class SCStrategy : public SCPlayObject
{
public:
    SC_AVOID_CLASS_COPY(SCStrategy)
    SC_DEFINE_CLASS_PTR(SCStrategy)
        
    virtual bool onUpdate(SCStage* pStage,SCMessage::Ptr ptrMsg) { return true;}
    
    SCStage* getStage() const { return _pStage; }
    
protected:
	SCStrategy(SCStage* pStage);
	SCStrategy(SCStage* pStage, int nID);
	virtual void onInit() {}

	void onActiveChanged(const bool bNewActive);

private:
	static int                          _nAutoIDCounter;
    SCStage*        _pStage;
};
    
///-------------- SCStrategyFunc
class SCStrategyFunc : public SCStrategy
{
public:
    SC_AVOID_CLASS_COPY(SCStrategyFunc)
    SC_DEFINE_CLASS_PTR(SCStrategyFunc)
        
    SC_DEFINE_CREATE_FUNC_3(SCStrategyFunc,SCStage*,const std::function<void(SCStage* pStage,SCMessage::Ptr ptrMsg)>&,const int)
    SC_DEFINE_CREATE_FUNC_2(SCStrategyFunc,SCStage*,const std::function<void(SCStage* pStage,SCMessage::Ptr ptrMsg)>&)
        
    virtual bool onUpdate(SCStage* pStage,SCMessage::Ptr ptrMsg) override;
protected:
    SCStrategyFunc(SCStage* pStage,const std::function<void(SCStage* pStage,SCMessage::Ptr ptrMsg)>& func,const int nID)
    :SCStrategy(pStage,nID)
    ,_func(func)
    {}
    
    SCStrategyFunc(SCStage* pStage,const std::function<void(SCStage* pStage,SCMessage::Ptr ptrMsg)>& func)
    :SCStrategy(pStage)
    ,_func(func)
    {}
    
private:
    std::function<void(SCStage* pStage,SCMessage::Ptr ptrMsg)>  _func;
};


///-------------- SCStrategyFSM
class SCStrategyFSM : public SCStrategy
{
public:
    SC_AVOID_CLASS_COPY(SCStrategyFSM)
    SC_DEFINE_CLASS_PTR(SCStrategyFSM)
    
    SC_DEFINE_CREATE_FUNC_4(SCStrategyFSM,SCStage*,SCFSMRunner::Ptr,const int,const int)
    SC_DEFINE_CREATE_FUNC_3(SCStrategyFSM,SCStage*,SCFSMRunner::Ptr,const int)
    
    virtual bool onUpdate(SCStage* pStage,SCMessage::Ptr ptrMsg) override;
protected:
    SCStrategyFSM(SCStage* pStage,SCFSMRunner::Ptr ptrRunner,const int nActorID,const int nID)
    :SCStrategy(pStage,nID)
    ,_nActorID(nActorID)
    ,_ptrFSMRunner(ptrRunner)
    {
        SCASSERT(_ptrFSMRunner != nullptr);
    }
    
    SCStrategyFSM(SCStage* pStage,SCFSMRunner::Ptr ptrRunner,const int nActorID)
    :SCStrategy(pStage)
    ,_nActorID(nActorID)
    ,_ptrFSMRunner(ptrRunner)
    {
        SCASSERT(_ptrFSMRunner != nullptr);
    }
    
private:
    SCFSMRunner::Ptr    _ptrFSMRunner;
    int                 _nActorID;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCSTRATEGY_H__
