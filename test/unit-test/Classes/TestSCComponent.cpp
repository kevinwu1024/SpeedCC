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

TEST(TestSCComponent, SingleComponent)
{
    /*
    bool bResult = false;
    auto cmpPtr0 = SCComponent::create();
    auto cmpPtr1 = SCComponent::create();
    
    bResult = cmpPtr0->hasComponent<SCComponent>();
    EXPECT_EQ(bResult,false);
    
    bResult = cmpPtr0->addComponent(cmpPtr0);
    EXPECT_EQ(bResult,false);
    bResult = cmpPtr0->addComponent(cmpPtr1);
    EXPECT_EQ(bResult,true);
    EXPECT_EQ(cmpPtr1.getRefCount(),2);
    
    cmpPtr0->removeComponent(cmpPtr1);
    EXPECT_EQ(cmpPtr1.getRefCount(),1);
    bResult = cmpPtr0->hasComponent<SCComponent>();
    EXPECT_EQ(bResult,false);
    
    bResult = cmpPtr0->addComponent(cmpPtr1);
    bResult = cmpPtr0->hasComponent<SCComponent>();
    EXPECT_EQ(bResult,true);
    
    SCComponent::Ptr cmpPtr3;
    cmpPtr3 = cmpPtr0->getComponent<SCComponent>();
    EXPECT_EQ(cmpPtr3!=NULL,true);
    EXPECT_EQ(cmpPtr3.getRefCount(),3);
    
    auto cmpVet = cmpPtr0->getComponents<SCComponent>();
    EXPECT_EQ(cmpPtr3.getRefCount(),4);
    EXPECT_EQ(cmpVet.size(),1);
    EXPECT_EQ(cmpVet[0]==cmpPtr3,true);
    
    cmpPtr3->setName("test");
    auto cmpPtr4 = cmpPtr0->getComponent<SCComponent>("abc");
    EXPECT_EQ(cmpPtr4==NULL,true);
    
    auto cmpPtr5 = cmpPtr0->getComponent<SCComponent>("test");
    EXPECT_EQ(cmpPtr5==cmpPtr3,true);
     */
}

TEST(TestSCComponent, MultipleComponents)
{
    /*
    bool bResult = false;
    auto cmpPtr0 = SCComponent::create();
    auto cmpPtr1 = SCComponent::create();
    auto cmpPtr2 = SCComponent::create();
    auto cmpPtr3 = SCComponent::create();
    
    cmpPtr0->addComponent(cmpPtr1);
    cmpPtr0->addComponent(cmpPtr2);
    cmpPtr0->addComponent(cmpPtr3);
     */
}




