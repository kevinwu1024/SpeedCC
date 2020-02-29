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


#ifndef __SPEEDCC__SCOBJPTRT_H__
#define __SPEEDCC__SCOBJPTRT_H__

#include "SCObjRefT.h"
#include "SCBaseMacros.h"

NAMESPACE_SPEEDCC_BEGIN

///----------- strong smart pointer
template<typename TargetT,bool IsStrong=true>
class SCObjPtrT : public SCObjRefT<TargetT>
{
    template<typename,bool> friend class SCObjPtrT;
protected:
    virtual void onInstanceCreated(void* pData)
    {
        this->getStub()->setObjPtrData(pData);
    }
    
    virtual void setCastFromOriginObjectFunc(funCastFromOriginObject_t p)
    {
        this->getStub()->setCastFromOriginObjectFunc(p);
    }
public:
    typedef TargetT type;
        
    SCObjPtrT()
    :_pCurInstance(nullptr)
    {}
    
    SCObjPtrT(std::nullptr_t p)
    :_pCurInstance(nullptr)
    {}
    
    explicit SCObjPtrT(void* p)
    :_pCurInstance(nullptr)
    {
        if(p!=nullptr)
        {
            this->_pObjData = p;
            _pCurInstance = p;
            this->increaseRef();
        }
    }
    
    explicit SCObjPtrT(void* pData,void* pInstance)
    :_pCurInstance(pInstance)
    {
        if(pData!=nullptr)
        {
            this->_pObjData = pData;
            this->increaseRef();
        }
    }
        
    SCObjPtrT(const SCObjPtrT& ptr)
    :_pCurInstance(nullptr)
    {
        *this = ptr;
    }
        
    template<typename T2,typename = typename std::enable_if<std::is_convertible<T2*,TargetT*>::value,T2>::type>
    SCObjPtrT(const SCObjPtrT<T2,true>& ptr)
    {
        *this = ptr;
    }
        
    TargetT& operator*()
    {
        SCASSERT(this->_pObjData!=nullptr);
        
        return (_pCurInstance == nullptr) ? (*this->getStub()) : (*(TargetT*)_pCurInstance);
    }
        
    const TargetT& operator*() const
    {
        SCASSERT(this->_pObjData!=nullptr);
        
        return (_pCurInstance == nullptr) ? (*this->getStub()) : (*(TargetT*)_pCurInstance);
    }
        
    TargetT* operator->()
    {
        return _pCurInstance == nullptr ? this->getStub() : (TargetT*)_pCurInstance;
    }
        
    TargetT* getRawPointer()
    {
        return _pCurInstance == nullptr ? this->getStub() : (TargetT*)_pCurInstance;
    }
        
    const TargetT* operator->() const
    {
        return _pCurInstance == nullptr ? this->getStub() : (TargetT*)_pCurInstance;
    }
        
    inline bool isNull() const {return (this->_pObjData==nullptr);}
        
    inline bool operator==(const SCObjPtrT<TargetT,true>& data) const
    {
        return (this->isNull() && data.isNull()) ? true : ((this->_pObjData)==(data._pObjData));
    }
        
    inline bool operator==(const SCObjPtrT<TargetT,false>& data) const
    {
        return (this->isNull() && data.isNull()) ? true : (data.isNull() ? false : ((TargetT*)(this->_pObjData)==((TargetT*)&(*data))));
    }

	inline bool operator!=(const SCObjPtrT<TargetT, true>& data) const
	{
		return !(*this == data);
	}
        
    template<typename T2>
    typename std::enable_if<std::is_convertible<T2*,TargetT*>::value,SCObjPtrT&>::type
    operator=(const SCObjPtrT<T2,true>& ptr)
    {
        if(ptr.getStub() != this->_pObjData)
        {
            this->decreaseRef();
            this->_pObjData = (void*)ptr.getStub();
            T2* p = reinterpret_cast<T2*>(ptr._pCurInstance);
            this->_pCurInstance = dynamic_cast<TargetT*>(p);
            this->increaseRef();
        }
            
        return *this;
    }
        
    template<typename T2>
    T2 cast() const
    {
        SC_RETURN_IF(this->_pObjData==nullptr,nullptr);
        
        TargetT* p1 = (TargetT*)(_pCurInstance == nullptr ? this->_pObjData : _pCurInstance);
        SCObjPtrT<typename T2::type> ptrRet;
        if(dynamic_cast<typename T2::type *>(p1))
        {
            this->increaseRef();
            ptrRet._pObjData = this->_pObjData;
            ptrRet._pCurInstance = dynamic_cast<typename T2::type *>(p1);
        }
            
        return ptrRet;
    }
        
    inline bool isWeak() const { return false;}
    
private:
    void*   _pCurInstance;
};


///----------- weak smart pointer
template<typename TargetT>
class SCObjPtrT<TargetT,false> : public SCObjRefT<void*>
{
    template<typename,bool> friend class SCObjPtrT;
public:
    typedef TargetT type;
        
    SCObjPtrT(void){}
        
    SCObjPtrT(void* p)
    {
        if(p!=nullptr)
        {
            this->SCObjRefT<void*>::createInstance();
            *(this->getStub()) = p;
        }
    }
        
    template<typename T2>
    SCObjPtrT(const SCObjPtrT<T2,false>& ptr)
    {
        *this = ptr;
    }
        
    template<typename T2>
    SCObjPtrT(const SCObjPtrT<T2,true>& ptr)
    {
        *this = ptr;
    }
        
    TargetT& operator*()
    {
        SCASSERT(this->_pObjData!=nullptr);
        return *((TargetT*)this->getTargetPointer());
    }
        
    const TargetT& operator*() const
    {
        SCASSERT(this->_pObjData!=nullptr);
        return *((TargetT*)this->getTargetPointer());
    }
        
    TargetT* operator->()
    {
        return (TargetT*)(this->getTargetPointer());
    }
        
    const TargetT* operator->() const
    {
        return (TargetT*)this->getTargetPointer();
    }
        
    inline bool isNull() const {return (this->getTargetPointer()==nullptr);}
        
    inline bool operator==(const SCObjPtrT& data) const
    {
        return (this->isNull() && data.isNull()) ? true : ((*this->getStub())==(*data.getStub()));
    }
        
    inline bool operator==(const SCObjPtrT<TargetT,true>& data) const
    {
        return (this->isNull() && data.isNull()) ? true : ((this->getTargetPointer())==&(*data));
    }
        
    template<typename T2>
    typename std::enable_if<std::is_convertible<T2*,TargetT*>::value,SCObjPtrT&>::type
    operator=(const SCObjPtrT<T2,true>& ptr)
    {
        if(ptr.getStub()!=this->_pObjData)
        {
            if(this->_pObjData==nullptr)
            {
                this->SCObjRefT<void*>::createInstance();
            }
            *(this->getStub()) = (void*)ptr.getStub();
        }
            
        return *this;
    }
        
    template<typename T2>
    typename std::enable_if<std::is_convertible<T2*,TargetT*>::value,SCObjPtrT&>::type
    operator=(const SCObjPtrT<T2,false>& ptr)
    {
        if(ptr._pObjData!=this->_pObjData)
        {
            this->decreaseRef();
            this->_pObjData = (void*)ptr.getStub();
            this->increaseRef();
        }
            
        return *this;
    }
        
    template<typename T2>
    SCObjPtrT<T2,false> cast() const
    {
        SC_RETURN_IF((std::is_same<T2,TargetT>::value),(*this));
        SC_RETURN_IF(_pObjData==nullptr || (*(this->getStub()))==nullptr,nullptr);
            
        TargetT* p1 = (TargetT*)(*(this->getStub()));
        SCObjPtrT<T2,false> ptrRet;
        if(dynamic_cast<T2*>(p1))
        {
            this->increaseRef();
            ptrRet._pObjData = this->_pObjData;
        }
            
        return ptrRet;
    }
        
    inline bool isWeak() const { return true;}
        
private:
    TargetT* getTargetPointer() const
    {
        return (this->_pObjData==nullptr) ? nullptr : ((TargetT*)(*(this->getStub())));
    }
};

    
// strong
template<typename T>
inline bool operator==(const SCObjPtrT<T>& ptr, std::nullptr_t)
{ return ptr.isNull(); }
    
template<typename T>
inline bool operator==(std::nullptr_t, const SCObjPtrT<T>& ptr)
{ return ptr.isNull(); }
    
template<typename T>
inline bool operator!=(const SCObjPtrT<T>& ptr, std::nullptr_t)
{ return !ptr.isNull(); }
    
template<typename T>
inline bool operator!=(std::nullptr_t, const SCObjPtrT<T>& ptr)
{ return !ptr.isNull();}
    

// weak
template<typename T>
inline bool operator==(const SCObjPtrT<T,false>& ptr, std::nullptr_t)
{ return ptr.isNull(); }
    
template<typename T>
inline bool operator==(std::nullptr_t, const SCObjPtrT<T,false>& ptr)
{ return ptr.isNull(); }
    
template<typename T>
inline bool operator!=(const SCObjPtrT<T,false>& ptr, std::nullptr_t)
{ return !ptr.isNull(); }
    
template<typename T>
inline bool operator!=(std::nullptr_t, const SCObjPtrT<T,false>& ptr)
{ return !ptr.isNull();}

    
    
///---------- check class whether object smart pointer
    
template<typename T, bool b = SCHasInternalTypeT<T>::value ? true : false>
struct SCIsObjPtrClassT
{
    enum {value = std::is_same<T, SCObjPtrT<typename T::type>>::value};
};
    
template<typename T>
struct SCIsObjPtrClassT<T,false>
{
    enum {value = 0};
};

NAMESPACE_SPEEDCC_END


#endif //__SPEEDCC__SCOBJPTRT_H__
