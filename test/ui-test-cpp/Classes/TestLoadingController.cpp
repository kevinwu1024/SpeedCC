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

#include "TestLoadingController.h"

USING_NS_CC;

using namespace SpeedCC;

///------------ TestLoadingController
void TestLoadingController::onCreate(SCDictionary parameters)
{
    SCViewController::onCreate(parameters);
    
    this->setupUI();
}
    
void TestLoadingController::setupUI()
{
    _ptrWatchStr = SCWatchString::create();
    _nCounter = 4;
    
    SC_BEGIN_PARENT_ROOT(nullptr, nullptr,SCWinSize())
        SC_BEGIN_PARENT_LAYER_COLOR(nullptr,"dock=center;",SCWinSize(),Color4B::WHITE)
            // title
            SC_INSERT_LABEL_BMFONT(nullptr,"dock=top|mid-x; y-by=-100;","Test Loading","blue_font.fnt")
    
            SC_INSERT_LABEL(nullptr, "dock=center; text-color=black;", _ptrWatchStr, "", 20)
        SC_END_PARENT
    SC_END_PARENT
    
    this->listenMessage(SCID::Msg::kMsgViewEnter, [this](SCMessage::Ptr ptrMsg)
                        {
                            this->schedule(SCF(onTimer), 1);
							return true;
                        });
    
    this->onTimer(0);
}

void TestLoadingController::onTimer(float)
{
    if(--_nCounter<0)
    {
        this->finish();
    }
    else
    {
        (*_ptrWatchStr) = SCString(0,"Time Left: %d seconds",_nCounter);
    }
}


///--------------- TestLoadingTraget0Controller
void TestLoadingTraget0Controller::onCreate(SpeedCC::SCDictionary parameters)
{
    parameters.setValue("title", "Test Target0 Loading");
    TestCaseController::onCreate(parameters);
    
    this->setupUI();
}

void TestLoadingTraget0Controller::setupUI()
{
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_INSERT_BUTTON_LABEL(nullptr, "dock=center; text-color=black;", "Test Back", "", 20, SCBehaviorViewGoto::create<TestLoadingTraget1Controller>())
    SC_END_PARENT
}

///--------------- TestLoadingTraget1Controller
void TestLoadingTraget1Controller::onCreate(SpeedCC::SCDictionary parameters)
{
    parameters.setValue("title", "Test Target1 Loading");
    TestCaseController::onCreate(parameters);
}






