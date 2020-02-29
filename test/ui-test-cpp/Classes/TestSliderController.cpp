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

#include "TestSliderController.h"

USING_NS_CC;

void TestSliderController::onCreate(SCDictionary parameters)
{
    parameters.setValue("name", "slider");
    parameters.setValue("title", "Test Slider");
    TestCaseController::onCreate(parameters);
    
    auto ptrWatch = SCWatchInt::create(20);
    
    ptrWatch->addUpdateFunc([this](SCWatchInt::Ptr ptr, const int nNew, const int nOld)
                            {
                                (*_ptrWatchValue) = ptr->getString();
                            });
    
    _ptrWatchValue = SCWatchString::create(ptrWatch->getString());
    auto ptrBvrAdd = SCBehaviorCallFunc::create([ptrWatch]()
                                                {
                                                    auto ptrWatch1 = ptrWatch;
                                                    (*ptrWatch1) += 10;
                                                });
    
    auto ptrBvrSub = SCBehaviorCallFunc::create([ptrWatch]()
                                                {
                                                    auto ptrWatch1 = ptrWatch;
                                                    (*ptrWatch1) -= 10;
                                                });
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,0)
            SC_INSERT_LABEL(nullptr, "text-color=black;", _ptrWatchValue, "Arial", 20)
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",true,6,0)
                SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "-", "Arial", 20, ptrBvrSub)
                SC_INSERT_SLIDER(nullptr, nullptr, "progressbar_bk.png", "progressbar_ft.png", "CloseNormal.png", ptrWatch)
                SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "+", "Arial", 20, ptrBvrAdd)
            SC_END_PARENT
    
            SC_INSERT_SLIDER(nullptr, nullptr, "progressbar_bk.png", "progressbar_ft.png", "CloseNormal.png", 50)
        SC_END_PARENT
    SC_END_PARENT
}

