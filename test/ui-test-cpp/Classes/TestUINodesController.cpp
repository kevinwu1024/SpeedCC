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

#include "TestUINodesController.h"

USING_NS_CC;

using namespace SpeedCC;

///------------ TestLoadingController
void TestUINodesController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test UI Nodes");
    TestCaseController::onCreate(parameters);

    _ptrCaseBvr->setCase(0, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseCommonNodes, this)));
    _ptrCaseBvr->setCase(1, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseRadioButton, this)));
    _ptrCaseBvr->setCase(2, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseEditBox, this)));
    _ptrCaseBvr->setCase(3, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseMask, this)));
    
    _ptrCaseBvr->execute();
}

void TestUINodesController::testCaseCommonNodes()
{
    (*_ptrWatchDescription) = "(Test Common Nodes)";
    _pContainerLayer->removeAllChildren();
    
    cocos2d::Sprite* pSprite = nullptr;
    cocos2d::Label* pLabel = nullptr;
    cocos2d::Node* pNodeSprite = nullptr;
    cocos2d::MenuItemSprite* pMenuItemSprite = nullptr;
    
    SC_BEGIN_PARENT_ROOT_EX(&_ptrBuilderCommandNode, nullptr, SCWinSize(), _pContainerLayer, this)
    
        SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", false, 10, nullptr)
            SC_BEGIN_PARENT_SPRITE(&pSprite, "dock=top|mid-x;", "HelloWorld.png")
                SC_INSERT_LABEL(100, "dock=center; text-color=red;", "Hello World", "Arial", 20)
            SC_END_PARENT

            SC_INSERT_SPRITE(&pNodeSprite, nullptr, "HelloWorld.png")
            SC_INSERT_BUTTON(&pMenuItemSprite, nullptr, "HelloWorld.png", nullptr)
        SC_END_PARENT
    
    SC_END_PARENT
    
    pLabel = dynamic_cast<Label*>(_ptrBuilderCommandNode->getNodeByID(100));
    
    SCASSERT(pSprite!=nullptr);
    SCASSERT(pLabel!=nullptr);
    SCASSERT(pNodeSprite!=nullptr);
    SCASSERT(pMenuItemSprite!=nullptr);
}

void TestUINodesController::testCaseRadioButton()
{
    (*_ptrWatchDescription) = "(Test Radio)";
    _pContainerLayer->removeAllChildren();
    
    _ptrRadioGroup1 = SCRadioGroup::create();
    _ptrRadioGroup2 = SCRadioGroup::create();
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", false, 20, nullptr)
            SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", true, 10, nullptr)
                SC_INSERT_LABEL(nullptr, "text-color=black;", "Group 1: ", "Arial", 18)
                SC_INSERT_BUTTON_RADIO(nullptr, "scale=2;", "CloseNormal.png", "CloseSelected.png", _ptrRadioGroup1,1,nullptr)
                SC_INSERT_BUTTON_RADIO(nullptr, "scale=2;", "CloseNormal.png", "CloseSelected.png", _ptrRadioGroup1,2,nullptr)
                SC_INSERT_BUTTON_RADIO(nullptr, "scale=2;", "CloseNormal.png", "CloseSelected.png", _ptrRadioGroup1,3,nullptr)
            SC_END_PARENT
    
            SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", true, 10, nullptr)
                SC_INSERT_LABEL(nullptr, "text-color=black;", "Group 2: ", "Arial", 18)
                SC_INSERT_BUTTON_RADIO(nullptr, "scale=2;", "CloseNormal.png", "CloseSelected.png", _ptrRadioGroup2,1,nullptr)
                SC_INSERT_BUTTON_RADIO(nullptr, "scale=2;", "CloseNormal.png", "CloseSelected.png", _ptrRadioGroup2,2,nullptr)
                SC_INSERT_BUTTON_RADIO(nullptr, "scale=2;", "CloseNormal.png", "CloseSelected.png", _ptrRadioGroup2,3,nullptr)
            SC_END_PARENT
    
        SC_END_PARENT
    SC_END_PARENT
    
    _ptrRadioGroup1->setRadioActive(1);
    _ptrRadioGroup1->setListenerFunc([this](SCRadioGroup::Ptr ptrGroup,int nNewRadioID,int nOldRadioID)
                                     {
                                         SCLog("Radio Group 1 Selected Radio ID %d",nNewRadioID);
                                     });
    
    _ptrRadioGroup2->setRadioActive(3);
    _ptrRadioGroup2->setListenerFunc([](SCRadioGroup::Ptr ptrGroup,int nNewRadioID,int nOldRadioID)
                                     {
                                         SCLog("Radio Group 2 Selected Radio ID %d",nNewRadioID);
                                     });
}

void TestUINodesController::testCaseLabel()
{
    (*_ptrWatchDescription) = "(Test Label)";
    _pContainerLayer->removeAllChildren();
}

void TestUINodesController::testCaseButton()
{
    (*_ptrWatchDescription) = "(Test Button)";
    _pContainerLayer->removeAllChildren();
}

void TestUINodesController::testCaseEditBox()
{
    (*_ptrWatchDescription) = "(Test EditBox)";
    _pContainerLayer->removeAllChildren();

    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", false, 20, nullptr)
            SC_INSERT_EDITBOX(nullptr,"dock=center;",Size(100,26),"progressbar_bk.png",this)
            //SC_INSERT_BUTTON_SWITCH(nullptr,"dock=center;","CloseNormal.png","CloseSelected.png",true,nullptr)
        SC_END_PARENT
    SC_END_PARENT
}

void TestUINodesController::testCaseMask()
{
    (*_ptrWatchDescription) = "(Test Mask)";
    _pContainerLayer->removeAllChildren();
    
    
    SC_BEGIN_PARENT_ROOT_EX(nullptr, nullptr, SCWinSize(), _pContainerLayer, this)
        SC_BEGIN_PARENT_ALIGNMENT(nullptr, "dock=center;", false, 20, nullptr)
    
            // hollow in retangle
            SC_BEGIN_PARENT_CROP(nullptr, "dock=center;", Size(200,40))
    
                SC_INSERT_LAYER_COLOR(nullptr, "dock=center;", Size(200, 40), Color4B::GREEN)
                SC_INSERT_LABEL(nullptr, "text-color=red; dock=mid-y;", "abcdefgh", "", 20)
            SC_END_PARENT
    
            // hollow in sprite shape
            SC_BEGIN_PARENT_CROP(nullptr, "dock=center;", Size(200,40))
    
                SC_INSERT_STENCIL(nullptr, "dock=center; scale=2;", "CloseNormal.png", false, 0.05)
            
                SC_INSERT_LAYER_COLOR(nullptr, "dock=center;", Size(200, 40), Color4B::GREEN)
                SC_INSERT_LABEL(nullptr, "text-color=red; dock=center;", "abcdefgh", "", 20)
            SC_END_PARENT
        SC_END_PARENT
    
    SC_END_PARENT
}

void TestUINodesController::editBoxReturn(ui::EditBox* editBox)
{
    SCLog("editbox text: %s",editBox->getText());
}
