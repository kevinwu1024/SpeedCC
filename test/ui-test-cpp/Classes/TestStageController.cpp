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

#include "TestStageController.h"

USING_NS_CC;

using namespace SpeedCC;

enum ETestStageID
{
    kTestUserID = SCID::kUserID,
    
    kTestEntityID1,
    kTestEntityID2,
    
    kTestStrategyID1,
    kTestStrategyID2,
    
    kTestMsgIDLog,
    kTestMsgUpdateStrategy,
};

#define kTestCmdLog "cmd_log"

struct SComponent1 : SCComponent
{
    int nVal;
};

struct SComponent2 : SCComponent
{
    int nVal;
};

void TestStageController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test ECS");
    SCViewController::onCreate(parameters);
    
    this->setupUI();
    this->setupStage();
}
    
void TestStageController::setupUI()
{
    auto ptrBvrMsgLog = SCBehaviorDeliverMessage::create(false, kTestMsgIDLog);
    auto ptrBvrCmdLog = SCBehaviorDeliverMessage::create(false, kTestCmdLog);
    
    auto ptrBvrStart = SCBehaviorCallFunc::create([this]()
                                                  {
                                                      this->schedule(SCF(onSchedule), 1.5f);
                                                      SCLog("Timer Started.");
                                                  });
    
    auto ptrBvrStop = SCBehaviorCallFunc::create([this]()
                                                 {
                                                     this->unschedule(SCF(onSchedule));
                                                     SCLog("Timer Stopped.");
                                                 });
    
    auto ptrWatchBool = SCWatchBool::create();
    _ptrTrigger = SCTriggerBool::create(ptrWatchBool);
    _ptrTrigger->addCondition(SCTrigger::EComparsion::kEqual, true, ptrBvrStart);
    _ptrTrigger->addCondition(SCTrigger::EComparsion::kEqual, false, ptrBvrStop);
    
    
    SC_BEGIN_PARENT_ROOT(nullptr, nullptr,SCWinSize())
        SC_BEGIN_PARENT_LAYER_COLOR(nullptr,"dock=center;",SCWinSize(),Color4B::GRAY)

            // title
            SC_INSERT_LABEL_BMFONT(nullptr,"dock=top|mid-x; y-by=-100;","Test ECS","blue_font.fnt")

            SC_INSERT_BUTTON_SWITCH(nullptr, "x=0.5; y=0.6;", SCUIArg::MenuItemPurifier("Stop",22), SCUIArg::MenuItemPurifier("Start",22), ptrWatchBool, nullptr)

            // back button
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black; dock=left|top; x-by=3; y-by=-3;", "Back", "", 22, SCBehaviorViewBack::create())
        SC_END_PARENT
    SC_END_PARENT
}

void TestStageController::setupStage()
{
	_ptrStage = SCStage::create();
	auto pStage = _ptrStage.getRawPointer();
    auto ptrEntity1 = SCEntity::create(pStage,kTestEntityID1);
    
    SComponent1 property1;
    property1.nVal = 1;
    ptrEntity1->addComponent(property1);
	_ptrStage->addEntity(ptrEntity1);
    
    auto ptrEntity2 = SCEntity::create(pStage,kTestEntityID2);
    
    SComponent2 property2;
    property2.nVal = 2;
    ptrEntity2->addComponent(property2);
	_ptrStage->addEntity(ptrEntity2);
    
    auto ptrStrategy1 = SCStrategyFunc::create(pStage,SC_MAKE_FUNC(onStrategyTest1, this), kTestStrategyID1);
	_ptrStage->addStrategy(ptrStrategy1);
    
    auto ptrStrategy2 = SCStrategyFunc::create(pStage,SC_MAKE_FUNC(onStrategyTest2, this), kTestStrategyID2);
	_ptrStage->addStrategy(ptrStrategy2);
}

void TestStageController::onStrategyTest1(SCStage* pStage,SCMessage::Ptr ptrMsg)
{
    if(ptrMsg->nMsgID == kTestMsgUpdateStrategy)
    {
        auto ptrEntity1 = pStage->getEntityByID(kTestEntityID1);
        auto ptrEntity2 = pStage->getEntityByID(kTestEntityID2);
        
        auto ptrComponent1 = ptrEntity1->getComponent<SComponent1>();
        auto ptrComponent2 = ptrEntity2->getComponent<SComponent2>();
        
        ptrComponent1->nVal += 1;
        ptrComponent2->nVal += 2;
    }
}

void TestStageController::onStrategyTest2(SCStage* pStage,SCMessage::Ptr ptrMsg)
{
    if(ptrMsg->nMsgID == kTestMsgUpdateStrategy)
    {
        auto ptrEntity1 = pStage->getEntityByID(kTestEntityID1);
        auto ptrEntity2 = pStage->getEntityByID(kTestEntityID2);
        
        auto ptrComponent1 = ptrEntity1->getComponent<SComponent1>();
        auto ptrComponent2 = ptrEntity2->getComponent<SComponent2>();
        
        SCLog("entity1.component1 = %d",ptrComponent1->nVal);
        SCLog("entity1.component2 = %d",ptrComponent2->nVal);
    }
}

void TestStageController::onSchedule(float fDelta)
{
    if(*(_ptrTrigger->getWatch()))
    {
        SCMsgDisp()->postMessage(kTestMsgUpdateStrategy);
    }
}

SCString TestStageController::getStrategyName(const int nID)
{
    switch(nID)
    {
        case kTestStrategyID1: return "kTestStrategyID1";
        case kTestStrategyID2: return "kTestStrategyID2";
    }
    
    return "Unknown Strategy ID";
}

