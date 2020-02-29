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

TEST(TestSCDictionary, Constructor)
{
    SCDictionary testPar;
    
    EXPECT_EQ(testPar.isEmpty(),true);
    EXPECT_EQ(testPar.getCount(),0);
    
    testPar.setValue("key1", 123);
    testPar.setValue("key2", "abc");
    testPar.setValue("key3", 'd');
    testPar.setValue("key4", 4.56f);
    
    EXPECT_EQ(testPar.isEmpty(),false);
    EXPECT_EQ(testPar.getCount(),4);
    
    EXPECT_EQ(testPar.hasKey("key10"),false);
    
    EXPECT_EQ(testPar.hasKey("key1"),true);
    EXPECT_EQ(testPar.getValue("key1").getInt(), 123);
    
    EXPECT_EQ(testPar.hasKey("key2"),true);
    EXPECT_EQ(testPar.getValue("key2").getString(), "abc");
    
    EXPECT_EQ(testPar.hasKey("key3"),true);
    EXPECT_EQ(testPar.getValue("key3").getChar(), 'd');
    
    EXPECT_EQ(testPar.hasKey("key4"),true);
    EXPECT_EQ(testPar.getValue("key4").getFloat(), 4.56f);
    
    testPar.removeKey("key1");
    EXPECT_EQ(testPar.hasKey("key1"),false);
}


TEST(TestSCDictionary, Json)
{
    SCString strJson = "{\"int\":123,\"float\":456.78,\"str\":\"abc\",\"obj\":{\"val1\":456},\"array1\":[12,34],\"array2\":[{\"aval\":1111.2},{\"aval\":\"2222\"}]}";
    
    SCDictionary testDic;
    
    EXPECT_EQ(testDic.loadFromJsonString(strJson),true);
    
    SCValue val1 = testDic["int"];
    EXPECT_EQ(val1.isNumberType(),true);
    EXPECT_EQ(val1.getInt(), 123);
    
    val1 = testDic["float"];
    EXPECT_EQ(val1.isNumberType(),true);
    EXPECT_EQ(val1.getDouble(), 456.78);
    
    val1 = testDic["str"];
    EXPECT_EQ(val1.isNumberType(),false);
    EXPECT_EQ(val1.getType(),SCValue::kTypeString);
    EXPECT_STREQ(val1.getString(), "abc");
    
    val1 = testDic["obj"];
    EXPECT_EQ(val1.getType(),SCValue::kTypeDictionary);
    SCDictionary dic1 = val1.getDictionary();
    SCValue valDic = dic1["val1"];
    EXPECT_EQ(valDic.isNumberType(),true);
    EXPECT_EQ(valDic.getInt(),456);
    
    
    val1 = testDic["array1"];
    EXPECT_EQ(val1.getType(),SCValue::kTypeArray);
    auto array = val1.getArray();
    EXPECT_EQ(array.size(),2);
    
    SCValue v1 = array[0];
    EXPECT_EQ(v1.isNumberType(),true);
    EXPECT_EQ(v1.getInt(),12);
    
    v1 = array[1];
    EXPECT_EQ(v1.isNumberType(),true);
    EXPECT_EQ(v1.getInt(),34);
    
    
    val1 = testDic["array2"];
    EXPECT_EQ(val1.getType(),SCValue::kTypeArray);
    array = val1.getArray();
    EXPECT_EQ(array.size(),2);
    
    v1 = array[0];
    EXPECT_EQ(v1.getType(),SCValue::kTypeDictionary);
    SCDictionary dic2 = v1.getDictionary();
    EXPECT_EQ(dic2["aval"].getDouble(),1111.2);
    
    v1 = array[1];
    EXPECT_EQ(v1.getType(),SCValue::kTypeDictionary);
    dic2 = v1.getDictionary();
    EXPECT_STREQ(dic2["aval"].getString().c_str(),"2222");
    
    
//    SCString strJson2 = testDic.exportJson(true);
//    std::cout << strJson2.c_str() << std::endl;
    EXPECT_EQ(testDic.loadFromJsonString("123"),false);
}


TEST(TestSCDictionary, Index)
{
    SCDictionary testDic;
    
    testDic.setValue("index1", 123);
    testDic.setValue("index2", "abc");
    EXPECT_EQ(testDic.hasKey("index1"), true);
    EXPECT_EQ(testDic.hasKey("index2"), true);
    EXPECT_EQ(testDic.hasKey("index3"), false);
    EXPECT_EQ(testDic.getCount(), 2);
    EXPECT_EQ(testDic.isEmpty(), false);
    EXPECT_EQ(testDic["index1"].getInt(), 123);
    EXPECT_STREQ(testDic["index2"].getString().c_str(), "abc");
    
    testDic["index1"] = "567";
    EXPECT_STREQ(testDic["index1"].getString().c_str(), "567");
    
    testDic.removeKey("index2");
    EXPECT_EQ(testDic.getCount(), 1);
    
    SCDictionary::SKVPair pair;
    pair.strKey = "index3";
    pair.value = 890;
    testDic.setValue(pair);
    
    EXPECT_EQ(testDic.getCount(), 2);
    EXPECT_EQ(testDic["index3"].getInt(), 890);
    EXPECT_EQ(testDic.hasKey("index3"), true);
    
    pair.strKey = "index1";
    pair.value = "9999";
    testDic.setValue(pair);
    EXPECT_EQ(testDic.getCount(), 2);
    EXPECT_STREQ(testDic["index1"].getString().c_str(), "9999");
    
    testDic.removeAllKeys();
    EXPECT_EQ(testDic.getCount(), 0);
    EXPECT_EQ(testDic.isEmpty(), true);
}


TEST(TestSCDictionary, ForEach)
{
    SCDateTime dtTest("2017-10-01 12:34:56","%Y-%m-%d %H:%M:%S");
    std::vector<SCDictionary::SKVPair> pairVct;
    pairVct.push_back(SCDictionary::SKVPair("key1",111));
    pairVct.push_back(SCDictionary::SKVPair("key2","abc"));
    pairVct.push_back(SCDictionary::SKVPair("key3",dtTest));
    
    SCDictionary testDic(pairVct);
    
    EXPECT_EQ(testDic.getCount(), 3);
    
    testDic.forEach([&dtTest](const SCString& str,const SCValue& value) -> bool{
        if(str == "key1")
        {
            std::cout << "SCDictionary foreach key1" << std::endl;
            EXPECT_EQ(value.isNumberType(), true);
            EXPECT_EQ(value.getInt(), 111);
        }
        else if(str == "key2")
        {
            std::cout << "SCDictionary foreach key2" << std::endl;
            EXPECT_EQ(value.getType(), SCValue::kTypeString);
            EXPECT_STREQ(value.getString().c_str(), "abc");
        }
        else if(str == "key3")
        {
            std::cout << "SCDictionary foreach key3" << std::endl;
            EXPECT_EQ(value.getType(), SCValue::kTypeDateTime);
            EXPECT_EQ(dtTest.getStamp(), value.getDateTime().getStamp());
        }
        else
        {
            SCASSERT(false);
        }
        
        return true;
    });
}
