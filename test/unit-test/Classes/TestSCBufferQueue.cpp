/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Wu Feng)
 
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

//#include <sys/time.h>

#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SpeedCC;


TEST(TestSCBufferQueue, Basic)
{
    const int nBufferSize = 64;
    SCBufferQueueT<true,nBufferSize> que1;
    
    EXPECT_EQ(que1.isEmpty(),true);
    EXPECT_EQ(que1.getLength(),0);
    
    char testBuf[] = {'1','2','3','4','5'};
    
    que1.pushBack(testBuf, SC_ARRAY_LENGTH(testBuf));
    
    EXPECT_EQ(que1.isEmpty(),false);
    EXPECT_EQ(que1.getLength(),SC_ARRAY_LENGTH(testBuf));
    
    char testBuf2[SC_ARRAY_LENGTH(testBuf)];
    
    que1.popFront(testBuf2, SC_ARRAY_LENGTH(testBuf));
    
    for(int i=0; i<SC_ARRAY_LENGTH(testBuf); ++i)
    {
        EXPECT_EQ(testBuf[i],testBuf2[i]);
    }
    
    EXPECT_EQ(que1.isEmpty(),true);
    EXPECT_EQ(que1.getLength(),0);
    
    que1.pushBack(testBuf, SC_ARRAY_LENGTH(testBuf));
    que1.cleanUp();
    
    EXPECT_EQ(que1.isEmpty(),true);
    EXPECT_EQ(que1.getLength(),0);
}


TEST(TestSCBufferQueue, SameSize)
{
    const int nBufferSize = 8;
    SCBufferQueueT<true,nBufferSize> que1;
    
    char testBuf[] = {'1','2','3','4','5','6','7','8'};
    
    que1.pushBack(testBuf, SC_ARRAY_LENGTH(testBuf));
    
    EXPECT_EQ(que1.isEmpty(),false);
    EXPECT_EQ(que1.getLength(),SC_ARRAY_LENGTH(testBuf));
    
    char testBuf2[SC_ARRAY_LENGTH(testBuf)];
    
    auto uPopSize = que1.popFront(testBuf2, SC_ARRAY_LENGTH(testBuf));
    
    EXPECT_EQ(uPopSize,SC_ARRAY_LENGTH(testBuf));
    
    for(int i=0; i<SC_ARRAY_LENGTH(testBuf); ++i)
    {
        EXPECT_EQ(testBuf[i],testBuf2[i]);
    }
    
    EXPECT_EQ(que1.isEmpty(),true);
    EXPECT_EQ(que1.getLength(),0);
}

TEST(TestSCBufferQueue, OverSize1)
{
    const int nBufferSize = 8;
    SCBufferQueueT<true,nBufferSize> que1;
    
    char testBuf[] = {'1','2','3','4','5','6','7','8','9','a','b','c'};
    
    que1.pushBack(testBuf, SC_ARRAY_LENGTH(testBuf));
    
    EXPECT_EQ(que1.isEmpty(),false);
    EXPECT_EQ(que1.getLength(),SC_ARRAY_LENGTH(testBuf));
    
    char testBuf2[SC_ARRAY_LENGTH(testBuf)];
    
    auto uPopSize = que1.popFront(testBuf2, SC_ARRAY_LENGTH(testBuf));
    
    EXPECT_EQ(uPopSize,SC_ARRAY_LENGTH(testBuf));
    
    for(int i=0; i<SC_ARRAY_LENGTH(testBuf); ++i)
    {
        EXPECT_EQ(testBuf[i],testBuf2[i]);
    }
    
    EXPECT_EQ(que1.isEmpty(),true);
    EXPECT_EQ(que1.getLength(),0);
}


TEST(TestSCBufferQueue, OverSize2)
{
    const int nBufferSize = 8;
    SCBufferQueueT<true,nBufferSize> que1;
    
    char testBuf[] = {'1','2','3','4','5','6','7','8','9','a','b','c'};
    
    que1.pushBack(testBuf, SC_ARRAY_LENGTH(testBuf));
    
    EXPECT_EQ(que1.isEmpty(),false);
    EXPECT_EQ(que1.getLength(),SC_ARRAY_LENGTH(testBuf));
    
    const int nOffset = 2;
    char testBuf2[SC_ARRAY_LENGTH(testBuf)];
    
    auto uPopSize = que1.popFront(testBuf2, SC_ARRAY_LENGTH(testBuf) - nOffset);
    
    EXPECT_EQ(uPopSize,SC_ARRAY_LENGTH(testBuf) - nOffset);
    
    for(int i=0; i<SC_ARRAY_LENGTH(testBuf) - nOffset; ++i)
    {
        EXPECT_EQ(testBuf[i],testBuf2[i]);
    }
    
    EXPECT_EQ(que1.isEmpty(),false);
    EXPECT_EQ(que1.getLength(),nOffset);
    
    uPopSize = que1.popFront(testBuf2, SC_ARRAY_LENGTH(testBuf));
    EXPECT_EQ(uPopSize,nOffset);
    
    for(int i=0; i<nOffset; ++i)
    {
        EXPECT_EQ(testBuf[SC_ARRAY_LENGTH(testBuf) - nOffset +i],testBuf2[i]);
    }
    
    EXPECT_EQ(que1.isEmpty(),true);
    EXPECT_EQ(que1.getLength(),0);
}


TEST(TestSCBufferQueue, MultipleTimes)
{
    const int nBufferSize = 8;
    SCBufferQueueT<true,nBufferSize> que1;
    int sizeArray[] = {3,12,5,7,1,2,4,21,5,16};
    
    char buf[128] = {0};
    
    int nPushCount = 0;
    int nPopCount = 0;
    for(int i=0; i<SC_ARRAY_LENGTH(sizeArray); ++i)
    {
        int nSize = sizeArray[i];
        
        for(int j=0; j<nSize; ++j)
        {
            buf[j] = nPushCount;
            ++nPushCount;
        }
        int nOldLength = que1.getLength();
        que1.pushBack(buf, nSize);
        int nNewLenght = nOldLength + nSize;
        
        EXPECT_EQ(que1.getLength(), nNewLenght);
        
        int nPopSize = que1.getLength() / 2;
        
        memset(buf,0,SC_ARRAY_LENGTH(buf));
        int nPopSize2 = que1.popFront(buf, nPopSize);
        EXPECT_EQ(nPopSize2, nPopSize);
        
        for(int j=0; j<nPopSize2; ++j)
        {
            EXPECT_EQ(buf[j], nPopCount);
            ++nPopCount;
        }
    }
    
    EXPECT_EQ(que1.isEmpty(),false);
    
    que1.cleanUp();
    
    EXPECT_EQ(que1.isEmpty(),true);
    EXPECT_EQ(que1.getLength(),0);
}




