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

#include "SCSystem.h"
#include "../base/SCBaseMacros.h"

#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStageMacros.h"
#include "../platform/SCOSSystem.h"
#include "../cocos/SCCocosDef.h"
#include "../cocos/SCView.h"
#include "SCConfig.h"

#include <iostream>

#define RESOLUTION_RATIO_SMALL      (SCSystem::getSpeedCCOption(SC_OPTION_KEY_RATIOOFRESOLUTIONSMALL).getFloat())
#define RESOLUTION_RATIO_MEDIUM     (SCSystem::getSpeedCCOption(SC_OPTION_KEY_RATIOOFRESOLUTIONMEDIUM).getFloat())
#define RESOLUTION_RATIO_LARGE      (SCSystem::getSpeedCCOption(SC_OPTION_KEY_RATIOOFRESOLUTIONLARGE).getFloat())
#define RESOLUTION_RATIO_XLARGE     (SCSystem::getSpeedCCOption(SC_OPTION_KEY_RATIOOFRESOLUTIONXLARGE).getFloat())

#define FOLDER_ASSET_SMALL     (SCSystem::getSpeedCCOption(SC_OPTION_KEY_FOLDEROFASSETSMALL).getString())
#define FOLDER_ASSET_MEDIUM     (SCSystem::getSpeedCCOption(SC_OPTION_KEY_FOLDEROFASSETMEDIUM).getString())
#define FOLDER_ASSET_LARGE     (SCSystem::getSpeedCCOption(SC_OPTION_KEY_FOLDEROFASSETLARGE).getString())
#define FOLDER_ASSET_XLARGE     (SCSystem::getSpeedCCOption(SC_OPTION_KEY_FOLDEROFASSETXLARGE).getString())

#define RESOLUTION_BASE_LINE_WIDTH      (SCSystem::getSpeedCCOption(SC_OPTION_KEY_WIDTHOFRESOLUTIONBASELINE).getFloat())
#define RESOLUTION_BASE_LINE_HEIGHT     (SCSystem::getSpeedCCOption(SC_OPTION_KEY_HEIGHTOFRESOLUTIONBASELINE).getFloat())

using namespace cocos2d;

NAMESPACE_SPEEDCC_BEGIN

int SCSystem::s_nSupportAssetType = 0;
bool SCSystem::s_bSaveLog = true;
SCDictionary*   SCSystem::s_pOptionDic = nullptr;
ResolutionPolicy SCSystem::s_resolutionPolicy = kSCResolutionPolicy;
    
void SCSystem::setMultipleTouches(const bool bEnable)
{
    ::scSetMultipleTouch(bEnable);
}
    
bool SCSystem::getMultipleTouches()
{
    return ::scGetMultipleTouch();
}
    
void SCSystem::setGlobalDisableTouch(const bool bDisable)
{
    auto pScene = SCCCDirector()->getRunningScene();
    const bool bHas = (pScene->getChildByTag(SCLayerDisableTouch::kTAG)!=nullptr);
        
    if(bDisable && !bHas)
    {
        auto pLayer = SCLayerDisableTouch::create();
        pScene->addChild(pLayer);
    }
    else if(!bDisable && bHas)
    {
        pScene->removeChildByTag(SCLayerDisableTouch::kTAG);
    }
}
    
bool SCSystem::getGlobalDisableTouch()
{
    auto pScene = SCCCDirector()->getRunningScene();
    return (pScene->getChildByTag(SCLayerDisableTouch::kTAG)!=nullptr);
}
    
SCString SCSystem::getProductName()
{
    char szBuffer[64+1] = {0};
    ::scGetProductName(szBuffer,SC_ARRAY_LENGTH(szBuffer));
    return szBuffer;
}
    
SCString SCSystem::getBundleID()
{
    char szBuffer[64+1] = {0};
    ::scGetBundleID(szBuffer,SC_ARRAY_LENGTH(szBuffer));
    return szBuffer;
}
    
SCVersion SCSystem::getOSVersion()
{
    SCVersion ret;
    ::scGetOSVersion(&ret.nMajor,&ret.nMinor,&ret.nFix);
    return ret;
}
    
SCVersion SCSystem::getAppVersion()
{
    SCVersion ret;
    ::scGetAppVersion(&ret.nMajor,&ret.nMinor,&ret.nFix);
    return ret;
}
    
bool SCSystem::getFreeStorage(unsigned long* pInternal,unsigned long* pExternal)
{
    return ::scGetFreeStorage(pInternal,pExternal);
}
    
int SCSystem::getSupportAssetSizeType()
{
    return s_nSupportAssetType;
}
    
void SCSystem::setSupportAssetSizeType(int type)
{
    const bool b = (s_nSupportAssetType==type);
    s_nSupportAssetType = type;
        
    if(!b)
    {
        SCSystem::adapterScreenResolution(false);
    }
}
    
bool SCSystem::getDeviceInfo(SDeviceInfo& di)
{
    int nOS = 0;
    int nDistribution = 0;
    int nDeviceType = 0;
    int nIsSimulator = 0;
    int nStoreType = 0;
    char szHardware[64+1] = {0};
        
    bool bRet = ::scGetDeviceInfo(&nOS,
                                    &nDistribution,
                                    &nDeviceType,
                                    &nIsSimulator,
                                    &nStoreType,
                                    szHardware,
                                    SC_ARRAY_LENGTH(szHardware));
        
    switch(nOS)
    {
        case 1: di.osType = kOSiOS; break;
        case 2: di.osType = kOSAndroid; break;
        default: di.osType = kOSUnknown; break;
    }
        
    // device type. 0: unkown; 1: phone; 2: tablet; 3: tv; 4:vehicle; 5: desktop
    switch(nDeviceType)
    {
        case 1: di.deviceType = kDevicePhone; break;
        case 2: di.deviceType = kDeviceTablet; break;
        case 3: di.deviceType = kDeviceTV; break;
        case 4: di.deviceType = kDeviceVehicle; break;
        case 5: di.deviceType = kDeviceDesktop; break;
        default: di.deviceType = kDeviceUnknown; break;
    }
        
    switch(nDistribution)
    {
        default:
        case kDeviceManufactureUnknown:
            di.manufacture = kDeviceManufactureUnknown;
            break;

        case kDeviceManufactureApple:
        case kDeviceManufactureGoogle:
        case kDeviceManufactureSamsung:
        case kDeviceManufactureHuawei:
        case kDeviceManufactureLGE:
        case kDeviceManufactureOnePlus:
        case kDeviceManufactureSony:
        case kDeviceManufactureXiaomi:
        case kDeviceManufactureMeizu:
        case kDeviceManufactureAmazon:
            di.manufacture = (EDeviceManufacture)nDistribution;
            break;
    }
        
    switch(nStoreType)
    {
        default:
        case 0:
            di.storeType = kStoreUnknown;
            break;
                
        case kStoreAppStore:
        case kStoreGooglePlay:
        case kStoreAmazon:
            di.storeType = (EStoreType)nStoreType;
            break;
    }
        
    di.bIsSimulator = (nIsSimulator!=0);
        
    return bRet;
}
    
SCSystem::EResolutionType SCSystem::getScreenSizeType()
{
    static EResolutionType _screenSizeType = kResolutionUnkown;
    SC_RETURN_IF(_screenSizeType != kResolutionUnkown,_screenSizeType);
        
    const cocos2d::Size& gameplaySize = SCWinSize();
        
    const int nScreenSquare = (int)(gameplaySize.width * gameplaySize.height*CC_CONTENT_SCALE_FACTOR()*CC_CONTENT_SCALE_FACTOR());
    
    const auto nRatioOfResolutionXLarge = RESOLUTION_RATIO_XLARGE;
    const auto nRatioOfResolutionLarge = RESOLUTION_RATIO_LARGE;
    const auto nRatioOfResolutionMedium = RESOLUTION_RATIO_MEDIUM;
    const auto nRatioOfResolutionSmall = RESOLUTION_RATIO_SMALL;
    
    const int nBaseSquare = kSCWidthOfResolutionBaseline * kSCHeightOfResolutionBaseline;
    const int nDiffOfXLarge = abs(nScreenSquare - nRatioOfResolutionXLarge*nRatioOfResolutionXLarge*nBaseSquare);
    const int nDiffOfLarge = abs(nScreenSquare - nRatioOfResolutionLarge*nRatioOfResolutionLarge*nBaseSquare);
    const int nDiffOfMedium = abs(nScreenSquare - nRatioOfResolutionMedium*nRatioOfResolutionMedium*nBaseSquare);
    const int nDiffOfSmall = abs(nScreenSquare - nRatioOfResolutionSmall*nRatioOfResolutionSmall*nBaseSquare);
        
    int nMinimum = std::min(nDiffOfXLarge,std::min(nDiffOfLarge,std::min(nDiffOfMedium,nDiffOfSmall)));
        
    SCString strScreenSize(0,"%d x %d",(int)gameplaySize.width,(int)gameplaySize.height);
    if(nMinimum==nDiffOfXLarge)
    {
        SCLog("Screen Resolution is 'XLarge'. %s",strScreenSize.c_str());
        _screenSizeType = kResolutionXLarge;
    }
    else if(nMinimum==nDiffOfLarge)
    {
        SCLog("Screen Resolution is 'Large'. %s",strScreenSize.c_str());
        _screenSizeType = kResolutionLarge;
    }
    else if(nMinimum==nDiffOfMedium)
    {
        SCLog("Screen Resolution is 'Medium'. %s",strScreenSize.c_str());
        _screenSizeType = kResolutionMedium;
    }
    else
    {
        SCASSERT(nMinimum==nDiffOfSmall);
        SCLog("Screen Resolution is 'Small'. %s",strScreenSize.c_str());
        _screenSizeType = kResolutionSmall;
    }
        
    return _screenSizeType;
}
    
SCSystem::EResolutionType SCSystem::getAssetSizeType(const bool bCache)
{
    static EResolutionType      _resourceSizeType = kResolutionUnkown;
    SC_RETURN_IF(_resourceSizeType!=kResolutionUnkown && bCache,_resourceSizeType);
        
    const EResolutionType screenSize = SCSystem::getScreenSizeType();
        
    switch(screenSize)
    {
        case kResolutionXLarge:
        {
            if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskXLarge))
            {
                SCLog("Use 'XLarge' Resolution Assets");
                _resourceSizeType = kResolutionXLarge;
            }
            else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskLarge))
            {
                SCLog("Use 'Large' Resolution Assets");
                _resourceSizeType = kResolutionLarge;
            }
            else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskMedium))
            {
                SCLog("Use 'Medium' Resolution Assets");
                _resourceSizeType = kResolutionMedium;
            }
            else
            {
                SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskSmall));
                SCLog("Use 'Small' Resolution Assets");
                _resourceSizeType = kResolutionSmall;
            }
        }
            break;
                
        case kResolutionLarge:
        {
            if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskLarge))
            {
                SCLog("Use 'Large' Resolution Assets");
                _resourceSizeType = kResolutionLarge;
            }
            else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskMedium))
            {
                SCLog("Use 'Medium' Resolution Assets");
                _resourceSizeType = kResolutionMedium;
            }
            else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskXLarge))
            {
                SCLog("Use 'XLarge' Resolution Assets");
                _resourceSizeType = kResolutionXLarge;
            }
            else
            {
                SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskSmall));
                SCLog("Use 'Small' Resolution Assets");
                _resourceSizeType = kResolutionSmall;
            }
        }
            break;
                
        case kResolutionMedium:
        {
            if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskMedium))
            {
                SCLog("Use 'Medium' Resolution Assets");
                _resourceSizeType = kResolutionMedium;
            }
            else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskSmall))
            {
                SCLog("Use 'Small' Resolution Assets");
                _resourceSizeType = kResolutionSmall;
            }
            else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskLarge))
            {
                SCLog("Use 'Large' Resolution Assets");
                _resourceSizeType = kResolutionLarge;
            }
            else
            {
                SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskXLarge));
                SCLog("Use 'XLarge' Resolution Assets");
                _resourceSizeType = kResolutionXLarge;
            }
        }
            break;
                
        case kResolutionSmall:
        {
            if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskSmall))
            {
                SCLog("Use 'Small' Resolution Assets");
                _resourceSizeType = kResolutionSmall;
            }
            else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskMedium))
            {
                SCLog("Use 'Medium' Resolution Assets");
                _resourceSizeType = kResolutionMedium;
            }
            else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskLarge))
            {
                SCLog("Use 'Large' Resolution Assets");
                _resourceSizeType = kResolutionLarge;
            }
            else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskXLarge))
            {
                SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskXLarge));
                SCLog("Use 'XLarge' Resolution Assets");
                _resourceSizeType = kResolutionXLarge;
            }
        }
            break;
                
        default:
            SCASSERT(false);
            break;
    }
        
    return _resourceSizeType;
}



void SCSystem::initSpeedCC(const int nSupportAssetType, SCDictionary* pOptionDic)
{
    SCLog("SpeedCC v%d.%d.%d",(int)SPEEDCC_VERSION_MAJOR,(int)SPEEDCC_VERSION_MINOR,(int)SPEEDCC_VERSION_FIX);
    
    if(pOptionDic)
    {
        SCDictionary optionDic = (*pOptionDic);
        
        // remove log file
        auto logFileVal = optionDic[SC_OPTION_KEY_ISDELETELOGFILE];
        if(!logFileVal.isUnknown() && logFileVal.getBool())
        {
            SCSystem::deleteLogFile();
            optionDic.removeKey(SC_OPTION_KEY_ISDELETELOGFILE);
        }
        
        // resolution policy
        auto policyVal = optionDic[SC_OPTION_KEY_RESOLUTION_POLICY];
        if(!policyVal.isUnknown())
        {
            s_resolutionPolicy = policyVal.getObject<ResolutionPolicy>();
            optionDic.removeKey(SC_OPTION_KEY_RESOLUTION_POLICY);
        }
        
        if(s_pOptionDic)
        {
            delete s_pOptionDic;
        }
        s_pOptionDic = new SCDictionary();
        (*s_pOptionDic) = optionDic;
    }

    s_nSupportAssetType = nSupportAssetType;
    ::scInitSpeedCC(nullptr);
    SCSystem::adapterScreenResolution(false);
    SCMsgDisp()->sendMessage(SCID::Msg::kMsgAppLaunch);
}
    
cocos2d::Size SCSystem::getResolutionSize(EResolutionType type)
{
    float fRatio = 0;
    const auto fRatioOfResolutionXLarge = RESOLUTION_RATIO_XLARGE;
    const auto fRatioOfResolutionLarge = RESOLUTION_RATIO_LARGE;
    const auto fRatioOfResolutionMedium = RESOLUTION_RATIO_MEDIUM;
    const auto fRatioOfResolutionSmall = RESOLUTION_RATIO_SMALL;
    
    switch(type)
    {
        case kResolutionSmall: fRatio = fRatioOfResolutionSmall; break;
        case kResolutionMedium: fRatio = fRatioOfResolutionMedium; break;
        case kResolutionLarge: fRatio = fRatioOfResolutionLarge; break;
        case kResolutionXLarge: fRatio = fRatioOfResolutionXLarge; break;
        default: break;
    }
        
    return cocos2d::Size(RESOLUTION_BASE_LINE_WIDTH * fRatio,
                            RESOLUTION_BASE_LINE_WIDTH * fRatio);
}

cocos2d::Size SCSystem::getGamePlaySize()
{
    const cocos2d::Size winSize = SCWinSize();
    cocos2d::Size retSize = winSize;
    auto safeRect = SCCCDirector()->getSafeAreaRect();
    const int ori = ::scGetDeviceOrientation();
    
    switch(ori)
    {
        case 1: // portrait
            // notch sreen
            if((int)(winSize.height*100) > (int)(safeRect.size.height*100))
            {
                retSize.height = safeRect.size.height + safeRect.origin.y;
            }
            break;
            
        case 2: // portrait upside down
            if((int)(winSize.height*100) > (int)(safeRect.size.height*100))
            {
                retSize.height = winSize.height - safeRect.origin.y;
            }
            break;
            
        case 3: // landscape right
            // notch sreen
            if((int)(winSize.width*100) > (int)(safeRect.size.width*100))
            {
                retSize.width = winSize.width - safeRect.origin.x;
            }
            break;
            
        case 4: // landscape left
            // notch sreen
            if((int)(winSize.width*100) > (int)(safeRect.size.width*100))
            {
                retSize.width = winSize.width - safeRect.origin.x;
            }
            break;
    }
    
    return retSize;
}
    
void SCSystem::adapterScreenResolution(const bool bCache)
{
    auto assetSizeType = SCSystem::getAssetSizeType(bCache);
    auto searchOrderVector = SCCCFileUtils()->getSearchResolutionsOrder();
    
    auto strFolderOfAssetSmall = FOLDER_ASSET_SMALL + "/";
    auto strFolderOfAssetMedium = FOLDER_ASSET_MEDIUM + "/";
    auto strFolderOfAssetLarge = FOLDER_ASSET_LARGE + "/";
    auto strFolderOfAssetXLarge = FOLDER_ASSET_XLARGE + "/";
    
    std::vector<std::string> newSearchVector;
    for(const auto& it : searchOrderVector)
    {
        if(it.compare(strFolderOfAssetSmall) &&
            it.compare(strFolderOfAssetMedium) &&
            it.compare(strFolderOfAssetLarge) &&
            it.compare(strFolderOfAssetXLarge))
        {
            newSearchVector.push_back(it);
        }
    }
        
    switch(assetSizeType)
    {
        case kResolutionXLarge:
            newSearchVector.insert(newSearchVector.begin(), strFolderOfAssetXLarge.c_str());
            break;
                
        case kResolutionLarge:
            newSearchVector.insert(newSearchVector.begin(), strFolderOfAssetLarge.c_str());
            break;
                
        case kResolutionMedium:
            newSearchVector.insert(newSearchVector.begin(), strFolderOfAssetMedium.c_str());
            break;
                
        case kResolutionSmall:
            newSearchVector.insert(newSearchVector.begin(), strFolderOfAssetSmall.c_str());
            break;
                
        default:
            SCASSERT(false);
            break;
    }
        
    SCCCFileUtils()->setSearchResolutionsOrder(newSearchVector);
    
    float fContentScale = 1.0f;
        
    const bool bPortrait = ::scGetDeviceOrientation()<3;
    
    const auto fRatioOfResolutionXLarge = RESOLUTION_RATIO_XLARGE;
    const auto fRatioOfResolutionLarge = RESOLUTION_RATIO_LARGE;
    const auto fRatioOfResolutionMedium = RESOLUTION_RATIO_MEDIUM;
    const auto fRatioOfResolutionSmall = RESOLUTION_RATIO_SMALL;
    
    switch(assetSizeType)
    {
        case kResolutionXLarge:fContentScale = fRatioOfResolutionXLarge; break;
        case kResolutionLarge: fContentScale = fRatioOfResolutionLarge; break;
        case kResolutionMedium: fContentScale = fRatioOfResolutionMedium; break;
        case kResolutionSmall: fContentScale = fRatioOfResolutionSmall; break;
        default: SCASSERT(false); break;
    }
        
    if(bPortrait)
    {
        SCCCDirector()->getOpenGLView()->setDesignResolutionSize(RESOLUTION_BASE_LINE_WIDTH,
                                                                    RESOLUTION_BASE_LINE_HEIGHT,
                                                                    s_resolutionPolicy);
    }
    else
    {
        SCCCDirector()->getOpenGLView()->setDesignResolutionSize(RESOLUTION_BASE_LINE_HEIGHT,
                                                                    RESOLUTION_BASE_LINE_WIDTH,
                                                                    s_resolutionPolicy);
    }
        
    SCLog("Content Scale Factor: %.2f",fContentScale);
    SCCCDirector()->setContentScaleFactor(fContentScale);
}
    
int SCSystem::showAlertBox(const SCString& strTitle,
                        const SCString& strText,
                        const SCString& strButton1,
                        const std::function<void(int)>& resultFunc)
{
    return SCSystem::showAlertBox(strTitle,strText,strButton1,"","",resultFunc);
}
    
int SCSystem::showAlertBox(const SCString& strTitle,
                        const SCString& strText,
                        const SCString& strButton1,
                        const SCString& strButton2,
                        const std::function<void(int)>& resultFunc)
{
    return SCSystem::showAlertBox(strTitle,strText,strButton1,strButton2,"",resultFunc);
}
    
int SCSystem::showAlertBox(const SCString& strTitle,
                            const SCString& strText,
                            const SCString& strButton1,
                            const SCString& strButton2,
                            const SCString& strButton3,
                            const std::function<void(int)>& resultFunc)
{
    int nAlertBoxID = (int)::time(nullptr);
        
    if(resultFunc!=nullptr)
    {
        SCMsgDisp()->getDefaultProc()->addAlertBoxCallback(resultFunc,nAlertBoxID);
    }

    ::scShowSystemAlertBox(strTitle,
                            strText,
                            strButton1,
                            strButton2,
                            strButton3,
                            nAlertBoxID);
        
    return nAlertBoxID;
}
    
int SCSystem::showAlertBox(SCBehaviorViewGoto::Ptr ptrBvr,
                            const SCString& strTitle,
                            const SCString& strText,
                            const SCString& strButton1,
                            const SCString& strButton2,
                            const SCString& strButton3,
                            const std::function<void(int)>& resultFunc)
{
    int nAlertBoxID = (int)::time(nullptr);
        
    SCDictionary::SKVPair pairArray[] =
    {
        {SC_KEY_TITLE,strTitle},
        {SC_KEY_TEXT,strText},
        {SC_KEY_ID,nAlertBoxID},
        {SC_KEY_STRING0,strButton1},
        {SC_KEY_STRING1,strButton2},
        {SC_KEY_STRING2,strButton3}
    };
        
    SCDictionary dic(pairArray,SC_ARRAY_LENGTH(pairArray));
        
    if(resultFunc!=nullptr)
    {
        SCViewController::FinishFunc_t call = [resultFunc](void* pUserData)
        {
            int nIndex = SC_PVOID_2_NUM(pUserData);
            resultFunc(nIndex);
        };
            
        dic.setValue(SC_KEY_FINISHFUNC, call);
    }
    ptrBvr->setSceneParameter(dic);
    ptrBvr->execute();
        
    return nAlertBoxID;
}

bool SCSystem::saveImage2Album(SCString strImageFile)
{
	return ::scSaveImage2Album(strImageFile.c_str());
}
    
    
void SCSystem::log(const char* pszFormat,...)
{
    SC_RETURN_V_IF(pszFormat==nullptr);
    SC_RETURN_V_IF(*pszFormat==0);
        
    char* szMessage = (char*)malloc(16*1024+1);
    SC_RETURN_V_IF(szMessage==nullptr);
        
    va_list argList;
    va_start(argList, pszFormat);
    vsprintf(szMessage, pszFormat, argList);
    va_end(argList);
        
    struct timeval  tv;
    ::gettimeofday(&tv, nullptr);
        
    time_t now;
    time(&now);
    struct tm* p= localtime(&now);
        
    char szBuf[64] = {0};
    sprintf(szBuf, "[%02d:%02d:%02d.%03d] ",(int)p->tm_hour,(int)p->tm_min,(int)p->tm_sec,(int)tv.tv_usec/1000);
        
    static std::mutex* pLock = nullptr;
        
    if(pLock==nullptr)
    {
        pLock = new std::mutex();
    }
        
    SCASSERT(pLock!=nullptr);
    SCAutoLock(*pLock);

	SCString strLog;
	strLog.format("SpeedCC %s: %s\n", szBuf, szMessage);

	free(szMessage);
        
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    __android_log_print(ANDROID_LOG_DEBUG, "SpeedCC DEBUG", strLog.c_str());
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	OutputDebugStringA(strLog.c_str());
#else
    printf("%s",strLog.c_str());
#endif
	
	if (s_bSaveLog)
	{
		SCSystem::writeToLogFile(strLog.c_str());
	}
}

void SCSystem::setSaveLog(const bool bSave)
{
	s_bSaveLog = bSave;
}

bool SCSystem::isSaveLog()
{
	return s_bSaveLog;
}

SCString SCSystem::getLogFileData()
{
	SCString strRet;
    auto data = FileUtils::getInstance()->getDataFromFile(SCSystem::getLogFileName().c_str());
    if(data.getSize() > 0)
    {
        strRet = SCString((const void*)data.getBytes(), (int)data.getSize());
    }
	
	return strRet;
}

void SCSystem::writeToLogFile(const char* szText)
{
	SC_RETURN_V_IF(szText == NULL || *szText == 0);
	FILE* file = ::fopen(SCSystem::getLogFileName().c_str(), "a+");
	SC_RETURN_V_IF(file == NULL);
	::fwrite(szText,strlen(szText),1,file);
	::fclose(file);
	file = NULL;
}

SCString SCSystem::getLogFileName()
{
    auto strFile = SCSystem::getSpeedCCOption(SC_OPTION_KEY_SPEEDCCFOLDERNAME).getString() + "/" + SCSystem::getSpeedCCOption(SC_OPTION_KEY_LOGFILENAME).getString();
	return FileUtils::getInstance()->getWritablePath() + strFile;
}

void SCSystem::deleteLogFile()
{
	::remove(SCSystem::getLogFileName().c_str());
}

SCValue SCSystem::getSpeedCCOption(SCString strKey)
{
    SCValue retValue;
    
    SC_RETURN_IF(strKey.isEmpty(), retValue);
    
    if(s_pOptionDic)
    {
        retValue = (*s_pOptionDic).getValue(strKey);
    }
    
    if(retValue.isUnknown())
    {
        if(strKey == SC_OPTION_KEY_FOLDEROFASSETSMALL)
        {
            retValue = kSCFolderOfAssetSmall;
        }
        else if(strKey == SC_OPTION_KEY_FOLDEROFASSETMEDIUM)
        {
            retValue = kSCFolderOfAssetMedium;
        }
        else if(strKey == SC_OPTION_KEY_FOLDEROFASSETLARGE)
        {
            retValue = kSCFolderOfAssetLarge;
        }
        else if(strKey == SC_OPTION_KEY_FOLDEROFASSETXLARGE)
        {
            retValue = kSCFolderOfAssetXLarge;
        }
        else if(strKey == SC_OPTION_KEY_FOLDEROFLANGUAGE)
        {
            retValue = kSCLanguageFolder;
        }
        else if(strKey == SC_OPTION_KEY_SPEEDCCFOLDERNAME)
        {
            retValue = kSCFolderName;
        }
        else if(strKey == SC_OPTION_KEY_LOGFILENAME)
        {
            retValue = kSCLogFileName;
        }
        else if(strKey == SC_OPTION_KEY_SCREENSHOTFILENAME)
        {
            retValue = kSCScreenshotFileName;
        }
        else if(strKey == SC_OPTION_KEY_SETTINGKEYOFSOUND)
        {
            retValue = kSCSettingKeySound;
        }
        else if(strKey == SC_OPTION_KEY_SETTINGKEYOFMUSIC)
        {
            retValue = kSCSettingKeyMusic;
        }
        else if(strKey == SC_OPTION_KEY_SETTINGKEYOFSTOREFEATUREPREFIX)
        {
            retValue = kSCSettingKeyStoreFeaturePrefix;
        }
        else if(strKey == SC_OPTION_KEY_SETTINGKEYOFSTORPOINTPREFIX)
        {
            retValue = kSCSettingKeyStorePointPrefix;
        }
        else if(strKey == SC_OPTION_KEY_WIDTHOFRESOLUTIONBASELINE)
        {
            retValue = kSCWidthOfResolutionBaseline;
        }
        else if(strKey == SC_OPTION_KEY_HEIGHTOFRESOLUTIONBASELINE)
        {
            retValue = kSCHeightOfResolutionBaseline;
        }
        else if(strKey == SC_OPTION_KEY_RATIOOFRESOLUTIONSMALL)
        {
            retValue = kSCRatioOfResolutionSmall;
        }
        else if(strKey == SC_OPTION_KEY_RATIOOFRESOLUTIONMEDIUM)
        {
            retValue = kSCRatioOfResolutionMedium;
        }
        else if(strKey == SC_OPTION_KEY_RATIOOFRESOLUTIONLARGE)
        {
            retValue = kSCRatioOfResolutionLarge;
        }
        else if(strKey == SC_OPTION_KEY_RATIOOFRESOLUTIONXLARGE)
        {
            retValue = kSCRatioOfResolutionXLarge;
        }
        else if(strKey == SC_OPTION_KEY_DURATIONOFTRANSITION)
        {
            retValue = kSCDurationOfSceneTransition;
        }
        else if(strKey == SC_OPTION_KEY_MAXNUMBEROFSCENESTACK)
        {
            retValue = kSCMaxNumberSceneInStack;
        }
    }
    
    return retValue;
}

NAMESPACE_SPEEDCC_END


