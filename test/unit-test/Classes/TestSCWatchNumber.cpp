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
using namespace cocos2d;

TEST(TestSCWatchNumber, Plus)
{
    SCWatchInt::Ptr numInt1 = SCWatchInt::create();
    
    EXPECT_EQ((*numInt1)==0,true);
    
    (*numInt1) = 3;
    EXPECT_EQ(*numInt1==3,true);
    EXPECT_EQ(3==*numInt1,true);
    
    int p1 = *numInt1 + 4;
    EXPECT_EQ(*numInt1==3,true);
    EXPECT_EQ(p1==7,true);
    
    SCWatchInt::Ptr numInt2 = SCWatchInt::create();
    *numInt2 = (int)(*numInt1 + 4);
    EXPECT_EQ(*numInt1==3,true);
    EXPECT_EQ(*numInt2==7,true);
    
    int p3 = 4 + *numInt1;
    EXPECT_EQ(*numInt1==3,true);
    EXPECT_EQ(p3==7,true);
    
    *numInt1 = 5;
    *numInt1 += 3;
    EXPECT_EQ(*numInt1==8,true);
    
    *numInt1 = 2;
    *numInt2 = 3;
    p1 = *numInt1 + *numInt2;
    EXPECT_EQ(p1==5,true);
    EXPECT_EQ(*numInt1==2,true);
    EXPECT_EQ(*numInt2==3,true);
    
    *numInt1 = 2;
    p1 = 4;
    p1 += *numInt1;
    EXPECT_EQ(p1==6,true);
    
    *numInt1 = 2;
    *numInt2 = 3;
    *numInt1 += *numInt2;
    EXPECT_EQ(*numInt1==5,true);
    
    *numInt1 = 2;
    *numInt1 += 4.2f;
    EXPECT_EQ(*numInt1==6,true);
    
    *numInt1 = 3;
    *numInt1 = *numInt1 + 4.2f;
    EXPECT_EQ(*numInt1==7,true);
    
    *numInt1 = 1;
    EXPECT_EQ((*numInt1)++ == 1,true);
    EXPECT_EQ(*numInt1 == 2,true);
    EXPECT_EQ(++(*numInt1) == 3,true);
}


TEST(TestSCWatchNumber, Boolean)
{
    SCWatchBool::Ptr numBool = SCWatchBool::create();
    
    (*numBool) = true;
    EXPECT_EQ(*numBool==true,true);
    *numBool = false;
    EXPECT_EQ(false==*numBool,true);
    
    bool testBool = *numBool;
    EXPECT_EQ(*numBool==testBool,true);
    
}

