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

#include "TestLabelBindingController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestLabelBindingController::onCreate(SCDictionary parameters)
{
    SCViewController::onCreate(parameters);
    
    _ptrWatchInt = SCWatchInt::create();
    _ptrWatchStr = SCWatchString::create();
    *_ptrWatchStr = "test string";
    
    SCBinderUILabel::Ptr binderStrPtr = SCBinderUILabel::create();
    binderStrPtr->setWatch(_ptrWatchStr);

    SC_BEGIN_PARENT_ROOT(nullptr, nullptr,SCWinSize())

        // title
        SC_INSERT_LABEL_BMFONT(nullptr,"x=0.5; y=0.95;","Label Binding","blue_font.fnt")
    
        // number binding
        SC_INSERT_LABEL(nullptr,"x=0.4; y=0.75;",_ptrWatchInt,"",30)
        SC_INSERT_BUTTON_LABEL(nullptr,"x=0.6; y=0.75; text-color=red;","+","",40,SCF(onButtonAdd))
        SC_INSERT_BUTTON_LABEL(nullptr,"x=0.7; y=0.75; text-color=red;","-","",40,SCF(onButtonSub))
    
        // string binding
        SC_INSERT_LABEL(nullptr,"x=0.4; y=0.5; text-color=yellow;",binderStrPtr,"",30)
        SC_INSERT_BUTTON_LABEL(nullptr,"x=0.65; y=0.5; text-color=red;","click","",25,SCF(onButtonRandomText))
    
        // back
        SC_INSERT_BUTTON_LABEL(nullptr,"x=0.15; y=0.95; text-color=red;","back","",25,SCF(onButtonBack))
    SC_END_PARENT
    
}

void TestLabelBindingController::onButtonAdd()
{
    ++(*_ptrWatchInt);
}

void TestLabelBindingController::onButtonSub()
{
    --(*_ptrWatchInt);
}

void TestLabelBindingController::onButtonRandomText()
{
    (*_ptrWatchStr).format("%d",rand());
}

void TestLabelBindingController::onButtonBack()
{
    SCViewNav()->back();
}

