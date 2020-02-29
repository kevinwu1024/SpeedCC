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

#include "TestLanguageController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestLanguageController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test Language");
    TestCaseController::onCreate(parameters);
    
    _ptrString1 = SCWatchString::create();
    _ptrString2 = SCWatchString::create();
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr,nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr,"dock=center;",false,40,0)
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "Chinese", "", 20, SCF(onButtonChinese))
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black;", "English", "", 20, SCF(onButtonEnglish))
            SC_INSERT_LABEL(nullptr, "text-color=black;", _ptrString1, "", 30)
            SC_INSERT_LABEL(nullptr, "text-color=black;", _ptrString2, "", 30)
        SC_END_PARENT
    SC_END_PARENT
    
    this->onButtonEnglish();
}

void TestLanguageController::onButtonChinese()
{
    SCLanguage::getInstance()->setCurrentLanguage(SCLanguage::ELanguageType::kChinese);
    this->updateText();
}

void TestLanguageController::onButtonEnglish()
{
    SCLanguage::getInstance()->setCurrentLanguage(SCLanguage::ELanguageType::kEnglish);
    this->updateText();
}

void TestLanguageController::updateText()
{
    auto strVal1 = SCLanguage::getInstance()->getString("key1");
    auto strVal2 = SCLanguage::getInstance()->getString("key2");
    
    (*_ptrString1) = "key1: " + strVal1;
    (*_ptrString2) = "key2: " + strVal2;
}
