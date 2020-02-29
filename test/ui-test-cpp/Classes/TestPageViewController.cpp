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

#include "TestPageViewController.h"

USING_NS_CC;

using namespace SpeedCC;

///------------ TestLoadingController
void TestPageViewController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test PageView");
    
    TestCaseController::onCreate(parameters);
    
    this->setupUI();
}
    
void TestPageViewController::setupUI()
{
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
    
        SC_BEGIN_PARENT_PAGEVIEW(nullptr,"dock=center;",true,Size(SCWinSize().width*2/3,SCWinSize().height/2),0,nullptr)
            SC_BEGIN_PARENT_PAGE(nullptr, SCWinSize())
                SC_INSERT_SPRITE(nullptr, "dock=center;", "HelloWorld.png")
            SC_END_PARENT

            SC_BEGIN_PARENT_PAGE(nullptr, SCWinSize())
                SC_INSERT_SPRITE(nullptr, "dock=center;", "HelloWorld.png")
            SC_END_PARENT

        SC_END_PARENT
    
    SC_END_PARENT
}
