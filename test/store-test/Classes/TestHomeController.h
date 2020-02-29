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

#ifndef __TESTHOME_SCENE_H__
#define __TESTHOME_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

// non-consumable IDs
#define kFeatureIDOfNonConsumable       1   // unique id for feature
#define kProductIDOfNonConsumable       "nonconsumable" // setup in IAP from App Store

// consumable IDs
#define kFeatureIDOfConsumable          2 // unique id for feature
#define kProductIDOfConsumable          "consumable" // setup in IAP from App Store
#define kPointIDOfConsumable            1
#define kPointDiffOfConsumable          10

// consume point IDs
#define kFeatureIDOfConsumePoint        3
#define kPointStepOfConsume             5

using namespace SpeedCC;

class TestHomeController : public SpeedCC::SCSceneController
{
public:
    virtual void onCreate(SCDictionary parameters) override;
    
    void onPurchaseResult(int nFeatureID,SCStore::EResultType result,void* pInfo);
    void onRequestProductResult(int nFeatureID,SCStore::EResultType result,void* pInfo);
    void onRestorePurchased(int nFeatureID,SCStore::EResultType result,void* pInfo);
    
private:
    SCWatchString::Ptr      _ptrConsumableCurrency;
    SCWatchFloat::Ptr       _ptrConsumablePrice;
    
    SCWatchString::Ptr      _ptrNonConsumableCurrency;
    SCWatchFloat::Ptr       _ptrNonConsumablePrice;
    
    SCWatchString::Ptr      _ptrFeatureEnabledString;
};

#endif // __TESTHOME_SCENE_H__
