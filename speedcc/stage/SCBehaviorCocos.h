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

#ifndef __SPEEDCC__SCBEHAVIORCOCOS_H__
#define __SPEEDCC__SCBEHAVIORCOCOS_H__

#include "SCPlayObject.h"
#include "../cocos/SCViewNavigator.h"
#include "SCBehaviorCommon.h"
#include "../system/SCStore.h"

NAMESPACE_SPEEDCC_BEGIN

///----------- SCBehaviorViewGoto
class SCBehaviorViewGoto : public SCBehavior
{
public:
	SC_AVOID_CLASS_COPY(SCBehaviorViewGoto)
    SC_DEFINE_CLASS_PTR(SCBehaviorViewGoto)

	virtual ~SCBehaviorViewGoto();
    template<typename SceneT, typename TransT = SCClassNull, typename LoadingT = SCClassNull>
    static Ptr create(const SCViewNavigator::ESceneSwitchType place = SCViewNavigator::kSceneReplace,
                        const SCDictionary& dic = SCDictionary())
    {
        SCViewNavigator::SSceneSwitchInfo swi;
        swi.setUp<SceneT,TransT,LoadingT>(place);
            
        SCBehaviorViewGoto::Ptr ptrRet;
        ptrRet.createInstanceWithCon([swi,dic](void* pData)
                                        {
                                            new(pData)SCBehaviorViewGoto(swi,dic);
                                        });
            
        return ptrRet;
    }
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
    void setSceneParameter(const SCDictionary& dic);
    inline void setDirect(const bool bDirect) { _bDirect = bDirect; }
    inline bool getDirect() const { return _bDirect; }
        
protected:
    SCBehaviorViewGoto(const SCViewNavigator::SSceneSwitchInfo& swi,const SCDictionary& dic);
        
    void onBvrFunc();
private:
    SCBehaviorDelayExecute::Ptr             _ptrDelayBvr;
    SCViewNavigator::SSceneSwitchInfo      _switch;
    SCDictionary                            _parameterDic;
    bool                                    _bDirect;
};
    
///-------------- SCBehaviorViewBack
class SCBehaviorViewBack : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorViewBack)
    SC_DEFINE_CLASS_PTR(SCBehaviorViewBack)
        
    SC_DEFINE_CREATE_FUNC_0(SCBehaviorViewBack)
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorViewBack,const int)
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
    inline void setDirect(const bool bDirect) { _bDirect = bDirect; }
    inline bool getDirect() const { return _bDirect; }
        
protected:
    SCBehaviorViewBack()
    :_nSceneNum(1)
    ,_bDirect(false)
    {
    }
        
    SCBehaviorViewBack(const int nSceneNum)
    :_nSceneNum(nSceneNum)
    ,_bDirect(false)
    {
    }
        
    void onBvrFunc();
private:
    SCBehaviorDelayExecute::Ptr     _ptrDelayBvr;
    int                             _nSceneNum;
    bool                            _bDirect;
};
    
    
///------------ SCBehaviorAlertBoxSelectedx
class SCViewController;
class SCBehaviorAlertBoxSelected : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorAlertBoxSelected)
    SC_DEFINE_CLASS_PTR(SCBehaviorAlertBoxSelected)
        
    SC_DEFINE_CREATE_FUNC_0(SCBehaviorAlertBoxSelected)
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorAlertBoxSelected,SCViewController*,const int)
        
    void setController(SCViewController* pController);
    void setSelectedIndex(const int nSelectedIndex);
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
protected:
    SCBehaviorAlertBoxSelected();
    SCBehaviorAlertBoxSelected(SCViewController* pController,const int nSelected);
        
private:
    SCViewController*      _pController;
    int                     _nSelected;
};
    

///----------- SCBehaviorShowLog
class SCBehaviorShowLog : public SCBehavior
{
public:
	SC_AVOID_CLASS_COPY(SCBehaviorShowLog)
	SC_DEFINE_CLASS_PTR(SCBehaviorShowLog)

	SC_DEFINE_CREATE_FUNC_0(SCBehaviorShowLog)

	virtual ~SCBehaviorShowLog();
	virtual void execute(const SCDictionary& par = SCDictionary()) override;

protected:
	SCBehaviorShowLog();
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCBEHAVIORCOCOS_H__
