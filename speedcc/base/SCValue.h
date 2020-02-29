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

#ifndef __SPEEDCC__SCVALUE_H__
#define __SPEEDCC__SCVALUE_H__


#include "SCObjPtrT.h"
#include "SCString.h"

NAMESPACE_SPEEDCC_BEGIN

class SCDateTime;
class SCDataBlock;
class SCString;
class SCDictionary;
    
struct SCValueStub
{
    union
    {
        void*           pObject;
        INT64           llValue;
        char            cValue;
        unsigned char   byValue;
        int             nValue;
        unsigned int    uValue;
        float           fValue;
        bool            bValue;
        long            lValue;
        double          dValue;
        void*           pValue;
    }data;
    int (*pfunDestroyFunctor_t)(void*);
        
    SCValueStub():
    pfunDestroyFunctor_t(nullptr)
    {
        ::memset(&data,0,sizeof(data));
    }
        
    ~SCValueStub()
    {
        if(pfunDestroyFunctor_t!=nullptr && data.pObject!=nullptr)
        {
            int nSize = pfunDestroyFunctor_t(data.pObject);
            SCMemAllocator::deallocate(data.pObject, nSize);
        }
    }
};
    
class SCValue
:public SCObjRefT<SCValueStub,int>
,public SCObject
{
public:
    SC_DEFINE_CLASS_PTR(SCValue)
    enum EType
    {
        kTypeUnknown = 0,
        kTypeByte,
        kTypeChar,
        kTypeInt,
		kTypeUInt,
        kTypeLong,
        kTypeInt64,
        kTypeBool,
        kTypeFloat,
        kTypeDouble,
        kTypePointer,
        kTypeString,
        kTypeDateTime,
        kTypeDataBlock,
		kTypeDictionary,
        kTypeArray,
        kTypeObject
    };
        
    SCValue();
    SCValue(const char cValue);
    SCValue(const unsigned char byValue);
    SCValue(const unsigned int nValue);
    SCValue(const int nValue);
    SCValue(const bool bValue);
    SCValue(const float fValue);
    SCValue(const double dValue);
    SCValue(const long lValue);
    SCValue(const INT64 llValue);
    SCValue(void* const pValue);
    SCValue(const SCString& strValue);
    SCValue(const char* pszValue);
    SCValue(SCDateTime& dateTime);
    SCValue(const SCDataBlock& dataBlock);
	SCValue(const SCDictionary& dic);
    SCValue(const std::vector<SCValue>& valueVtr);
    template<typename ObjectT,typename = typename std::enable_if<std::is_class<ObjectT>::value || std::is_enum<ObjectT>::value,ObjectT>::type>
    SCValue(const ObjectT& obj)
    {
        auto result = SCValue::create(obj);
        _pObjData = result._pObjData;
        this->increaseRef();
    }
        
    virtual ~SCValue();
        
    bool isNumberType() const;
    inline EType getType() const {return (EType)*this->getCookie();}
    inline bool isUnknown() const {return (getType()==kTypeUnknown);}
        
    char getChar(bool* pResult=nullptr,const bool bExactMatch=false) const;
    unsigned char getByte(bool* pResult=nullptr,const bool bExactMatch=false) const;
    unsigned int getUnsignedInt(bool* pResult=nullptr,const bool bExactMatch=false) const;
    int getInt(bool* pResult=nullptr,const bool bExactMatch=false) const;
    long getLong(bool* pResult=nullptr,const bool bExactMatch=false) const;
    bool getBool(bool* pResult=nullptr,const bool bExactMatch=false) const;
    float getFloat(bool* pResult=nullptr,const bool bExactMatch=false) const;
    double getDouble(bool* pResult=nullptr,const bool bExactMatch=false) const;
    void* getPointer(bool* pResult=nullptr,const bool bExactMatch=false) const;
    INT64 getInt64(bool* pResult=nullptr,const bool bExactMatch=false) const;
    SCString getString(bool* pResult=nullptr,const bool bExactMatch=false) const;
    SCDataBlock getDataBlock(bool* pResult=nullptr,const bool bExactMatch=false) const;
    SCDateTime getDateTime(bool* pResult=nullptr,const bool bExactMatch=false) const;
	SCDictionary getDictionary(bool* pResult = nullptr, const bool bExactMatch = false) const;
    std::vector<SCValue> getArray(bool* pResult=nullptr,const bool bExactMatch=false) const;

	SCString* getRefString();
	SCDataBlock* getRefDataBlock();
	SCDateTime* getRefDateTime();
	SCDictionary* getRefDictionary();
	std::vector<SCValue>* getRefArray();
        
    void setChar(const char cValue);
    void setByte(const unsigned char byValue);
    void setUnsignedInt(const unsigned int uValue);
    void setInt(const int nValue);
    void setLong(const long lValue);
    void setBool(const bool bValue);
    void setFloat(const float fValue);
    void setDouble(const double dValue);
    void setPointer(void* const pValue);
    void setInt64(INT64 llValue);
    void setString(const SCString& strValue);
    void setString(const char* pszValue);
    void setDataBlock(const SCDataBlock& db);
    void setDateTime(const SCDateTime& dateTime);
	void setDictionary(const SCDictionary& dic);
    void setArray(const std::vector<SCValue>& valueVcr);
        
    SCValue& operator=(const unsigned char byValue);
    SCValue& operator=(const int nValue);
    SCValue& operator=(const unsigned int uValue);
    SCValue& operator=(const long lValue);
    SCValue& operator=(const bool bValue);
    SCValue& operator=(const float fValue);
    SCValue& operator=(const double dValue);
    SCValue& operator=(void* const pValue);
    SCValue& operator=(const INT64 llValue);
    SCValue& operator=(const SCString& strValue);
    SCValue& operator=(const char* pszValue);
    SCValue& operator=(const SCDataBlock& db);
    SCValue& operator=(const SCDateTime& dateTime);
	SCValue& operator=(const SCDictionary& dic);
    SCValue& operator=(const std::vector<SCValue>& valueVcr);
        
    template<typename ObjectT,typename = typename std::enable_if<std::is_class<ObjectT>::value || std::is_enum<ObjectT>::value,ObjectT>::type>
    bool isValidObject() const
    {
        if(this->getCookieDesc()->cookie!=kTypeObject)
        {
            return false;
        }
            
        const SCValueStub& stub = *(this->getStub());
        return (stub.pfunDestroyFunctor_t==SCDataTypeLifeCycleT<ObjectT>::destroy);
    }
        
    template<typename ObjectT,typename = typename std::enable_if<std::is_class<ObjectT>::value || std::is_enum<ObjectT>::value,ObjectT>::type>
    ObjectT getObject(bool* pResult=nullptr) const
    {
        static_assert(std::is_same<ObjectT,SCString>::value==0, "Using getString() instead getObject() for SCString");
        static_assert(std::is_same<ObjectT,SCDataBlock>::value==0, "Using getDataBlock() instead getObject() for SCDataBlock");
        static_assert(std::is_same<ObjectT,SCDateTime>::value==0, "Using getDateTime() instead getObject() for SCDateTime");
		static_assert(std::is_same<ObjectT, SCDictionary>::value == 0, "Using getDictionary() instead getObject() for SCDateTime");
        static_assert(std::is_same<ObjectT,std::vector<SCValue>>::value==0, "Using getArray() instead getObject() for std::vector<SCValue>");
            
        if(pResult!=nullptr)
        {
            *pResult = false;
        }
            
        if(this->getCookieDesc()->cookie!=kTypeObject)
        {
            return ObjectT();
        }
            
        const SCValueStub& stub = *(this->getStub());
            
        if(stub.data.pObject==nullptr || stub.pfunDestroyFunctor_t!=SCDataTypeLifeCycleT<ObjectT>::destroy)
        {
            return ObjectT();
        }
            
        if(pResult!=nullptr)
        {
            *pResult = true;
        }
        return *((ObjectT*)(stub.data.pObject));
    }
        
    template<typename ObjectT,typename = typename std::enable_if<std::is_class<ObjectT>::value || std::is_enum<ObjectT>::value,ObjectT>::type>
    ObjectT* getRefObject(bool* pResult=nullptr)
    {
        static_assert(std::is_same<ObjectT,SCString>::value==0, "Using getString() instead getRefObject() for SCString");
        static_assert(std::is_same<ObjectT,SCDataBlock>::value==0, "Using getDataBlock() instead getRefObject() for SCDataBlock");
        static_assert(std::is_same<ObjectT,SCDateTime>::value==0, "Using getDateTime() instead getRefObject() for SCDateTime");
		static_assert(std::is_same<ObjectT,SCDictionary>::value == 0, "Using getDictionary() instead getRefObject() for SCDateTime");
        static_assert(std::is_same<ObjectT,std::vector<SCValue>>::value==0, "Using getArray() instead getRefObject() for std::vector<SCValue>");
            
        if(pResult!=nullptr)
        {
            *pResult = false;
        }
            
        if(this->getCookieDesc()->cookie!=kTypeObject)
        {
            return nullptr;
        }
            
        const SCValueStub& stub = *(this->getStub());
            
        if(stub.data.pObject==nullptr || stub.pfunDestroyFunctor_t!=SCDataTypeLifeCycleT<ObjectT>::destroy)
        {
            return nullptr;
        }
            
        if(pResult!=nullptr)
        {
            *pResult = true;
        }
        return (ObjectT*)(stub.data.pObject);
    }
        
    template<typename ObjectT,typename = typename std::enable_if<std::is_class<ObjectT>::value || std::is_enum<ObjectT>::value,ObjectT>::type>
    void setObject(const ObjectT& value)
    {
        static_assert(std::is_same<ObjectT,SCString>::value==0, "Using setString() instead setObject() for SCString");
        static_assert(std::is_same<ObjectT,SCDataBlock>::value==0, "Using setDataBlock() instead setObject() for SCDataBlock");
        static_assert(std::is_same<ObjectT,SCDateTime>::value==0, "Using setDateTime() instead setObject() for SCDateTime");
		static_assert(std::is_same<ObjectT, SCDictionary>::value == 0, "Using setDictionary() instead setObject() for SCDateTime");
        static_assert(std::is_same<ObjectT,std::vector<SCValue>>::value==0, "Using setArray() instead setObject() for std::vector<SCValue>");
            
        *this = SCValue::create(value);
    }
    
protected:
//    static SCValue create(const SCValue& value)
//    {
//        return value;
//    }
    
    template<typename T,typename = typename std::enable_if<std::is_arithmetic<T>::value,T>::type >
    static SCValue create(const T value)
    {
        return SCValue(value);
    }
        
//    static SCValue create(void* const value)
//    {
//        return SCValue(value);
//    }
    
    template<typename ObjectT,typename = typename std::enable_if<std::is_class<ObjectT>::value || std::is_enum<ObjectT>::value,ObjectT>::type>
    static SCValue create(const ObjectT& value)
    {
        SCValue ret;
        auto type = (std::is_same<ObjectT, SCString>::value ? kTypeString :
                        (std::is_same<ObjectT, SCDataBlock>::value ? kTypeDataBlock :
						(std::is_same<ObjectT, SCDictionary>::value ? kTypeDictionary :
                        (std::is_same<ObjectT, SCDateTime>::value ? kTypeDateTime :
                        (std::is_same<ObjectT, std::vector<SCValue>>::value) ? kTypeArray : kTypeObject))));
            
        ret.getCookieDesc()->cookie = type;
        SCValueStub& stub = *(ret.getStub());
            
        void* pBuf = SCMemAllocator::allocate(sizeof(ObjectT));
        ObjectT* pMyClass = new(pBuf)ObjectT(value);
        stub.data.pObject = pMyClass;
        stub.pfunDestroyFunctor_t = SCDataTypeLifeCycleT<ObjectT>::destroy;
            
        return ret;
    }
        
private:
    void check4Write();
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCVALUE_H__
