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

#include "TestProgressController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestProgressController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test Progress");
    TestCaseController::onCreate(parameters);

    _ptrCaseBvr->setCase(0, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseBarBasic, this)));
    _ptrCaseBvr->setCase(1, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseRadialBasic, this)));
    _ptrCaseBvr->setCase(2, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseBarBinding, this)));
    _ptrCaseBvr->setCase(3, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseRadialBinding, this)));
    
    _ptrCaseBvr->execute();
}

void TestProgressController::testCaseBarBasic()
{
    (*_ptrWatchDescription) = "(Bar Basic)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
    
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,20,SCNodeUtils::kDockCenter)
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(nullptr, "text-color=black;", "(bar, left to right, horizontal, 60%)", "", 15)
                SC_INSERT_PROGRESS_BAR(nullptr, "", "progressbar_bk.png", "progressbar_ft.png", 60, true, true)
            SC_END_PARENT
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(nullptr, "text-color=black;", "(bar, right to left, horizontal, 30%)", "", 15)
                SC_INSERT_PROGRESS_BAR(nullptr, "", "progressbar_bk.png", "progressbar_ft.png", 30, true, false)
            SC_END_PARENT
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,20,SCNodeUtils::kDockCenter)
    
                SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_LABEL(nullptr, "text-color=black;", "(bar, down to up, vertical, 30%)", "", 15)
                    SC_INSERT_PROGRESS_BAR(nullptr,"", "progressbar_v_bk.png", "progressbar_v_ft.png", 30, false,  true)
                SC_END_PARENT

                SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_LABEL(nullptr, "text-color=black;", "(bar, up to down, vertical, 30%)", "", 15)
                    SC_INSERT_PROGRESS_BAR(nullptr,"", "progressbar_v_bk.png", "progressbar_v_ft.png", 30, false, false)
                SC_END_PARENT
    
            SC_END_PARENT
    
        SC_END_PARENT
    
    SC_END_PARENT
}

void TestProgressController::testCaseRadialBasic()
{
    (*_ptrWatchDescription) = "(Radial Basic)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
    
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,20,SCNodeUtils::kDockCenter)
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(nullptr,  "text-color=black;", "(radial, cw, 60%)", "", 15)
                SC_INSERT_PROGRESS_RADIAL(nullptr,  "", "HelloWorld.png", "mask.png", 60,false)
            SC_END_PARENT
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(nullptr, "text-color=black;", "(radial, ccw, 60%)", "", 15)
                SC_INSERT_PROGRESS_RADIAL(nullptr, "", "HelloWorld.png", "mask.png", 60,true)
            SC_END_PARENT
    
        SC_END_PARENT
    SC_END_PARENT
}

void TestProgressController::testCaseBarBinding()
{
    (*_ptrWatchDescription) = "(Bar Binding)";
    _pContainerLayer->removeAllChildren();
    
    auto ptrInt1 = SCWatchInt::create(60);
    _ptrWatchStr1 = SCWatchString::create("(bar, left to right, horizontal, 60%)");
    ptrInt1->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr1) = SCString(0,"(bar, left to right, horizontal, %d%%)",kk);
                           });
    
    auto ptrInt2 = SCWatchInt::create(30);
    _ptrWatchStr2 = SCWatchString::create("(bar, right to left, horizontal, 30%)");
    ptrInt2->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr2) = SCString(0,"(bar, right to left, horizontal, %d%%)",kk);
                           });
    
    auto ptrInt3 = SCWatchInt::create(30);
    _ptrWatchStr3 = SCWatchString::create("(bar, down to up, vertical, 30%)");
    ptrInt3->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr3) = SCString(0,"(bar, down to up, vertical, %d%%)",kk);
                           });
    
    auto ptrInt4 = SCWatchInt::create(30);
    _ptrWatchStr4 = SCWatchString::create("(bar, right to left, horizontal, 30%)");
    ptrInt4->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr4) = SCString(0,"(bar, right to left, horizontal, %d%%)",kk);
                           });
    
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
    
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,20,SCNodeUtils::kDockCenter)
    
            // bar 1
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,10,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(nullptr, "text-color=black;", _ptrWatchStr1, "", 15)
    
                SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "-", "", 20,SCBehaviorAddInt::create(ptrInt1,-10))
                    SC_INSERT_PROGRESS_BAR(nullptr, "", "progressbar_bk.png", "progressbar_ft.png", ptrInt1, true, true)
                    SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "+", "", 20,
                                           SCBehaviorAddInt::create(ptrInt1,10))
                SC_END_PARENT
    
            SC_END_PARENT
    
            // bar 2
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,10,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(nullptr,"text-color=black;", _ptrWatchStr2, "", 15)
    
                SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "+", "", 20,SCBehaviorAddInt::create(ptrInt2,10))
                    SC_INSERT_PROGRESS_BAR(nullptr, "", "progressbar_bk.png", "progressbar_ft.png", ptrInt2, true, false)
                    SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;", "-", "", 20,
                                       SCBehaviorAddInt::create(ptrInt2,-10))
                SC_END_PARENT
    
            SC_END_PARENT
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,20,SCNodeUtils::kDockCenter)
    
                // bar 3
                SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_LABEL(nullptr, "text-color=black;", _ptrWatchStr3, "", 15)
    
                    SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,5,SCNodeUtils::kDockCenter)
                        SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "+", "", 20,SCBehaviorAddInt::create(ptrInt3,10))
                        SC_INSERT_PROGRESS_BAR(nullptr, "", "progressbar_v_bk.png", "progressbar_v_ft.png", ptrInt3, false, true)
                        SC_INSERT_BUTTON_LABEL(nullptr,"text-color=black;", "-", "", 20,
                                           SCBehaviorAddInt::create(ptrInt3,-10))
                    SC_END_PARENT
                SC_END_PARENT

                // bar 4
                SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_LABEL(nullptr, "text-color=black;", _ptrWatchStr4, "", 15)
    
                    SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,5,SCNodeUtils::kDockCenter)
                        SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "+", "", 20,SCBehaviorAddInt::create(ptrInt4,10))
                        SC_INSERT_PROGRESS_BAR(nullptr, "", "progressbar_v_bk.png", "progressbar_v_ft.png", ptrInt4, false, false)
                        SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "-", "", 20,
                                           SCBehaviorAddInt::create(ptrInt4,-10))
                    SC_END_PARENT
                SC_END_PARENT
    
            SC_END_PARENT
 
        SC_END_PARENT
    
    SC_END_PARENT
}


void TestProgressController::testCaseRadialBinding()
{
    (*_ptrWatchDescription) = "(Radial Binding)";
    _pContainerLayer->removeAllChildren();
    
    auto ptrInt1 = SCWatchInt::create(60);
    _ptrWatchStr1 = SCWatchString::create("(radial, cw, 60%)");
    ptrInt1->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr1) = SCString(0,"(radial, cw, %d%%)",kk);
                           });
    
    auto ptrInt2 = SCWatchInt::create(30);
    _ptrWatchStr2 = SCWatchString::create("(radial, ccw, 60%)");
    ptrInt2->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr2) = SCString(0,"(radial, ccw, %d%%)",kk);
                           });
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
    
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,20,SCNodeUtils::kDockCenter)
    
            // radial 1
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(nullptr, "text-color=black;", _ptrWatchStr1, "", 15)
    
                SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "-", "", 20,SCBehaviorAddInt::create(ptrInt1,-10))
                    SC_INSERT_PROGRESS_RADIAL(nullptr, "", "HelloWorld.png", "mask.png", ptrInt1,false)
                    SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "+", "", 20,SCBehaviorAddInt::create(ptrInt1,10))
                SC_END_PARENT
            SC_END_PARENT
    
            // radial 2
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(nullptr, "text-color=black;", _ptrWatchStr2, "", 15)
    
                SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "-", "", 20,SCBehaviorAddInt::create(ptrInt2,-10))
                    SC_INSERT_PROGRESS_RADIAL(nullptr, "", "HelloWorld.png", "mask.png", ptrInt2,true)
                    SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "+", "", 20,SCBehaviorAddInt::create(ptrInt2,10))
                SC_END_PARENT
            SC_END_PARENT
    
        SC_END_PARENT
    SC_END_PARENT
}



