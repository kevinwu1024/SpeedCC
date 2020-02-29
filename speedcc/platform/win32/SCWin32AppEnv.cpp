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

#include <windows.h>

HWND g_hMainWnd = NULL;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	if (GetParent(hWnd) == NULL)
	{
		DWORD PID;
		BOOL  Result = TRUE;
		::GetWindowThreadProcessId(hWnd, &PID);
		if (PID == GetCurrentProcessId())
		{
			g_hMainWnd = hWnd;
			return false;
		}
	}
	return true;
}

HWND  getCurrentWndHandle()
{
	if (g_hMainWnd == NULL)
	{
		::EnumWindows(EnumWindowsProc, NULL);
	}
	
	return g_hMainWnd;
}

#ifdef __cplusplus
extern "C"
{
#endif  // __cplusplus


// 0: unknown; 1: portrait; 2: portrait upside down;
// 3: landscape right; 4: landscape left
    int scGetDeviceOrientation()
    {
        int nRet = 0;

		auto hWnd = getCurrentWndHandle();
		RECT rect;
		if (::GetClientRect(hWnd, &rect))
		{
			nRet = (rect.right - rect.left) > (rect.bottom-rect.top) ? 3 : 1;
		}

        return nRet;
    }

int scGetBundleID(char* pszBuffer, const int nBufferSize)
{
    int nRet = 0;

	const char szBundle[] = "org.speedcc.debug.win32";

	if (pszBuffer != nullptr && nBufferSize >= sizeof(szBundle))
	{
		strcpy(pszBuffer, szBundle);
		nRet = sizeof(szBundle) - 1;
	}

    return nRet;
}

int scGetProductName(char* pszBuffer,const int nBufferSize)
{
    int nRet = 0;

	if (pszBuffer != nullptr && nBufferSize > 0)
	{
		auto hWnd = getCurrentWndHandle();
		nRet = ::GetWindowTextA(hWnd, pszBuffer, nBufferSize);
	}

    return nRet;
}

bool scGetAppVersion(int* pMajor,int* pMinor,int* pFix)
{
	if (pMajor)
	{
		*pMajor = 1;
	}

	if (pMinor)
	{
		*pMinor = 0;
	}

	if (pFix)
	{
		*pFix = 0;
	}
    return true;
}


int scGetMonthName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort)
{
    int nRet = 0;

	if (pszBuf != nullptr && nBufSize>0)
	{
		switch (nMonth)
		{
		case 1: (bShort) ? strcpy(pszBuf, "Jan") : strcpy(pszBuf, "January"); break;
		case 2: (bShort) ? strcpy(pszBuf, "Feb") : strcpy(pszBuf, "February"); break;
		case 3: (bShort) ? strcpy(pszBuf, "Mar") : strcpy(pszBuf, "March"); break;
		case 4: (bShort) ? strcpy(pszBuf, "Apr") : strcpy(pszBuf, "April"); break;
		case 5: (bShort) ? strcpy(pszBuf, "May") : strcpy(pszBuf, "May"); break;
		case 6: (bShort) ? strcpy(pszBuf, "Jun") : strcpy(pszBuf, "June"); break;
		case 7: (bShort) ? strcpy(pszBuf, "Jul") : strcpy(pszBuf, "July"); break;
		case 8: (bShort) ? strcpy(pszBuf, "Aug") : strcpy(pszBuf, "August"); break;
		case 9: (bShort) ? strcpy(pszBuf, "Sep") : strcpy(pszBuf, "September"); break;
		case 10: (bShort) ? strcpy(pszBuf, "Oct") : strcpy(pszBuf, "October"); break;
		case 11: (bShort) ? strcpy(pszBuf, "Nov") : strcpy(pszBuf, "November"); break;
		case 12: (bShort) ? strcpy(pszBuf, "Dec") : strcpy(pszBuf, "December"); break;
		}
		nRet = strlen(pszBuf);

	}

    return nRet;
}

int scGetWeekName(char* pszBuf,const int nBufSize,const int nWeek,const bool bShort)
{
    int nRet = 0;

	if (pszBuf != nullptr && nBufSize>0)
	{
		switch (nWeek)
		{
		case 1: (bShort) ? strcpy(pszBuf, "Sun") : strcpy(pszBuf, "Sunday"); break;
		case 2: (bShort) ? strcpy(pszBuf, "Mon") : strcpy(pszBuf, "Monday"); break;
		case 3: (bShort) ? strcpy(pszBuf, "Tue") : strcpy(pszBuf, "Tuesday"); break;
		case 4: (bShort) ? strcpy(pszBuf, "Wed") : strcpy(pszBuf, "Wednesday"); break;
		case 5: (bShort) ? strcpy(pszBuf, "Thu") : strcpy(pszBuf, "Thursday"); break;
		case 6: (bShort) ? strcpy(pszBuf, "Fri") : strcpy(pszBuf, "Friday"); break;
		case 7: (bShort) ? strcpy(pszBuf, "Sat") : strcpy(pszBuf, "Saturday"); break;
		}
		nRet = strlen(pszBuf);

	}

    return nRet;
}


#ifdef __cplusplus
}
#endif // __cplusplus
