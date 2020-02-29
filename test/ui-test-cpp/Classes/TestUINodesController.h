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

#ifndef __TESTUIMISC_SCENE_H__
#define __TESTUIMISC_SCENE_H__
#include "cocos2d.h"
#include "SpeedCC.h"
#include "TestCaseController.h"

using namespace SpeedCC;

///--------- TestUIMiscController
class TestUINodesController :
public TestCaseController,
public cocos2d::ui::EditBoxDelegate
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters) override;
    
    void testCaseCommonNodes();
    void testCaseLabel();
    void testCaseButton();
    void testCaseRadioButton();
    void testCaseMask();
    
    void testCaseEditBox();
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox) override;
    
private:
    SCRadioGroup::Ptr       _ptrRadioGroup1;
    SCRadioGroup::Ptr       _ptrRadioGroup2;
    SCViewBuilder::Ptr      _ptrBuilderCommandNode;
};


#endif // __TESTUIMISC_SCENE_H__
