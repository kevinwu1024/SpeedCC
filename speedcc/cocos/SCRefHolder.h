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

#ifndef __SPEEDCC__SCREF2PTR_H__
#define __SPEEDCC__SCREF2PTR_H__

#include "cocos2d.h"
#include "../base/SCObject.h"

NAMESPACE_SPEEDCC_BEGIN

///---------- SCRef2Ptr
class SCRef2Ptr : public SCObject
{
public:
    SC_AVOID_CLASS_COPY(SCRef2Ptr)
    SC_DEFINE_CLASS_PTR(SCRef2Ptr)
        
    SC_DEFINE_CREATE_FUNC_1(SCRef2Ptr,cocos2d::Ref*)
        
    virtual ~SCRef2Ptr();
        
    inline cocos2d::Ref* getRef() const {return _pObject;}

protected:
    SCRef2Ptr(cocos2d::Ref* pObject);
        
private:
    cocos2d::Ref*   _pObject;
};
    
///------------- SCPtr2Ref
class SCPtr2Ref : public cocos2d::Ref
{
public:
    static cocos2d::Ref* create();
    static cocos2d::Ref* create(SCObject::Ptr ptr);
        
    virtual ~SCPtr2Ref();
        
    inline void setPtr(SCObject::Ptr ptr) { _ptrObj = ptr; }
    inline SCObject::Ptr getPtr() const { return _ptrObj;}
        
protected:
    SCPtr2Ref();
    SCPtr2Ref(SCObject::Ptr ptr);
        
private:
    SCObject::Ptr       _ptrObj;
};
    
// internal class, don't use in directly.
template<typename T,int n = std::is_convertible<T,cocos2d::Ref*>::value==1 ? 1 :
(SCIsObjPtrClassT<T>::value==1 ? 2 :0 )>
struct SCRefHolderTmpHelper;
    
// for cocos2d::Ref*
// internal class, don't use in directly.
template<typename T>
struct SCRefHolderTmpHelper<T,1>
{
    static void removeObj(std::list<SCObject::Ptr>& objList)
    {
        objList.remove_if([](SCObject::Ptr ptrIt)
                            {
                                auto ptrTem = ptrIt.cast<SCRef2Ptr::Ptr>();
                                return (ptrTem!=nullptr && dynamic_cast<T>(ptrTem->getRef())!=nullptr);
                            });
    }
        
    static T getRefObj(const std::list<SCObject::Ptr>& objList)
    {
        for(const auto& it : objList)
        {
            auto p = it.cast<SCRef2Ptr::Ptr>();
            SC_CONTINUE_IF(p==nullptr);
            auto p1 = dynamic_cast<T>(p->getRef());
            SC_RETURN_IF(p1!=nullptr, p1);
        }
            
        return nullptr;
    }
};
    
// for SCObject::Ptr
// internal class, don't use in directly.
template<typename T>
struct SCRefHolderTmpHelper<T,2>
{
    static void removeObj(std::list<SCObject::Ptr>& objList)
    {
        objList.remove_if([](SCObject::Ptr ptrIt)
                            {
                                return (ptrIt.cast<T>()!=nullptr);
                            });
    }
        
    static T getObj(const std::list<SCObject::Ptr>& objList)
    {
        for(const auto& it : objList)
        {
            auto p = it.cast<T>();
            SC_RETURN_IF(p!=nullptr, p);
        }
            
        return nullptr;
    }
};
    
    
///----------- SCRefHolder
// internal class, don't use in directly.
class SCRefHolder : public cocos2d::Ref
{
public:
    static SCRefHolder* create();
        
    virtual ~SCRefHolder();
        
    void addObj(cocos2d::Ref* pRef);
    void addObj(SCObject::Ptr ptr);
        
    
    template<typename T,
    typename = typename std::enable_if<std::is_convertible<T,cocos2d::Ref*>::value==1 ||
        SCIsObjPtrClassT<T>::value==1>::type >
    void removeObj()
    {
        SCRefHolderTmpHelper<T>::removeObj(_objList);
    }
        
    template<typename T,
    typename = typename std::enable_if<SCIsObjPtrClassT<T>::value==1 ||
    std::is_convertible<T,cocos2d::Ref*>::value==1 >::type>
    T getObj() const
    {
        return SCRefHolderTmpHelper<T>::getObj(_objList);
    }
        
    template<typename T,
    typename = typename std::enable_if<SCIsObjPtrClassT<T>::value==1 ||
    std::is_convertible<T,cocos2d::Ref*>::value==1 >::type>
    bool hasObj() const
    {
        return (this->getObj<T>()!=nullptr);
    }
        
    inline bool isEmpty() const { return _objList.empty(); }
        
protected:
    SCRefHolder();
        
private:
    std::list<SCObject::Ptr>    _objList;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCREF2PTR_H__
