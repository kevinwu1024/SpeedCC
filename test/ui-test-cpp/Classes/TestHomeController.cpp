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

#include "TestHomeController.h"
#include "TestLabelBindingController.h"
#include "TestStageController.h"
#include "TestDockController.h"
#include "TestProgressController.h"
#include "TestLoadingController.h"
#include "TestPageViewController.h"
#include "TestUINodesController.h"
#include "TestAlertBoxController.h"
#include "TestAlignmentController.h"
#include "TestTriggerController.h"
#include "TestHttpFetcherController.h"
#include "TestSliderController.h"
#include "TestLogFileController.h"
#include "TestLanguageController.h"
#include "TestFSMController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestHomeController::onCreate(SCDictionary parameters)
{
    SCViewController::onCreate(parameters);

    auto viewSize = Size(SCWinSize().width*3/4,SCWinSize().height*3/4+20);
    auto containerSize = Size(viewSize.width,700);
    
    auto ptrLoadingBvr = SCBehaviorViewGoto::create<TestLoadingTraget0Controller,SCClassNull,TestLoadingController>();
    
	cocos2d::ui::ScrollView* pScrollView = nullptr;

    SC_BEGIN_PARENT_ROOT(nullptr, nullptr,nullptr)
        SC_BEGIN_PARENT_LAYER_COLOR(nullptr,"dock=center;",SCWinSize(),Color4B::WHITE)
            SC_INSERT_LABEL_BMFONT(nullptr,"x=0.5; y=0.90;","Home Scene","blue_font.fnt")
    
            SC_BEGIN_PARENT_SCROLLVIEW(&pScrollView,"dock=bottom|mid-x; y-by=20;",false,viewSize,containerSize,nullptr)
                SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=top|mid-x;",false,20,SCNodeUtils::kDockCenter)
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","UI Nodes","",23,SCBehaviorViewGoto::create<TestUINodesController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","Alignment","",23,SCBehaviorViewGoto::create<TestAlignmentController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","Slider","",23,SCBehaviorViewGoto::create<TestSliderController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","Http Fetcher","",23,SCBehaviorViewGoto::create<TestHttpFetcherController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","Label Binding","",23,SCBehaviorViewGoto::create<TestLabelBindingController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","ECS","",23,SCBehaviorViewGoto::create<TestStageController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","FSM","",23,SCBehaviorViewGoto::create<TestFSMController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","Dock","",23,SCBehaviorViewGoto::create<TestDockController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","Progress","",23,SCBehaviorViewGoto::create<TestProgressController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","Loading","",23,ptrLoadingBvr)
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","PageView","",23,SCBehaviorViewGoto::create<TestPageViewController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","Trigger","",23,SCBehaviorViewGoto::create<TestTriggerController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;","AlertBox","",23,SCBehaviorViewGoto::create<TestAlertBoxController>())

					SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Log File", "", 23, SCBehaviorViewGoto::create<TestLogFileController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Language", "", 23, SCBehaviorViewGoto::create<TestLanguageController>())
    
                SC_END_PARENT
            SC_END_PARENT
        SC_END_PARENT
    SC_END_PARENT

		pScrollView->setScrollBarAutoHideTime(0);
}


