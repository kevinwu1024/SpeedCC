/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Wu Feng)
 
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

#include "TestHomeController.h"

USING_NS_CC;

void TestHomeController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    // consumable feature
    auto bFeatureEnabled = SCStore::getInstance()->isFeatureEnabled(kFeatureIDOfNonConsumable);
    _ptrFeatureEnabledString = SCWatchString::create(bFeatureEnabled ? "true" : "false");
    
    _ptrConsumablePrice = SCWatchFloat::create();
    _ptrConsumableCurrency = SCWatchString::create();
    
    auto ptrBvrConsumable = SCBehaviorPurchase::create(kFeatureIDOfConsumable,
                                                       SC_MAKE_FUNC(onPurchaseResult, this));
    
    // non-consumable feature
    _ptrNonConsumablePrice = SCWatchFloat::create();
    _ptrNonConsumableCurrency = SCWatchString::create();
    
    auto ptrBvrNonConsumable = SCBehaviorPurchase::create(kFeatureIDOfNonConsumable,
                                                          SC_MAKE_FUNC(onPurchaseResult, this));
    
    auto ptrPoint = SCStore::getInstance()->getPointByID(kPointIDOfConsumable);
    
    // consume point feature
    auto ptrConsumPoint = SCBehaviorPurchase::create(kFeatureIDOfConsumePoint, nullptr);
    
    // request IAP info
    auto ptrBvrRequestProduct = SCBehaviorRequestProduct::create(SC_MAKE_FUNC(onRequestProductResult, this));
    
    // restore purchase
    auto ptrBvrRestore = SCBehaviorRestorePurchased::create(SC_MAKE_FUNC(onRestorePurchased, this));
    
    // NOTE: Performing "Rquest Product Price" first before purchasing 'consumable' and 'non-consumable' feature.
    
    SC_BEGIN_PARENT_ROOT(nullptr,nullptr)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", false, 20, nullptr)

            // consumable features
            SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", true, 5, nullptr)
                SC_INSERT_LABEL(nullptr, "", "Consumable Price:   ", "", 20)
                SC_INSERT_LABEL(nullptr, "text-color=red;", _ptrConsumableCurrency, "", 15)
                SC_INSERT_LABEL(nullptr, "", "  ", "", 15)
                SC_INSERT_LABEL(nullptr, "text-color=red;", _ptrConsumablePrice, "", 15)
            SC_END_PARENT

            SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", true, 5, nullptr)
                SC_INSERT_LABEL(nullptr, "", "Consumable Points:   ", "", 20)
                SC_INSERT_LABEL(nullptr, "", "  ", "", 15)
                SC_INSERT_LABEL(nullptr, "text-color=red;", ptrPoint, "", 15)
            SC_END_PARENT

            SC_INSERT_LAYER(nullptr, "", Size(10,5))

            // non-consumable features
            SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", true, 5, nullptr)
                SC_INSERT_LABEL(nullptr, "", "Non-Consumable Price:   ", "", 20)
                SC_INSERT_LABEL(nullptr, "text-color=red;", _ptrNonConsumableCurrency, "", 15)
                SC_INSERT_LABEL(nullptr, "", "  ", "", 15)
                SC_INSERT_LABEL(nullptr, "text-color=red;", _ptrNonConsumablePrice, "", 15)
            SC_END_PARENT
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", true, 5, nullptr)
                SC_INSERT_LABEL(nullptr,"","Feature Enabled:  ","",20)
                SC_INSERT_LABEL(nullptr, "", "  ", "", 15)
                SC_INSERT_LABEL(nullptr, "text-color=red;", _ptrFeatureEnabledString, "", 20)
            SC_END_PARENT

            SC_INSERT_LAYER(nullptr, "", Size(10,40))

            // buttons
            SC_INSERT_BUTTON_LABEL(nullptr, "", "Purchase Consumable Feature", "", 15, ptrBvrConsumable)
            SC_INSERT_BUTTON_LABEL(nullptr, "", "Purchase Non-Consumable Feature", "", 15, ptrBvrNonConsumable)
            SC_INSERT_BUTTON_LABEL(nullptr, "", "Consume Points", "", 15, ptrConsumPoint)
            SC_INSERT_BUTTON_LABEL(nullptr, "", "Rquest Product Price", "", 15, ptrBvrRequestProduct)
            SC_INSERT_BUTTON_LABEL(nullptr, "", "Restore Purchased Products", "", 15, ptrBvrRestore)
    
        SC_END_PARENT
    SC_END_PARENT
}

void TestHomeController::onPurchaseResult(int nFeatureID,SCStore::EResultType result,void* pInfo)
{
    switch(result)
    {
        case SCStore::EResultType::kSuccess:
        {
            if(nFeatureID==kFeatureIDOfNonConsumable)
            {// non-consumable
                (*_ptrFeatureEnabledString) = "true";
            }
            else if(nFeatureID==kFeatureIDOfConsumable)
            {// consumable

            }
            else
            {// consume point
                
            }
            
            SCLog("Purchase success.");
        }
            break;
            
        case SCStore::EResultType::kFailed:
        {
            SCLog("Purchase failed.");
        }
            break;
            
        case SCStore::EResultType::kUserCancelled:
        {
            SCLog("User cancels purchase.");
        }
            break;
    }
}

void TestHomeController::onRequestProductResult(int nFeatureID,SCStore::EResultType result,void* pInfo)
{
    if(result==SCStore::EResultType::kSuccess)
    {
        SCLog("Store IAP info request success.");
        SCASSERT(pInfo!=nullptr);
        
        SCStore::SIAPInfo* pInfo2 = (SCStore::SIAPInfo*)pInfo;
        
        if(nFeatureID==kFeatureIDOfNonConsumable)
        {// non-consumable
            (*_ptrNonConsumablePrice) = *(pInfo2->ptrPrice);
            (*_ptrNonConsumableCurrency) = pInfo2->strCurrency;
        }
        else if(nFeatureID==kFeatureIDOfConsumable)
        {// consumable
            (*_ptrConsumablePrice) = *(pInfo2->ptrPrice);
            (*_ptrConsumableCurrency) = pInfo2->strCurrency;
        }
        else
        {
            SCASSERT(false);
        }
    }
    else
    {
        SCLog("Store IAP info request failed.");
    }
}

void TestHomeController::onRestorePurchased(int nFeatureID,SCStore::EResultType result,void* pInfo)
{
    if(result==SCStore::EResultType::kSuccess)
    {
        SCLog("Restore success.");
    }
    else
    {
        SCLog("Restore failed.");
    }
}


