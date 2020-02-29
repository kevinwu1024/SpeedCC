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

#ifndef __SPEEDCC__SCSTRING_H__
#define __SPEEDCC__SCSTRING_H__

#include <string>
#include <vector>
#include <functional>
#include "SCBaseMacros.h"
#include "SCObjPtrT.h"
#include "SCObject.h"

#ifdef WIN32
#pragma warning (disable:4290)
#endif

NAMESPACE_SPEEDCC_BEGIN

class SCString;
    
class SCEncodingChar final
{
    friend class SCString;
public:
    enum EEncodingType
    {
        kEncodingUTF8,
        kEncodingUTF16,
    };
        
    SCEncodingChar();
    SCEncodingChar(const SCEncodingChar& encodingChar);
        
    static int getUTF8CharNumber(const unsigned char uc);
        
    inline EEncodingType getEncoding() const {return _encoding;}
    void setEncoding(const EEncodingType encoding);
        
    SCEncodingChar& operator=(const SCEncodingChar& encodingChar);
    SCEncodingChar& operator=(const char c);
    int getLength() const;
    inline bool isNull() const {return *((unsigned short*)_charArray)==0;}
    inline char* getPointer() {return _charArray;}
        
private:
    EEncodingType   _encoding;
    char            _charArray[6];
};
    
SCString operator+(const SCString& str1,const SCString& str2);
SCString operator+(const SCString& str,const char ch);
SCString operator+(const char ch,const SCString& str);
SCString operator+(const SCString& str, const char* psz);
SCString operator+(const char* psz, const SCString& str);
    
SCString operator+(const SCString& str, const int nNumber);
//SCString operator+(const SCString& str, const float fNumber);
SCString operator+(const SCString& str, const unsigned uNumber);
    
SCString operator+(const int nNumber,const SCString& str);
//SCString operator+(const float fNumber,const SCString& str);
SCString operator+(const unsigned uNumber,const SCString& str);
    
SCString operator+(const std::string& str1,const SCString& str2);
SCString operator+(const SCString& str2,const std::string& str1);
    
SCString operator+(const SCEncodingChar& encodingChar,const SCString& str2);
SCString operator+(const SCString& str2,const SCEncodingChar& encodingChar);
    
/*!
    SCString is C string wrapper class, it provides convenient methods for handling string value.
    */
class SCString
{
private:
    struct SStringDesc
    {
        unsigned short                      nRefs;	// reference counter
        unsigned short                      nUsedSize;	// string length
        unsigned short                      nMallocBufSize;	// length of memory allocated
        SCEncodingChar::EEncodingType      encoding; // buffer encoding
            
        SStringDesc():
        nRefs(0),
        nUsedSize(0),
        nMallocBufSize(0),
        encoding(SCEncodingChar::kEncodingUTF8)
        {}
            
        inline void* getStringPtr() const { return (void*)(this+1); }
        inline int getStrBufSize() const { return nMallocBufSize-sizeof(SStringDesc);}
        inline SCEncodingChar::EEncodingType getEncoding() const {return encoding;}
    };
        
public:
    SC_DEFINE_CLASS_PTR(SCString)
    
    enum {kEndingNullSize = 2};
        
    SCString();
    SCString(const SCString& strSring);
        
    SCString(const std::string& str);
    SCString(const char ch);
    SCString(const unsigned char byte);
    SCString(const long lNumber);
    SCString(const unsigned long ulNumber);
    SCString(const INT64 llNumber);
    SCString(const float fNumber);
    SCString(const double dNumber);
    SCString(const int nNumber);
    SCString(const unsigned int uNumber);
    SCString(const SCEncodingChar& encodingChar);
    SCString(const void* pData,const int nSize);
    SCString(const char* pszStr);
    SCString(const unsigned short* pszStr); // utf16 encoding
    SCString(int,const char* pszFormat, ...);
        
    virtual ~SCString();
        
    inline int getLength() const { return (this->getStringDesc()->nUsedSize);}
    inline bool isEmpty() const {return (this->getStringDesc()->nUsedSize==0);}
    inline int getRefCount() const {return this->getStringDesc()->nRefs;}
    inline const char* c_str() const { return (const char*)_pchStrData;}
    inline operator const char*() const {return (const char*)_pchStrData;}
        
    void setEmpty();
    void format(const char* pszFormat, ...);
    void formatV(const char* pszFormat, va_list argList);
        
    // encoding
    int getEncodingCharCount() const;
    inline SCEncodingChar::EEncodingType getEncoding() const {return this->getStringDesc()->encoding;}
    void setEncoding(const SCEncodingChar::EEncodingType encoding);
    void foreachEncodingChar(const std::function<bool(const SCEncodingChar& encodingChar)>& fun) const;
        
    // assign
    const SCString& operator=(const SCString& stringSrc);
    const SCString& operator=(char ch);
    const SCString& operator=(const char* psz);
    const SCString& operator=(const unsigned short* pszStr); // utf16 encoding
    const SCString& operator=(const std::string& str);
    const SCString& operator=(const SCEncodingChar& encodingChar);
    const SCString& operator=(const int nNumber);
    //    const SCString& operator=(const float fNumber);
    const SCString& operator=(const unsigned uNumber);
        
    // connect
    friend SCString operator+(const SCString& str1,const SCString& str2);
    friend SCString operator+(const SCString& str,const char ch);
    friend SCString operator+(const char ch,const SCString& str);
    friend SCString operator+(const SCString& str, const char* psz);
    friend SCString operator+(const char* psz, const SCString& str);
        
    friend SCString operator+(const SCString& str, const int nNumber);
    friend SCString operator+(const SCString& str, const float fNumber);
    friend SCString operator+(const SCString& str, const unsigned uNumber);
        
    friend SCString operator+(const int nNumber,const SCString& str);
    friend SCString operator+(const float fNumber,const SCString& str);
    friend SCString operator+(const unsigned uNumber,const SCString& str);
        
    friend SCString operator+(const std::string& str1,const SCString& str2);
    friend SCString operator+(const SCString& str2,const std::string& str1);
        
    friend SCString operator+(const SCEncodingChar& encodingChar,const SCString& str2);
    friend SCString operator+(const SCString& str2,const SCEncodingChar& encodingChar);
        
    // connect and assign
    const SCString& operator+=(const SCString& string);
    const SCString& operator+=(char ch);
    const SCString& operator+=(const char* psz);
    const SCString& operator+=(const std::string& str);
    const SCString& operator+=(const int nNumber);
    const SCString& operator+=(const float fNumber);
    const SCString& operator+=(const unsigned uNumber);
    const SCString& operator+=(const SCEncodingChar& encodingChar);
        
    // compare
    bool operator==(const char* psz) const;
    bool operator==(const std::string& str) const;
    bool operator==(char ch) const;
        
    bool operator!=(const char* psz) const;
    bool operator!=(const std::string& str) const;
    bool operator!=(char ch) const;
        
    bool operator<(const SCString& str) const;
    bool operator>(const SCString& str) const;
        
    int compareNoCase(const char* psz) const;
    int compareNoCase(const std::string& str) const;
    int compare(const char* psz) const;
    int compare(const std::string& str) const;
        
    // extract
    SCString mid(int nFirst, int nCount) const;
    SCString left(int nCount) const;
    SCString right(int nCount) const;
        
    // find
    int find(const char* pszSub, int nStart=0) const;
    int find(char ch, int nStart=0) const;
    int find(const std::string& str, int nStart=0) const;
    int getStringCount(const SCString& strSub);
        
    int reverseFind(char ch) const;
    int reverseFind(char ch, int nStart) const;
    //    int findOneOf(const char* lpszCharSet) const;
    //    int findOneOf(const std::string& str) const;
        
    void setEncodingAt(int nEncodingCharIndex, const SCEncodingChar& ch);
    SCEncodingChar getEncodingAt(const int nEncodingCharIndex) const;
    int getEncodingCharMemoryIndex(const int nEncodingCharIndex) const;
        
    void setAt(const int nIndex, const char ch);
    char getAt(const int nIndex) const;
    char operator[](int nIndex) const;
    char& operator[](int nIndex);
        
    // edit
    int replace(char chOld, char chNew);
    int replace(const char* pszOld, const char* pszNew);
    int replace(const std::string& strOld,const std::string& strNew);
    int remove(int nBegin,int nLength=1);
    int remove(char chRemove);
    int remove(const char* pszStr);
    int remove(const std::string& str);
        
    int insert(int nIndex, const char* pstr);
    int insert(int nIndex, char ch);
    int insert(int nIndex, const std::string& str);
        
    int trimRight(char c);
    int trimRight(const char* szStr);
    int trimRight(const std::string& str);
        
    int trimLeft(char c);
    int trimLeft(const char* szStr);
    int trimLeft(const std::string& str);
        
    void makeUpper();
    void makeLower();
        
    std::vector<SCString> split(const SCString& strSep) const;
    std::vector<SCString> extract(const SCString& strBeginSep,const SCString& strEndSep) const;
        
    //    int loadFromeFile(const SCString& strFile);
    //    int saveToFile(const SCString& strFile);
        
    int asInt(bool bThrow=true,int nDefault=0) const throw(int);
    unsigned asUnsignedInt(bool bThrow=true,unsigned uDefault=0) const throw(unsigned int);
    float asFloat(bool bThrow=true,float fDefault=0.0f) const throw(float);
    bool asBool(bool bThrow=true,bool bDefault=false) const throw(bool);
        
private:
    inline SStringDesc* getStringDesc() const {return (((SStringDesc*)_pchStrData)-1); }
        
    void allocBuf(const int nStringSize);
    void freeBuf();
        
    int decreaseRef();
    int increaseRef() const;
        
    void beforeWrite(const int nStringSize);
    void cloneBeforeWrite();
        
    inline SStringDesc* getEmptyBuffer() const { return (SStringDesc*)_emptyBuf;}
    char* getEncodingPointer(const int nEncodingCharIndex) const;
        
protected:
    char*                               _pchStrData;
    static unsigned char	_emptyBuf[sizeof(SStringDesc)+sizeof(char)*kEndingNullSize];
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCSTRING_H__
