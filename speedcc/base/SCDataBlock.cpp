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

#include "SCDataBlock.h"
#include "SCMemAllocator.h"
#include "SCBaseMacros.h"
#include "SCString.h"

NAMESPACE_SPEEDCC_BEGIN

SCDataBlock::SCDataBlock()
{
    this->clear();
}
    
SCDataBlock::SCDataBlock(const SCString& str):
SCBufferRefT<SCBufferRefCookie>((void*)str.c_str(),str.getLength())
{
}
    
SCDataBlock::SCDataBlock(const void* pData,const int nDataSize):
SCBufferRefT<SCBufferRefCookie>(pData,nDataSize)
{
}
    
SCDataBlock::SCDataBlock(const SCDataBlock& data):
SCBufferRefT<SCBufferRefCookie>((SCBufferRefT)data)
{
}

void SCDataBlock::pushByte(unsigned char byte)
{
    this->append(&byte, 1);
}

void SCDataBlock::pushWord(unsigned short word)
{
    this->append(&word, 2);
}

void SCDataBlock::pushDword(unsigned int dword)
{
    this->append(&dword, 4);
}

void SCDataBlock::pushInt64(long long ll)
{
    this->append(&ll, 8);
}

void SCDataBlock::pushString(const SCString& str)
{
    this->append(str.c_str(), str.getLength());
}

unsigned char SCDataBlock::popByte(bool* bSuccess)
{
    unsigned char ret = 0;
    bool bResult = true;
    const int nNumOfByte = 1;
    const int nCurSize = this->getSize();
    if(nCurSize < nNumOfByte)
    {
        bResult = false;
    }
    else
    {
        const char* pData = (const char*)this->getDataPtr();
        ret = *((unsigned char*)(pData+(nCurSize - nNumOfByte)));
        this->resize(nCurSize - nNumOfByte);
        
        bResult = true;
    }
    
    if(bSuccess)
    {
        *bSuccess = bResult;
    }
    
    return ret;
}

unsigned short SCDataBlock::popWord(bool* bSuccess)
{
    unsigned short ret = 0;
    bool bResult = true;
    const int nNumOfByte = 2;
    const int nCurSize = this->getSize();
    
    if(nCurSize < nNumOfByte)
    {
        bResult = false;
    }
    else
    {
        const char* pData = (const char*)this->getDataPtr();
        ret = *((unsigned short*)(pData+(nCurSize - nNumOfByte)));
        this->resize(nCurSize - nNumOfByte);
        
        bResult = true;
    }
    
    if(bSuccess)
    {
        *bSuccess = bResult;
    }
    
    return ret;
}

unsigned int SCDataBlock::popDword(bool* bSuccess)
{
    unsigned int ret = 0;
    bool bResult = true;
    const int nNumOfByte = 4;
    const int nCurSize = this->getSize();
    
    if(nCurSize < nNumOfByte)
    {
        bResult = false;
    }
    else
    {
        const char* pData = (const char*)this->getDataPtr();
        ret = *((unsigned int*)(pData+(nCurSize - nNumOfByte)));
        this->resize(nCurSize - nNumOfByte);
        
        bResult = true;
    }
    
    if(bSuccess)
    {
        *bSuccess = bResult;
    }
    
    return ret;
}

INT64 SCDataBlock::popInt64(bool* bSuccess)
{
    INT64 ret = 0;
    bool bResult = true;
    const int nNumOfByte = 8;
    const int nCurSize = this->getSize();
    
    if(nCurSize < nNumOfByte)
    {
        bResult = false;
    }
    else
    {
        const char* pData = (const char*)this->getDataPtr();
        ret = *((INT64*)(pData+(nCurSize - nNumOfByte)));
        this->resize(nCurSize - nNumOfByte);
        
        bResult = true;
    }
    
    if(bSuccess)
    {
        *bSuccess = bResult;
    }
    
    return ret;
}

SCString SCDataBlock::popString(const int nLen, bool* bSuccess)
{
    SCString ret;
    bool bResult = true;
    const int nNumOfByte = nLen;
    const int nCurSize = this->getSize();
    
    if(nLen < 0 || nCurSize < nNumOfByte)
    {
        bResult = false;
    }
    else if(nLen > 0)
    {
        const char* pData = (const char*)this->getDataPtr();
        const char* pStr= (char*)(pData+(nCurSize - nNumOfByte));
        ret = SCString(pStr,nNumOfByte);
        
        this->resize(nCurSize - nNumOfByte);
    }
    
    if(bSuccess)
    {
        *bSuccess = bResult;
    }
    
    return ret;
}

NAMESPACE_SPEEDCC_END

