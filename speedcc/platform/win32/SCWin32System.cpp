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
#include <windows.h>

#ifdef __cplusplus

HHOOK s_hMsgBoxHook;
std::string s_strMsgBoxButton1;
std::string s_strMsgBoxButton2;
std::string s_strMsgBoxButton3;

HWND  getCurrentWndHandle();

LRESULT   __stdcall   cbMessageBoxHookProc(long   nCode, WPARAM   wParam, LPARAM   lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		::SetDlgItemTextA((HWND)wParam, IDYES, s_strMsgBoxButton1.c_str());
		::SetDlgItemTextA((HWND)wParam, IDNO, s_strMsgBoxButton2.c_str());
		::SetDlgItemTextA((HWND)wParam, IDOK, s_strMsgBoxButton1.c_str());
		if (s_strMsgBoxButton3.empty())
		{
			::SetDlgItemTextA((HWND)wParam, IDCANCEL, s_strMsgBoxButton2.c_str());
		}
		else
		{
			::SetDlgItemTextA((HWND)wParam, IDCANCEL, s_strMsgBoxButton3.c_str());
		}
		
		::UnhookWindowsHookEx(s_hMsgBoxHook);

		s_strMsgBoxButton1.clear();
		s_strMsgBoxButton2.clear();
		s_strMsgBoxButton3.clear();
	}
	return   0;
}

extern "C"
{
#endif  // __cplusplus

	///------------- callback functions
	void scbAlertBoxSelected(const int nAlertBoxID, const int nButton);
	void scbStorePurchaseItemResult(const char* pszIAP, int nResult);
	void scbStoreRestoreItemResult(const char* pszIAP, int nResult);
	void scbStoreRetrieveItemInfoResult(const char* pszIAP, const char* pszCurrency, float fPrice, int nResult);

///--------- C

void scInitSpeedCC(void* pController)
{
}

bool scGetOSVersion(int* pMajor,int* pMinor,int* pFix)
{
	OSVERSIONINFOW ver;
	if (::GetVersionEx(&ver))
	{
		if (pMajor)
		{
			*pMajor = ver.dwMajorVersion;
		}

		if (pMinor)
		{
			*pMinor = ver.dwMinorVersion;
		}

		if (pFix)
		{
			*pFix = ver.dwBuildNumber;
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
        *pOSMainType = 3; // Win32
    }

	if (pOSDistributionType)
	{
		*pOSDistributionType = 0;
	}

	if (pDeviceType)
	{
		*pDeviceType = 5;
	}

	if (pIsSimulator)
	{
		*pIsSimulator = 1;
	}

	if (pStoreType)
	{
		*pStoreType = 0;
	}

	if (pszHwBuffer && nHwBufferSize > 0)
	{
		*pszHwBuffer = '\0';
	}

    return true;
}

bool scGetFreeStorage(unsigned long* pInternal,unsigned long* pExternal)
{
	if (pInternal)
	{
		*pInternal = 2 * 1024 * 1024 * 1024;
	}

	if (pInternal)
	{
		*pInternal = 0;
	}

    return true;
}

void scSetMultipleTouch(bool bEnable)
{
    
}

bool scGetMultipleTouch()
{
    return true;
}

void scShowSystemAlertBox(const char* pszTitle,
                              const char* pszMessge,
                              const char* pszButton1,
                              const char* pszButton2,
                              const char* pszButton3,
                              const int nAlertBoxID)
{
	s_hMsgBoxHook = ::SetWindowsHookExA(WH_CBT, (HOOKPROC)cbMessageBoxHookProc, NULL, GetCurrentThreadId());
	s_strMsgBoxButton1 = pszButton1;
	int nButtonType = MB_OK;
	if (pszButton2 != nullptr && *pszButton2 != '\0')
	{
		if (pszButton3 != nullptr && *pszButton3 != '\0')
		{
			s_strMsgBoxButton3 = pszButton3;
			nButtonType = MB_YESNOCANCEL;
		}
		else
		{
			s_strMsgBoxButton2 = pszButton2;
			nButtonType = MB_OKCANCEL;
		}
	}

	int nResult = ::MessageBoxA(getCurrentWndHandle(), pszMessge, pszTitle, nButtonType);
	
	switch (nButtonType)
	{
	case MB_OK: // 1 button
		scbAlertBoxSelected(nAlertBoxID,0);
		break;

	case MB_OKCANCEL: // 2 buttons
		scbAlertBoxSelected(nAlertBoxID, nResult==IDOK ? 0 : 1);
		break;

	case MB_YESNOCANCEL: // 3 buttons
		scbAlertBoxSelected(nAlertBoxID, nResult == IDYES ? 0 : ( nResult == IDNO ? 1 : 2));
		break;
	}
}

bool scCopyStringToClipboard(const char* pszText)
{
	if (pszText == nullptr)
	{
		return false;
	}

	if (pszText[0] == '\0')
	{
		return true;
	}

	int nLen = strlen(pszText) + 1;
	HANDLE hGlobalMemory = ::GlobalAlloc(GHND, nLen);
	char* lpGlobalMemory = (char*)GlobalLock(hGlobalMemory); 

	memcpy(lpGlobalMemory, pszText, nLen);

	GlobalUnlock(hGlobalMemory); 

	::OpenClipboard(getCurrentWndHandle()); 
	::EmptyClipboard(); 
	::SetClipboardData(CF_TEXT, hGlobalMemory); 
	::CloseClipboard(); 

	::GlobalFree(hGlobalMemory);

	return true;
}

void scLaunchApp(const char* pszSchema)
{
	// do nothing
}

bool scStorePurchaseItem(const char* pszIAP,const bool bConsumable)
{
	scbStorePurchaseItemResult(pszIAP,0); // always return success
    return true;
}

// callback: scbPurchaseItemInfoResult()
bool scStoreRequestItemInfo(char** pszIAP,const int nIAPCount)
{
	for (int i=0;i<nIAPCount;++i)
	{
		scbStoreRetrieveItemInfoResult(pszIAP[i], "USD", 0.99f, 0);
	}
		
    return true;
}

// callback: scbPurchaseRestoreResult()
bool scStoreRestorePurchased()
{
	scbStoreRestoreItemResult("win32-iap",0);
    return true;
}

bool scSaveImage2Album(const char* pszFile)
{
	// do nothing
	OutputDebugStringA("Win32 doesn't support scSaveImage2Album()");
	return false;
}

bool scAndroidGetSDCardWritablePath(char* pszPathBuf, const int nBufSize)
{
	OutputDebugStringA("Win32 doesn't support scAndroidGetSDCardWritablePath()");
    return false;
}
    
bool scAndroidInstallAPK(const char* pszAPKFile)
{
	OutputDebugStringA("Win32 doesn't support scAndroidInstallAPK()");
    return false;
}

#ifdef __cplusplus
}
#endif // __cplusplus
