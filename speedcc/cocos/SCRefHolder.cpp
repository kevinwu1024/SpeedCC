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

#include "SCRefHolder.h"
#include "../base/SCBaseMacros.h"

NAMESPACE_SPEEDCC_BEGIN

///------------- SCRef2Ptr
SCRef2Ptr::SCRef2Ptr(cocos2d::Ref* pObject)
:_pObject(pObject)
{
    SCASSERT(_pObject!=nullptr);
    _pObject->retain();
}
    
SCRef2Ptr::~SCRef2Ptr()
{
    if(_pObject!=nullptr)
    {
        _pObject->release();
    }
}
    
///------------- SCPtr2Ref
SCPtr2Ref::SCPtr2Ref()
{
}
    
SCPtr2Ref::~SCPtr2Ref()
{
}
    
SCPtr2Ref::SCPtr2Ref(SCObject::Ptr ptr)
:_ptrObj(ptr)
{
}
    
cocos2d::Ref* SCPtr2Ref::create()
{
    auto ret = new (std::nothrow) SCPtr2Ref();
    ret->autorelease();
    return ret;
}
    
cocos2d::Ref* SCPtr2Ref::create(SCObject::Ptr ptr)
{
    auto ret = new (std::nothrow) SCPtr2Ref(ptr);
    ret->autorelease();
    return ret;
}
    
///----------- SCRefHolder
    
SCRefHolder::SCRefHolder()
{
        
}
    
SCRefHolder::~SCRefHolder()
{
        
}
    
SCRefHolder* SCRefHolder::create()
{
    auto ret = new (std::nothrow) SCRefHolder();
    ret->autorelease();
    return ret;
}
    
void SCRefHolder::addObj(cocos2d::Ref* pRef)
{
    SC_RETURN_V_IF(pRef==nullptr);
        
    _objList.push_back(SCRef2Ptr::create(pRef));
}
    
void SCRefHolder::addObj(SCObject::Ptr ptr)
{
    SC_RETURN_V_IF(ptr==nullptr);
        
    _objList.push_back(ptr);
}
    
NAMESPACE_SPEEDCC_END

