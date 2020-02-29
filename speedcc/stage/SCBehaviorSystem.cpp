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

#include "SCBehaviorSystem.h"
#include "../cocos/SCViewController.h"
#include "../system/SCSystem.h"

NAMESPACE_SPEEDCC_BEGIN

    
///--------- SCBehaviorPurchase
SCBehaviorPurchase::SCBehaviorPurchase(const int nFeatureID,SCStore::ResultFunc_t resultFunc)
:_nFeatureID(nFeatureID)
{
    this->setResultFunc(resultFunc);
}
    
SCBehaviorPurchase::~SCBehaviorPurchase()
{
    SCStore::getInstance()->setPurchaseResultFunc(nullptr);
}
    
void SCBehaviorPurchase::setResultFunc(const SCStore::ResultFunc_t& func)
{
    _resultFunc = [func](int nFeatureID,SCStore::EResultType result,void* pInfo)
    {
        auto ptrCtrl = SCViewNav()->getCurrentController();
        ptrCtrl->showBlackMask(false);
        ptrCtrl->setTouchAcceptable(true);
            
        if(func!=nullptr)
        {
            func(nFeatureID,result,pInfo);
        }
    };
}
    
void SCBehaviorPurchase::execute(const SCDictionary& par)
{
    auto ptrCtrl = SCViewNav()->getCurrentController();
    ptrCtrl->showBlackMask(true);
    ptrCtrl->setTouchAcceptable(false);
    SCStore::getInstance()->purchaseFeature(_nFeatureID,_resultFunc);
}
    
///---------- SCBehaviorRequestProduct
SCBehaviorRequestProduct::~SCBehaviorRequestProduct()
{
    SCStore::getInstance()->setRequestProductResultFunc(nullptr);
}
    
void SCBehaviorRequestProduct::execute(const SCDictionary& par)
{
    SCStore::getInstance()->requestProductInfo(_resultFunc);
}
    
    
///----------- SCBehaviorRestorePurchased
SCBehaviorRestorePurchased::~SCBehaviorRestorePurchased()
{
    SCStore::getInstance()->setRestoreResultFunc(nullptr);
}
    
void SCBehaviorRestorePurchased::execute(const SCDictionary& par)
{
    SCStore::getInstance()->restorePurchased(_resultFunc);
}

NAMESPACE_SPEEDCC_END
