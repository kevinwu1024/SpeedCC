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

#ifndef __SPEEDCC__SCBINDER_H__
#define __SPEEDCC__SCBINDER_H__

#include "SCObject.h"
#include "SCBaseMacros.h"
#include "SCWatchNumberT.h"
#include "SCWatchString.h"

NAMESPACE_SPEEDCC_BEGIN

/*!
    SCBinder is base class binder for /a Watch /a Value (SCWatchNumberT or SCWatchString) binding specific functional class,
    such as UI Node, /a Watch /a Value.
     
    Must specify a source /a Watch /a Value for binding.
    */
class SCBinder : public SCObject
{
public:
    SC_AVOID_CLASS_COPY(SCBinder)
    SC_DEFINE_CLASS_PTR(SCBinder)
        
    /*!
        Create SCBinder instance in smart pointer.
        */
    SC_DEFINE_CREATE_FUNC_0(SCBinder)
        
    virtual ~SCBinder();
        
    /*!
        Set binder to new active state.
         
        /param bActive Active state as expect.
        */
    void setActive(const bool bActive);
        
    /*!
            Get binder current active state.
            By Default, active state is actived once instance created.
         
            /return Active state of currently.
        */
    inline bool getActive() const {return _bActive;}
        
    /*!
        Reset Binder to initial state.
        Active state to true, /a Watch /a Value to empty, removes /a Watch /a Value listen function.
        */
    virtual void reset();
        
    /*!
        Remove /a Watch /a Value listen function. Binding feature is not available once it is called.
        */
    void removeUpdateFunc();
        
protected:
    SCBinder():
    _bActive(true),
    _nFuncID(0)
    {}
        
    virtual void onActiveChanged(const bool bNewActive) {}
        
protected:
    SCObject::Ptr       _ptrWatch;      //!< Smart pointer to source Watch Value
    std::function<void(SCObject::Ptr ptr,const int nID)>   _removeUpdateFunc; //!< Source Watch Value
    int                     _nFuncID;
        
private:
    bool    _bActive;   //!<
};
    
    
/*!
    Binding a /a Watch /a Value.
     
    The source value will be casted to target value type statically.
     
    /tparam T1 Source /a Watch /a Value type.
    /tparam T2 Target /a Watch /a Value type.
    */
template<typename T1, typename T2,
typename = typename std::enable_if<SCIsWatchNumberIntegerT<typename T1::type>::value==1 &&
SCIsWatchNumberIntegerT<typename T2::type>::value==1,T1>::type>
class SCBinderWatchNumberT : public SCBinder
{
public:
    SC_AVOID_CLASS_COPY(SCBinderWatchNumberT)
    SC_DEFINE_CLASS_PTR(SCBinderWatchNumberT)
        
    /*!
        Create SCBinderWatchNumberT instance in smart pointer.
        */
    SC_DEFINE_CREATE_FUNC_2(SCBinderWatchNumberT,T1,T2)
        
    /*!
        Set source /a Watch /a Value.
         
        /param ptrWatch Source /a Watch /a Value.
        */
    void setWatch(T1 ptrWatch)
    {
        this->removeUpdateFunc();
        const int nID = ptrWatch->addUpdateFunc([this](T1 ptrNum,
                                                        typename T1::type newNum,
                                                        typename T1::type oldNum)
                                            {
                                                if(this->getActive() && _ptrTarget!=nullptr)
                                                {
                                                    (*_ptrTarget) = (typename T2::type::type)newNum;
                                                }
                                            });
            
        if(_ptrTarget!=nullptr && this->getActive())
        {
            (*_ptrTarget) = (typename T2::type::type)(*ptrWatch);
        }
            
        _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
        {
            SC_RETURN_V_IF(ptr==nullptr || nID<=0);
                
            auto p = ptr.cast<T1>();
            p->removeUpdateFunc(nID);
        };
            
        _ptrWatch = ptrWatch;
        _nFuncID = nID;
    }
        
    /*!
        Get source /a Watch /a Value
         
        /return Samrt pointer to source /a Watch /a Value
        */
    inline T1 getSourceWatch() const
    {
        return _ptrWatch==nullptr ? nullptr : _ptrWatch.cast<T1>();
    }
        
    /*!
        Get target /a Watch /a Value
         
        /return Target /a Watch /a Value
        */
    inline T2 getTargetWatch() const
    {
        return _ptrTarget;
    }
        
    /*!
        Set target /a Watch /a Value.
         
        /param ptrWatch Target /a Watch /a Value.
        */
    void setTargetWatch(typename T2::Ptr ptrWatch)
    {
        _ptrTarget = ptrWatch;
            
        if(_ptrTarget!=nullptr && _ptrWatch!=nullptr)
        {
            (*_ptrTarget) = (typename T2::type::type)(*(_ptrWatch.cast<T1>()));
        }
    }
        
    /*!
        Reset Binder to initial state.
        Active state to true, /a Watch /a Value to empty, removes /a Watch /a Value listen function.
         
        */
    virtual void reset() override
    {
        SCBinder::reset();
        _ptrTarget = nullptr;
    }
        
protected:
    SCBinderWatchNumberT(T1 ptrSrc, T2 ptrTarget)
    {
        _ptrTarget = ptrTarget;
        this->setWatch(ptrSrc);
    }
        
private:
    T2    _ptrTarget; //!< Target Watch Value to be updated
};
    
    
template<typename T1>
class SCBinderWatchNumberT<T1,SCWatchString::Ptr> : public SCBinder
{
public:
    SC_AVOID_CLASS_COPY(SCBinderWatchNumberT)
    SC_DEFINE_CLASS_PTR(SCBinderWatchNumberT)
        
    /*!
        Create SCBinderWatchNumberT instance in smart pointer.
        */
    SC_DEFINE_CREATE_FUNC_2(SCBinderWatchNumberT,T1,SCWatchString::Ptr)
        
    /*!
        Set source /a Watch /a Value.
         
        /param ptrWatch Source /a Watch /a Value.
        */
    void setWatch(T1 ptrWatch)
    {
        this->removeUpdateFunc();
        const int nID = ptrWatch->addUpdateFunc([this](T1 ptrNum,
                                                        typename T1::type::type newNum,
                                                        typename T1::type::type oldNum)
                                                {
                                                    if(this->getActive() && _ptrTarget!=nullptr)
                                                    {
                                                        (*_ptrTarget) = ptrNum->getString();
                                                    }
                                                });
            
        if(_ptrTarget!=nullptr && this->getActive())
        {
            (*_ptrTarget) = ptrWatch->getString();
        }
            
        _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
        {
            SC_RETURN_V_IF(ptr==nullptr || nID<=0);
                
            auto p = ptr.cast<T1>();
            p->removeUpdateFunc(nID);
        };
            
        _ptrWatch = ptrWatch;
        _nFuncID = nID;
    }
        
    /*!
        Get source /a Watch /a Value
         
        /return Samrt pointer to source /a Watch /a Value
        */
    inline T1 getSourceWatch() const
    {
        return _ptrWatch==nullptr ? nullptr : _ptrWatch.cast<T1>();
    }
        
    /*!
        Get target /a Watch /a Value
         
        /return Target /a Watch /a Value
        */
    inline SCWatchString::Ptr getTargetWatch() const
    {
        return _ptrTarget;
    }
        
    /*!
        Set target /a Watch /a Value.
         
        /param ptrWatch Target /a Watch /a Value.
        */
    void setTargetWatch(SCWatchString::Ptr ptrWatch)
    {
        _ptrTarget = ptrWatch;
            
        if(_ptrTarget!=nullptr && _ptrWatch!=nullptr)
        {
            (*_ptrTarget) = _ptrWatch.cast<T1>()->getString();
        }
    }
        
    /*!
        Reset Binder to initial state.
        Active state to true, /a Watch /a Value to empty, removes /a Watch /a Value listen function.
         
        */
    virtual void reset() override
    {
        SCBinder::reset();
        _ptrTarget = nullptr;
    }
        
protected:
    SCBinderWatchNumberT(T1 ptrSrc, SCWatchString::Ptr ptrTarget)
    {
        _ptrTarget = ptrTarget;
        this->setWatch(ptrSrc);
    }
        
private:
    SCWatchString::Ptr      _ptrTarget;
};
	
NAMESPACE_SPEEDCC_END

#endif //__SPEEDCC__SCBINDER_H__
