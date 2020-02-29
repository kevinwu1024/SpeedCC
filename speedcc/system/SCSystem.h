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

#ifndef __SPEEDCC__SCSYSTEM_H__
#define __SPEEDCC__SCSYSTEM_H__

#include "cocos2d.h"
#include "../base/SCVersion.h"
#include "../stage/SCBehaviorCocos.h"
#include "../base/SCValue.h"

// overwrite default configs
#define SC_OPTION_KEY_FOLDEROFASSETSMALL                        "folder_of_asset_small"
#define SC_OPTION_KEY_FOLDEROFASSETMEDIUM                       "folder_of_asset_medium"
#define SC_OPTION_KEY_FOLDEROFASSETLARGE                        "folder_of_asset_large"
#define SC_OPTION_KEY_FOLDEROFASSETXLARGE                       "folder_of_asset_xlarge"
#define SC_OPTION_KEY_FOLDEROFLANGUAGE                          "folder_of_language"
#define SC_OPTION_KEY_SPEEDCCFOLDERNAME                         "speedcc_folder_name"
#define SC_OPTION_KEY_LOGFILENAME                               "log_file_name"
#define SC_OPTION_KEY_SCREENSHOTFILENAME                        "screenshot_file_name"
#define SC_OPTION_KEY_SETTINGKEYOFSOUND                         "setting_key_of_sound"
#define SC_OPTION_KEY_SETTINGKEYOFMUSIC                         "setting_key_of_music"
#define SC_OPTION_KEY_SETTINGKEYOFSTOREFEATUREPREFIX            "setting_key_of_store_feature_prefix"
#define SC_OPTION_KEY_SETTINGKEYOFSTORPOINTPREFIX               "setting_key_of_store_point_prefix"

#define SC_OPTION_KEY_WIDTHOFRESOLUTIONBASELINE                 "width_of_solution_base_line"
#define SC_OPTION_KEY_HEIGHTOFRESOLUTIONBASELINE                "height_of_solution_base_line"
#define SC_OPTION_KEY_RATIOOFRESOLUTIONSMALL                    "ratio_of_solution_small"
#define SC_OPTION_KEY_RATIOOFRESOLUTIONMEDIUM                   "ratio_of_solution_medium"
#define SC_OPTION_KEY_RATIOOFRESOLUTIONLARGE                    "ratio_of_solution_large"
#define SC_OPTION_KEY_RATIOOFRESOLUTIONXLARGE                   "ratio_of_solution_xlarge"

#define SC_OPTION_KEY_DURATIONOFTRANSITION                      "duration_of_transition"
#define SC_OPTION_KEY_MAXNUMBEROFSCENESTACK                     "max_number_of_scene_stack"

// use once option
#define SC_OPTION_KEY_ISDELETELOGFILE                           "is_delete_log_file"
#define SC_OPTION_KEY_RESOLUTION_POLICY                         "resolution_policy"


NAMESPACE_SPEEDCC_BEGIN

class SCDictionary;

class SCSystem final
{
public:
    enum EResolutionType
    {
        kResolutionUnkown               = 0,
        kResolutionSmall                = 1,
        kResolutionMedium               = 2,
        kResolutionLarge                = 3,
        kResolutionXLarge               = 4,
    };
        
    enum EOSType
    {
        kOSUnknown      = 0,
        kOSiOS          = 1,
        kOSAndroid      = 2,
    };
        
    enum EResolutionSizeBitMaskType
    {
        kResolutionBitMaskSmall       = (1<<kResolutionSmall),
        kResolutionBitMaskMedium      = (1<<kResolutionMedium),
        kResolutionBitMaskLarge       = (1<<kResolutionLarge),
        kResolutionBitMaskXLarge      = (1<<kResolutionXLarge),
    };
        
    enum EDeviceType
    {
        kDeviceUnknown  = 0,
        kDevicePhone    = 1,
        kDeviceTablet   = 2,
        kDeviceTV       = 3,
        kDeviceVehicle  = 4,
        kDeviceDesktop  = 5,
    };
        
    enum EStoreType
    {
        kStoreUnknown            = 0,
        kStoreAppStore           = 1,
        kStoreGooglePlay         = 2,
        kStoreAmazon             = 3,
    };
        
    enum EDeviceManufacture
    {
        kDeviceManufactureUnknown       = 0,
        kDeviceManufactureApple         = 1,
        kDeviceManufactureGoogle        = 2,
        kDeviceManufactureSamsung       = 3,
        kDeviceManufactureHuawei        = 4,
        kDeviceManufactureLGE           = 5,
        kDeviceManufactureOnePlus       = 6,
        kDeviceManufactureSony          = 7,
        kDeviceManufactureXiaomi        = 8,
        kDeviceManufactureMeizu         = 9,
        kDeviceManufactureAmazon        = 10,
    };
        
    struct SDeviceInfo
    {
        EOSType                 osType;
        EDeviceManufacture      manufacture; // EDeviceManufacture
        EDeviceType             deviceType;
        EStoreType              storeType;
        bool                    bIsSimulator;
        SCString                strHardware;
    };
    
    static SCValue getSpeedCCOption(SCString strKey);
    static SCVersion getOSVersion();
    static SCVersion getAppVersion();
    static bool getFreeStorage(unsigned long* pInternal,unsigned long* pExternal=NULL);
        
    static void setMultipleTouches(const bool bEnable);
    static bool getMultipleTouches();
        
    static int getSupportAssetSizeType();
    static void setSupportAssetSizeType(int type);
    static void setGlobalDisableTouch(const bool bDisable);
    static bool getGlobalDisableTouch();
        
    static int showAlertBox(const SCString& strTitle,
                                const SCString& strText,
                                const SCString& strButton1,
                                const SCString& strButton2,
                                const SCString& strButton3,
                                const std::function<void(int)>& resultFunc = NULL);
        
    static int showAlertBox(const SCString& strTitle,
                            const SCString& strText,
                            const SCString& strButton1,
                            const std::function<void(int)>& resultFunc = NULL);
        
    static int showAlertBox(const SCString& strTitle,
                            const SCString& strText,
                            const SCString& strButton1,
                            const SCString& strButton2,
                            const std::function<void(int)>& resultFunc = NULL);
        
    template<typename T>
    static int showAlertBox(const SCString& strTitle,
                            const SCString& strText,
                            const SCString& strButton1,
                            const std::function<void(int)>& resultFunc = NULL)
    {
        auto ptrBvr = SCBehaviorViewGoto::create<T>(SCViewNavigator::kLayerModal);
        return SCSystem::showAlertBox(ptrBvr,strTitle,strText,strButton1,"","",resultFunc);
    }
        
    template<typename T>
    static int showAlertBox(const SCString& strTitle,
                            const SCString& strText,
                            const SCString& strButton1,
                            const SCString& strButton2,
                            const std::function<void(int)>& resultFunc = NULL)
    {
        auto ptrBvr = SCBehaviorViewGoto::create<T>(SCViewNavigator::kLayerModal);
        return SCSystem::showAlertBox(ptrBvr,strTitle,strText,strButton1,strButton2,"",resultFunc);
    }
        
    template<typename T>
    static int showAlertBox(const SCString& strTitle,
                            const SCString& strText,
                            const SCString& strButton1,
                            const SCString& strButton2,
                            const SCString& strButton3,
                            const std::function<void(int)>& resultFunc = NULL)
    {
        auto ptrBvr = SCBehaviorViewGoto::create<T>(SCViewNavigator::kLayerModal);
        return SCSystem::showAlertBox(ptrBvr,strTitle,strText,strButton1,strButton2,strButton3,resultFunc);
    }
    
    static cocos2d::Size getResolutionSize(EResolutionType type);
    static cocos2d::Size getGamePlaySize();
        
    static bool getDeviceInfo(SDeviceInfo& di);
    static SCString getProductName();
    static SCString getBundleID();
    static EResolutionType getScreenSizeType();
    static void initSpeedCC(const int nSupportAssetType,SCDictionary* pOptionDic = nullptr);
    static EResolutionType getAssetSizeType(const bool bCache=true);
    static void adapterScreenResolution(const bool bCache=true);

	static bool saveImage2Album(SCString strImageFile);

    // log file
    static void log(const char* pszFormat,...);
	static void setSaveLog(const bool bSave);
	static bool isSaveLog();
	static SCString getLogFileData();
	static void deleteLogFile();
        
private:
    static int showAlertBox(SCBehaviorViewGoto::Ptr ptrBvr,
                            const SCString& strTitle,
                            const SCString& strText,
                            const SCString& strButton1,
                            const SCString& strButton2= "",
                            const SCString& strButton3 = "",
                            const std::function<void(int)>& resultFunc = NULL);

	static void writeToLogFile(const char* szText);
	static SCString getLogFileName();
        
private:
    static int              s_nSupportAssetType;
	static bool		        s_bSaveLog;
    static ResolutionPolicy s_resolutionPolicy;
    static SCDictionary*    s_pOptionDic;
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCSYSTEM_H__
