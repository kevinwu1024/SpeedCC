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

#include "TestAlertBoxController.h"

USING_NS_CC;

using namespace SpeedCC;

///------------ TestAlertBoxController
void TestAlertBoxController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test AlertBox");
    TestCaseController::onCreate(parameters);
    this->setupUI();
}
    
void TestAlertBoxController::setupUI()
{
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,20,SCNodeUtils::kDockCenter)
            SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","Show System AlertBox","",23,
                                   SCBehaviorCallFunc::create(SC_MAKE_FUNC(showSystemAlertBox, this)))
            SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","Show Customize AlertBox","",23,
                                   SCBehaviorCallFunc::create(SC_MAKE_FUNC(showCustomizeAlertBox, this)))
        SC_END_PARENT
    SC_END_PARENT
}

void TestAlertBoxController::showSystemAlertBox()
{
    SCSystem::showAlertBox("Test Title","OS built-in AlertBox","OK","Cancel",[](int nSelectedIndex)
                           {
                               SCLog("AlertBox Selected Button, Selected Index: %d", nSelectedIndex);
                           });
}

void TestAlertBoxController::showCustomizeAlertBox()
{
    SCSystem::showAlertBox<TestCustomizeABController>("Test Title","Customize AlertBox","OK","Cancel",[](int nSelectedIndex)
                           {
                               SCLog("AlertBox Selected Button, Selected Index: %d", nSelectedIndex);
                           });
}

///------------ TestCustomizeABController
void TestCustomizeABController::onCreate(SpeedCC::SCDictionary parameters)
{
    SCViewController::onCreate(parameters);
    
    bool bResult = false;
    auto strTitle = parameters.getValue(SC_KEY_TITLE).getString(&bResult);
    SCASSERT(bResult);
    bResult = false;
    auto strMessage = parameters.getValue(SC_KEY_TEXT).getString(&bResult);
    SCASSERT(bResult);
    bResult = false;
    auto strButton1 = parameters.getValue(SC_KEY_STRING0).getString(&bResult);
    SCASSERT(bResult);
    bResult = false;
    auto strButton2 = parameters.getValue(SC_KEY_STRING1).getString(&bResult);
    
    SC_BEGIN_PARENT_ROOT(nullptr, nullptr,SCWinSize())
        SC_BEGIN_PARENT_LAYER_COLOR(nullptr,"dock=center;",Size(280,140),Color4B::GRAY)
            SC_INSERT_LABEL(nullptr,  "y-by=-5; x-by=5; dock=top|left;", strTitle, "", 15)
            SC_INSERT_LABEL(nullptr,"dock=center; y-by=10;",strMessage,"",20)
    
            SC_BEGIN_PARENT_LAYER_COLOR(nullptr,"dock=bottom|mid-x; x-by=-50; y-by=10;",Size(70,25),Color4B::BLUE)
                SC_INSERT_BUTTON_LABEL(nullptr, "dock=center;", strButton1, "", 18, SCBehaviorAlertBoxSelected::create(this,0))
            SC_END_PARENT
    
            SC_BEGIN_PARENT_LAYER_COLOR(nullptr,"dock=bottom|mid-x; x-by=50; y-by=10;",Size(70,25),Color4B::BLUE)
                SC_INSERT_BUTTON_LABEL(nullptr, "dock=center;", strButton2, "", 18, SCBehaviorAlertBoxSelected::create(this,1))
            SC_END_PARENT
    
        SC_END_PARENT
    SC_END_PARENT
}
