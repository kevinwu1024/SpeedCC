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

#include "SCStore.h"
#include "SCSetting.h"
#include "../platform/SCOSSystem.h"
#include "../system/SCSystem.h"

NAMESPACE_SPEEDCC_BEGIN

SCStore*      SCStore::s_pInstance = nullptr;
    
SCStore::SCStore()
:_nCurrentFeatureID(0)
{
    SCMsgDisp()->addListener(this);
}
    
SCStore::~SCStore()
{
    SCMsgDisp()->removeListener(this);
}
    
SCStore* SCStore::getInstance()
{
    if(s_pInstance==nullptr)
    {
        s_pInstance = new SCStore();
    }
        
    return s_pInstance;
}
    
bool SCStore::setUpFeature(const int nFeatureID,const SCString& strProductID,const int nPointID,const int nPointInc)
{
    SCASSERT(nFeatureID>0);
    SFeaturePointInfo info;
    info.nFeatureID = nFeatureID;
    info.strProductID = strProductID;
    info.nPointID = nPointID;
    info.nPointInc = nPointInc;
        
    const auto type = this->getBuyTypeByInfo(info);
        
    if(type==kBuyUnknown)
    {
        SCLog("Setup Feature Failed. Unknown ID combination.");
        return false;
    }

    if(this->isFeatureExist(nFeatureID))
    {
        SCLog("Setup Feature Failed. Feature ID already exist.");
        return false;
    }
        
    if(!strProductID.isEmpty() && this->isProductExit(strProductID))
    {
        SCLog("Setup Feature Failed. Product ID already exist.");
        return false;
    }
        
    if(nPointID>0 && !strProductID.isEmpty() && this->isPointExist(nPointID))
    {
        SCLog("Setup Feature Failed. Point ID already exist.");
        return false;
    }
        
    SCMapInsert(_feature2InfoMap, nFeatureID, info);
        
    if(nPointID>0)
    {
        SCWatchInt::Ptr ptr = SCWatchInt::create();
        SCMapInsert(_pointID2WatchIntMap,nPointID,ptr);
    }
        
    switch(this->getBuyTypeByFeature(nFeatureID))
    {
        case kBuyConsumable:
        {// consumable
            auto strSettingKeyStorePoint = SCSystem::getSpeedCCOption(SC_OPTION_KEY_SETTINGKEYOFSTORPOINTPREFIX).getString();
            this->bindPoint2Setting(nPointID, SCString(0,strSettingKeyStorePoint + "_%d__",nPointID), true);
        }
            break;
                
        case kBuyNonConsumable:
        {// non-consumable
            auto strSettingKeyStoreFeature = SCSystem::getSpeedCCOption(SC_OPTION_KEY_SETTINGKEYOFSTOREFEATUREPREFIX).getString();
            this->bindFeature2Setting(nFeatureID,SCString(0,strSettingKeyStoreFeature + "_%d__",nFeatureID),true);
        }
            break;
                
        default: break;
    }
        
    return true;
}
    
bool SCStore::setPointIncByFeature(const int nFeatureID,const int nPointInc)
{
    SCASSERT(nFeatureID>0);
    SC_RETURN_IF(nFeatureID<=0,false);
    auto it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
    (*it).second.nPointInc = nPointInc;
    return true;
}
    
bool SCStore::purchaseFeature(const int nFeatureID,const ResultFunc_t& resultFunc)
{
    SCASSERT(nFeatureID>0);
    SC_RETURN_IF(nFeatureID<=0,false);
    const auto& it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
    auto type = this->getBuyTypeByInfo((*it).second);
    SC_RETURN_IF(type==kBuyUnknown, false);
    _purchaseResultFunc = resultFunc;
    _nCurrentFeatureID = nFeatureID;
        
    if(type==kBuyConsumePoint)
    {
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kMsgStorePurchaseSuccess;
        ptrMsg->parameters.setValue(SC_KEY_FEATUREID, nFeatureID);
        SCMsgDisp()->postMessage(ptrMsg);
    }
    else
    {
        if(type==kBuyNonConsumable && !(*((*it).second.ptrFeatureLocked)))
        {
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = SCID::Msg::kMsgStorePurchaseSuccess;
            ptrMsg->parameters.setValue(SC_KEY_FEATUREID, nFeatureID);
            SCMsgDisp()->postMessage(ptrMsg);
        }
        else
        {
            ::scStorePurchaseItem((*it).second.strProductID,type==kBuyConsumable);
        }
    }
        
    return true;
}
    
bool SCStore::isFeatureEnabled(const int nFeatureID) const
{
    SCASSERT(nFeatureID>0);
    SC_RETURN_IF(nFeatureID<=0,false);
    const auto& it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
    auto ptr = (*it).second.ptrFeatureLocked;
    return !(*ptr);
}
    
SCWatchBool::Ptr SCStore::getFeatureEnabled(const int nFeatureID) const
{
    SCASSERT(nFeatureID>0);
    SC_RETURN_IF(nFeatureID<=0,nullptr);
    const auto& it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(it==_feature2InfoMap.end(), nullptr);
        
    return (*it).second.ptrFeatureLocked;
}
    
bool SCStore::setFeatureEnabled(const int nFeatureID,const bool bEnable)
{
    SCASSERT(nFeatureID>0);
    SC_RETURN_IF(nFeatureID<=0,false);
    SC_RETURN_IF(this->getBuyTypeByFeature(nFeatureID)!=kBuyNonConsumable, false);
    const auto& it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
    *((*it).second.ptrFeatureLocked) = !bEnable;
    return true;
}
    
bool SCStore::getProductInfo(const SCString& strProductID,SIAPInfo& info)
{
    SCASSERT(!strProductID.isEmpty());
    SC_RETURN_IF(strProductID.isEmpty(), false);
    SC_RETURN_IF(!this->isProductExit(strProductID), false);
        
    bool bRet = false;
    const auto& it = _iap2PriceInfoMap.find(strProductID);
    if(it==_iap2PriceInfoMap.end())
    {
//            if(bRquest)
//            {
//                this->requestPriceInfo(strProductID);
//            }
    }
    else
    {
        info = (*it).second;
        bRet = true;
    }
        
    return bRet;
}
    
bool SCStore::getPriceInfoByFeature(const int nFeatureID,SIAPInfo& info)
{
    SC_RETURN_IF(nFeatureID<=0, false);
    auto strProductID = this->getProductIDByFeature(nFeatureID);
    SC_RETURN_IF(strProductID.isEmpty(), false);
    return this->getProductInfo(strProductID,info);
}
    
bool SCStore::restorePurchased(const ResultFunc_t& resultFunc)
{
    _restoreResultFunc = resultFunc;
    return ::scStoreRestorePurchased();
}
    
bool SCStore::requestProductInfo(const ResultFunc_t& resultFunc)
{
    bool bRet = false;
    int nCount = 0;
    char** pProductIDArray = new char*[_feature2InfoMap.size()];
    ::memset(pProductIDArray,0,_feature2InfoMap.size());
        
    for(const auto& it : _feature2InfoMap)
    {
        if(!it.second.strProductID.isEmpty())
        {
            char* pszProductID = (char*)::malloc(it.second.strProductID.getLength()+2);
            ::strcpy(pszProductID,it.second.strProductID);
            pProductIDArray[nCount] = pszProductID;
            ++nCount;
        }
    }
    if(nCount>0)
    {
        _requestProductResultFunc = resultFunc;
        bRet = ::scStoreRequestItemInfo(pProductIDArray,nCount);
        for(int i=0; i<nCount; ++i)
        {
            ::free(pProductIDArray[i]);
            pProductIDArray[i] = nullptr;
        }
    }
    else
    {
        resultFunc(0,EResultType::kFailed,nullptr);
    }
        
    delete [] pProductIDArray;
    pProductIDArray = nullptr;
        
    return bRet;
}
    
SCString SCStore::getProductIDByFeature(const int nFeatureID)
{
    SCASSERT(nFeatureID>0);
    SC_RETURN_IF(nFeatureID<=0,0);
    const auto& it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(_feature2InfoMap.end()==it, 0);
    return (*it).second.strProductID;
}
    
int SCStore::getPointIDByFeature(const int nFeatureID)
{
    SCASSERT(nFeatureID>0);
    SC_RETURN_IF(nFeatureID<=0,0);
    const auto& it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(_feature2InfoMap.end()==it, 0);
    return (*it).second.nPointID;
}
    
SCWatchInt::Ptr SCStore::getPointByID(const int nPointID) const
{
    auto ret = SCWatchInt::create();
    auto it = _pointID2WatchIntMap.find(nPointID);
        
    if(it!=_pointID2WatchIntMap.end())
    {
        ret = (*it).second;
    }
        
    return ret;
}
    
bool SCStore::isFeatureExist(const int nFeatureID) const
{
    SCASSERT(nFeatureID>0);
    SC_RETURN_IF(_feature2InfoMap.empty() || nFeatureID<=0, false);
     
    return (_feature2InfoMap.find(nFeatureID)!=_feature2InfoMap.end());
}
    
bool SCStore::isPointExist(const int nPointID) const
{
    SCASSERT(nPointID>0);
    SC_RETURN_IF(_pointID2WatchIntMap.empty() || nPointID<=0, false);
        
    return (_pointID2WatchIntMap.find(nPointID)!=_pointID2WatchIntMap.end());
}
    
bool SCStore::isProductExit(const SCString& strProductID) const
{
    SCASSERT(!strProductID.isEmpty());
    SC_RETURN_IF(_feature2InfoMap.empty() || strProductID.isEmpty(), false);
        
    for(const auto& it : _feature2InfoMap)
    {
        SC_RETURN_IF(it.second.strProductID==strProductID,true);
    }
        
    return false;
}
    
SCStore::EBuyType SCStore::getBuyTypeByFeature(const int nFeatureID)
{
    SCASSERT(nFeatureID>0);
    SC_RETURN_IF(_feature2InfoMap.empty() || nFeatureID<=0, kBuyUnknown);
    const auto& it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(it==_feature2InfoMap.end(),kBuyUnknown);
        
    return this->getBuyTypeByInfo((*it).second);
}
    
SCStore::EBuyType SCStore::getBuyTypeByInfo(const SFeaturePointInfo& info)
{
    SC_RETURN_IF(info.nFeatureID<=0, kBuyUnknown);
        
    if(info.strProductID.isEmpty())
    {
        return (info.nPointID>0) ? kBuyConsumePoint : kBuyUnknown;
    }
    else
    {
        return (info.nPointID>0) ? kBuyConsumable : kBuyNonConsumable;
    }
}
    
bool SCStore::bindPoint2Setting(const int nPointID,const SCString& strSettingKey,const bool bUseSetting)
{
    SCASSERT(nPointID>0);
    SC_RETURN_IF(nPointID<=0, false);
    SC_RETURN_IF(strSettingKey.isEmpty(), false);
        
    auto it = _pointID2WatchIntMap.find(nPointID);
    SC_RETURN_IF(_pointID2WatchIntMap.end()==it, false);
        
    auto ptr = SCSetting::getInstance()->getWatchInt(strSettingKey,0);
    if(!bUseSetting)
    {
        (*ptr) = (*(*it).second);
    }
        
    (*it).second = ptr;
        
    return true;
}
    
bool SCStore::unbindPoint2Setting(const int nPointID)
{
    SCASSERT(nPointID>0);
    SC_RETURN_IF(nPointID<=0, false);
        
    auto it = _pointID2WatchIntMap.find(nPointID);
    SC_RETURN_IF(_pointID2WatchIntMap.end()==it, false);
        
    int n = (*(*it).second);
    (*it).second = SCWatchInt::create(n);
    return true;
}
    
bool SCStore::bindFeature2Setting(const int nFeatureID,const SCString& strSettingKey,const bool bUseSetting)
{
    SC_RETURN_IF(nFeatureID<=0 || strSettingKey.isEmpty(), false);
        
    auto it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
    auto ptr = SCSetting::getInstance()->getWatchBool(strSettingKey,true);
    if(!bUseSetting)
    {
        (*ptr) = (*(*it).second.ptrFeatureLocked);
    }
        
    (*it).second.ptrFeatureLocked = ptr;
        
    return true;
}
    
bool SCStore::unbindFeature(const int nFeatureID)
{
    SC_RETURN_IF(nFeatureID<=0, false);
        
    auto it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
    const bool b = *((*it).second.ptrFeatureLocked);
    (*it).second.ptrFeatureLocked = SCWatchBool::create(b);
        
    return true;
}
    
bool SCStore::setFeaturePurchased(const int nFeatureID)
{
    SC_RETURN_IF(nFeatureID<=0,false);
        
    auto it = _feature2InfoMap.find(nFeatureID);
    SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
    switch(this->getBuyTypeByFeature(nFeatureID))
    {
        case kBuyConsumable:
        {
            auto it2 = _pointID2WatchIntMap.find((*it).second.nPointID);
            (*(*it2).second) += (*it).second.nPointInc;
        }
            break;
                
        case kBuyConsumePoint:
        {
            auto it2 = _pointID2WatchIntMap.find((*it).second.nPointID);
            (*(*it2).second) -= (*it).second.nPointInc;
        }
            break;
                
        case kBuyNonConsumable:
        {
            *((*it).second.ptrFeatureLocked) = false;
        }
            break;
                
        default: break;
    }
        
    return true;
}
    
int SCStore::getFeatureIDByProduct(const SCString& strProductID) const
{
    SC_RETURN_IF(strProductID.isEmpty(),0);
        
    for(auto& it : _feature2InfoMap)
    {
        SC_RETURN_IF(it.second.strProductID==strProductID,it.second.nFeatureID);
    }
        
    return 0;
}
    
void SCStore::setProductInfo(const SCString& strProductID,const float fPrice,const SCString& strCurrency)
{
    SC_RETURN_V_IF(strProductID.isEmpty());
        
    if(this->isProductExit(strProductID))
    {
        SIAPInfo info;
        *(info.ptrPrice) = fPrice;
        info.strCurrency = strCurrency;
        _iap2PriceInfoMap[strProductID] = info;
    }
}
    
void SCStore::setPurchaseResultFunc(const ResultFunc_t& resultFunc)
{
    _purchaseResultFunc = resultFunc;
}
    
void SCStore::setRestoreResultFunc(const ResultFunc_t& resultFunc)
{
    _restoreResultFunc = resultFunc;
}
    
void SCStore::setRequestProductResultFunc(const ResultFunc_t& resultFunc)
{
    _requestProductResultFunc = resultFunc;
}
    
bool SCStore::onSCMessageProcess(SCMessage::Ptr ptrMsg)
{
    switch(ptrMsg->nMsgID)
    {
            // store relative
        case SCID::Msg::kMsgStoreUserCancelled:
        {
            SCLog("IAP operation cancelled by user.");
            if(_purchaseResultFunc!=nullptr)
            {
                _purchaseResultFunc(_nCurrentFeatureID,EResultType::kUserCancelled,nullptr);
            }
        }
            break;
                
        case SCID::Msg::kMsgStorePurchaseSuccess:
        {
            SCLog("IAP Purchase success.");
            auto nFeatureID = ptrMsg->parameters.getValue(SC_KEY_FEATUREID).getInt();
            SCASSERT(_nCurrentFeatureID==nFeatureID);
                
            if(nFeatureID>0)
            {
                this->setFeaturePurchased(nFeatureID);
            }
                
            if(_purchaseResultFunc!=nullptr)
            {
                _purchaseResultFunc(nFeatureID,EResultType::kSuccess,nullptr);
            }
        }
            break;
                
        case SCID::Msg::kMsgStorePurchaseFailed:
        {
            SCLog("IAP Purchase failed.");
            if(_purchaseResultFunc!=nullptr)
            {
                _purchaseResultFunc(_nCurrentFeatureID,EResultType::kFailed,nullptr);
            }
        }
            break;
                
        case SCID::Msg::kMsgStoreRestoreSuccess:
        {
            SCLog("Restored IAP success.");
            auto nFeatureID = ptrMsg->parameters.getValue(SC_KEY_FEATUREID).getInt();
                
            if(nFeatureID>0)
            {
                this->setFeaturePurchased(nFeatureID);
            }
                
            if(_restoreResultFunc!=nullptr)
            {
                _restoreResultFunc(nFeatureID,EResultType::kSuccess,nullptr);
            }
        }
            break;
                
        case SCID::Msg::kMsgStoreRestoreFailed:
        {
            SCLog("Restored IAP failed.");
            if(_restoreResultFunc!=nullptr)
            {
                _restoreResultFunc(0,EResultType::kFailed,nullptr);
            }
        }
            break;
                
        case SCID::Msg::kMsgStoreIAPInfoSuccess:
        {
            SCLog("Request product info success.");
            bool bResult = false;
            auto nFeatureID = ptrMsg->parameters.getValue(SC_KEY_FEATUREID).getInt();
            bResult = false;
            auto strCurrency = ptrMsg->parameters.getValue(SC_KEY_CURRENCY).getString(&bResult);
            SCASSERT(bResult);
            float fPrice = ptrMsg->parameters.getValue(SC_KEY_PRICE).getFloat();
            if(bResult)
            {
                SCLog("feature id: '%d'; price: %.2f; currency: %s",nFeatureID,fPrice,strCurrency.c_str());
                auto strProductID = this->getProductIDByFeature(nFeatureID);
                this->setProductInfo(strProductID, fPrice, strCurrency);
                    
                if(_requestProductResultFunc!=nullptr)
                {
                    SIAPInfo info = _iap2PriceInfoMap[strProductID];
                    _requestProductResultFunc(nFeatureID,EResultType::kSuccess,&info);
                }
            }
            else
            {
                if(_requestProductResultFunc!=nullptr)
                {
                    _requestProductResultFunc(nFeatureID,EResultType::kFailed,nullptr);
                }
            }
        }
            break;
                
        case SCID::Msg::kMsgStoreIAPInfoFailed:
        {
            SCLog("Request IAP info failed.");
            if(_requestProductResultFunc!=nullptr)
            {
                _requestProductResultFunc(0,EResultType::kFailed,nullptr);
            }
        }
            break;
    }
        
    return true;
}

NAMESPACE_SPEEDCC_END
