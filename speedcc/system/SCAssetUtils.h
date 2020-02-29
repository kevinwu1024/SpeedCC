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

#ifndef __SPEEDCC__SCASSETUTILS_H__
#define __SPEEDCC__SCASSETUTILS_H__

#include "../base/SCString.h"

NAMESPACE_SPEEDCC_BEGIN

class SCAssetUtils
{
public:
    static SCString createUUID();
    
    // return 0xffffffff in callback function if EOF
    static bool readFile(const SCString& strFile,const std::function<bool(const void*,unsigned int)>& funCallback);
    static void readFileAsyn(const SCString& strFile,const std::function<bool(const void*,unsigned int)>& funCallback);
    
	// block if funDoneCallback == nullptr, non-block if funDoneCallback != nullptr
    static bool copyResourceFile2Writable(const SCString& strResourceFile,const SCString& strWritableFile, const std::function<void(const bool)>& funDoneCallback = nullptr);
 
    // if nMaxDepth < 0, means always recursive
    static bool goThroughDirectory(SCString strDirectory,int nMaxDepth,const std::function<bool(const SCString& strFullPathFile,const bool bDirectory)>& funCallback);
    static void goThroughDirectoryAsyn(SCString strDirectory, int nMaxDepth, const std::function<bool(const SCString& strFullPathFile,const bool bDirectory)>& funCallback);
    
    static SCString getResourcePath();
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCASSETUTILS_H__
