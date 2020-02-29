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

#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStageMacros.h"
#include "../base/SCBaseMacros.h"
#include "../cocos/SCCocosDef.h"
#include "../system/SCStore.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
    extern "C"
    {
#endif  // __cplusplus
        
        ///------------ store
        // nResult, 0: success; non-zero: failed
        void scbStorePurchaseItemResult(const char* pszIAP,int nResult)
        {
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = (nResult==0) ? SCID::Msg::kMsgStorePurchaseSuccess : SCID::Msg::kMsgStorePurchaseFailed;
            if(pszIAP!=NULL)
            {
                int nFeatureID = SCStore::getInstance()->getFeatureIDByProduct(pszIAP);
                ptrMsg->parameters.setValue(SC_KEY_FEATUREID, nFeatureID);
            }
            else
            {
                ptrMsg->parameters.setValue(SC_KEY_FEATUREID, (int)0);
            }
            
            SCMsgDisp()->postMessage(ptrMsg);
        }
        
        // nResult, 0: success; non-zero: failed
        void scbStoreRestoreItemResult(const char* pszIAP,int nResult)
        {
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = ((nResult==0) ? SCID::Msg::kMsgStoreRestoreSuccess : SCID::Msg::kMsgStoreRestoreFailed);

            if(pszIAP!=NULL)
            {
                int nFeatureID = SCStore::getInstance()->getFeatureIDByProduct(pszIAP);
                ptrMsg->parameters.setValue(SC_KEY_FEATUREID, nFeatureID);
            }
            else
            {
                ptrMsg->parameters.setValue(SC_KEY_FEATUREID, (int)0);
            }
            SCMsgDisp()->postMessage(ptrMsg);
        }
        
        void scbStoreUserCancelled()
        {
            SCMsgDisp()->postMessage(SCID::Msg::kMsgStoreUserCancelled);
        }
        
        // nResult, 0: success; non-zero: failed
        void scbStoreRetrieveItemInfoResult(const char* pszIAP, const char* pszCurrency, float fPrice,int nResult)
        {
            SCMessage::Ptr ptrMsg = SCMessage::create();
            if(pszIAP!=NULL)
            {
                int nFeatureID = SCStore::getInstance()->getFeatureIDByProduct(pszIAP);
                ptrMsg->parameters.setValue(SC_KEY_FEATUREID, nFeatureID);
            }
            else
            {
                ptrMsg->parameters.setValue(SC_KEY_FEATUREID, (int)0);
            }
            
            if(nResult==0 && pszIAP!=NULL)
            {// all are fine
                ptrMsg->nMsgID = SCID::Msg::kMsgStoreIAPInfoSuccess;
                ptrMsg->parameters.setValue(SC_KEY_CURRENCY, SCString(pszCurrency));
                ptrMsg->parameters.setValue(SC_KEY_PRICE, fPrice);
                
                SCMsgDisp()->postMessage(ptrMsg);
            }
            else if(nResult!=0 && pszIAP!=NULL)
            {// the IAP is invalid
                
            }
            else if(nResult!=0 && pszIAP==NULL)
            {// the retrieve all failed
                ptrMsg->nMsgID = SCID::Msg::kMsgStoreIAPInfoFailed;
                SCMsgDisp()->postMessage(ptrMsg);
            }
        }
        
        ///------------- system
        void scbAlertBoxSelected(const int nAlertBoxID,const int nButton)
        {
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = SCID::Msg::kMsgAlertBoxSelected;
            ptrMsg->parameters.setValue(SC_KEY_ID, nAlertBoxID);
            ptrMsg->parameters.setValue(SC_KEY_RESULT, nButton);
            SCMsgDisp()->postMessage(ptrMsg);
        }
        
        ///------------- app
        /*
        void scbAppEnterBackground()
        {
            SCMsgDisp()->sendMessage(SCID::Msg::kMsgAppEnterBackground);
        }
        
        void scbAppEnterForeground()
        {
            SCMsgDisp()->sendMessage(SCID::Msg::kMsgAppEnterForeground);
        }

        
        void scbAppLaunched()
        {
            SCMsgDisp()->sendMessage(SCID::Msg::kMsgAppLaunch);
        }
        */
        ///------------- network
        void scbInternetReachableChanged(const bool bNewState)
        {
            
        }
        
#ifdef __cplusplus
    }
#endif  // __cplusplus
NAMESPACE_SPEEDCC_END


