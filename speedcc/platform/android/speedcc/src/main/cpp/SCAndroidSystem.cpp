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

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../../../../../../../cocos2d-x/v3/cocos/platform/android/jni/JniHelper.h"
#include <android/log.h>

#define CLASS_NAME_SYSTEM "org/speedcc/lib/JNISystem"
#define CLASS_NAME_IAP "org/speedcc/lib/GooglePlayIAP"

using namespace cocos2d;

#ifdef __cplusplus
extern "C"
{
#endif  // __cplusplus


///--------- C => Java

void scInitSpeedCC(void* pController)
{
    // do nothing
}

bool scGetOSVersion(int* pMajor,int* pMinor,int* pFix)
{
    JniMethodInfo t;

    if (pMajor)
        *pMajor = 0;
    if (pMinor)
        *pMinor = 0;
    if (pFix)
        *pFix = 0;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "getOSVersion", "()Ljava/lang/String;"))
    {
        jstring s = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        std::string strResult = JniHelper::jstring2string(s);

        t.env->DeleteLocalRef(s);
        t.env->DeleteLocalRef(t.classID);

        std::vector<std::string> strNumberVer;

        std::stringstream ss(strResult);
        std::string item;
        while (std::getline(ss, item, '.'))
        {
            strNumberVer.push_back(item);
        }

        int i = 0;
        for (const auto& it : strNumberVer)
        {
            switch (i++)
            {
                case 0:
                    if (pMajor)
                        *pMajor = atoi(it.c_str());
                    break;
                case 1:
                    if (pMinor)
                        *pMinor = atoi(it.c_str());
                    break;
                case 2:
                    if (pFix)
                        *pFix = atoi(it.c_str());
                    break;
                default:
                    break;
            }
        }
        return true;
    }

    return false;
}

// OS type. 0: unknown; 1: iOS; 2: Android
// device type. 0: unkown; 1: phone; 2: tablet; 3: tv; 4:vehicle; 5: desktop
// store type. 0:unkown; 1: apple app store; 2: google play; 3: amazon;
//kDeviceManufactureGoogle        = 2,
//        kDeviceManufactureSamsung       = 3,
//        kDeviceManufactureHuawei        = 4,
//        kDeviceManufactureLGE           = 5,
//        kDeviceManufactureOnePlus       = 6,
//        kDeviceManufactureSony          = 7,
//        kDeviceManufactureXiaomi        = 8,
//        kDeviceManufactureMeizu         = 9,
//        kDeviceManufactureAmazon        = 10,
bool scGetDeviceInfo(int* pOSMainType,
                     int* pOSDistributionType,
                     int* pDeviceType,
                     int* pIsSimulator,
                     int* pStoreType,
                     char* pszHwBuffer,
                     const int nHwBufferSize)
{
    if(pOSMainType)
    {
        *pOSMainType = 2; // Android
    }

    JniMethodInfo t;
    if(pDeviceType && JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "getDeviceType",
                                                     "()I"))
    {
        *pDeviceType = t.env->CallStaticIntMethod(t.classID, t.methodID);

        t.env->DeleteLocalRef(t.classID);
    }

    if(pIsSimulator && JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "getProduct", "()Ljava/lang/String;"))
    {
        jstring s = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID);

        std::string strProduct = JniHelper::jstring2string(s);
        t.env->DeleteLocalRef(s);
        t.env->DeleteLocalRef(t.classID);

        *pIsSimulator = (strProduct == "google_sdk") ? 1 : 0;
    }

    if(pOSDistributionType || pszHwBuffer)
    {
        std::string strModel;
        std::string strBrand;
        std::string strManufacture;

        if(JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "getDeviceBrand", "()Ljava/lang/String;"))
        {
            jstring s = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID);
            strBrand = JniHelper::jstring2string(s);
            t.env->DeleteLocalRef(s);
            t.env->DeleteLocalRef(t.classID);
        }

        if(JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "getDeviceManufacturer", "()Ljava/lang/String;"))
        {
            jstring s = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID);
            strManufacture = JniHelper::jstring2string(s);
            t.env->DeleteLocalRef(s);
            t.env->DeleteLocalRef(t.classID);
        }



        if(pszHwBuffer)
        {
            if(JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "getDeviceModel", "()Ljava/lang/String;"))
            {
                jstring s = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID);
                strModel = JniHelper::jstring2string(s);
                t.env->DeleteLocalRef(s);
                t.env->DeleteLocalRef(t.classID);
            }

            if(strModel.size()<nHwBufferSize)
            {
                strcpy(pszHwBuffer,strModel.c_str());
            }
        }

        if(strManufacture=="Amazon")
        {// refer to:
         // https://developer.amazon.com/docs/fire-tablets/ft-device-and-feature-specifications.html
         // https://developer.amazon.com/docs/fire-tv/device-specifications.html
            *pOSDistributionType = 10;
        }
        else if(strManufacture=="Huawei")
        {
            *pOSDistributionType = 4;
        }
        else if(strManufacture=="Google")
        {
            *pOSDistributionType = 2;
        }
        else if(strManufacture=="Samsung")
        {
            *pOSDistributionType = 3;
        }
        else if(strManufacture=="Sony")
        {
            *pOSDistributionType = 7;
        }
        else if(strManufacture=="LGE")
        {
            *pOSDistributionType = 5;
        }
        else if(strManufacture=="OnePlus")
        {
            *pOSDistributionType = 6;
        }
        else if(strManufacture=="Meizu")
        {
            *pOSDistributionType = 9;
        }
        else if(strManufacture=="Xiaomi")
        {
            *pOSDistributionType = 8;
        }
    }

    if(pStoreType)
    {
        *pStoreType = 2; // google play
    }

    return true;
}

bool scGetFreeStorage(unsigned long* pInternal,unsigned long* pExternal)
{
    return false;
}

void scSetMultipleTouch(bool bEnable)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "setMultipleTouch", "(Z)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID,(jboolean)bEnable);

        t.env->DeleteLocalRef(t.classID);
    }
}

bool scGetMultipleTouch()
{
    bool bRet = false;
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "getMultipleTouch", "()Z"))
    {
        bRet = (t.env->CallStaticBooleanMethod(t.classID, t.methodID)==JNI_TRUE);

        t.env->DeleteLocalRef(t.classID);
    }
    return bRet;
}

void scShowSystemAlertBox(const char* pszTitle,
                              const char* pszMessge,
                              const char* pszButton1,
                              const char* pszButton2,
                              const char* pszButton3,
                              const int nAlertBoxID)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "showMessageBox","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V"))
    {
        jstring strTitle = t.env->NewStringUTF(pszTitle==0?"":pszTitle);
        jstring strMessage = t.env->NewStringUTF(pszMessge==0?"":pszMessge);
        jstring strButton1 = t.env->NewStringUTF(pszButton1==0?"":pszButton1);
        jstring strButton2 = t.env->NewStringUTF(pszButton2==0?"":pszButton2);
        jstring strButton3 = t.env->NewStringUTF(pszButton3==0?"":pszButton3);

        t.env->CallStaticVoidMethod(t.classID, t.methodID, strTitle,strMessage,strButton1,strButton2,strButton3,nAlertBoxID);

        t.env->DeleteLocalRef(t.classID);

        t.env->DeleteLocalRef(strTitle);
        t.env->DeleteLocalRef(strMessage);
        t.env->DeleteLocalRef(strButton1);
        t.env->DeleteLocalRef(strButton2);
        t.env->DeleteLocalRef(strButton3);
    }
}

// android feature only
bool scAndroidGetSDCardWritablePath(char* pszPathBuf, const int nBufSize)
{
    if(pszPathBuf == NULL || nBufSize <= 0)
    {
        return false;
    }

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "getSDCardWritablePath", "()Ljava/lang/String;"))
    {
        jstring s = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        std::string strResult = JniHelper::jstring2string(s);

        t.env->DeleteLocalRef(s);
        t.env->DeleteLocalRef(t.classID);

        if(nBufSize > strResult.size())
        {
            strcpy(pszPathBuf,strResult.c_str());
            return true;
        }
    }

    return false;
}

// android only
bool scAndroidInstallAPK(const char* pszAPKFile)
{
    if(pszAPKFile == NULL)
    {
        return false;
    }

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_SYSTEM, "installAPK","(Ljava/lang/String;)V"))
    {
        jstring stringAPK = t.env->NewStringUTF(pszAPKFile);

        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringAPK);
        t.env->DeleteLocalRef(stringAPK);
        t.env->DeleteLocalRef(t.classID);
    }
    
    return true;
}

bool scStorePurchaseItem(const char* pszIAP,const bool bConsumable)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_IAP, "purchaseItem","(Ljava/lang/String;Z)V"))
    {
        jstring stringSku = t.env->NewStringUTF(pszIAP);

        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringSku, bConsumable ? JNI_TRUE : JNI_FALSE);
        t.env->DeleteLocalRef(stringSku);
        t.env->DeleteLocalRef(t.classID);
    }

    return true;
}

// callback: scbPurchaseItemInfoResult()
bool scStoreRequestItemInfo(char** pszIAP,const int nIAPCount)
{
    JniMethodInfo t;

    for(int i=0;i<nIAPCount;++i)
    {
        const char* psz = pszIAP[i];

        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_IAP, "requestItemPrice","(Ljava/lang/String;)V"))
        {
            jstring stringSku = t.env->NewStringUTF(psz);

            t.env->CallStaticVoidMethod(t.classID, t.methodID, stringSku);
            t.env->DeleteLocalRef(stringSku);
            t.env->DeleteLocalRef(t.classID);
        }
    }

	return true;
}

// callback: scbPurchaseRestoreResult()
bool scStoreRestorePurchased()
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_IAP, "restoreItem","()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }

    return true;
}


///------------- Java => C
void scbAlertBoxSelected(const int nAlertBoxID,const int nButton);
void scbStorePurchaseItemResult(const char* pszIAP,int nResult);
void scbStoreRestoreItemResult(const char* pszIAP,int nResult);
void scbStoreRetrieveItemInfoResult(const char* pszIAP, const char* pszCurrency, float fPrice,int nResult);

void Java_org_speedcc_lib_JNISystem_onAlertBoxSelected(JNIEnv *env, jobject thiz,jint nButtonIndex,jint nMsgBoxID)
{
    scbAlertBoxSelected((int)nMsgBoxID,(int)nButtonIndex);
}

jint Java_org_speedcc_lib_GooglePlayIAP_onPurchaseResultEvent(JNIEnv *env,jobject thiz, jstring sku, jint result)
{
    std::string strIAP = JniHelper::jstring2string(sku);
    scbStorePurchaseItemResult(strIAP.c_str(),result);
    return 0;
}

jint Java_org_speedcc_lib_GooglePlayIAP_onPurchaseItemPriceEvent(JNIEnv *env, jobject thiz,jstring iap,jstring currency,jfloat price)
{
    std::string strIAP = JniHelper::jstring2string(iap);
    std::string strCurrency = JniHelper::jstring2string(currency);
    scbStoreRetrieveItemInfoResult(strIAP.c_str(),strCurrency.c_str(),(float)price,0);
    return 0;
}


#ifdef __cplusplus
}
#endif // __cplusplus
