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

#include "SCBinderCocos.h"


NAMESPACE_SPEEDCC_BEGIN
    
///------------- SCBinderUILabel

SCBinderUILabel::~SCBinderUILabel()
{
}
    
void SCBinderUILabel::setLabel(cocos2d::Label* pLabel)
{
    _pLabel = pLabel;
    if(_pLabel!=nullptr && this->getActive())
    {
        _pLabel->setString(_strLast.c_str());
    }
}
    
void SCBinderUILabel::onActiveChanged(const bool bNewActive)
{
    if(bNewActive && _pLabel!=nullptr)
    {
        _pLabel->setString(_strLast.c_str());
    }
}
    
void SCBinderUILabel::setWatch(SCWatchString::Ptr watchStr)
{
    SCASSERT(watchStr!=nullptr);
        
    this->removeUpdateFunc();
        
    const int nID = watchStr->addUpdateFunc([this](SCWatchString::Ptr watchPtr,const SCString& strNew,const SCString& strOld)
                                            {
                                                if(_pLabel!=nullptr && this->getActive())
                                                {
                                                    _pLabel->setString(strNew.c_str());
                                                }
                                                _strLast = strNew;
                                            });
        
    if(_pLabel!=nullptr && this->getActive())
    {
        _pLabel->setString(watchStr->getValue().c_str());
    }
    else
    {
        _strLast = watchStr->getValue();
    }
        
    _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
    {
        SC_RETURN_V_IF(ptr==nullptr || nID<=0);
            
        auto p = ptr.cast<SCWatchString::Ptr>();
        p->removeUpdateFunc(nID);
    };
        
    _ptrWatch = watchStr;
    _nFuncID = nID;
}
    
void SCBinderUILabel::reset()
{
    SCBinder::reset();
    _pLabel = nullptr;
}
    
///----------------- SCBinderUISwitch
SCBinderUISwitch::SCBinderUISwitch()
:_pToggleMenuItem(nullptr)
,_callbackFunc(nullptr)
{
}
    
SCBinderUISwitch::SCBinderUISwitch(SCWatchBool::Ptr ptrWatch)
:_pToggleMenuItem(nullptr)
,_callbackFunc(nullptr)
{
    this->setWatch(ptrWatch);
}
    
SCBinderUISwitch::SCBinderUISwitch(SCWatchBool::Ptr ptrWatch,cocos2d::MenuItemToggle* pToggle)
:_callbackFunc(nullptr)
{
    this->setWatch(ptrWatch);
    this->setToggle(pToggle);
}
    
SCBinderUISwitch::SCBinderUISwitch(cocos2d::MenuItemToggle* pToggle)
:_callbackFunc(nullptr)
{
    this->setToggle(pToggle);
}
    
SCBinderUISwitch::~SCBinderUISwitch()
{
}
    
void SCBinderUISwitch::setWatch(SCWatchBool::Ptr ptrWatch)
{
    SCASSERT(ptrWatch!=nullptr);
        
    this->removeUpdateFunc();
        
    const int nID = ptrWatch->addUpdateFunc([this](SCWatchBool::Ptr ptrWatch,
                                                    const bool bNew,
                                                    const bool bOld)
                                            {
                                                this->updateValue2Toggle();
                                            });
        
    if(_pToggleMenuItem!=nullptr && this->getActive())
    {
        _pToggleMenuItem->setSelectedIndex(*(ptrWatch) ? 0 : 1);
    }
        
    _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
    {
        SC_RETURN_V_IF(ptr==nullptr || nID<=0);
            
        auto p = ptr.cast<SCWatchBool::Ptr>();
        SCASSERT(p!=nullptr);
        p->removeUpdateFunc(nID);
    };
        
    _ptrWatch = ptrWatch;
    _nFuncID = nID;
}
    
void SCBinderUISwitch::setToggle(cocos2d::MenuItemToggle* pToggle)
{
    SC_RETURN_V_IF(pToggle==nullptr);
        
    _pToggleMenuItem = pToggle;
    if(_pToggleMenuItem!=nullptr)
    {
        _pToggleMenuItem->setCallback(SC_MAKE_FUNC(onMenuItemClicked, this));
    }
        
    this->updateValue2Toggle();
}
    
void SCBinderUISwitch::reset()
{
    SCBinder::reset();
    _pToggleMenuItem = nullptr;
    _callbackFunc = nullptr;   
}
    
void SCBinderUISwitch::onActiveChanged(const bool bNewActive)
{
    this->updateValue2Toggle();
}
    
void SCBinderUISwitch::updateValue2Toggle()
{
    if(_ptrWatch!=nullptr && _pToggleMenuItem!=nullptr && this->getActive())
    {
        auto ptrWatch = _ptrWatch.cast<SCWatchBool::Ptr>();
        const int nIndex = (*(ptrWatch) ? 0 : 1);
            
        if(_pToggleMenuItem->getSelectedIndex()!=nIndex)
        {
            _pToggleMenuItem->setSelectedIndex(nIndex);
        }
    }
}
    
void SCBinderUISwitch::onMenuItemClicked(cocos2d::Ref* pSender)
{
    SC_RETURN_V_IF(_ptrWatch==nullptr);
    auto pToggle = dynamic_cast<cocos2d::MenuItemToggle*>(pSender);
    SCASSERT(pToggle!=nullptr);
    SC_RETURN_V_IF(pToggle==nullptr);
        
    auto ptrWatch = _ptrWatch.cast<SCWatchBool::Ptr>();
    (*ptrWatch) = (pToggle->getSelectedIndex()==0);
        
    if(_callbackFunc!=nullptr)
    {
        _callbackFunc(pSender);
    }
}
    
///----------------- SCBinderUIProgress
SCBinderUIProgress::~SCBinderUIProgress()
{
}
    
void SCBinderUIProgress::reset()
{
    SCBinder::reset();
        
    _pProgressTimer = nullptr;
    _getValueFunc = nullptr;
}
    
void SCBinderUIProgress::onActiveChanged(const bool bNewActive)
{
    if(bNewActive && _pProgressTimer!=nullptr && _getValueFunc!=nullptr && this->getActive())
    {
        _pProgressTimer->setPercentage((float)_getValueFunc(_ptrWatch));
    }
}
    
void SCBinderUIProgress::setProgressTimer(cocos2d::ProgressTimer* pProgress)
{
    SC_RETURN_V_IF(_pProgressTimer==pProgress);
    _pProgressTimer = pProgress;
        
    if(_pProgressTimer!=nullptr && _getValueFunc!=nullptr && this->getActive())
    {
        _pProgressTimer->setPercentage((float)_getValueFunc(_ptrWatch));
    }
}
    
///----------------- SCBinderUISlider
SCBinderUISlider::~SCBinderUISlider()
{
}
    
void SCBinderUISlider::reset()
{
    SCBinder::reset();
        
    _pSlider = nullptr;
    _getValueFunc = nullptr;
    _setValueFunc = nullptr;
}
    
void SCBinderUISlider::onActiveChanged(const bool bNewActive)
{
    if(bNewActive && _pSlider!=nullptr && _getValueFunc!=nullptr && this->getActive())
    {
        _pSlider->setPercent(_getValueFunc(_ptrWatch));
    }
}
    
void SCBinderUISlider::setSlider(cocos2d::ui::Slider* pSlider)
{
    SC_RETURN_V_IF(pSlider==_pSlider);
    _pSlider = pSlider;
        
    if(_pSlider!=nullptr && _getValueFunc!=nullptr && _setValueFunc!=nullptr && this->getActive())
    {
        _pSlider->setPercent(_getValueFunc(_ptrWatch));
        _pSlider->addEventListener([this](cocos2d::Ref*,cocos2d::ui::Slider::EventType type)
                                    {
                                        if(type==cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED
                                            && _setValueFunc!=nullptr)
                                        {
                                            _setValueFunc(_ptrWatch,_pSlider->getPercent());
                                        }
                                    });
    }
}

NAMESPACE_SPEEDCC_END
