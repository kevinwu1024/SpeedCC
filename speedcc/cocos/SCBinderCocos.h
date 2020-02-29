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

#ifndef __SPEEDCC__SCBINDERCOCOS_H__
#define __SPEEDCC__SCBINDERCOCOS_H__

#include "cocos2d.h"

#include "../base/SCString.h"
#include "../base/SCWatchString.h"
#include "../base/SCBinder.h"

#include "ui/CocosGUI.h"

NAMESPACE_SPEEDCC_BEGIN

///-------------- SCBinderUILabel
class SCBinderUILabel : public SCBinder
{
public:
    SC_AVOID_CLASS_COPY(SCBinderUILabel)
    SC_DEFINE_CLASS_PTR(SCBinderUILabel)
        
    SC_DEFINE_CREATE_FUNC_0(SCBinderUILabel)
    SC_DEFINE_CREATE_FUNC_1(SCBinderUILabel,cocos2d::Label*)
        
    virtual ~SCBinderUILabel();
        
    inline cocos2d::Label* getLabel() const { return _pLabel; }
    void setLabel(cocos2d::Label* pLabel);
        
    template<typename T,
    typename = typename std::enable_if<SCIsWatchNumberableT<typename T::type>::value==1,T>::type >
    void setWatch(T num)
    {
        this->removeUpdateFunc();
            
        const int nID = num->addUpdateFunc([this](T ptrNum,typename T::type newNum,typename T::type oldNum)
                                            {
                                                if(_pLabel!=nullptr && this->getActive())
                                                {
                                                    _pLabel->setString(ptrNum->getString().c_str());
                                                }
                                                _strLast = ptrNum->getString();
                                            });
            
        if(_pLabel!=nullptr && this->getActive())
        {
            _pLabel->setString(num->getString().c_str());
        }
        else
        {
            _strLast = num->getString();
        }
            
        _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
        {
            SC_RETURN_V_IF(ptr==nullptr || nID<=0);
                
            auto p = ptr.cast<T>();
            p->removeUpdateFunc(nID);
        };
            
        _ptrWatch = num;
        _nFuncID = nID;
    }
        
    void setWatch(SCWatchString::Ptr watchStr);
    virtual void reset() override;
        
protected:
    SCBinderUILabel()
    :_pLabel(nullptr)
    {}
        
    SCBinderUILabel(cocos2d::Label* pLabel)
    :_pLabel(pLabel)
    {}
        
    virtual void onActiveChanged(const bool bNewActive) override;

private:
    cocos2d::Label*     _pLabel;
    SCString            _strLast;
};
    
    
///--------------- SCBinderUIToggle
class SCBinderUISwitch : public SCBinder
{
public:
    virtual ~SCBinderUISwitch();
        
    SC_AVOID_CLASS_COPY(SCBinderUISwitch)
    SC_DEFINE_CLASS_PTR(SCBinderUISwitch)
        
    SC_DEFINE_CREATE_FUNC_0(SCBinderUISwitch)
    SC_DEFINE_CREATE_FUNC_1(SCBinderUISwitch,SCWatchBool::Ptr)
    SC_DEFINE_CREATE_FUNC_1(SCBinderUISwitch,cocos2d::MenuItemToggle*)
    SC_DEFINE_CREATE_FUNC_2(SCBinderUISwitch,SCWatchBool::Ptr,cocos2d::MenuItemToggle*)
        
    void setWatch(SCWatchBool::Ptr ptrWatch);
    void setCallback(const std::function<void(cocos2d::Ref*)>& func) { _callbackFunc = func;}
        
    inline cocos2d::MenuItemToggle* getToggle() const { return _pToggleMenuItem; }
    void setToggle(cocos2d::MenuItemToggle* pToggle);
        
    inline SCWatchBool::Ptr getWatch() const { return _ptrWatch.cast<SCWatchBool::Ptr>(); }
    virtual void reset() override;
        
protected:
    SCBinderUISwitch();
    SCBinderUISwitch(SCWatchBool::Ptr ptrWatch);
    SCBinderUISwitch(SCWatchBool::Ptr ptrWatch,cocos2d::MenuItemToggle* pToggle);
    SCBinderUISwitch(cocos2d::MenuItemToggle* pToggle);
        
    virtual void onActiveChanged(const bool bNewActive) override;
        
    void updateValue2Toggle();
    void onMenuItemClicked(cocos2d::Ref* pSender);
        
private:
    cocos2d::MenuItemToggle*                _pToggleMenuItem;
    std::function<void(cocos2d::Ref*)>      _callbackFunc;
};
    
///--------------- SCBinderUIProgress
class SCBinderUIProgress : public SCBinder
{
public:
    virtual ~SCBinderUIProgress();
        
    SC_AVOID_CLASS_COPY(SCBinderUIProgress)
    SC_DEFINE_CLASS_PTR(SCBinderUIProgress)
        
    SC_DEFINE_CREATE_FUNC_0(SCBinderUIProgress)
        
    template<typename T,
    typename = typename std::enable_if<SCIsWatchNumberableT<typename T::type>::value==1,T>::type >
    void setWatch(T num)
    {
        this->removeUpdateFunc();
        const int nID = num->addUpdateFunc([this](T ptrNum,typename T::type newNum,typename T::type oldNum)
                                            {
                                                if(_pProgressTimer!=nullptr && this->getActive())
                                                {
                                                    _pProgressTimer->setPercentage((*ptrNum));
                                                }
                                            });
            
        if(_pProgressTimer!=nullptr && this->getActive())
        {
            _pProgressTimer->setPercentage((*num));
        }
            
        _getValueFunc = [](SCObject::Ptr ptr) -> int
        {
            auto p = ptr.cast<T>();
            return (int)(*p);
        };
            
        _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
        {
            SC_RETURN_V_IF(ptr==nullptr || nID<=0);
                
            auto p = ptr.cast<T>();
            p->removeUpdateFunc(nID);
        };
            
        _ptrWatch = num;
        _nFuncID = nID;
    }
        
    void setProgressTimer(cocos2d::ProgressTimer* pProgress);
    virtual void reset() override;
        
protected:
    SCBinderUIProgress()
    :_pProgressTimer(nullptr)
    {}
        
    virtual void onActiveChanged(const bool bNewActive) override;
        
private:
    cocos2d::ProgressTimer*                 _pProgressTimer;
    std::function<int(SCObject::Ptr ptr)>   _getValueFunc;
};
    
///--------------- SCBinderUISlider
class SCBinderUISlider : public SCBinder
{
public:
    virtual ~SCBinderUISlider();
        
    SC_AVOID_CLASS_COPY(SCBinderUISlider)
    SC_DEFINE_CLASS_PTR(SCBinderUISlider)
        
    SC_DEFINE_CREATE_FUNC_0(SCBinderUISlider)
        
    template<typename T,
    typename = typename std::enable_if<SCIsWatchNumberableT<typename T::type>::value==1,T>::type >
    void setWatch(T num)
    {
        this->removeUpdateFunc();
        const int nID = num->addUpdateFunc([this](T ptrNum,typename T::type newNum,typename T::type oldNum)
                                            {
                                                if(_pSlider!=nullptr && this->getActive())
                                                {
                                                    _pSlider->setPercent((*ptrNum));
                                                }
                                            });
            
        if(_pSlider!=nullptr && this->getActive())
        {
            _pSlider->setPercent((*num));
            _pSlider->addEventListener([this](cocos2d::Ref*,cocos2d::ui::Slider::EventType type)
                                        {
                                            if(type==cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED
                                                && _setValueFunc!=nullptr)
                                            {
                                                _setValueFunc(_ptrWatch,_pSlider->getPercent());
                                            }
                                        });
        }
            
        _getValueFunc = [](SCObject::Ptr ptr) -> int
        {
            auto p = ptr.cast<T>();
            return (int)(*p);
        };
            
        _setValueFunc = [](SCObject::Ptr ptr,int value)
        {
            auto p = ptr.cast<T>();
            (*p) = (typename T::type)value;
        };
            
        _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
        {
            SC_RETURN_V_IF(ptr==nullptr || nID<=0);
                
            auto p = ptr.cast<T>();
            p->removeUpdateFunc(nID);
        };
            
        _ptrWatch = num;
        _nFuncID = nID;
    }
        
    void setSlider(cocos2d::ui::Slider* pSlider);
    virtual void reset() override;
        
protected:
    SCBinderUISlider()
    :_pSlider(nullptr)
    {}
        
    virtual void onActiveChanged(const bool bNewActive) override;
        
private:
    cocos2d::ui::Slider*                        _pSlider;
    std::function<int(SCObject::Ptr ptr)>       _getValueFunc;
    std::function<void(SCObject::Ptr ptr,int)>  _setValueFunc;
};

NAMESPACE_SPEEDCC_END

#endif //__SPEEDCC__SCBINDERCOCOS_H__
