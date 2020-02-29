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

#include "SCValue.h"
#include "SCDataBlock.h"
#include "SCDateTime.h"
#include "SCBaseMacros.h"
#include "SCDictionary.h"

NAMESPACE_SPEEDCC_BEGIN

SCValue::SCValue()
{
    this->createInstance();
    this->getCookieDesc()->cookie = kTypeUnknown;
}
    
SCValue::SCValue(const int nValue)
{
    this->createInstance();
        
    this->getStub()->data.nValue = nValue;
    this->getCookieDesc()->cookie = kTypeInt;
}
    
SCValue::SCValue(const bool bValue)
{
    this->createInstance();
        
    this->getStub()->data.nValue = bValue;
    this->getCookieDesc()->cookie = kTypeBool;
}
    
SCValue::SCValue(const float fValue)
{
    this->createInstance();
        
    this->getStub()->data.fValue = fValue;
    this->getCookieDesc()->cookie = kTypeFloat;
}
    
SCValue::SCValue(const double dValue)
{
    this->createInstance();
        
    this->getStub()->data.dValue = dValue;
    this->getCookieDesc()->cookie = kTypeDouble;
}
    
SCValue::SCValue(const long lValue)
{
    this->createInstance();
        
    this->getStub()->data.lValue = lValue;
    this->getCookieDesc()->cookie = kTypeLong;
}
    
SCValue::SCValue(const char cValue)
{
    this->createInstance();
        
    this->getStub()->data.cValue = cValue;
    this->getCookieDesc()->cookie = kTypeChar;
}
    
SCValue::SCValue(const unsigned char byValue)
{
    this->createInstance();
        
    this->getStub()->data.byValue = byValue;
    this->getCookieDesc()->cookie = kTypeByte;
}

SCValue::SCValue(const unsigned int nValue)
{
	this->createInstance();

	this->getStub()->data.uValue = nValue;
	this->getCookieDesc()->cookie = kTypeUInt;
}
    
SCValue::SCValue(const INT64 llValue)
{
    this->createInstance();
        
    this->getStub()->data.llValue = llValue;
    this->getCookieDesc()->cookie = kTypeInt64;
}
    
SCValue::SCValue(void* const pValue)
{
    this->createInstance();
        
    this->getStub()->data.pValue = pValue;
    this->getCookieDesc()->cookie = kTypePointer;
}
    
SCValue::SCValue(const char* pszValue)
{
    this->setString(pszValue);
}
    
SCValue::SCValue(const SCString& strValue)
{
    this->setString(strValue);
}
    
SCValue::SCValue(SCDateTime& dateTime)
{
    this->setDateTime(dateTime);
}
    
SCValue::SCValue(const SCDataBlock& dataBlock)
{
    this->setDataBlock(dataBlock);
}
    
SCValue::SCValue(const SCDictionary& dic)
{
	this->setDictionary(dic);
}

SCValue::SCValue(const std::vector<SCValue>& valueVtr)
{
    this->setArray(valueVtr);
}
    
SCValue::~SCValue()
{
}
    
void SCValue::check4Write()
{
    SC_RETURN_V_IF(this->getRefCount()!=1);
        
    switch(this->getType())
    {
        case kTypeString:
        case kTypeDateTime:
        case kTypeDataBlock:
        case kTypeArray:
        case kTypeObject:
        {
            this->decreaseRef(); // cause to free buffer and destroy object
            this->createInstance();
        }
            break;
                
        default:break;
    }
}
    
bool SCValue::isNumberType() const
{
    switch(this->getType())
    {
        case kTypeByte:
        case kTypeChar:
        case kTypeInt:
        case kTypeUInt:
        case kTypeLong:
        case kTypeInt64:
        case kTypeFloat:
        case kTypeDouble:
            return true;
                
        default: break;
    }
        
    return false;
}
    
char SCValue::getChar(bool* pResult,const bool bExactMatch) const
{
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    bool bResult = false;
    char cRet = 0;
    if(!(bExactMatch && type!=kTypeChar))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: cRet = (char)data.nValue; break;
            case kTypeByte: cRet = (char)data.byValue; break;
            case kTypeChar: cRet = data.cValue; break;
            case kTypeUInt: cRet = (char)data.uValue; break;
            case kTypeLong: cRet = (char)data.lValue; break;
            case kTypeInt64: cRet = (char)data.llValue; break;
            case kTypeFloat: cRet = (char)data.fValue; break;
            case kTypeDouble: cRet = (char)data.dValue; break;
            case kTypePointer: cRet = (char)(long)data.pValue; break;
            case kTypeBool: cRet = data.bValue ? 1 : 0; break;
            default: bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return cRet;
}
    
unsigned char SCValue::getByte(bool* pResult,const bool bExactMatch) const
{
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    bool bResult = false;
    unsigned char byRet = 0;
    if(!(bExactMatch && type!=kTypeByte))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: byRet = (unsigned char)data.nValue; break;
            case kTypeByte: byRet = data.byValue; break;
            case kTypeChar: byRet = (unsigned char)data.cValue; break;
            case kTypeUInt: byRet = (unsigned char)data.uValue; break;
            case kTypeLong: byRet = (unsigned char)data.lValue; break;
            case kTypeInt64: byRet = (unsigned char)data.llValue; break;
            case kTypeFloat: byRet = (unsigned char)data.fValue; break;
            case kTypeDouble: byRet = (unsigned char)data.dValue; break;
            case kTypePointer: byRet = (unsigned char)(long)data.pValue; break;
            case kTypeBool: byRet = data.bValue ? 1 : 0; break;
            default: bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return byRet;
}
    
unsigned int SCValue::getUnsignedInt(bool* pResult,const bool bExactMatch) const
{
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    bool bResult = false;
    unsigned int uRet = 0;
    if(!(bExactMatch && type!=kTypeUInt))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: uRet = (unsigned int)data.nValue; break;
            case kTypeByte: uRet = (unsigned int)data.byValue; break;
            case kTypeChar: uRet = (unsigned int)data.cValue; break;
            case kTypeUInt: uRet = data.uValue; break;
            case kTypeLong: uRet = (unsigned int)data.lValue; break;
            case kTypeInt64: uRet = (unsigned int)data.llValue; break;
            case kTypeFloat: uRet = (unsigned int)data.fValue; break;
            case kTypeDouble: uRet = (unsigned int)data.dValue; break;
            case kTypePointer: uRet = (unsigned int)(long)data.pValue; break;
            case kTypeBool: uRet = data.bValue ? 1 : 0; break;
            default: bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return uRet;
}
    
int SCValue::getInt(bool* pResult,const bool bExactMatch) const
{
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    bool bResult = false;
    int nRet = 0;
    if(!(bExactMatch && type!=kTypeInt))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: nRet = data.nValue; break;
            case kTypeByte: nRet = (int)data.byValue; break;
            case kTypeChar: nRet = (int)data.cValue; break;
            case kTypeUInt: nRet = (int)data.uValue; break;
            case kTypeLong: nRet = (int)data.lValue; break;
            case kTypeInt64: nRet = (int)data.llValue; break;
            case kTypeFloat: nRet = (int)data.fValue; break;
            case kTypeDouble: nRet = (int)data.dValue; break;
            case kTypePointer: nRet = (int)(long)data.pValue; break;
            case kTypeBool: nRet = data.bValue ? 1 : 0; break;
            default: bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return nRet;
}
    
long SCValue::getLong(bool* pResult,const bool bExactMatch) const
{
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    bool bResult = false;
    long lRet = 0;
    if(!(bExactMatch && type!=kTypeLong))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: lRet = (long)data.nValue; break;
            case kTypeByte: lRet = (long)data.byValue; break;
            case kTypeChar: lRet = (long)data.cValue; break;
            case kTypeUInt: lRet = (long)data.uValue; break;
            case kTypeLong: lRet = data.lValue; break;
            case kTypeInt64: lRet = (long)data.llValue; break;
            case kTypeFloat: lRet = (long)data.fValue; break;
            case kTypeDouble: lRet = (long)data.dValue; break;
            case kTypePointer: lRet = (long)data.pValue; break;
            case kTypeBool: lRet = data.bValue ? 1 : 0; break;
            default: bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return lRet;
}
    
bool SCValue::getBool(bool* pResult,const bool bExactMatch) const
{
    bool bRet = 0;
    bool bResult = false;
        
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    if(!(bExactMatch && type!=kTypeBool))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: bRet = (data.nValue!=0); break;
            case kTypeByte: bRet = (data.byValue!=0); break;
            case kTypeChar: bRet = (data.cValue!=0); break;
            case kTypeUInt: bRet = (data.uValue!=0); break;
            case kTypeLong: bRet = (data.lValue!=0); break;
            case kTypeInt64: bRet = (data.llValue!=0); break;
            case kTypeFloat: bRet = (data.fValue!=0.0f); break;
            case kTypeDouble: bRet = (data.dValue!=0.0); break;
            case kTypePointer: bRet = (data.pValue!=nullptr); break;
            case kTypeBool: bRet = data.bValue; break;
                    
            default:bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return bRet;
}
    
float SCValue::getFloat(bool* pResult,const bool bExactMatch) const
{
    float fRet = 0;
    bool bResult = false;
        
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    if(!(bExactMatch && type!=kTypeFloat))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: fRet = (float)data.nValue; break;
            case kTypeByte: fRet = (float)data.byValue; break;
            case kTypeChar: fRet = (float)data.cValue; break;
            case kTypeUInt: fRet = (float)data.uValue; break;
            case kTypeLong: fRet = (float)data.lValue; break;
            case kTypeInt64: fRet = (float)data.llValue; break;
            case kTypeFloat: fRet = data.fValue; break;
            case kTypeDouble: fRet = (float)data.dValue; break;
            case kTypePointer: fRet = (float)(long)data.pValue; break;
            case kTypeBool: fRet = data.bValue ? 1.0f : 0.0f; break;
                    
            default:bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return fRet;
}
    
double SCValue::getDouble(bool* pResult,const bool bExactMatch) const
{
    double dRet = 0;
    bool bResult = false;
        
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    if(!(bExactMatch && type!=kTypeDouble))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: dRet = (double)data.nValue; break;
            case kTypeByte: dRet = (double)data.byValue; break;
            case kTypeChar: dRet = (double)data.cValue; break;
            case kTypeUInt: dRet = (double)data.uValue; break;
            case kTypeLong: dRet = (double)data.lValue; break;
            case kTypeInt64: dRet = (double)data.llValue; break;
            case kTypeFloat: dRet = (double)data.fValue; break;
            case kTypeDouble: dRet = data.dValue; break;
            case kTypePointer: dRet = (double)(long)data.pValue; break;
            case kTypeBool: dRet = data.bValue ? 1 : 0; break;
                    
            default:bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return dRet;
}
    
void* SCValue::getPointer(bool* pResult,const bool bExactMatch) const
{
    void* pRet = nullptr;
    bool bResult = false;
        
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    if(!(bExactMatch && type!=kTypePointer))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: pRet = (void*)(long)data.nValue; break;
            case kTypeByte: pRet = (void*)(long)data.byValue; break;
            case kTypeChar: pRet = (void*)(long)data.cValue; break;
            case kTypeUInt: pRet = (void*)(long)data.uValue; break;
            case kTypeLong: pRet = (void*)data.lValue; break;
            case kTypeInt64: pRet = (void*)data.llValue; break;
            case kTypeFloat: pRet = (void*)(long)data.fValue; break;
            case kTypeDouble: pRet = (void*)(long)data.dValue; break;
            case kTypePointer: pRet = data.pValue; break;
            case kTypeBool: pRet = (void*)(long)(data.bValue ? 1 : 0); break;
                    
            default:bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return pRet;
}
    
INT64 SCValue::getInt64(bool* pResult,const bool bExactMatch) const
{
    INT64 llRet = 0;
    bool bResult = false;
        
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    if(!(bExactMatch && type!=kTypeInt64))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: llRet = (INT64)data.nValue; break;
            case kTypeByte: llRet = (INT64)data.byValue; break;
            case kTypeChar: llRet = (INT64)data.cValue; break;
            case kTypeUInt: llRet = (INT64)data.uValue; break;
            case kTypeLong: llRet = (INT64)data.lValue; break;
            case kTypeInt64: llRet = data.llValue; break;
            case kTypeFloat: llRet = (INT64)data.fValue; break;
            case kTypeDouble: llRet = (INT64)data.dValue; break;
            case kTypePointer: llRet = (INT64)data.pValue; break;
            case kTypeBool: llRet = data.bValue ? 1 : 0; break;
                    
            default:bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return llRet;
}
    
SCDataBlock SCValue::getDataBlock(bool* pResult,const bool bExactMatch) const
{
    SCDataBlock dbRet;
    bool bResult = false;
        
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    if(!(bExactMatch && type!=kTypeDataBlock))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: dbRet.append(&data.nValue, sizeof(data.nValue)); break;
            case kTypeByte: dbRet.append(&data.byValue, sizeof(data.byValue)); break;
            case kTypeChar: dbRet.append(&data.cValue, sizeof(data.cValue)); break;
            case kTypeUInt: dbRet.append(&data.uValue, sizeof(data.uValue)); break;
            case kTypeLong: dbRet.append(&data.lValue, sizeof(data.lValue)); break;
            case kTypeInt64: dbRet.append(&data.llValue, sizeof(data.llValue)); break;
            case kTypeFloat: dbRet.append(&data.fValue, sizeof(data.fValue)); break;
            case kTypeDouble: dbRet.append(&data.dValue, sizeof(data.dValue)); break;
            case kTypePointer: dbRet.append(&data.pValue, sizeof(data.pValue)); break;
            case kTypeBool: dbRet.append(&data.bValue, sizeof(data.bValue)); break;
            case kTypeDataBlock: dbRet = *((SCDataBlock*)data.pObject); break;
                    
            default:bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return dbRet;
}
    
SCString SCValue::getString(bool* pResult,const bool bExactMatch) const
{
    SCString strRet;
    bool bResult = false;
        
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    if(!(bExactMatch && type!=kTypeString))
    {
        bResult = true;
        switch(type)
        {
            case kTypeInt: strRet.format("%d",data.nValue); break;
            case kTypeByte: strRet.format("%d",data.byValue); break;
            case kTypeChar: strRet.format("%c",data.cValue); break;
            case kTypeUInt: strRet.format("%u",data.uValue); break;
            case kTypeLong: strRet.format("%d",data.lValue); break;
            case kTypeInt64: strRet.format("%lld",data.llValue); break;
            case kTypeFloat: strRet.format("%f",data.fValue); break;
            case kTypeDouble: strRet.format("%f",data.dValue); break;
            case kTypePointer: strRet.format("%p",data.pValue); break;
            case kTypeBool: strRet.format("%s",data.bValue ? "true" : "false"); break;
            case kTypeString: strRet = *((SCString*)data.pObject); break;
            case kTypeDateTime: strRet = ((SCDateTime*)data.pObject)->getFormatString(""); break;
                    
            default:bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return strRet;
}
    
SCDateTime SCValue::getDateTime(bool* pResult,const bool bExactMatch) const
{
    SCDateTime dtRet;
    bool bResult = false;
        
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    if(!(bExactMatch && type!=kTypeDateTime))
    {
        bResult = true;
        switch(type)
        {
            case kTypeString: dtRet = SCDateTime(*((SCString*)data.pObject),"%Y-%m-%d %h:%M"); break;
            case kTypeInt: dtRet = SCDateTime(data.nValue); break;
            case kTypeByte: dtRet = SCDateTime(data.byValue); break;
            case kTypeChar: dtRet = SCDateTime(data.cValue); break;
            case kTypeUInt: dtRet = SCDateTime(data.uValue); break;
            case kTypeLong: dtRet = SCDateTime(data.lValue); break;
            case kTypeInt64: dtRet = SCDateTime(data.llValue); break;
            case kTypeDateTime: dtRet = *((SCDateTime*)data.pObject); break;
                    
            default: bResult = false; break;
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return dtRet;
}

SCDictionary SCValue::getDictionary(bool* pResult, const bool bExactMatch) const
{
	SCDictionary retDic;

	bool bResult = false;

	const auto& type = this->getType();
	const auto& data = this->getStub()->data;

	if (!(bExactMatch && type != kTypeDictionary))
	{
		if (type == kTypeString)
		{
			SCDictionary dic(this->getString());
			retDic = dic;
			bResult = true;
		}
		else if (type == kTypeDictionary)
		{
			retDic = *((SCDictionary*)data.pObject);
			bResult = true;
		}
	}

	return retDic;
}
    
std::vector<SCValue> SCValue::getArray(bool* pResult,const bool bExactMatch) const
{
    std::vector<SCValue> retVtr;
    bool bResult = false;
        
    const auto& type = this->getType();
    const auto& data = this->getStub()->data;
        
    if(!(bExactMatch && type!=kTypeArray))
    {
        bResult = true;
        SCValue value;
        switch(type)
        {
            case kTypeInt: value = data.nValue; break;
            case kTypeByte: value = data.byValue; break;
            case kTypeChar: value = data.cValue; break;
            case kTypeUInt: value = data.uValue; break;
            case kTypeLong: value = data.lValue; break;
            case kTypeInt64: value = data.llValue; break;
            case kTypeBool: value = data.bValue; break;
            case kTypeFloat: value = data.fValue; break;
            case kTypeDouble: value = data.dValue; break;
            case kTypePointer: value = data.pValue; break;
            case kTypeString: value = *((SCString*)data.pObject); break;
            case kTypeDateTime: value = *((SCDateTime*)data.pObject); break;
            case kTypeDataBlock: value = *((SCDataBlock*)data.pObject); break;
            case kTypeArray: retVtr = *((std::vector<SCValue>*)data.pObject); break;
                    
            default: bResult = false; break;
        }
            
        if(bResult && !value.isUnknown())
        {
            retVtr.push_back(value);
        }
    }
        
    if(pResult!=nullptr)
    {
        *pResult = bResult;
    }
        
    return retVtr;
}

SCString* SCValue::getRefString()
{
	SC_RETURN_IF(this->getType() != kTypeString, nullptr);
	return (SCString*)this->getStub()->data.pObject;
}

SCDataBlock* SCValue::getRefDataBlock()
{
	SC_RETURN_IF(this->getType() != kTypeDataBlock, nullptr);
	return (SCDataBlock*)this->getStub()->data.pObject;
}

SCDateTime* SCValue::getRefDateTime()
{
	SC_RETURN_IF(this->getType() != kTypeDateTime, nullptr);
	return (SCDateTime*)this->getStub()->data.pObject;
}

SCDictionary* SCValue::getRefDictionary()
{
	SC_RETURN_IF(this->getType() != kTypeDictionary, nullptr);
	return (SCDictionary*)this->getStub()->data.pObject;
}

std::vector<SCValue>* SCValue::getRefArray()
{
	SC_RETURN_IF(this->getType() != kTypeArray, nullptr);
	return (std::vector<SCValue>*)this->getStub()->data.pObject;
}

void SCValue::setUnsignedInt(const unsigned int uValue)
{
	this->check4Write();
	this->clone4Write();
	this->getStub()->data.uValue = uValue;
	(*(this->getStub())).pfunDestroyFunctor_t = nullptr;
	this->getCookieDesc()->cookie = kTypeUInt;
}

void SCValue::setInt(const int nValue)
{
    this->check4Write();
    this->clone4Write();
    this->getStub()->data.nValue = nValue;
    (*(this->getStub())).pfunDestroyFunctor_t = nullptr;
    this->getCookieDesc()->cookie = kTypeInt;
}
    
void SCValue::setByte(const unsigned char byValue)
{
    this->check4Write();
    this->clone4Write();
    this->getStub()->data.byValue = byValue;
    (*(this->getStub())).pfunDestroyFunctor_t = nullptr;
    this->getCookieDesc()->cookie = kTypeByte;
}
    
void SCValue::setChar(const char cValue)
{
    this->check4Write();
    this->clone4Write();
    this->getStub()->data.cValue = cValue;
    (*(this->getStub())).pfunDestroyFunctor_t = nullptr;
    this->getCookieDesc()->cookie = kTypeChar;
}
    
SCValue& SCValue::operator=(const unsigned int uValue)
{
    this->check4Write();
    this->clone4Write();
    this->getStub()->data.uValue = uValue;
    (*(this->getStub())).pfunDestroyFunctor_t = nullptr;
    this->getCookieDesc()->cookie = kTypeUInt;
        
    return *this;
}
    
void SCValue::setLong(const long lValue)
{
    this->check4Write();
    this->clone4Write();
    this->getStub()->data.lValue = lValue;
    (*(this->getStub())).pfunDestroyFunctor_t = nullptr;
    this->getCookieDesc()->cookie = kTypeLong;
}
    
void SCValue::setBool(const bool bValue)
{
    this->check4Write();
    this->clone4Write();
    this->getStub()->data.bValue = bValue;
    (*(this->getStub())).pfunDestroyFunctor_t = nullptr;
    this->getCookieDesc()->cookie = kTypeBool;
}
    
void SCValue::setFloat(const float fValue)
{
    this->check4Write();
    this->clone4Write();
    this->getStub()->data.fValue = fValue;
    (*(this->getStub())).pfunDestroyFunctor_t = nullptr;
    this->getCookieDesc()->cookie = kTypeFloat;
}
    
void SCValue::setDouble(const double dValue)
{
    this->check4Write();
    this->clone4Write();
    this->getStub()->data.dValue = dValue;
    (*(this->getStub())).pfunDestroyFunctor_t = nullptr;
    this->getCookieDesc()->cookie = kTypeDouble;
}
    
void SCValue::setInt64(INT64 llValue)
{
    this->check4Write();
    this->clone4Write();
    this->getStub()->data.llValue = llValue;
    (*(this->getStub())).pfunDestroyFunctor_t = nullptr;
    this->getCookieDesc()->cookie = kTypeInt64;
}
    
void SCValue::setPointer(void* const pValue)
{
    this->check4Write();
    this->clone4Write();
    this->getStub()->data.pValue = pValue;
    (*(this->getStub())).pfunDestroyFunctor_t = nullptr;
    this->getCookieDesc()->cookie = kTypePointer;
}
    
void SCValue::setString(const char* pszValue)
{
    SCString s(pszValue);
    this->setString(s);
}
    
void SCValue::setString(const SCString& strValue)
{
    SCValue v = SCValue::create(strValue);
    *this = v;
}
    
void SCValue::setDataBlock(const SCDataBlock& db)
{
    SCValue v = SCValue::create(db);
    *this = v;
}
    
void SCValue::setDateTime(const SCDateTime& dateTime)
{
    SCValue v = SCValue::create(dateTime);
    *this = v;
}

void SCValue::setDictionary(const SCDictionary& dic)
{
	SCValue v = SCValue::create(dic);
	*this = v;
}
    
void SCValue::setArray(const std::vector<SCValue>& valueVcr)
{
    SCValue v = SCValue::create(valueVcr);
    *this = v;
}
    
SCValue& SCValue::operator=(const unsigned char byValue)
{
    this->setByte(byValue);
    return *this;
}
    
SCValue& SCValue::operator=(const int nValue)
{
    this->setInt(nValue);
    return *this;
}
    
SCValue& SCValue::operator=(const long lValue)
{
    this->setLong(lValue);
    return *this;
}
    
SCValue& SCValue::operator=(const bool bValue)
{
    this->setBool(bValue);
    return *this;
}
    
SCValue& SCValue::operator=(const float fValue)
{
    this->setFloat(fValue);
    return *this;
}
    
SCValue& SCValue::operator=(const double dValue)
{
    this->setDouble(dValue);
    return *this;
}
    
SCValue& SCValue::operator=(void* const pValue)
{
    this->setPointer(pValue);
    return *this;
}
    
SCValue& SCValue::operator=(const INT64 llValue)
{
    this->setInt64(llValue);
    return *this;
}
    
SCValue& SCValue::operator=(const SCString& strValue)
{
    this->setString(strValue);
    return *this;
}
    
SCValue& SCValue::operator=(const char* pszValue)
{
    this->setString(pszValue);
    return *this;
}
    
SCValue& SCValue::operator=(const SCDataBlock& db)
{
    this->setDataBlock(db);
    return *this;
}
    
SCValue& SCValue::operator=(const SCDateTime& dateTime)
{
    this->setDateTime(dateTime);
    return *this;
}

SCValue& SCValue::operator=(const SCDictionary& dic)
{
	this->setDictionary(dic);
	return *this;
}
    
SCValue& SCValue::operator=(const std::vector<SCValue>& valueVcr)
{
    this->setArray(valueVcr);
    return *this;
}

NAMESPACE_SPEEDCC_END

