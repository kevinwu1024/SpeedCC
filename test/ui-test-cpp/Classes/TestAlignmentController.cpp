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

#include "TestAlignmentController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestAlignmentController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test Alignment");
    TestCaseController::onCreate(parameters);
    
    _ptrCaseBvr->setCase(0, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseHorizontal, this)));
    _ptrCaseBvr->setCase(1, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseVertical, this)));
    _ptrCaseBvr->setCase(2, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseNestHV, this)));
    _ptrCaseBvr->setCase(3, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseNestVH, this)));
    
    _ptrCaseBvr->execute();
}

void TestAlignmentController::testCaseHorizontal()
{
    (*_ptrWatchDescription) = "(Alignment Horizontal)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,40,SCNodeUtils::EDockType::kDockCenter)
            SC_INSERT_LABEL(nullptr, "text-color=black;", "ABC", "", 20)
            SC_INSERT_SPRITE(nullptr, "scale=0.4;", "HelloWorld.png")
            SC_INSERT_LABEL(nullptr, "text-color=black;", "123", "", 20)
        SC_END_PARENT
    SC_END_PARENT
}

void TestAlignmentController::testCaseVertical()
{
    (*_ptrWatchDescription) = "(Alignment Vertical)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,SCNodeUtils::EDockType::kDockCenter)
            SC_INSERT_LABEL(nullptr, "text-color=black;", "ABC", "", 20)
            SC_INSERT_SPRITE(nullptr, "scale=0.4;", "HelloWorld.png")
            SC_INSERT_LABEL(nullptr, "text-color=black;", "123", "", 20)
        SC_END_PARENT
    SC_END_PARENT
}

void TestAlignmentController::testCaseNestHV()
{
    (*_ptrWatchDescription) = "(Alignment Nest Horizontal=>Vertical)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,40,SCNodeUtils::EDockType::kDockCenter)
            SC_INSERT_LABEL(nullptr, "text-color=black;", "ABC", "", 20)
            SC_INSERT_SPRITE(nullptr, "scale=0.4;", "HelloWorld.png")
            SC_INSERT_LABEL(nullptr, "text-color=black;", "123", "", 20)
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,SCNodeUtils::EDockType::kDockCenter)
                SC_INSERT_LABEL(nullptr, "text-color=black;", "ABC", "", 20)
                SC_INSERT_SPRITE(nullptr, "scale=0.4;", "HelloWorld.png")
                SC_INSERT_LABEL(nullptr, "text-color=black;", "123", "", 20)
            SC_END_PARENT
    
        SC_END_PARENT
    SC_END_PARENT
}

void TestAlignmentController::testCaseNestVH()
{
    (*_ptrWatchDescription) = "(Alignment Nest Vertical=>Horizontal)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,SCNodeUtils::EDockType::kDockCenter)
            SC_INSERT_LABEL(nullptr, "text-color=black;", "ABC", "", 20)
            SC_INSERT_SPRITE(nullptr, "scale=0.4;", "HelloWorld.png")
            SC_INSERT_LABEL(nullptr, "text-color=black;", "123", "", 20)
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,40,SCNodeUtils::EDockType::kDockCenter)
                SC_INSERT_LABEL(nullptr, "text-color=black;", "ABC", "", 20)
                SC_INSERT_SPRITE(nullptr, "scale=0.4;", "HelloWorld.png")
                SC_INSERT_LABEL(nullptr, "text-color=black;", "123", "", 20)
            SC_END_PARENT
    
        SC_END_PARENT
    SC_END_PARENT
}


