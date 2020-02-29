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


#include "SCString.h"
#include "SCBaseMacros.h"
#include "SCMemAllocator.h"

#include <sstream>
#include <algorithm>

#ifndef strinc
#define strinc(pc) ((pc)+1)
#endif

NAMESPACE_SPEEDCC_BEGIN
    
///-------- SCEncodingChar
const char g_UTF8CharNumberArray[256] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1
};
    
SCEncodingChar::SCEncodingChar():_encoding(kEncodingUTF8)
{
    ::memset(_charArray,0,SC_ARRAY_LENGTH(_charArray));
}
    
SCEncodingChar::SCEncodingChar(const SCEncodingChar& encodingChar)
{
    ::memcpy(this,&encodingChar,sizeof(SCEncodingChar));
}
    
int SCEncodingChar::getUTF8CharNumber(const unsigned char uc)
{
    return g_UTF8CharNumberArray[uc];
}
    
SCEncodingChar& SCEncodingChar::operator=(const SCEncodingChar& encodingChar)
{
    ::memcpy(this,&encodingChar,sizeof(SCEncodingChar));
    return *this;
}
    
SCEncodingChar& SCEncodingChar::operator=(const char c)
{
    _charArray[0] = c;
    _encoding = kEncodingUTF8;
    return *this;
}
    
int SCEncodingChar::getLength() const
{
    SC_RETURN_IF(this->isNull(), 0);
    SC_RETURN_IF(_encoding==kEncodingUTF16, 2);
    SC_RETURN_IF(_encoding==kEncodingUTF8, g_UTF8CharNumberArray[(unsigned char)_charArray[0]]);
    SCASSERT(false);
    return 0;
}
    
void SCEncodingChar::setEncoding(const EEncodingType encoding)
{
    if(encoding!=_encoding)
    {
        if(_encoding==kEncodingUTF8 && encoding==kEncodingUTF16)
        {// utf8 => utf16
            unsigned char ch = (unsigned char)_charArray[0];
            int todo;
            unsigned short  uni = 0;
                
            if(ch < 128)
            {
                todo = 1;
                uni = ch & 0x7f;
            }
            else if((ch & 0xe0) == 0xc0)
            {
                todo = 2;
                uni = ch & 0x1f;
            }
            else if((ch & 0xf0) == 0xe0)
            {
                todo = 3;
                uni = ch & 0x0f;
            }
            else if((ch & 0xf8) == 0xf0)
            {
                todo = 4;
                uni = ch & 0x07;
            }
            else if((ch & 0xfc) == 0xf8)
            {
                todo = 5;
                uni = ch & 0x03;
            }
            else if((ch & 0xfe) == 0xfc)
            {
                todo = 6;
                uni = ch & 0x01;
            }
            else
            {
                SCASSERT(false);
                todo = -1;
            }
                
            for(int i=1; i<todo; ++i)
            {
                if(((unsigned char)_charArray[i] & 0xc0) != 0x80)
                {
                    SCASSERT(false);
                    uni = -1;
                    break;
                }
                uni <<= 6;
                uni |= ((unsigned char)_charArray[i] & 0x3f);
            }
                
            *((unsigned short*)_charArray) = uni;
        }
        else if(_encoding==kEncodingUTF16 && encoding==kEncodingUTF8)
        {// utf16 => utf8
            unsigned short c = *((unsigned short*)_charArray);
            unsigned int len = 0;
            int first;
            int i;
                
            if(c < 0x80)
            {
                first = 0;
                len = 1;
            }
            else if(c < 0x800)
            {
                first = 0xc0;
                len = 2;
            }
            else
            {
                first = 0xe0;
                len = 3;
            }
                
            for(i = len - 1; i > 0; --i)
            {
                _charArray[i] = (c & 0x3f) | 0x80;
                c >>= 6;
            }
            _charArray[0] = c | first;
                
        }
        else
        {
            SCASSERT(false);
        }
            
        _encoding = encoding;
    }
}
    
///----------- SCString
// empty string buffer reference always 0
unsigned char	SCString::_emptyBuf[sizeof(SCString::SStringDesc)+sizeof(char)*SCString::kEndingNullSize] = {0};
    
void SCString::allocBuf(const int nStringSize)
{
    if(nStringSize>0)
    {
        const int nBufferSize = nStringSize+sizeof(SStringDesc)+SCString::kEndingNullSize;
            
        SStringDesc* pDesc = (SStringDesc*)SCMemAllocator::allocate(nBufferSize);
        pDesc->nMallocBufSize = nBufferSize;
        pDesc->encoding = SCEncodingChar::kEncodingUTF8;
        //SCLog("SCString allocate: %d %p",nBufferSize,pDesc);
            
        _pchStrData = (char*)pDesc->getStringPtr();
        ::memset(_pchStrData,0,pDesc->getStrBufSize());
            
        pDesc->nRefs = 1; // reference 1 times
        pDesc->nUsedSize = 0; // length is 0
    }
    else
    {
        _pchStrData = (char*)(this->getEmptyBuffer())->getStringPtr();
    }
}
    
void SCString::freeBuf()
{
    auto pDesc = this->getStringDesc();
    //SCLog("SCString deallocate: %d %p",pDesc->nMallocBufSize,pDesc);
    SCMemAllocator::deallocate(pDesc, pDesc->nMallocBufSize);
    _pchStrData = nullptr;
        
}
    
int SCString::decreaseRef()
{
    SCASSERT(nullptr!=_pchStrData);
        
    if(this->getStringDesc()!=this->getEmptyBuffer())
    {// if not empty string
            
        const int nNewRef = --(this->getStringDesc()->nRefs);
            
        if(nNewRef==0)
        {
            this->freeBuf();
        }
            
        return nNewRef;
    }
        
    return 1; // empty buffer always 1 ref
}
    
    
int SCString::increaseRef() const
{
    SCASSERT(nullptr!=_pchStrData);
        
    if(this->getStringDesc()!=this->getEmptyBuffer())
    {// if not empty string
        return (++this->getStringDesc()->nRefs);
    }
        
    return 1; // empty buffer always 1 ref
}
    
void SCString::beforeWrite(const int nStringSize)
{
    bool bNew = true;
        
    if(_pchStrData!=nullptr && this->getStringDesc()!=this->getEmptyBuffer())
    {
        SStringDesc* pDesc = this->getStringDesc();
        if(1==pDesc->nRefs && (pDesc->getStrBufSize() > nStringSize+(int)sizeof(char)))
        {
            memset(_pchStrData,0,pDesc->getStrBufSize());
            pDesc->nUsedSize = 0;
            bNew = false;
        }
    }
        
    if(bNew)
    {
        this->decreaseRef();
        this->allocBuf(nStringSize);
    }
}
    
void SCString::cloneBeforeWrite()
{
    if(this->getRefCount()==1)
    {
        return;
    }
        
    const int nOrgLen = this->getStringDesc()->nUsedSize;
        
    SCString sb = *this;
        
    this->beforeWrite(nOrgLen);
        
    ::memcpy(_pchStrData,sb._pchStrData,nOrgLen);
    this->getStringDesc()->nUsedSize = nOrgLen;
}
    
//-------- SCString operation function
    
SCString::SCString():
_pchStrData(nullptr)
{
    this->setEmpty();
}
    
SCString::SCString(const SCString& strString):
_pchStrData(nullptr)
{
    strString.increaseRef();
    _pchStrData = (char*)strString.getStringDesc()->getStringPtr();
}
    
SCString::SCString(const char ch):
_pchStrData(nullptr)
{
    this->allocBuf(sizeof(char));
    this->getStringDesc()->nUsedSize = sizeof(char);
        
    ::memset(_pchStrData, ch, 1);
}
    
SCString::SCString(const unsigned char byte)
{
    char szBuf[32+1] = {0};
    sprintf(szBuf, "%d",byte);
        
    int nLenOfByte = (int)strlen(szBuf);
        
    this->allocBuf(nLenOfByte);
    strcpy(_pchStrData,szBuf);
        
    this->getStringDesc()->nUsedSize = nLenOfByte;
        
}
    
SCString::SCString(const long lNumber)
{
    char szBuf[64+1] = {0};
    sprintf(szBuf, "%ld",lNumber);
        
    int nLenOfByte = (int)strlen(szBuf);
        
    this->allocBuf(nLenOfByte);
    strcpy(_pchStrData,szBuf);
        
    this->getStringDesc()->nUsedSize = nLenOfByte;
}
    
SCString::SCString(const unsigned long ulNumber)
{
    char szBuf[64+1] = {0};
    sprintf(szBuf, "%lu",ulNumber);
        
    int nLenOfByte = (int)strlen(szBuf);
        
    this->allocBuf(nLenOfByte);
    strcpy(_pchStrData,szBuf);
        
    this->getStringDesc()->nUsedSize = nLenOfByte;
}
    
SCString::SCString(const INT64 llNumber)
{
    char szBuf[64+1] = {0};
    sprintf(szBuf, "%lld",llNumber);
        
    int nLenOfByte = (int)strlen(szBuf);
        
    this->allocBuf(nLenOfByte);
    strcpy(_pchStrData,szBuf);
        
    this->getStringDesc()->nUsedSize = nLenOfByte;
}
    
SCString::SCString(const float fNumber)
{
    char szBuf[64+1] = {0};
    sprintf(szBuf, "%.2f",fNumber);
        
    int nLenOfByte = (int)strlen(szBuf);
        
    this->allocBuf(nLenOfByte);
    strcpy(_pchStrData,szBuf);
        
    this->getStringDesc()->nUsedSize = nLenOfByte;
}
    
SCString::SCString(const double dNumber)
{
    char szBuf[64+1] = {0};
    sprintf(szBuf, "%.2f",dNumber);
        
    int nLenOfByte = (int)strlen(szBuf);
        
    this->allocBuf(nLenOfByte);
    strcpy(_pchStrData,szBuf);
        
    this->getStringDesc()->nUsedSize = nLenOfByte;
}
    
SCString::SCString(const std::string& str):
_pchStrData(nullptr)
{
    if(str.empty())
    {
        this->setEmpty();
    }
    else
    {
        const auto nLen = str.size();
            
        this->allocBuf((int)nLen);
        ::memcpy(_pchStrData,str.c_str(),nLen);
        this->getStringDesc()->nUsedSize = (decltype(SStringDesc::nUsedSize)) nLen;
    }
}
    
SCString::SCString(const int nNumber):
_pchStrData(nullptr)
{
    char szBuf[32+1] = {0};
    sprintf(szBuf, "%d",nNumber);
        
    int nLenOfByte = (int)strlen(szBuf);
        
    this->allocBuf(nLenOfByte);
    strcpy(_pchStrData,szBuf);
        
    this->getStringDesc()->nUsedSize = nLenOfByte;
}
    
SCString::SCString(const unsigned int uNumber):
_pchStrData(nullptr)
{
    char szBuf[32+1] = {0};
    sprintf(szBuf, "%u",uNumber);
        
    int nLenOfByte = (int)strlen(szBuf);
        
    this->allocBuf(nLenOfByte);
    strcpy(_pchStrData,szBuf);
        
    this->getStringDesc()->nUsedSize = nLenOfByte;
}
    
SCString::SCString(const unsigned short* pszStr):
_pchStrData(nullptr)
{
    SCASSERT(pszStr!=nullptr);
        
    const unsigned short* p = pszStr;
    int nLen = 0;
    while(*p)
    {
        ++p;
        ++nLen;
    }
        
    if(nLen>0)
    {
        this->allocBuf(nLen*2);
        ::memcpy(_pchStrData,pszStr,nLen*2);
        this->getStringDesc()->nUsedSize = nLen*2;
    }
    else
    {
        this->setEmpty();
    }
        
    this->getStringDesc()->encoding = SCEncodingChar::kEncodingUTF16;
}
    
SCString::SCString(const char* pszStr):
_pchStrData(nullptr)
{
    const auto nLen = pszStr==nullptr ? 0 : strlen(pszStr);
        
    if(nLen>0)
    {
        this->allocBuf((int)nLen);
        ::memcpy(_pchStrData,pszStr,nLen);
        this->getStringDesc()->nUsedSize = (decltype(SStringDesc::nUsedSize))nLen;
    }
    else
    {
        this->setEmpty();
    }
}
    
SCString::SCString(const void* pData,const int nSize):
_pchStrData(nullptr)
{
    if(pData!=nullptr && nSize>0)
    {
        this->allocBuf(nSize + kEndingNullSize);
        ::memcpy(_pchStrData,pData,nSize);
        this->getStringDesc()->nUsedSize = strlen((const char*)pData);
    }
    else
    {
        this->setEmpty();
    }
}
    
SCString::SCString(const SCEncodingChar& encodingChar):
_pchStrData(nullptr)
{
    if(!encodingChar.isNull())
    {
        int nLen = encodingChar.getLength();
        this->allocBuf(nLen);
        ::memcpy(_pchStrData,encodingChar._charArray,nLen);
        this->getStringDesc()->nUsedSize = nLen;
    }
    else
    {
        this->setEmpty();
    }
        
    this->getStringDesc()->encoding = encodingChar._encoding;
}
    
SCString::SCString(int,const char* pszFormat, ...):
_pchStrData(nullptr)
{
    this->setEmpty();
        
    va_list argList;
    va_start(argList, pszFormat);
    this->formatV(pszFormat, argList);
    va_end(argList);
}
    
SCString::~SCString()
{
    this->decreaseRef();
}
    
void SCString::setEmpty()
{
    if(_pchStrData!=nullptr && this->getRefCount()>0)
    {
        this->decreaseRef();
    }
        
    _pchStrData = (char*)(this->getEmptyBuffer())->getStringPtr();
}
    
void SCString::format(const char* pszFormat, ...)
{
    va_list argList;
    va_start(argList, pszFormat);
    this->formatV(pszFormat, argList);
    va_end(argList);
}
    
void SCString::formatV(const char* pszFormat, va_list argList)
{
    SCASSERT(pszFormat!=nullptr);
        
    SC_RETURN_V_IF(pszFormat==nullptr);
        
    //va_list argListSave = argList;
    va_list argListSave;
    va_copy(argListSave, argList);
        
    // calcuate max buffer needs that will allocate from heap
    // following specifier refer to http://www.cplusplus.com/reference/cstdio/printf/
    int nMaxLen = 0;
    for(const char* psz = pszFormat; *psz!='\0'; psz = psz+1)
    {
        if (*psz!='%' || *(psz = psz+1)=='%')
        {
            nMaxLen += 1;
            continue;
        }
            
        int nItemLen = 0;
            
        int nWidth = 0;
        for (; *psz!='\0'; psz = (psz+1))
        {
                
            if (*psz=='#')
            {
                nMaxLen += 2; // for '0x'
            }
            else if (*psz=='*')
            {
                nWidth = va_arg(argList, int);
            }
            else if (*psz=='-' || *psz=='+' || *psz=='0' || *psz==' ')
            {
                    
            }
            else
            {
                break;
            }
        }
            
        if (nWidth==0)
        {
            nWidth = atoi(psz);
            for (; *psz!='\0' && isdigit(*psz); psz = (psz+1))
                ;
        }
            
        SCASSERT(nWidth>=0);
            
        int nPrecision = 0;
            
        if (*psz=='.')
        {
            psz = psz+1;
                
            if (*psz=='*')
            {
                nPrecision = va_arg(argList, int);
                psz = psz+1;
            }
            else
            {
                nPrecision = atoi(psz);
                for (; *psz!='\0' && isdigit(*psz); psz = psz+1)
                    ;
            }
            SCASSERT(nPrecision >= 0);
        }
            
        int nModifier = 0;
        switch (*psz)
        {
            case 'h':
                psz = psz+1;
                break;
            case 'l':
                psz = psz+1;
                break;
                    
                // modifiers that do not affect size
            case 'F':
            case 'L':
                psz = psz+1;
                break;
        }
            
            
        // should be on specifier
        switch (*psz | nModifier)
        {
                // single characters
            case 'c':
            case 'C':
                nItemLen = 2;
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS || CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
                va_arg(argList, int);
#else
                va_arg(argList, char);
#endif
                    
                break;
                    
                // strings
            case 's':
            case 'S':
            {
                const char* pstrNextArg = va_arg(argList, const char*);
                if (pstrNextArg==nullptr)
                {
                    nItemLen = 6; // "(nullptr)"
                }
                else
                {
                    nItemLen = (int)strlen(pstrNextArg);
                    nItemLen = MAX(1, nItemLen);
                }
            }
                break;
        }
            
        // adjust nItemLen for strings
        if (nItemLen!=0)
        {
            if (nPrecision!=0)
            {
                nItemLen = MIN(nItemLen, nPrecision);
            }
            nItemLen = MAX(nItemLen, nWidth);
        }
        else
        {
            switch (*psz)
            {
                    // integers
                case 'd':
                case 'i':
                case 'u':
                case 'x':
                case 'X':
                case 'o':
                {
                    va_arg(argList, int);
                    nItemLen = 32/2;
                    nItemLen = MAX(nItemLen, nWidth+nPrecision);
                }
                    break;
                        
                case 'e':
                case 'g':
                case 'G':
                {
                    va_arg(argList, double);
                    nItemLen = 128/2;
                    nItemLen = MAX(nItemLen, nWidth+nPrecision);
                }
                    break;
                        
                case 'f':
                {
                    va_arg(argList, double);
                    nItemLen = 128/2;
                    nItemLen = MAX(nItemLen, 312+nPrecision);
                }
                    break;
                        
                case 'p':
                {
                    va_arg(argList, void*);
                    nItemLen = 32/2;
                    nItemLen = MAX(nItemLen, nWidth+nPrecision);
                }
                    break;
                        
                case 'n':
                    va_arg(argList, int*);
                    break;
                        
                default:
                    SCASSERT(false);
            }
        }
            
        // adjust nMaxLen for output nItemLen
        nMaxLen += nItemLen;
    }
        
    SCString strTem = *this;
        
    this->beforeWrite(nMaxLen);
        
    int nLen = vsprintf((char*)_pchStrData, pszFormat, argListSave);
        
    if(nLen>0)
    {
        this->getStringDesc()->nUsedSize = nLen;
    }
    else
    {
        this->setEmpty();
    }
        
    va_end(argListSave);
}
    
int SCString::getEncodingCharCount() const
{
    int nRet = 0;
    char* pScan = _pchStrData;
        
    switch(this->getEncoding())
    {
        case SCEncodingChar::kEncodingUTF8:
            while(*pScan)
            {
                pScan += g_UTF8CharNumberArray[(unsigned char)*pScan];
                ++nRet;
            }
            break;
                
        case SCEncodingChar::kEncodingUTF16:
            SCASSERT(this->getLength()%2==0);
            nRet = this->getLength()/2;
            break;
                
        default: SCASSERT(false);
    }
        
    return nRet;
}
    
void SCString::setEncoding(const SCEncodingChar::EEncodingType encoding)
{
    if(encoding!=this->getEncoding())
    {
        if(!this->isEmpty())
        {
            if(this->getEncoding()==SCEncodingChar::kEncodingUTF8 && encoding==SCEncodingChar::kEncodingUTF16)
            {// utf8 => utf16
                int nBufSize = (this->getEncodingCharCount()+1)*2;
                char* pBuf = (char*)SCMemAllocator::allocate(nBufSize);
                ::memset(pBuf,0,nBufSize);
                unsigned short* pUTF16 = (unsigned short*)pBuf;
                    
                this->foreachEncodingChar([&pUTF16](const SCEncodingChar& encodingChar) ->bool
                                            {
                                                SCEncodingChar resultChar = encodingChar;
                                                resultChar.setEncoding(SCEncodingChar::kEncodingUTF16);
                                                *pUTF16 = *((unsigned short*)resultChar._charArray);
                                                ++pUTF16;
                                                return true;
                                            });
                *this = pBuf;
                SCMemAllocator::deallocate(pBuf, nBufSize);
            }
            else if(this->getEncoding()==SCEncodingChar::kEncodingUTF16 && encoding==SCEncodingChar::kEncodingUTF8)
            {// utf16 => utf8
                int nBufSize = (this->getEncodingCharCount()+1)*6;
                char* pBuf = (char*)SCMemAllocator::allocate(nBufSize);
                ::memset(pBuf,0,nBufSize);
                char* pUTF8 = pBuf;
                    
                this->foreachEncodingChar([this,&pUTF8](const SCEncodingChar& encodingChar) ->bool
                                            {
                                                SCEncodingChar resultChar = encodingChar;
                                                resultChar.setEncoding(SCEncodingChar::kEncodingUTF8);
                                                const int nLen = resultChar.getLength();
                                                ::memcpy(pUTF8,resultChar._charArray,nLen);
                                                pUTF8 += nLen;
                                                return true;
                                            });
                *this = pBuf;
                SCMemAllocator::deallocate(pBuf, nBufSize);
            }
        }
            
        this->getStringDesc()->encoding = encoding;
    }
}
    
void SCString::foreachEncodingChar(const std::function<bool(const SCEncodingChar& encodingChar)>& fun) const
{
    SC_RETURN_V_IF(this->isEmpty());
        
    SCEncodingChar encodingChar;
    encodingChar._encoding = this->getEncoding();
        
    switch(this->getEncoding())
    {
        case SCEncodingChar::kEncodingUTF8:
        {
            char* pScan = _pchStrData;
            while(*pScan)
            {
                ::memcpy(encodingChar._charArray,pScan,g_UTF8CharNumberArray[(unsigned char)*pScan]);
                SC_BREAK_IF(!fun(encodingChar));
                pScan += g_UTF8CharNumberArray[(unsigned char)*pScan];
            }
        }
            break;
                
        case SCEncodingChar::kEncodingUTF16:
        {
            unsigned short* pScan = (unsigned short*)_pchStrData;
                
            while(*pScan)
            {
                *((unsigned short*)encodingChar._charArray) = *pScan;
                SC_BREAK_IF(!fun(encodingChar));
                ++pScan;
            }
        }
            break;
                
        default: SCASSERT(false); break;
    }
}
    
char* SCString::getEncodingPointer(const int nEncodingCharIndex) const
{
    char* pRet = nullptr;
        
    switch(this->getEncoding())
    {
        case SCEncodingChar::kEncodingUTF8:
        {
            int nCount = 0;
            char* pScan = _pchStrData;
            do
            {
                if(nCount==nEncodingCharIndex)
                {
                    pRet = pScan;
                    break;
                }
                pScan += g_UTF8CharNumberArray[(unsigned char)*pScan];
                ++nCount;
            }
            while(*pScan);
        }
            break;
                
        case SCEncodingChar::kEncodingUTF16:
            pRet = (char*)((unsigned short*)_pchStrData + nEncodingCharIndex);
            break;
                
        default: SCASSERT(false); break;
    }
        
    return pRet;
}
    
void SCString::setEncodingAt(int nEncodingCharIndex, const SCEncodingChar& ch)
{
    SCASSERT(nEncodingCharIndex >= 0);
    int nEncodingCharCount = this->getEncodingCharCount();
    SCASSERT(nEncodingCharIndex < nEncodingCharCount);
        
    bool bDone = false;
        
    if(ch.getEncoding()==this->getEncoding())
    {
        bDone = true;
    }
    else if(ch.getEncoding()==SCEncodingChar::kEncodingUTF16 && this->getEncoding()==SCEncodingChar::kEncodingUTF8)
    {// utf16 => utf8
        const auto encodingChar = this->getEncodingAt(nEncodingCharIndex);
        if(g_UTF8CharNumberArray[(unsigned char)encodingChar._charArray[0]]==2)
        {
            bDone = true;
                
            SCEncodingChar chTem = ch;
            chTem.setEncoding(SCEncodingChar::kEncodingUTF8);
            this->cloneBeforeWrite();
                
            char* p = this->getEncodingPointer(nEncodingCharIndex);
            ::memcpy(p,chTem._charArray,2);
        }
    }
    else if(ch.getEncoding()==SCEncodingChar::kEncodingUTF8 && this->getEncoding()==SCEncodingChar::kEncodingUTF16)
    {// utf8 => utf16
        if(g_UTF8CharNumberArray[(unsigned char)ch._charArray[0]]==2)
        {
            bDone = true;
                
            SCEncodingChar chTem = ch;
            chTem.setEncoding(SCEncodingChar::kEncodingUTF16);
            this->cloneBeforeWrite();
                
            char* p = this->getEncodingPointer(nEncodingCharIndex);
            ::memcpy(p,chTem._charArray,2);
        }
    }
        
    if(!bDone)
    {
        SCString strTem = *this;
        strTem.setEncoding(ch.getEncoding());
        strTem.setEncodingAt(nEncodingCharIndex, ch);
        strTem.setEncoding(this->getEncoding());
        *this = strTem;
    }
}
    
SCEncodingChar SCString::getEncodingAt(const int nEncodingCharIndex) const
{
    SCASSERT(nEncodingCharIndex >= 0);
    int nEncodingCharCount = this->getEncodingCharCount();
    SCASSERT(nEncodingCharIndex < nEncodingCharCount);
        
    SCEncodingChar retChar;
        
    if(this->getEncoding()==SCEncodingChar::kEncodingUTF16)
    {
        retChar._encoding = SCEncodingChar::kEncodingUTF16;
        *((unsigned short*)retChar._charArray) = *(((unsigned short*)_pchStrData) + nEncodingCharIndex);
    }
    else if(this->getEncoding()==SCEncodingChar::kEncodingUTF8)
    {
        char* p = this->getEncodingPointer(nEncodingCharIndex);
        retChar._encoding = SCEncodingChar::kEncodingUTF8;
        ::memcpy(retChar._charArray,p,g_UTF8CharNumberArray[(unsigned char)*p]);
    }
        
    return retChar;
}
    
int SCString::getEncodingCharMemoryIndex(const int nEncodingCharIndex) const
{
    char* p = this->getEncodingPointer(nEncodingCharIndex);
        
    return (int)(p==nullptr? -1 : p - _pchStrData);
}
    
void SCString::setAt(const int nIndex, const char ch)
{
    SCASSERT(nIndex >= 0);
    SCASSERT(nIndex < this->getLength());
        
    this->cloneBeforeWrite();
    ((char*)_pchStrData)[nIndex] = ch;
}
    
char SCString::getAt(const int nIndex) const
{
    SCASSERT(nIndex >= 0);
    SCASSERT(nIndex < this->getLength());
        
    return ((char*)_pchStrData)[nIndex];
}
    
char SCString::operator[]( int nIndex ) const
{
    SCASSERT(nIndex >= 0);
    SCASSERT(nIndex < this->getLength());
        
    return ((char*)_pchStrData)[nIndex];
}
    
char& SCString::operator[](int nIndex)
{
    SCASSERT(nIndex >= 0);
    SCASSERT(nIndex < this->getLength());
        
    return((char*)_pchStrData)[nIndex];
}
    
int SCString::getStringCount(const SCString& strSub)
{
    SCASSERT(!strSub.isEmpty());
    SC_RETURN_IF(strSub.isEmpty(), 0);
        
    int nRet = 0;
    int nStart = 0;
        
    do
    {
        int n = this->find(strSub,nStart);
        SC_BREAK_IF(n<0);
        ++nRet;
        nStart = n + strSub.getLength();
    }while(true);
        
    return nRet;
}
    
int SCString::find(const char* pszSub, int nStart) const
{
    SCASSERT(pszSub!=nullptr);
        
    int nLength = this->getLength();
    SC_RETURN_IF(nStart > nLength, -1);
        
    const char* lpsz = ::strstr(_pchStrData + nStart, pszSub);
        
    return (lpsz == nullptr) ? -1 : (int)(lpsz - (char*)_pchStrData);
}
    
int SCString::find(const std::string& str, int nStart) const
{
    return this->find(str.c_str(),nStart);
}
    
int SCString::find(char ch, int nStart) const
{
    int nLength = this->getLength();
    SC_RETURN_IF(nStart >= nLength, -1);
        
    const char* lpsz = ::strchr(_pchStrData + nStart, ch);
        
    return (lpsz == nullptr) ? -1 : (int)(lpsz - (char*)_pchStrData);
}
    
int SCString::reverseFind(char ch) const
{
    const char* lpsz = ::strrchr(_pchStrData , (unsigned char)ch);
        
    return (lpsz == nullptr) ? -1 : (int)(lpsz - (char*)_pchStrData);
}
    
int SCString::reverseFind(char ch, int nStart) const
{
    int nRet = -1;
        
    if(nStart<this->getLength())
    {
        while(nStart>=0)
        {
            if(_pchStrData[nStart]==ch)
            {
                nRet = nStart;
                break;
            }
            --nStart;
        }
    }
        
    return nRet;
}
    
//int SCString::findOneOf(const char* lpszCharSet) const
//{
//    SCASSERT(lpszCharSet!=nullptr);
//
//    const char* lpsz = ::strtok(_pchStrData , lpszCharSet);
//
//    return (lpsz == nullptr) ? -1 : (int)(lpsz - (char*)_pchStrData);
//}
//
//int SCString::findOneOf(const std::string& str) const
//{
//    return this->findOneOf(str.c_str());
//}
    
int SCString::replace(const std::string& strOld,const std::string& strNew)
{
    return this->replace(strOld.c_str(), strNew.c_str());
}
    
int SCString::replace(char chOld, char chNew)
{
    int nCount = 0;
        
    if (chOld != chNew)
    {
        this->cloneBeforeWrite();
            
        char* psz = (char*)_pchStrData;
        char* pszEnd = psz + this->getLength();
        while (psz < pszEnd)
        {
            if (*psz == chOld)
            {
                *psz = chNew;
                nCount++;
            }
            psz = strinc(psz);
        }
    }
        
    return nCount;
}
    
int SCString::replace(const char* lpszOld, const char* lpszNew)
{
    SCASSERT(lpszOld!=nullptr);
    SCASSERT(lpszNew!=nullptr);
        
    SC_RETURN_IF((*lpszOld==0 || *lpszNew==0), 0);
        
    size_t nOldLength = strlen(lpszOld);
    size_t nNewLength = strlen(lpszNew);
        
    size_t start_pos = 0;
        
    std::string strThis = _pchStrData;
        
    int i = 0;
    while((start_pos = strThis.find(lpszOld, start_pos)) != std::string::npos)
    {
        strThis.replace(start_pos, nOldLength, lpszNew);
        start_pos += nNewLength;
        ++i;
    }
        
    if(i>0)
    {
        *this = strThis.c_str();
    }
        
    return (int)(nOldLength*i);
}
    
int SCString::remove(int nBegin,int nLength)
{
    SCASSERT(nBegin>=0);
        
    SC_RETURN_IF(nLength<=0, 0);
        
    const int nStrLength = this->getLength();
        
    if(nBegin+nLength>nStrLength)
    {
        return 0;
    }
    else if(nBegin==0 && nLength==nStrLength)
    {
        this->setEmpty();
        return nLength;
    }
        
    this->cloneBeforeWrite();
        
    if(nBegin+nLength-1==nStrLength)
    {
        ((char*)_pchStrData)[nBegin] = '\0';
    }
    else
    {
        ::memmove((char*)_pchStrData+nBegin,(char*)_pchStrData+nBegin+nLength,nStrLength-nLength-nBegin+1);
    }
        
    this->getStringDesc()->nUsedSize -= nLength;
        
    return nLength;
}
    
int SCString::remove(char chRemove)
{
    if(this->getLength()==1 && this->getAt(0)==chRemove)
    {
        this->setEmpty();
        return 1;
    }
        
    this->cloneBeforeWrite();
        
    char* pstrSource = (char*)_pchStrData;
    char* pstrDest = (char*)_pchStrData;
    char* pstrEnd = (char*)_pchStrData + this->getLength();
        
    while (pstrSource < pstrEnd)
    {
        if (*pstrSource != chRemove)
        {
            *pstrDest = *pstrSource;
            pstrDest = strinc(pstrDest);
        }
        pstrSource = strinc(pstrSource);
    }
    *pstrDest = '\0';
    int nCount = (int)(pstrSource - pstrDest);
    this->getStringDesc()->nUsedSize -= nCount;
        
    return nCount;
}
    
int SCString::remove(const char* pszStr)
{
    SCASSERT(pszStr!=nullptr);
        
    int nRet = 0;
    int nFindStrLength = (int)strlen(pszStr);
        
    if(nFindStrLength>0)
    {
        int nOldLen = this->getLength();
            
        do
        {
            int nBegin = this->find(pszStr);
            SC_BREAK_IF(nBegin<0);
            this->remove(nBegin,nFindStrLength);
                
        } while (1);
            
        nRet = nOldLen - this->getLength();
    }
        
    return nRet;
        
}
    
int SCString::remove(const std::string& str)
{
    return this->remove(str.c_str());
}
    
int SCString::insert(int nIndex, char ch)
{
    this->cloneBeforeWrite();
        
    if (nIndex < 0)
    {
        nIndex = 0;
    }
        
    int nNewLength = this->getLength();
        
    if (nIndex > nNewLength)
    {
        nIndex = nNewLength;
    }
        
    nNewLength++;
        
    if (this->getStringDesc()->getStrBufSize() < nNewLength)
    {
        SCString str(*this);
        const char* pstr = (char*)_pchStrData;
        this->allocBuf(nNewLength);
        ::memcpy(_pchStrData, pstr, (str.getLength()+1)*sizeof(char));
    }
        
    ::memmove((char*)_pchStrData + nIndex + 1,
                (char*)_pchStrData + nIndex, (nNewLength-nIndex)*sizeof(char));
    ((char*)_pchStrData)[nIndex] = ch;
    this->getStringDesc()->nUsedSize = nNewLength;
        
    return nNewLength;
}
    
int SCString::insert(int nIndex, const char* pstr)
{
    SCASSERT(pstr!=nullptr);
        
    if (nIndex < 0)
    {
        nIndex = 0;
    }
        
    int nInsertLength = (int)::strlen(pstr);
    int nNewLength = this->getLength();
        
    if (nInsertLength > 0)
    {
        this->cloneBeforeWrite();
        if (nIndex > nNewLength)
        {
            nIndex = nNewLength;
        }
            
        nNewLength += nInsertLength;
            
        if (this->getStringDesc()->getStrBufSize() < nNewLength)
        {
            SCString str(*this);
            const char* pstr = (char*)_pchStrData;
            this->allocBuf(nNewLength);
            memcpy(_pchStrData, pstr, str.getLength()*sizeof(char));
        }
            
        ::memmove((char*)_pchStrData + nIndex + nInsertLength,
                    (char*)_pchStrData + nIndex,
                    (nNewLength-nIndex-nInsertLength+1)*sizeof(char));
            
        ::memcpy((char*)_pchStrData + nIndex,
                    pstr, nInsertLength*sizeof(char));
            
        this->getStringDesc()->nUsedSize = nNewLength;
    }
        
    return nNewLength;
}
    
int SCString::insert(int nIndex, const std::string& str)
{
    return this->insert(nIndex, str.c_str());
}
    
    
int SCString::asInt(bool bThrow,int nDefault) const throw(int)
{
    char* It = (char*)_pchStrData;
        
    while(*It!=0)
    {
        if((*It<'0' || *It>'9') && (*It!='.') && !((*It=='-') && (It==(char*)_pchStrData)))
        {
            if(bThrow)
            {
                throw 0;
            }
            else
            {
                return nDefault;
            }
        }
        It++;
    }
        
    return ::atoi((char*)_pchStrData);
}
    
unsigned SCString::asUnsignedInt(bool bThrow,unsigned uDefault) const throw(unsigned int)
{
    char* It = (char*)_pchStrData;
        
    while(*It!=0)
    {
        if((*It<'0' || *It>'9') && (*It!='.') && (*It!='-'))
        {
            if(bThrow)
            {
                throw 0;
            }
            else
            {
                return uDefault;
            }
        }
            
        It++;
    }
        
    return (unsigned)strtoul(_pchStrData, nullptr, 0);
}
    
float SCString::asFloat(bool bThrow,float fDefault) const throw(float)
{
    char* It = (char*)_pchStrData;
        
    while(*It!=0)
    {
        if((*It<'0' || *It>'9') && (*It!='.') && !((*It=='-') && (It==(char*)_pchStrData)))
        {
            if(bThrow)
            {
                throw 0.0f;
            }
            else
            {
                return fDefault;
            }
        }
            
        It++;
    }
    return (float)::atof((char*)_pchStrData);
}
    
bool SCString::asBool(bool bThrow,bool bDefault) const throw(bool)
{
    if(this->compareNoCase("true")==0)
    {
        return true;
    }
    else if(this->compareNoCase("false")==0)
    {
        return false;
    }
        
    if(bThrow)
    {
        throw false;
    }
    else
    {
        return bDefault;
    }
}
    
int SCString::trimLeft(char c)
{
    const int nLength = this->getLength();
        
    if(nLength>0 && ((char*)_pchStrData)[0]==c)
    {
        int i=1;
            
        for(i=1;i<nLength;++i)
        {
            if(((char*)_pchStrData)[i]!=c)
            {
                break;
            }
        }
            
        this->remove(0,i);
            
        return i;
    }
        
    return 0;
}
    
int SCString::trimLeft(const char* szStr)
{
    if(szStr!=nullptr)
    {
        const int nLength = (const int)::strlen(szStr);
        const int nStrLen = this->getLength();
            
        if(nLength<nStrLen)
        {
            int nIndex = 0;
                
            while(nIndex+nLength<=nStrLen)
            {
                if(::memcmp((char*)_pchStrData+nIndex,szStr,nLength)!=0)
                {
                    break;
                }
                    
                nIndex += nLength;
            }
                
            if(nIndex>0)
            {
                this->remove(0,nIndex);
                    
                return nIndex;
            }
        }
    }
        
    return 0;
}
    
int SCString::trimLeft(const std::string& str)
{
    return this->trimLeft(str.c_str());
}
    
int SCString::trimRight(char c)
{
    const int nLength = this->getLength();
        
    if(nLength>0 && ((char*)_pchStrData)[nLength-1]==c)
    {
        int i=nLength-2;
            
        for(i=nLength-2;i>=0;--i)
        {
            if(((char*)_pchStrData)[i]!=c)
            {
                ++i;
                break;
            }
        }
            
        this->remove(i,nLength-i);
            
        return nLength-i;
    }
        
    return 0;
}
    
int SCString::trimRight(const char* szStr)
{
    if(szStr!=nullptr)
    {
        const int nLength = (const int)::strlen(szStr);
        const int nStrLen = this->getLength();
            
        if(nLength<=nStrLen)
        {
            int nIndex = nStrLen-nLength;
                
            while(nIndex>=0)
            {
                if(::memcmp((char*)_pchStrData+nIndex,szStr,nLength)!=0)
                {
                    nIndex += nLength;
                    break;
                }
                    
                nIndex -= nLength;
            }
                
            if(nIndex<nStrLen-1)
            {
                this->remove(nIndex,nStrLen-nIndex);
                    
                return nStrLen-nIndex;
            }
        }
    }
        
    return 0;
}
    
int SCString::trimRight(const std::string& str)
{
    return this->trimRight(str.c_str());
}
    
const SCString& SCString::operator=(const SCString& str)
{
    if(str._pchStrData!=this->_pchStrData)
    {
        this->decreaseRef();
            
        SStringDesc* pDesc = str.getStringDesc();
        _pchStrData = (char*)pDesc->getStringPtr();
        this->increaseRef();
    }
        
    return *this;
}
    
const SCString& SCString::operator=(char ch)
{
    this->beforeWrite(sizeof(ch));
    this->getStringDesc()->nUsedSize = sizeof(ch);
    ((char*)_pchStrData)[0] = ch;
        
    return *this;
}
    
const SCString& SCString::operator=(const char* psz)
{
    const int nLen = psz==nullptr ? 0 : (int)strlen(psz);
        
    if(nLen>0)
    {
        this->beforeWrite(nLen);
        ::memcpy(_pchStrData,psz,nLen);
        this->getStringDesc()->nUsedSize = nLen;
    }
    else
    {
        this->setEmpty();
    }
        
    return *this;
}
    
const SCString& SCString::operator=(const unsigned short* pszStr)
{
    const auto oldEncoding = this->getEncoding();
    SCString str(pszStr);
    *this = str;
    this->getStringDesc()->encoding = SCEncodingChar::kEncodingUTF16;
        
    if(oldEncoding!=SCEncodingChar::kEncodingUTF16)
    {
        this->setEncoding(oldEncoding);
    }
        
    return *this;
}
    
const SCString& SCString::operator=(const int nNumber)
{
    SCString str(0,"%d",nNumber);
    *this = str;
        
    return *this;
}
    
const SCString& SCString::operator=(const unsigned uNumber)
{
    SCString str(0,"%u",uNumber);
    *this = str;
        
    return *this;
}
    
const SCString& SCString::operator=(const std::string& str)
{
    if(str.empty())
    {
        this->setEmpty();
    }
    else
    {
        auto nLen = str.size();
            
        this->beforeWrite((int)nLen);
        this->getStringDesc()->nUsedSize = (decltype(SStringDesc::nUsedSize))nLen;
            
        ::memcpy(_pchStrData,str.c_str(),nLen);
    }
        
    return *this;
}
    
const SCString& SCString::operator=(const SCEncodingChar& encodingChar)
{
    if(encodingChar.isNull())
    {
        this->setEmpty();
    }
    else
    {
        auto nLen = encodingChar.getLength();
            
        this->beforeWrite(nLen);
        this->getStringDesc()->nUsedSize = nLen;
            
        ::memcpy(_pchStrData,encodingChar._charArray,nLen);
    }
        
    this->getStringDesc()->encoding = encodingChar.getEncoding();
        
    return *this;
}
    
const SCString& SCString::operator+=(const SCString& str)
{
    if(str.getLength()>0)
    {
        if(this->getLength()==0)
        {
            *this = str;
        }
        else
        {
            std::stringstream stream;
            stream << this->c_str() << str.c_str();
            (*this) = stream.str();
        }
    }
        
    return *this;
}
    
    
const SCString& SCString::operator+=(char ch)
{
    std::stringstream stream;
    stream << this->c_str() << ch;
    (*this) = stream.str();
        
    return *this;
}
    
const SCString& SCString::operator+=(const char* psz)
{
    if(psz!=nullptr)
    {
        SCString str(psz);
        *this += str;
    }
        
    return *this;
}
    
const SCString& SCString::operator+=(const std::string& str)
{
    SCString strResult(str);
    *this += strResult;
    return *this;
}
    
const SCString& SCString::operator+=(const int nNumber)
{
    SCString str(nNumber);
    *this += str;
    return *this;
}
    
const SCString& SCString::operator+=(const float fNumber)
{
    SCString str(fNumber);
    *this += str;
    return *this;
}
    
const SCString& SCString::operator+=(const unsigned uNumber)
{
    SCString str(uNumber);
    *this += str;
    return *this;
}
    
const SCString& SCString::operator+=(const SCEncodingChar& encodingChar)
{
    SCString str(encodingChar);
    *this += str;
    return *this;
}
    
SCString operator+(const SCEncodingChar& encodingChar,const SCString& str2)
{
    SCString strResult(encodingChar);
    strResult += str2;
    return strResult;
}
    
SCString operator+(const SCString& str2,const SCEncodingChar& encodingChar)
{
    SCString strResult(str2);
    strResult += SCString(encodingChar);
    return strResult;
}
    
SCString operator+(const SCString& str1,const SCString& str2)
{
    SCString strResult(str1);
    strResult += str2;
    return strResult;
}
    
    
SCString operator+(const SCString& str,const char ch)
{
    SCString strResult(str);
    strResult += ch;
    return strResult;
}
    
    
SCString operator+(const char ch,const SCString& str)
{
    SCString strResult(ch);
    strResult += str;
    return strResult;
}
    
SCString operator+(const SCString& str, const char* psz)
{
    SCString strResult(str);
    strResult += psz;
    return strResult;
}
    
SCString operator+(const char* psz, const SCString& str)
{
    SCString strResult(psz);
    strResult += str;
    return strResult;
}
    
SCString operator+(const std::string& str1,const SCString& str2)
{
    SCString strResult(str1);
    strResult += str2;
    return strResult;
}
    
SCString operator+(const SCString& str2,const std::string& str1)
{
    SCString strResult(str1);
    strResult = str2 + strResult;
    return strResult;
}
    
bool SCString::operator==(const char* psz) const
{
    SCASSERT(psz!=nullptr);
    return strcmp((char*)psz,(char*)_pchStrData) ? false : true;
}
    
bool SCString::operator==(char ch) const
{
    return (this->getLength()==1 && *((char*)_pchStrData)==ch);
}
    
bool SCString::operator==(const std::string& str) const
{
    return strcmp((char*)str.c_str(),(char*)_pchStrData) ? false : true;
}
    
bool SCString::operator!=(const char* psz) const
{
    SCASSERT(psz!=nullptr);
    return !((*this)==psz);
}
    
bool SCString::operator!=(char ch) const
{
    return !((*this)==ch);
}
    
bool SCString::operator!=(const std::string& str) const
{
    return !((*this)==str);
}
    
bool SCString::operator<(const SCString& str) const
{
    return strcmp((char*)str._pchStrData,(char*)_pchStrData) > 0 ? true : false;
}
    
bool SCString::operator>(const SCString& str) const
{
    return strcmp((char*)str._pchStrData,(char*)_pchStrData) < 0 ? true : false;
}
    
int SCString::compare(const char* psz) const
{
    return strcmp((char*)_pchStrData,(char*)psz);
}
    
int SCString::compare(const std::string& str) const
{
    return this->compare(str.c_str());
}
    
int SCString::compareNoCase(const char* psz) const
{
    SCASSERT(psz!=nullptr);
        
    SCString str1(*this);
    SCString str2(psz);
        
    str1.makeLower();
    str2.makeLower();
        
    return strcmp((char*)str1._pchStrData,(char*)str2._pchStrData);
}
    
int SCString::compareNoCase(const std::string& str) const
{
    return this->compareNoCase(str.c_str());
}
    
SCString SCString::mid(int nFirst, int nCount) const
{
    if(nFirst < 0)
    {
        nFirst = 0;
    }
        
    if(nCount < 0)
    {
        nCount = 0;
    }
        
    const int nCharCount = this->getLength();
        
    if (nFirst + nCount > nCharCount)
    {
        nCount = nCharCount - nFirst;
    }
        
    if (nFirst > nCharCount)
    {
        nCount = 0;
    }
        
    if (nFirst == 0 && nFirst + nCount == nCharCount)
    {
        return *this;
    }
        
    SCString strResult;
        
    if(nCount>0)
    {
        strResult.beforeWrite(nCount+2);
        ::memcpy(strResult._pchStrData,(char*)_pchStrData+nFirst,nCount);
        strResult.getStringDesc()->nUsedSize = nCount;
    }
        
    return strResult;
}
    
SCString SCString::left(int nCount) const
{
    return this->mid(0,nCount);
}
    
SCString SCString::right(int nCount) const
{
    return this->mid(this->getLength()-nCount,nCount);
}
    
void SCString::makeUpper()
{
    SC_RETURN_V_IF(this->getLength()==0);
        
    this->cloneBeforeWrite();
        
    char* p = _pchStrData;
    while ((*p = toupper(*p))) p++;
        
}
    
void SCString::makeLower()
{
    SC_RETURN_V_IF(this->getLength()==0);
        
    this->cloneBeforeWrite();
        
    char* p = _pchStrData;
    while ((*p = tolower(*p))) p++;
}
    
std::vector<SCString> SCString::split(const SCString& strSep) const
{
    std::vector<SCString> ret;
        
    if(this->getLength()>0 && strSep.getLength()>0)
    {
        int nStart = 0;
        int nPos = 0;
            
        std::list<SCString> strList;
        while(1)
        {
            nPos = this->find(strSep,nStart);
            if(nPos>=0)
            {
                strList.push_back(this->mid(nStart,nPos-nStart));
                nStart = nPos + strSep.getLength();
            }
            else if(nPos<0)
            {
                if(nStart==this->getLength())
                {
                    strList.push_back("");
                }
                else if(!strList.empty())
                {
                    strList.push_back(this->mid(nStart,this->getLength()-nStart));
                }
                    
                break;
            }
        }
            
        if(strList.empty())
        {
            strList.push_back(*this);
        }
        ret.assign(strList.begin(), strList.end());
    }
        
    return ret;
}
    
std::vector<SCString> SCString::extract(const SCString& strBeginSep,const SCString& strEndSep) const
{
    SCASSERT(!strBeginSep.isEmpty());
    SCASSERT(!strEndSep.isEmpty());
        
    std::vector<SCString> ret;
        
    SC_RETURN_IF(this->isEmpty(), ret);
    SC_RETURN_IF(strBeginSep.isEmpty(), ret);
    SC_RETURN_IF(strEndSep.isEmpty(), ret);
        
    int nBeginPos = 0;
    int nEndPos = 0;
        
    const int nBeginSepLength = strEndSep.getLength();
    const int nEndSpeLength = strEndSep.getLength();
    std::list<SCString> strList;
        
    while(1)
    {
        nBeginPos = this->find(strBeginSep,nEndPos);
        SC_BREAK_IF(nBeginPos<0);
        nEndPos = this->find(strEndSep,nBeginPos+nBeginSepLength);
        SC_BREAK_IF(nEndPos<0);
            
        strList.push_back(this->mid(nBeginPos+nBeginSepLength,nEndPos-(nBeginPos+nBeginSepLength)));
        nEndPos += nEndSpeLength;
    }
        
    ret.assign(strList.begin(), strList.end());
        
    return ret;
}

NAMESPACE_SPEEDCC_END


