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

#include "SCBehaviorCocos.h"
#include "../cocos/SCViewController.h"
#include "../cocos/SCViewControllerLog.h"
#include "../system/SCSystem.h"

NAMESPACE_SPEEDCC_BEGIN

///--------------- SCBehaviorViewGoto
SCBehaviorViewGoto::~SCBehaviorViewGoto()
{
}

SCBehaviorViewGoto::SCBehaviorViewGoto(const SCViewNavigator::SSceneSwitchInfo& swi,const SCDictionary& dic)
:_switch(swi)
,_parameterDic(dic)
,_bDirect(false)
{
}

void SCBehaviorViewGoto::execute(const SCDictionary& par)
{
    SC_RETURN_V_IF(!this->getActive());
    
    if(_bDirect)
    {
        this->onBvrFunc();
    }
    else if(_ptrDelayBvr==nullptr)
    {
        auto ptr = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrFunc, this));
        _ptrDelayBvr = SCBehaviorDelayExecute::create(0, ptr);
        _ptrDelayBvr->addObject(this->makeObjPtr(this)); // keep this instance alive
        _ptrDelayBvr->execute(par);
    }
}
    
void SCBehaviorViewGoto::setSceneParameter(const SCDictionary& dic)
{
    _parameterDic = dic;
}
    
void SCBehaviorViewGoto::onBvrFunc()
{
    SCViewNav()->setSceneParameter(_parameterDic);
    SCViewNav()->gotoView(_switch);
    _ptrDelayBvr->frameRetain(); // instance keep alive in current frame
    _ptrDelayBvr = nullptr;
}
    
///--------------- SCBehaviorViewBack
void SCBehaviorViewBack::execute(const SCDictionary& par)
{
    SC_RETURN_V_IF(!this->getActive());
    
    if(_bDirect)
    {
        this->onBvrFunc();
    }
    else if(_ptrDelayBvr==nullptr)
    {
        auto ptr = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrFunc, this));
        _ptrDelayBvr = SCBehaviorDelayExecute::create(0, ptr);
        _ptrDelayBvr->addObject(this->makeObjPtr(this));
        _ptrDelayBvr->execute(par);
    }
}
    
void SCBehaviorViewBack::onBvrFunc()
{
    SCViewNavigator::getInstance()->back(_nSceneNum);
    _ptrDelayBvr->frameRetain(); // instance keep alive in current frame
    _ptrDelayBvr = nullptr;
}
    
///--------------- SCBehaviorAlertBoxSelected
SCBehaviorAlertBoxSelected::SCBehaviorAlertBoxSelected()
:_pController(nullptr)
,_nSelected(0)
{
}
    
SCBehaviorAlertBoxSelected::SCBehaviorAlertBoxSelected(SCViewController* pController,const int nSelected)
:_pController(pController)
,_nSelected(nSelected)
{
}
    
void SCBehaviorAlertBoxSelected::setController(SCViewController* pController)
{
    _pController = pController;
}
    
void SCBehaviorAlertBoxSelected::setSelectedIndex(const int nSelectedIndex)
{
    _nSelected = nSelectedIndex;
}
    
void SCBehaviorAlertBoxSelected::execute(const SCDictionary& par)
{
    SC_RETURN_V_IF(!this->getActive());
    
    if(_pController!=nullptr)
    {
        SCBehaviorViewBack::create()->execute();
        _pController->finish(SC_NUM_2_PVOID(_nSelected));
    }
}
    
///----------- SCBehaviorShowLog
SCBehaviorShowLog::SCBehaviorShowLog()
{
}

SCBehaviorShowLog::~SCBehaviorShowLog()
{
}

void SCBehaviorShowLog::execute(const SCDictionary& par)
{
    SC_RETURN_V_IF(!this->getActive());
    
	SCBehaviorViewGoto::create<SCViewControllerLog>(SCViewNavigator::kLayerModal)->execute();
}

NAMESPACE_SPEEDCC_END
