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

#include "SCNodeAttachment.h"
#include "SCNodeClickable.h"

#include "../base/SCBaseMacros.h"

NAMESPACE_SPEEDCC_BEGIN

///----------- SCNodeAttachment
    
SCNodeAttachment::SCNodeAttachment(cocos2d::Node* pNode)
:_pNode(pNode)
{
    SCASSERT(_pNode);
}
    
SCNodeAttachment::~SCNodeAttachment()
{
}
    
void SCNodeAttachment::addClickable(SCBehavior::Ptr ptrBvr)
{
    SCASSERT(_pNode!=nullptr);
        
    auto ptrClick = this->getUserObj<SCNodeClickable::Ptr>();
        
    if(ptrClick==nullptr)
    {
        ptrClick = SCNodeClickable::create(_pNode,ptrBvr);
        this->addUserObj(ptrClick);
    }
    else
    {
        ptrClick->setBehavior(ptrBvr);
    }
}
    
void SCNodeAttachment::removeClickable()
{
    SCASSERT(_pNode!=nullptr);
    this->removeUserObj<SCNodeClickable::Ptr>();
}
    
bool SCNodeAttachment::hasRadioID()
{
    return this->hasUserObj<SRadioObj::Ptr>();
}
    
int SCNodeAttachment::getRadioID()
{
    int nRet = 0;
    if(this->hasUserObj<SRadioObj::Ptr>())
    {
        auto ptr = this->getUserObj<SRadioObj::Ptr>();
        nRet = ptr->nID;
    }
        
    return nRet;
}
    
void SCNodeAttachment::setRadioID(int nID)
{
    auto ptr = this->getUserObj<SRadioObj::Ptr>();
    if(ptr==nullptr)
    {
        auto ptrRad = SRadioObj::create(nID);
        this->addUserObj(ptrRad);
    }
}
    
void SCNodeAttachment::addUserObj(cocos2d::Ref* pRef)
{
    SC_RETURN_V_IF(pRef==nullptr);
        
    auto pHolder = this->getUserHolder(true);
    pHolder->addObj(pRef);
}
    
void SCNodeAttachment::addUserObj(SCObject::Ptr ptrObj)
{
    SC_RETURN_V_IF(ptrObj==nullptr);
        
    auto pHolder = this->getUserHolder(true);
    pHolder->addObj(ptrObj);
}
    
SCRefHolder* SCNodeAttachment::getUserHolder(const bool bCreate)
{
    SC_RETURN_IF(_pNode==nullptr,nullptr);
    auto pUserObj = _pNode->getUserObject();
    SC_RETURN_IF(pUserObj==nullptr && !bCreate,nullptr);
        
    SCRefHolder* pHolder = nullptr;
        
    if(pUserObj==nullptr)
    {
        pHolder = SCRefHolder::create();
    }
    else
    {
        pHolder = dynamic_cast<SCRefHolder*>(pUserObj);
            
        if(pHolder==nullptr)
        {
            pHolder = SCRefHolder::create();
            pHolder->addObj(pUserObj);
        }
    }
        
    _pNode->setUserObject(pHolder);
    return pHolder;
}

NAMESPACE_SPEEDCC_END

