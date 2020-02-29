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

#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SpeedCC;

TEST(TestSCValue, Constructor)
{
    SCDateTime dtTest("2017-10-01 12:34:56","%Y-%m-%d %H:%M:%S");
    SCDataBlock dbTest("12345");
    std::vector<SCValue> vetArrayTest;
    
    SCValue value1;
    SCValue value2(123);
    SCValue value3(true);
    SCValue value4(1.23f);
    SCValue value5("abc");
    SCValue value6(1.23);
    SCValue value7(dtTest);
    SCValue value8(dbTest);
    
    bool bResult = false;
    SCString strValue;
    SCDateTime dt;
    SCDataBlock db;
    std::vector<SCValue> vetArray;
    
    EXPECT_EQ(value1.getType(), SCValue::kTypeUnknown);
    EXPECT_EQ(value1.getRefCount(), 1);
    
    EXPECT_EQ(value2.getType(), SCValue::kTypeInt);
    EXPECT_EQ(value2.getInt(&bResult), 123);
    EXPECT_EQ(bResult, true);
    value2.getLong(&bResult,true);
    EXPECT_EQ(bResult, false);
    EXPECT_EQ(value2.getRefCount(), 1);
    
    EXPECT_EQ(value3.getType(), SCValue::kTypeBool);
    EXPECT_EQ(value3.getBool(&bResult), true);
    EXPECT_EQ(bResult, true);
    value3.getLong(&bResult,true);
    EXPECT_EQ(bResult, false);
    EXPECT_EQ(value3.getRefCount(), 1);
    
    EXPECT_EQ(value4.getType(), SCValue::kTypeFloat);
    EXPECT_EQ(value4.getFloat(&bResult), 1.23f);
    EXPECT_EQ(bResult, true);
    value4.getLong(&bResult,true);
    EXPECT_EQ(bResult, false);
    EXPECT_EQ(value4.getRefCount(), 1);
    
    EXPECT_EQ(value5.getType(), SCValue::kTypeString);
    EXPECT_EQ(value5.getString(&bResult), "abc");
    EXPECT_EQ(bResult,true);
    value5.getLong(&bResult,true);
    EXPECT_EQ(bResult, false);
    EXPECT_EQ(value5.getRefCount(), 1);
    
    EXPECT_EQ(value6.getType(), SCValue::kTypeDouble);
    EXPECT_EQ(value6.getDouble(&bResult), 1.23);
    EXPECT_EQ(bResult, true);
    value6.getFloat(&bResult,true);
    EXPECT_EQ(bResult, false);
    EXPECT_EQ(value6.getRefCount(), 1);
    
    {
        SCValue value100(value1);
        EXPECT_EQ(value1.getType(), SCValue::kTypeUnknown);
        EXPECT_EQ(value1.getRefCount(), 2);
        EXPECT_EQ(value100.getType(), SCValue::kTypeUnknown);
        EXPECT_EQ(value100.getRefCount(), 2);
    }
    
    EXPECT_EQ(value1.getType(), SCValue::kTypeUnknown);
    EXPECT_EQ(value1.getRefCount(), 1);
    
    
    {
        SCValue value101(value5);
        EXPECT_EQ(value5.getType(), SCValue::kTypeString);
        EXPECT_STREQ(value5.getString(&bResult),"abc");
        EXPECT_EQ(bResult, true);
        EXPECT_EQ(value5.getRefCount(), 2);
        
        EXPECT_EQ(value101.getType(), SCValue::kTypeString);
        EXPECT_STREQ(value101.getString(&bResult),"abc");
        EXPECT_EQ(bResult, true);
        EXPECT_EQ(value101.getRefCount(), 2);
    }
    
    EXPECT_EQ(value5.getType(), SCValue::kTypeString);
    EXPECT_STREQ(value5.getString(&bResult),"abc");
    EXPECT_EQ(bResult, true);
    EXPECT_EQ(value5.getRefCount(), 1);
    
    EXPECT_EQ(value7.getRefCount(), 1);
    EXPECT_EQ(value7.getType(), SCValue::kTypeDateTime);
    dt = value7.getDateTime(&bResult);
    EXPECT_EQ(bResult, true);
    EXPECT_EQ(dt.getYear(), dtTest.getYear());
    EXPECT_EQ(dt.getMonth(), dtTest.getMonth());
    EXPECT_EQ(dt.getDayOfMonth(), dtTest.getDayOfMonth());
    EXPECT_EQ(dt.getHour(), dtTest.getHour());
    EXPECT_EQ(dt.getMinute(), dtTest.getMinute());
    EXPECT_EQ(dt.getSeconds(), dtTest.getSeconds());
    
    EXPECT_EQ(value8.getRefCount(), 1);
    EXPECT_EQ(value8.getType(), SCValue::kTypeDataBlock);
    EXPECT_STREQ((char*)value8.getDataBlock(&bResult).getDataPtr(),"12345");
    EXPECT_EQ(bResult, true);
    
    vetArrayTest.push_back(value1);
    vetArrayTest.push_back(value2);
    vetArrayTest.push_back(value3);
    vetArrayTest.push_back(value4);
    vetArrayTest.push_back(value5);
    vetArrayTest.push_back(value6);
    vetArrayTest.push_back(value7);
    vetArrayTest.push_back(value8);
    SCValue value9(vetArrayTest);
    
    EXPECT_EQ(value1.getRefCount(), 3);
    EXPECT_EQ(value2.getRefCount(), 3);
    EXPECT_EQ(value3.getRefCount(), 3);
    EXPECT_EQ(value4.getRefCount(), 3);
    EXPECT_EQ(value5.getRefCount(), 3);
    EXPECT_EQ(value6.getRefCount(), 3);
    EXPECT_EQ(value7.getRefCount(), 3);
    EXPECT_EQ(value8.getRefCount(), 3);
    EXPECT_EQ(value9.getRefCount(), 1);
    EXPECT_EQ(value9.getType(), SCValue::kTypeArray);
    vetArray = value9.getArray(&bResult);
    EXPECT_EQ(bResult, true);
    EXPECT_EQ(vetArray[0]==value1, true);
    EXPECT_EQ(vetArray[1]==value2, true);
    EXPECT_EQ(vetArray[2]==value3, true);
    EXPECT_EQ(vetArray[3]==value4, true);
    EXPECT_EQ(vetArray[4]==value5, true);
    EXPECT_EQ(vetArray[5]==value6, true);
    EXPECT_EQ(vetArray[6]==value7, true);
    EXPECT_EQ(vetArray[7]==value8, true);
    
    
    SCValue val1;
    EXPECT_EQ(val1.isNumberType(),false);
    EXPECT_EQ(val1.getType(), SCValue::kTypeUnknown);
}

TEST(TestSCValue, Assignment1)
{
    SCValue value1;
    
    bool bResult = false;
    const int nTest = 234;
    
    value1.setInt(nTest);
    EXPECT_EQ(value1.getType(),SCValue::kTypeInt);
    EXPECT_EQ(value1.getInt(&bResult),nTest);
    EXPECT_EQ(bResult,true);
    
    const bool bTest = true;
    value1.setBool(bTest);
    EXPECT_EQ(value1.getType(),SCValue::kTypeBool);
    EXPECT_EQ(value1.getBool(&bResult),bTest);
    EXPECT_EQ(bResult,true);
    
    const float fTest = 1.23f;
    value1.setFloat(fTest);
    EXPECT_EQ(value1.getType(),SCValue::kTypeFloat);
    EXPECT_EQ(value1.getFloat(&bResult),fTest);
    EXPECT_EQ(bResult,true);
    
    const double dTest = 1.23;
    value1.setDouble(dTest);
    EXPECT_EQ(value1.getType(),SCValue::kTypeDouble);
    EXPECT_EQ(value1.getDouble(&bResult),dTest);
    EXPECT_EQ(bResult,true);
    
    const SCString strTest = "abc123";
    SCString strValue = "";
    value1.setString(strTest);
    EXPECT_EQ(value1.getType(),SCValue::kTypeString);
    EXPECT_STREQ(value1.getString(&bResult), strTest);
    EXPECT_EQ(bResult,true);
    
    const SCDateTime dtTest("2017-10-01 12:34:56","%Y-%m-%d %H:%M:%S");
    SCDateTime dtValue;
    value1.setDateTime(dtTest);
    EXPECT_EQ(value1.getType(),SCValue::kTypeDateTime);
    EXPECT_EQ(dtTest.getStamp(), value1.getDateTime(&bResult).getStamp());
    EXPECT_EQ(bResult,true);
    
    const SCDataBlock dbTest("12345");
    SCDataBlock dbValue;
    value1.setDataBlock(dbTest);
    EXPECT_EQ(value1.getType(),SCValue::kTypeDataBlock);
    dbValue = value1.getDataBlock(&bResult);
    EXPECT_EQ(dbTest.getSize(),dbValue.getSize());
    EXPECT_EQ(bResult,true);
    EXPECT_EQ(memcmp(dbTest.getDataPtr(),dbValue.getDataPtr(),dbValue.getSize()),0);
    
    const SCValue valueTest(123);
    SCValue value2 = valueTest;
    
    EXPECT_EQ(value2.getType(),SCValue::kTypeInt);
    EXPECT_EQ(value2.getInt(&bResult),123);
    EXPECT_EQ(bResult,true);
    
    std::vector<SCValue> vetArrayTest;
    value1.setInt(nTest);
    
    vetArrayTest.push_back(value1);
    value1.setString(strTest);
    strValue = "";
    vetArrayTest.push_back(value1);
    value1.setDataBlock(dbTest);
    dbValue.clear();
    vetArrayTest.push_back(value1);
    value1.setArray(vetArrayTest);
    
    std::vector<SCValue> vetArrayValue;
    EXPECT_EQ(value1.getType(),SCValue::kTypeArray);
    vetArrayValue = value1.getArray(&bResult);
    EXPECT_EQ(bResult,true);
    EXPECT_EQ(vetArrayValue.size(),vetArrayTest.size());
}

TEST(TestSCValue, Assignment2)
{
    SCValue val;
    bool bResult = false;
    const bool bTest = true;
    const float fTest = 1.23f;
    const double dTest = 1.23;
    const SCString strTest = "abc123";
    const SCDateTime dtTest("2017-10-01 12:34:56","%Y-%m-%d %H:%M:%S");
    const SCDataBlock dbTest("12345");
    const int nTest = 567;
    const unsigned char byTest = 234;
    const unsigned int uTest = 890;
    
    val = nTest;
    bResult = false;
    EXPECT_EQ(val.getType(),SCValue::kTypeInt);
    EXPECT_EQ(val.getInt(&bResult),nTest);
    EXPECT_EQ(bResult,true);
    
    val = byTest;
    bResult = false;
    EXPECT_EQ(val.getType(),SCValue::kTypeByte);
    EXPECT_EQ(val.getByte(&bResult),byTest);
    EXPECT_EQ(bResult,true);
    
    val = uTest;
    bResult = false;
    EXPECT_EQ(val.getType(),SCValue::kTypeUInt);
    EXPECT_EQ(val.getUnsignedInt(&bResult),uTest);
    EXPECT_EQ(bResult,true);
    
    val = bTest;
    bResult = false;
    EXPECT_EQ(val.getType(),SCValue::kTypeBool);
    EXPECT_EQ(val.getBool(&bResult),bTest);
    EXPECT_EQ(bResult,true);
    
    val = fTest;
    bResult = false;
    EXPECT_EQ(val.getType(),SCValue::kTypeFloat);
    EXPECT_EQ(val.getFloat(&bResult),fTest);
    EXPECT_EQ(bResult,true);
    
    val = dTest;
    bResult = false;
    EXPECT_EQ(val.getType(),SCValue::kTypeDouble);
    EXPECT_EQ(val.getDouble(&bResult),dTest);
    EXPECT_EQ(bResult,true);
    
    val = strTest;
    bResult = false;
    EXPECT_EQ(val.getType(),SCValue::kTypeString);
    EXPECT_STREQ(val.getString(&bResult).c_str(),strTest.c_str());
    EXPECT_EQ(bResult,true);
    EXPECT_EQ(val.isValidObject<SCString>(),false);
    
    val = dtTest;
    bResult = false;
    EXPECT_EQ(val.getType(),SCValue::kTypeDateTime);
    EXPECT_EQ(dtTest.getStamp(), val.getDateTime(&bResult).getStamp());
    EXPECT_EQ(bResult,true);
    EXPECT_EQ(val.isValidObject<SCDateTime>(),false);
    
    val = dbTest;
    bResult = false;
    EXPECT_EQ(val.getType(),SCValue::kTypeDataBlock);
    SCDataBlock dbValue = val.getDataBlock(&bResult);
    EXPECT_EQ(dbTest.getSize(),dbValue.getSize());
    EXPECT_EQ(bResult,true);
    EXPECT_EQ(memcmp(dbTest.getDataPtr(),dbValue.getDataPtr(),dbValue.getSize()),0);
    EXPECT_EQ(val.isValidObject<SCDataBlock>(),false);
}

TEST(TestSCValue, GetRef)
{
    SCValue val1;
    EXPECT_EQ(val1.getRefString(), nullptr);
    val1.setString("abc");
    EXPECT_NE(val1.getRefString(), nullptr);
    EXPECT_STREQ(val1.getRefString()->c_str(), "abc");
    EXPECT_EQ(val1.getRefDataBlock(), nullptr);
    *(val1.getRefString()) = "123";
    SCString str1 = val1.getString();
    EXPECT_STREQ(str1.c_str(), "123");
    
    SCDataBlock db1;
    db1.pushString("1234");
    val1.setDataBlock(db1);
    SCDataBlock* pBd1 = val1.getRefDataBlock();
    EXPECT_NE(pBd1, nullptr);
    EXPECT_EQ(pBd1->compare(SCDataBlock("1234",4)),0);
    pBd1->pushString("5678");
    SCDataBlock db2 = val1.getDataBlock();
    EXPECT_EQ(db2.compare(SCDataBlock("12345678")),0);
    
    
    SCDateTime dt1("2017-10-01 12:34:56","%Y-%m-%d %H:%M:%S");
    val1.setDateTime(dt1);
    SCDateTime* dt6 = val1.getRefDateTime();
    EXPECT_NE(dt6, nullptr);
    EXPECT_EQ(dt6->getYear(), 2017);
    EXPECT_EQ(dt6->getMonth(), 10);
    EXPECT_EQ(dt6->getDayOfMonth(), 1);
    EXPECT_EQ(dt6->getHour(), 12);
    EXPECT_EQ(dt6->getMinute(), 34);
    EXPECT_EQ(dt6->getSeconds(), 56);
    
    SCDictionary dic1;
    dic1["abc"] = 123;
    val1.setDictionary(dic1);
    SCDictionary* pDic = val1.getRefDictionary();
    EXPECT_NE(pDic, nullptr);
    SCValue val = pDic->getValue("abc");
    EXPECT_EQ(val.getInt(), 123);
    pDic->setValue("efg", 789);
    SCDictionary dic2 = val1.getDictionary();
    EXPECT_EQ(dic2["efg"].getInt(), 789);
    
    std::vector<SCValue> strVct;
    strVct.push_back("aaa");
    strVct.push_back("bbb");
    strVct.push_back("ccc");
    val1.setArray(strVct);
    std::vector<SCValue>* pVct = val1.getRefArray();
    EXPECT_NE(pVct, nullptr);
    EXPECT_EQ(pVct->size(),3);
    EXPECT_STREQ((*pVct)[0].getString().c_str(),"aaa");
    EXPECT_STREQ((*pVct)[1].getString().c_str(),"bbb");
    EXPECT_STREQ((*pVct)[2].getString().c_str(),"ccc");
}

TEST(TestSCValue, Object)
{
    struct TestValueStruct1
    {
        int a;
    };
    
    struct TestValueStruct2
    {
        int b;
    };
    
    SCValue val;
    TestValueStruct1 t1;
    TestValueStruct2 t2;
    
    t1.a = 123;
    val.setObject(t1);
    EXPECT_EQ(val.isValidObject<TestValueStruct1>(),true);
    EXPECT_EQ(val.getType(),SCValue::kTypeObject);
    auto at1 = val.getObject<TestValueStruct1>();
    EXPECT_EQ(at1.a,t1.a);
    auto pat1 = val.getRefObject<TestValueStruct1>();
    EXPECT_NE(pat1,nullptr);
    EXPECT_EQ(pat1->a,t1.a);
    
    t2.b = 789;
    val.setObject(t2);
    EXPECT_EQ(val.isValidObject<TestValueStruct1>(),false);
    EXPECT_EQ(val.isValidObject<TestValueStruct2>(),true);
    EXPECT_EQ(val.getType(),SCValue::kTypeObject);
    auto at2 = val.getObject<TestValueStruct2>();
    EXPECT_EQ(at2.b,t2.b);
    auto pat2 = val.getRefObject<TestValueStruct2>();
    EXPECT_NE(pat2,nullptr);
    EXPECT_EQ(pat2->b,t2.b);
    pat1 = val.getRefObject<TestValueStruct1>();
    EXPECT_EQ(pat1,nullptr);
    
}
