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

#ifndef __SPEEDCC__SCBEHAVIORSYSTEM_H__
#define __SPEEDCC__SCBEHAVIORSYSTEM_H__

#include "SCPlayObject.h"
#include "../cocos/SCViewNavigator.h"
#include "SCBehaviorCommon.h"
#include "../system/SCStore.h"

NAMESPACE_SPEEDCC_BEGIN

///--------- SCBehaviorPurchase
class SCBehaviorPurchase : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorPurchase)
    SC_DEFINE_CLASS_PTR(SCBehaviorPurchase)
        
    virtual ~SCBehaviorPurchase();
        
    SC_DEFINE_CREATE_FUNC_2(SCBehaviorPurchase,const int,SCStore::ResultFunc_t)
        
    inline int getFeatureID() const { return _nFeatureID; }
    inline void setFeatureID(const int nFeatureID) { _nFeatureID = nFeatureID; }
        
    void setResultFunc(const SCStore::ResultFunc_t& func);
        
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
protected:
    SCBehaviorPurchase(const int nFeatureID,SCStore::ResultFunc_t resultFunc);
        
private:
    int                     _nFeatureID;
    SCStore::ResultFunc_t   _resultFunc;
};
    
    
///---------- SCBehaviorRequestProduct
class SCBehaviorRequestProduct : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorRequestProduct)
    SC_DEFINE_CLASS_PTR(SCBehaviorRequestProduct)
        
    virtual ~SCBehaviorRequestProduct();
        
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorRequestProduct,SCStore::ResultFunc_t)
        
    inline void setResultFunc(const SCStore::ResultFunc_t& func) { _resultFunc = func; }
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
protected:
    SCBehaviorRequestProduct(SCStore::ResultFunc_t resultFunc)
    :_resultFunc(resultFunc)
    {}
        
private:
    SCStore::ResultFunc_t   _resultFunc;
};
    
///----------- SCBehaviorRestorePurchased
class SCBehaviorRestorePurchased : public SCBehavior
{
public:
    SC_AVOID_CLASS_COPY(SCBehaviorRestorePurchased)
    SC_DEFINE_CLASS_PTR(SCBehaviorRestorePurchased)
        
    virtual ~SCBehaviorRestorePurchased();
        
    SC_DEFINE_CREATE_FUNC_1(SCBehaviorRestorePurchased,SCStore::ResultFunc_t)
        
    inline void setResultFunc(const SCStore::ResultFunc_t& func) { _resultFunc = func; }
    virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
protected:
    SCBehaviorRestorePurchased(SCStore::ResultFunc_t resultFunc)
    {}
        
private:
    SCStore::ResultFunc_t   _resultFunc;
        
};


NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCBEHAVIORSYSTEM_H__
