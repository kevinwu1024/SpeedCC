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

#ifndef __SPEEDCC__SCNODEATTACHMENT_H__
#define __SPEEDCC__SCNODEATTACHMENT_H__

#include "cocos2d.h"
#include "../base/SCObject.h"
#include "SCRefHolder.h"
#include "../stage/SCPlayObject.h"

NAMESPACE_SPEEDCC_BEGIN

///----------- SCNodeAttachment
class SCNodeAttachment : public SCObject
{
public:
    SC_AVOID_CLASS_COPY(SCNodeAttachment)
    SC_DEFINE_CLASS_PTR(SCNodeAttachment)
        
    virtual ~SCNodeAttachment();
        
    SC_DEFINE_CREATE_FUNC_1(SCNodeAttachment,cocos2d::Node*)
        
    void addClickable(SCBehavior::Ptr ptrBvr);
    void removeClickable();
        
    bool hasRadioID();
    int getRadioID();
    void setRadioID(int nID);
        
    void addUserObj(cocos2d::Ref* pRef);
    void addUserObj(SCObject::Ptr ptrObj);
        
    template<typename T,
    typename = typename std::enable_if<std::is_convertible<T,cocos2d::Ref*>::value==1 ||
    SCIsObjPtrClassT<T>::value==1>::type>
    void removeUserObj()
    {
        SC_RETURN_V_IF(_pNode==nullptr || _pNode->getUserObject()==nullptr);
        auto pHolder = this->getUserHolder(false);
            
        SC_RETURN_V_IF(pHolder==nullptr || pHolder->isEmpty());
            
        pHolder->removeObj<T>();
    }
        
    template<typename T,
    typename = typename std::enable_if<SCIsObjPtrClassT<T>::value==1 ||
    std::is_convertible<T,cocos2d::Ref*>::value==1 >::type>
    T getUserObj()
    {
        SC_RETURN_IF(_pNode==nullptr || _pNode->getUserObject()==nullptr,nullptr);
        auto pHolder = this->getUserHolder(false);
            
        SC_RETURN_IF(pHolder==nullptr || pHolder->isEmpty(),nullptr);
            
        return pHolder->getObj<T>();
    }
        
    template<typename T,
    typename = typename std::enable_if<SCIsObjPtrClassT<T>::value==1 ||
    std::is_convertible<T,cocos2d::Ref*>::value==1 >::type>
    bool hasUserObj()
    {
        SC_RETURN_IF(_pNode==nullptr || _pNode->getUserObject()==nullptr,false);
        auto pHolder = this->getUserHolder(false);
        SC_RETURN_IF(pHolder==nullptr || pHolder->isEmpty(),false);
        return pHolder->hasObj<T>();
    }
        
private:
    struct SRadioObj : public SCObject
    {
        SC_DEFINE_CLASS_PTR(SRadioObj)
        SC_DEFINE_CREATE_FUNC_1(SRadioObj,int)
            
        SRadioObj(int i):nID(i){}
        int     nID;
    };
        
protected:
    SCNodeAttachment(cocos2d::Node* pNode);
        
private:
    SCRefHolder* getUserHolder(const bool bCreate=true);
        
private:
    cocos2d::Node*      _pNode;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCNODEATTACHMENT_H__
