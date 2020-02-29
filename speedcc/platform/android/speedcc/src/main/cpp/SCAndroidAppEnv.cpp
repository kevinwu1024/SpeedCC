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

#define CLASS_NAME "org/speedcc/lib/JNISystem"

using namespace cocos2d;

#ifdef __cplusplus
extern "C"
{
#endif  // __cplusplus

// 0: unknown; 1: portrait; 2: portrait upside down;
// 3: landscape right; 4: landscape left
    int scGetDeviceOrientation()
    {
        int nRet = 0;

        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME,
                                           "getOrientation", "()I"))
        {
            nRet = t.env->CallStaticIntMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }

        return nRet;
    }

int scGetBundleID(char* pszBuffer, const int nBufferSize)
{
    int nRet = 0;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME,
                                         "getPackageName", "()Ljava/lang/String;"))
    {
        jstring s = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        std::string strResult = JniHelper::jstring2string(s);

        t.env->DeleteLocalRef(s);
        t.env->DeleteLocalRef(t.classID);

        const int len = (int)strResult.size();
        if(pszBuffer!=NULL && nBufferSize>len+2)
        {
            strcpy(pszBuffer,strResult.c_str());
            nRet = len;
        }
        else
        {
            nRet = len+2;
        }
    }

    return nRet;
}

int scGetProductName(char* pszBuffer,const int nBufferSize)
{
    int nRet = 0;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME,
                                         "getProductName", "()Ljava/lang/String;"))
    {
        jstring s = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        std::string strResult = JniHelper::jstring2string(s);

        t.env->DeleteLocalRef(s);
        t.env->DeleteLocalRef(t.classID);

        const int len = (int)strResult.size();
        if(pszBuffer!=NULL && nBufferSize>len+2)
        {
            strcpy(pszBuffer,strResult.c_str());
            nRet = len;
        }
        else
        {
            nRet = len+2;
        }
    }

    return nRet;
}

bool scGetAppVersion(int* pMajor,int* pMinor,int* pFix)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME,
                                         "getAppVersion", "()Ljava/lang/String;"))
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


int scGetMonthName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort)
{
    int nRet = 0;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME,
                                         "getMonthName", "(IZ)Ljava/lang/String;"))
    {
        jstring s = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID,(jint)nMonth,(jboolean)bShort);
        std::string strMonName = JniHelper::jstring2string(s);
        t.env->DeleteLocalRef(s);
        t.env->DeleteLocalRef(t.classID);

        if(pszBuf && nBufSize>strMonName.size())
        {
            nRet = (int)strMonName.size();
            strcpy(pszBuf,strMonName.c_str());
        }
        else if(pszBuf==NULL)
        {
            nRet = (int)strMonName.size() + 2;
        }
    }

    return nRet;
}

int scGetWeekName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort)
{
    int nRet = 0;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME,
                                         "getWeekName", "(IZ)Ljava/lang/String;"))
    {
        jstring s = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID,(jint)nMonth,(jboolean)bShort);
        std::string strWeekName = JniHelper::jstring2string(s);
        t.env->DeleteLocalRef(s);
        t.env->DeleteLocalRef(t.classID);

        if(pszBuf && nBufSize>strWeekName.size())
        {
            nRet = (int)strWeekName.size();
            strcpy(pszBuf,strWeekName.c_str());
        }
        else if(pszBuf==NULL)
        {
            nRet = (int)strWeekName.size() + 2;
        }
    }

    return nRet;
}


#ifdef __cplusplus
}
#endif // __cplusplus
