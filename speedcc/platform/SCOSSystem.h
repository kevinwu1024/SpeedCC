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



#ifndef __SC__SCOSSYSTEM_H__
#define __SC__SCOSSYSTEM_H__

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
    
    ///-------- datetime
    int scGetMonthName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort);
    int scGetWeekName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort);
    
    ///-------- system
    // 0: unknown; 1: portrait; 2: portrait upside down;
    // 3: landscape right; 4: landscape left
    int scGetDeviceOrientation();
    void scInitSpeedCC(void* pController);
    bool scGetFreeStorage(unsigned long* pInternal,unsigned long* pExternal);
    bool scGetOSVersion(int* pMajor,int* pMinor,int* pFix);
    // OS type. 0: unknown; 1: iOS; 2: Android
    // OS distribution. 0: unkown; 1: offical;
    // device type. 0: unkown; 1: phone; 2: tablet; 3: tv; 4:vehicle;
    // store type. 0:unkown; 1: apple app store; 2: google play; 3: amazon;
    bool scGetDeviceInfo(int* pOSMainType,
                         int* pOSDistributionType,
                         int* pDeviceType,
                         int* pIsSimulator,
                         int* pStoreType,
                         char* pszHwBuffer,
                         const int nHwBufferSize);
    void scSetMultipleTouch(const bool bEnable);
    bool scGetMultipleTouch();
    void scShowSystemAlertBox(const char* pszTitle,
                              const char* pszMessge,
                              const char* pszButton1,
                              const char* pszButton2,
                              const char* pszButton3,
                              const int nAlertBoxID);
    bool scGetResourcePath(char* pszBuffer,const int nBufferSize);

	bool scCopyStringToClipboard(const char* pszText);
	void scLaunchApp(const char* pszSchema);
	bool scSaveImage2Album(const char* pszFile);
    
    ///-------- app
    int scGetProductName(char* pszBuffer, int nBufferSize);
    bool scGetAppVersion(int* pMajor,int* pMinor,int* pFix);
    int scGetBundleID(char* pszBuffer, int nBufferSize);
    
    ///-------- store
    // callback: scbPurchaseItemResult() 
    bool scStorePurchaseItem(const char* pszIAP,const bool bConsumable);
    // callback: scbPurchaseItemInfoResult()
    bool scStoreRequestItemInfo(char** pszIAP,const int nIAPCount);
    // callback: scbPurchaseRestoreResult()
    bool scStoreRestorePurchased();
    
    /// network
    
    //------ for Android only
    bool scAndroidGetSDCardWritablePath(char* pszPathBuf, const int nBufSize);
    bool scAndroidInstallAPK(const char* pszAPKFile);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // __SC__SCOSSYSTEM_H__
