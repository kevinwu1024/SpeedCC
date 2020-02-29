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

TEST(TestSCDataBlock, Constructor)
{
    const char testData[] = "abcdef";
    
    SCDataBlock db1;
    SCDataBlock db2(db1);
    
    EXPECT_EQ(db1.getSize(), 0);
    EXPECT_EQ(db2.getSize(), 0);
    EXPECT_EQ(db1.getDataPtr(),db2.getDataPtr());
    
    SCDataBlock db3((void*)testData,sizeof(testData));
    EXPECT_EQ(db3.getSize(), sizeof(testData));
    EXPECT_EQ(memcmp(db3.getDataPtr(), testData, sizeof(testData)),0);
    EXPECT_EQ(db3.getRefCount(), 1);
    
    SCDataBlock db4(db3);
    EXPECT_EQ(db3.getSize(), db4.getSize());
    EXPECT_EQ(db3.getDataPtr(), db4.getDataPtr());
    EXPECT_EQ(db3.getRefCount(), 2);
    
    db4.clear();
    EXPECT_EQ(db4.getRefCount(), 0);
    EXPECT_EQ(db3.getRefCount(), 1);
    
    SCString str = "123456";
    SCDataBlock db5(str);
    EXPECT_EQ(db5.getSize(), str.getLength());
    EXPECT_EQ(memcmp(db5.getDataPtr(), str.c_str(), db5.getSize()),0);
}

TEST(TestSCDataBlock, Assignment)
{
    const char testData[] = "abcdef";
    
    SCDataBlock db1;
    db1.assign(testData, sizeof(testData));
    EXPECT_EQ(db1.getSize(), sizeof(testData));
    EXPECT_EQ(memcmp(db1.getDataPtr(), testData, sizeof(testData)),0);
    
    SCDataBlock db2;
    db2.assign(db1);
    EXPECT_EQ(db1.getSize(), db2.getSize());
    EXPECT_EQ(memcmp(db1.getDataPtr(), db2.getDataPtr(), db2.getSize()),0);
    
    SCDataBlock db3;
    db3 = db1;
    EXPECT_EQ(db1.getSize(), db3.getSize());
    EXPECT_EQ(memcmp(db1.getDataPtr(), db3.getDataPtr(), db3.getSize()),0);
}

TEST(TestSCDataBlock, Append)
{
    const char testData1[] = "abcdef";
    const char testData2[] = "123456";
    
    SCDataBlock db1;
    db1.append(testData1, (int)strlen(testData1));
    EXPECT_EQ(db1.getSize(), strlen(testData1));
    EXPECT_EQ(memcmp(db1.getDataPtr(), testData1, strlen(testData1)),0);
    
    db1.append(testData2, sizeof(testData2));
    EXPECT_EQ(db1.getSize(), strlen(testData1)+sizeof(testData2));
    EXPECT_EQ(memcmp(db1.getDataPtr(), "abcdef123456", strlen("abcdef123456")),0);
    
    SCDataBlock db2;
    db1.clear();
    db2.append(testData1, (int)strlen(testData1));
    db1.append(testData2, sizeof(testData2));
    db2.append(db1);
    EXPECT_EQ(db2.getSize(), strlen(testData1)+sizeof(testData2));
    EXPECT_EQ(memcmp(db2.getDataPtr(), "abcdef123456", strlen("abcdef123456")),0);
    
    db1.clear();
    db2.clear();
    db2.append(testData1, (int)strlen(testData1));
    db1.append(testData2, sizeof(testData2));
    db2 += db1;
    EXPECT_EQ(db2.getSize(), strlen(testData1)+sizeof(testData2));
    EXPECT_EQ(memcmp(db2.getDataPtr(), "abcdef123456", strlen("abcdef123456")),0);
    
    db1.clear();
    db2.clear();
    db1.append(testData2, sizeof(testData2));
    db2 += db1;
    EXPECT_EQ(memcmp(db2.getDataPtr(), testData2, strlen(testData2)),0);
}


TEST(TestSCDataBlock, PushPop)
{
    unsigned char testByte = 7;
    unsigned short testWord = 61234;
    unsigned int testDword = 8888888;
    INT64 testInt64 = 7777777777;
    SCString testStr = "abcd1234";
    bool bSuccess = false;
    
    SCDataBlock db1;
    
    db1.pushByte(testByte);
    EXPECT_EQ(db1.getSize(),1);
    
    db1.pushWord(testWord);
    EXPECT_EQ(db1.getSize(),1+2);
    
    db1.pushDword(testDword);
    EXPECT_EQ(db1.getSize(),1+2+4);
    
    db1.pushInt64(testInt64);
    EXPECT_EQ(db1.getSize(),1+2+4+8);
    
    db1.pushString(testStr);
    EXPECT_EQ(db1.getSize(),1+2+4+8+8);
    
    bSuccess = false;
    auto strResult = db1.popString(8,&bSuccess);
    EXPECT_EQ(bSuccess,true);
    EXPECT_EQ(db1.getSize(),1+2+4+8);
    EXPECT_STREQ(strResult.c_str(), testStr.c_str());
    
    bSuccess = false;
    auto n64Result = db1.popInt64(&bSuccess);
    EXPECT_EQ(bSuccess,true);
    EXPECT_EQ(db1.getSize(),1+2+4);
    EXPECT_EQ(n64Result,testInt64);
    
    bSuccess = false;
    auto dwResult = db1.popDword(&bSuccess);
    EXPECT_EQ(bSuccess,true);
    EXPECT_EQ(db1.getSize(),1+2);
    EXPECT_EQ(dwResult,testDword);
    
    bSuccess = false;
    auto wResult = db1.popWord(&bSuccess);
    EXPECT_EQ(bSuccess,true);
    EXPECT_EQ(db1.getSize(),1);
    EXPECT_EQ(wResult,testWord);
    
    bSuccess = false;
    auto byResult = db1.popByte(&bSuccess);
    EXPECT_EQ(bSuccess,true);
    EXPECT_EQ(db1.getSize(),0);
    EXPECT_EQ(byResult,testByte);
}

TEST(TestSCDataBlock, Compare)
{
    SCDataBlock db1;
    
    EXPECT_EQ(db1.getSize(),0);
    db1.resize(10);
    EXPECT_EQ(db1.getSize(),10);
    db1.zero();
    char buf[10] = {0};
    int result = memcmp(db1.getDataPtr(),buf,0);
    EXPECT_EQ(result,0);
    
    SCDataBlock db2;
    EXPECT_NE(db2.compare(db1), 0);
    db1.resize(0);
    EXPECT_EQ(db1.getSize(),0);
    db1.pushString("1235");
    db2.pushString("1234");
    EXPECT_NE(db2.compare(db1), -1);
    
    db1.clear();
    EXPECT_EQ(db1.getSize(),0);
    db1.pushString("1234");
    EXPECT_NE(db2.compare(db1), -1);
    
    db1.clear();
    db2.clear();
    EXPECT_NE(db2.compare(db1), 0);
    
    db1.pushString("123");
    db2.pushString("1234");
    EXPECT_NE(db2.compare(db1), 1);
}
