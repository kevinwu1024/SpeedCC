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

#include "SCDictionary.h"
#include "../system/SCSystem.h"

#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "json/prettywriter.h"

NAMESPACE_SPEEDCC_BEGIN

///------------- SCDictionary
SCDictionary::SCDictionary()
{
    this->createInstance();
}
    
SCDictionary::SCDictionary(const SCString& strKey,const SCValue& value)
{
    this->createInstance();
    this->setValue(strKey, value);
}
    
SCDictionary::SCDictionary(const SKVPair& pair)
{
    this->createInstance();
    this->setValue(pair);
}
    
SCDictionary::SCDictionary(const SKVPair* pPairArray,const int nCount)
{
    this->createInstance();
    this->setValue(pPairArray,nCount);
}
    
SCDictionary::SCDictionary(const std::vector<SKVPair>& pairVct)
{
    this->createInstance();
    this->setValue(pairVct);
}
    
SCDictionary::SCDictionary(const SCString& strJson)
{
    this->createInstance();
    this->loadFromJsonString(strJson);
}
    
SCValue& SCDictionary::operator[](const SCString& strKey)
{
    SCASSERT(!strKey.isEmpty());
    this->clone4Write();
    return (*this->getStub())[strKey];
}
    
SCValue SCDictionary::operator[](const SCString& strKey) const
{
    SCASSERT(!strKey.isEmpty());
    return (*this->getStub())[strKey];
}
    
void SCDictionary::setValue(const SCString& strKey,const SCValue& value)
{
    SCASSERT(!strKey.isEmpty());
    this->clone4Write();
    auto& map = (*this->getStub());
    map[strKey] = value;
}
    
void SCDictionary::setValue(const SKVPair& pair)
{
    SCASSERT(!pair.strKey.isEmpty());
    this->clone4Write();
    auto& map = (*this->getStub());
    map[pair.strKey] = pair.value;
}
    
void SCDictionary::setValue(const SKVPair* pPairArray,const int nCount)
{
    SC_RETURN_V_IF(pPairArray==nullptr || nCount<=0);
    this->clone4Write();
    auto& map = (*this->getStub());
        
    for(int i=0;i<nCount;++i)
    {
        auto pair = pPairArray[i];
        SCASSERT(!pair.strKey.isEmpty());
        map[pair.strKey] = pair.value;
    }
}
    
void SCDictionary::setValue(const std::vector<SKVPair>& pairVct)
{
    SC_RETURN_V_IF(pairVct.empty());
    this->clone4Write();
    auto& map = (*this->getStub());

    for(const auto& pair : pairVct)
    {
        SCASSERT(!pair.strKey.isEmpty());
        map[pair.strKey] = pair.value;
    }
}
    
//void SCDictionary::setDictionary(const SCString& strKey,const SCDictionary& dic)
//{
//    this->setValue(strKey,SCValue::create(dic));
//}
    
SCValue SCDictionary::getValue(const SCString& strKey) const
{
    SCASSERT(!strKey.isEmpty());
    return (*this->getStub())[strKey];
}
    
//SCDictionary SCDictionary::getDictionary(const SCString& strKey) const
//{
//    SCDictionary retDic;
//    auto value = this->getValue(strKey);
//	return value.getDictionary();
//}
    
bool SCDictionary::hasKey(const SCString& strKey) const
{
    SCASSERT(!strKey.isEmpty());
    const auto& it = this->getStub()->find(strKey);
    return (this->getStub()->end()!=it);
}
    
int SCDictionary::getCount() const
{
    return (int)this->getStub()->size();
}
    
void SCDictionary::removeKey(const SCString& strKey)
{
    SCASSERT(!strKey.isEmpty());
    this->clone4Write();
    this->getStub()->erase(strKey);
}
    
void SCDictionary::removeAllKeys()
{
    this->clone4Write();
    this->getStub()->clear();
}
    
bool SCDictionary::isEmpty() const
{
    return this->getStub()->empty();
}
    
void SCDictionary::forEach(const std::function<bool(const SCString& strKey,const SCValue& value)>& func) const
{
    const auto& map = *(this->getStub());
    for(auto& it : map)
    {
        SC_RETURN_V_IF(!func(it.first,it.second));
    }
}
    
void SCDictionary::forEach(const std::function<bool(const SCString& strKey,SCValue& value)>& func)
{
    this->clone4Write();
    auto& map = *(this->getStub());
    for(auto& it : map)
    {
        SC_RETURN_V_IF(!func(it.first,it.second));
    }
}
    
///------------- json relate
SCValue parseJsonObject(const rapidjson::Value& val);
SCValue parseJsonArray(const rapidjson::Value& val);
rapidjson::Value exportJsonObject(const SCDictionary& dic,rapidjson::Document::AllocatorType& allocator);
rapidjson::Value exportJsonArray(const std::vector<SCValue>& array,rapidjson::Document::AllocatorType& allocator);
    
bool SCDictionary::loadFromJsonString(const SCString& strJson)
{
    if(strJson.isEmpty())
    {
        this->removeAllKeys();
        return true;
    }
        
    rapidjson::Document jsonDoc;
    jsonDoc.Parse(strJson.c_str());
        
    if(jsonDoc.HasParseError())
    {
        SCLog("SCDictionary parse json error: %d",jsonDoc.GetParseError());
        return false;
    }
    
    if(!jsonDoc.IsObject())
    {
        SCLog("SCDictionary parse json error: json string is not json object");
        return false;
    }
        
    for(auto it = jsonDoc.MemberBegin(); it!=jsonDoc.MemberEnd(); ++it)
    {
        auto key = (it->name).GetString();
        const rapidjson::Value& val = it->value;
            
        switch(val.GetType())
        {
            case rapidjson::kNullType: this->setValue(key, SCValue()); break;
            case rapidjson::kTrueType:
            case rapidjson::kFalseType: this->setValue(key, SCValue(val.GetBool())); break;
            case rapidjson::kStringType: this->setValue(key, SCValue(val.GetString()));break;
            case rapidjson::kObjectType: this->setValue(key,parseJsonObject(val));break;
            case rapidjson::kArrayType: this->setValue(key,parseJsonArray(val));break;
            case rapidjson::kNumberType:
            {
                if(val.IsInt())
                {
                    this->setValue(key, SCValue(val.GetInt()));
                }
                else if(val.IsUint())
                {
                    this->setValue(key, SCValue(val.GetUint()));
                }
                else if(val.IsInt64())
                {
                    this->setValue(key, SCValue(val.GetInt64()));
                }
                else
                {
                    this->setValue(key, SCValue(val.GetDouble()));
                }
            }
                break;
        }
    }
        
    return true;
}
    
SCString SCDictionary::exportJson(const bool bPrettyPrint)
{
    SC_RETURN_IF(this->isEmpty(), "{}");
        
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    auto call = [&jsonDoc](const SCString& strKey,const SCValue& value) -> bool
    {
        rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
            
        switch(value.getType())
        {
            default:
            case SCValue::kTypeDataBlock:
            case SCValue::kTypePointer:
            case SCValue::kTypeUnknown:       jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(rapidjson::kNullType),allocator);
                break;
                    
            case SCValue::kTypeByte:
            case SCValue::kTypeInt:
            case SCValue::kTypeLong:
                jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getInt()),allocator);
                break;
                    
            case SCValue::kTypeUInt: jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getUnsignedInt()),allocator);
                break;
                    
            case SCValue::kTypeInt64: jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getInt64()),allocator);
                break;
                    
            case SCValue::kTypeBool:
                jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getBool()),allocator);
                break;
                    
            case SCValue::kTypeFloat:
                jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getFloat()),allocator);
                break;
                    
            case SCValue::kTypeDouble:
                jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getDouble()),allocator);
                break;
                    
            case SCValue::kTypeDateTime:
            case SCValue::kTypeChar:
            case SCValue::kTypeString:
                jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getString(),allocator),allocator);
                break;
                    
            case SCValue::kTypeArray:
            {
                auto array = value.getArray();
                auto val = exportJsonArray(array,allocator);
                jsonDoc.AddMember(rapidjson::Value(strKey,allocator),val,allocator);
            }
                break;

			case SCValue::kTypeDictionary:
			{
				auto dic = value.getDictionary();
				auto val = exportJsonObject(dic, allocator);
				jsonDoc.AddMember(rapidjson::Value(strKey, allocator), val, allocator);
			}
				break;
        }
        return true;
    };
        
    this->forEach(call);
        
    rapidjson::StringBuffer buffer;
        
    if(bPrettyPrint)
    {
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        jsonDoc.Accept(writer);
    }
    else
    {
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        jsonDoc.Accept(writer);
    }
        
    return buffer.GetString();
}
    
rapidjson::Value exportJsonObject(const SCDictionary& dic,rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value retVal;
    retVal.SetObject();
        
    auto call = [&retVal,&allocator](const SCString& strKey,const SCValue& value) -> bool
    {
        switch(value.getType())
        {
            default:
            case SCValue::kTypeDataBlock:
            case SCValue::kTypePointer:
            case SCValue::kTypeUnknown:       retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(rapidjson::kNullType),allocator);
                break;
                    
            case SCValue::kTypeByte:
            case SCValue::kTypeInt:
            case SCValue::kTypeLong:
                retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getInt()),allocator);
                break;
                    
            case SCValue::kTypeUInt:
                retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getUnsignedInt()),allocator);
                break;
                    
            case SCValue::kTypeInt64:
                retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getInt64()),allocator);
                break;
                    
            case SCValue::kTypeBool:
                retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getBool()),allocator);
                break;
                    
            case SCValue::kTypeFloat:
                retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getFloat()),allocator);
                break;
                    
            case SCValue::kTypeDouble:
                retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getDouble()),allocator);
                break;
                    
            case SCValue::kTypeDateTime:
            case SCValue::kTypeChar:
            case SCValue::kTypeString:
                retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getString(),allocator),allocator);
                break;
                    
            case SCValue::kTypeArray:
            {
                auto array = value.getArray();
                auto val = exportJsonArray(array,allocator);
                retVal.AddMember(rapidjson::Value(strKey,allocator),val,allocator);
            }
                break;
			case SCValue::kTypeDictionary:
			{
				auto dic = value.getDictionary();
				auto val = exportJsonObject(dic, allocator);
				retVal.AddMember(rapidjson::Value(strKey, allocator), val, allocator);
			}
				break;
        }
        return true;
    };
        
    dic.forEach(call);
        
    return retVal;
}
    
rapidjson::Value exportJsonArray(const std::vector<SCValue>& array,rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value retVal;
    retVal.SetArray();
        
    for(const auto& value : array)
    {
        switch(value.getType())
        {
            default:
            case SCValue::kTypeDataBlock:
            case SCValue::kTypePointer:
            case SCValue::kTypeUnknown:
                retVal.PushBack(rapidjson::Value(rapidjson::kNullType),allocator);
                break;
                    
            case SCValue::kTypeByte:
            case SCValue::kTypeInt:
            case SCValue::kTypeLong:
                retVal.PushBack(rapidjson::Value(value.getInt()),allocator);
                break;
                    
            case SCValue::kTypeUInt:
                retVal.PushBack(rapidjson::Value(value.getUnsignedInt()),allocator);
                break;
                    
            case SCValue::kTypeInt64:
                retVal.PushBack(rapidjson::Value(value.getInt64()),allocator);
                break;
                    
            case SCValue::kTypeBool:
                retVal.PushBack(rapidjson::Value(value.getBool()),allocator);
                break;
                    
            case SCValue::kTypeFloat:
                retVal.PushBack(rapidjson::Value(value.getFloat()),allocator);
                break;
                    
            case SCValue::kTypeDouble:
                retVal.PushBack(rapidjson::Value(value.getDouble()),allocator);
                break;
                    
            case SCValue::kTypeDateTime:
            case SCValue::kTypeChar:
            case SCValue::kTypeString:
                retVal.PushBack(rapidjson::Value(value.getString(),allocator),allocator);
                break;
                    
            case SCValue::kTypeArray:
            {
                auto array = value.getArray();
                auto val = exportJsonArray(array,allocator);
                retVal.PushBack(val,allocator);
            }
                break;

			case SCValue::kTypeDictionary:
			{
				auto dic = value.getDictionary();
				auto val = exportJsonObject(dic, allocator);
				retVal.PushBack(val, allocator);
			}
			break;
        }
    }
        
    return retVal;
}
    
SCValue parseJsonArray(const rapidjson::Value& val)
{
    SCValue retVal;
        
    SC_RETURN_IF(!val.IsArray(), retVal);
        
    std::vector<SCValue> array;
    array.resize(val.Capacity());
        
    const auto jsonArray = val.GetArray();
        
    for (int i = 0; i<jsonArray.Capacity(); ++i)
    {
        const rapidjson::Value& val2 = jsonArray[i];
        switch(val2.GetType())
        {
            case rapidjson::kNullType: array[i] = SCValue(); break;
            case rapidjson::kTrueType:
            case rapidjson::kFalseType: array[i] = SCValue(val2.GetBool()); break;
            case rapidjson::kStringType: array[i] = SCValue(val2.GetString());break;
            case rapidjson::kObjectType: array[i] = parseJsonObject(val2);break;
            case rapidjson::kArrayType: array[i] = parseJsonArray(val2);break;
            case rapidjson::kNumberType:
            {
                if(val2.IsInt())
                {
                    array[i] = val2.GetInt();
                }
                else if(val2.IsUint())
                {
                    array[i] = val2.GetUint();
                }
                else if(val2.IsInt64())
                {
                    array[i] = val2.GetInt64();
                }
                else
                {
                    array[i] = val2.GetDouble();
                }
            }
                break;
        }
    }
        
    retVal.setArray(array);
        
    return retVal;
}
    
SCValue parseJsonObject(const rapidjson::Value& val)
{
    SC_RETURN_IF(!val.IsObject(), SCValue());
        
    const auto jsonObj = val.GetObject();
    SCDictionary dic;
        
    for(auto it = jsonObj.MemberBegin(); it!=jsonObj.MemberEnd(); ++it)
    {
        auto key = (it->name).GetString();
        const rapidjson::Value& val2 = it->value;
            
        switch(val2.GetType())
        {
            case rapidjson::kNullType: dic.setValue(key, SCValue()); break;
            case rapidjson::kTrueType:
            case rapidjson::kFalseType: dic.setValue(key, SCValue(val2.GetBool())); break;
            case rapidjson::kStringType: dic.setValue(key, SCValue(val2.GetString()));break;
            case rapidjson::kObjectType: dic.setValue(key,parseJsonObject(val2));break;
            case rapidjson::kArrayType: dic.setValue(key,parseJsonArray(val2));break;
            case rapidjson::kNumberType:
            {
                if(val2.IsInt())
                {
                    dic.setValue(key, SCValue(val2.GetInt()));
                }
                else if(val.IsUint())
                {
                    dic.setValue(key, SCValue(val.GetUint()));
                }
                else if(val.IsInt64())
                {
                    dic.setValue(key, SCValue(val2.GetInt64()));
                }
                else
                {
                    dic.setValue(key, SCValue(val2.GetDouble()));
                }
            }
                break;
        }
    }
        
    return SCValue(dic);
}

NAMESPACE_SPEEDCC_END
