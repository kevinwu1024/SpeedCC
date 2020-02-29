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

#ifndef __SPEEDCC__SCVERSION_H__
#define __SPEEDCC__SCVERSION_H__

#include "SCString.h"

NAMESPACE_SPEEDCC_BEGIN

///------------- SCVersion
struct SCVersion
{
public:
    int nMajor;
    int nMinor;
    int nFix;
        
public:
    SCVersion();
    SCVersion(const SCVersion& info);
    SCVersion(const char* pszVersion);
    SCVersion(const SCString& str);
    SCVersion(unsigned uVersion);
        
    SCString getString(int nBit=2) const;
    unsigned getHexValue(int nBit=2) const;
        
    int compare(const SCVersion& info) const;
    bool operator<(const SCVersion& info) const;
    bool operator<=(const SCVersion& info) const;
    bool operator>(const SCVersion& info) const;
    bool operator>=(const SCVersion& info) const;
    bool operator==(const SCVersion& info) const;
        
private:
    void setString(const SCString& strVersion);
        
};

NAMESPACE_SPEEDCC_END

#endif //__SPEEDCC__SCVERSION_H__
