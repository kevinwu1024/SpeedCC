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

#ifndef __SPEEDCC__SCDATABLOCK_H__
#define __SPEEDCC__SCDATABLOCK_H__

#include "SCBufferRefT.h"
#include "SCString.h"

NAMESPACE_SPEEDCC_BEGIN

class SCDataBlock
:public SCBufferRefT<SCBufferRefCookie>
,public SCObject
{
public:
    SC_DEFINE_CLASS_PTR(SCDataBlock)
    SCDataBlock();
    SCDataBlock(const SCString& str);
    SCDataBlock(const SCDataBlock& data);
    SCDataBlock(const void* pData,const int nDataSize);
    
    void pushByte(unsigned char byte);
    void pushWord(unsigned short word);
    void pushDword(unsigned int dword);
    void pushInt64(long long ll);
    void pushString(const SCString& str);
    
    unsigned char popByte(bool* bSuccess = nullptr);
    unsigned short popWord(bool* bSuccess = nullptr);
    unsigned int popDword(bool* bSuccess = nullptr);
    INT64 popInt64(bool* bSuccess = nullptr);
    SCString popString(const int nLen, bool* bSuccess = nullptr);
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCDATABLOCK_H__
