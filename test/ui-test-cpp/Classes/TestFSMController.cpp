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

#include "TestFSMController.h"

USING_NS_CC;

using namespace SpeedCC;

enum ETestStageID
{
    kTestUserID = SCID::kUserID,
    
    kTestStateID1,
    kTestStateID2,
    kTestStateID3,
    kTestStateID4,
    
    kTestMsgIDLog,
    kTestMsgIDNextState,
};

#define kTestCmdLog "cmd_log"

void TestFSMController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test FSM");
    SCViewController::onCreate(parameters);
    
    this->setupUI();
    this->setupStage();
}
    
void TestFSMController::setupUI()
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
            SC_INSERT_LABEL_BMFONT(nullptr,"dock=top|mid-x; y-by=-100;","Test FSM","blue_font.fnt")

            SC_INSERT_BUTTON_SWITCH(nullptr, "x=0.5; y=0.6;", SCUIArg::MenuItemPurifier("Stop",22), SCUIArg::MenuItemPurifier("Start",22), ptrWatchBool, nullptr)
    
            SC_INSERT_BUTTON_LABEL(nullptr, "x=0.5; y=0.4;", "Message Log", "", 20, ptrBvrMsgLog)
            SC_INSERT_BUTTON_LABEL(nullptr, "x=0.5; y=0.3;", "Command Log", "", 20, ptrBvrCmdLog)

            // back button
            SC_INSERT_BUTTON_LABEL(nullptr, "text-color=black; dock=left|top; x-by=3; y-by=-3;", "Back", "", 22, SCBehaviorViewBack::create())
        SC_END_PARENT
    SC_END_PARENT
}


void TestFSMController::onStateChanged(int nOldState, int nNewState)
{
    auto strOldName = this->getStateName(nOldState);
    auto strNewName = this->getStateName(nNewState);
    
    SCLog("State From [%s] Changed To [%s]",strOldName.c_str(),strNewName.c_str());
}

void TestFSMController::setupStage()
{
	_ptrStage = SCStage::create();

    _ptrEntity = SCEntity::create(_ptrStage.getRawPointer(),1);
    TestStateComponent testComponent;
    testComponent.nCurrentState = kTestStateID1; // begin state
    testComponent.stateChangedFunc = SC_MAKE_FUNC(onStateChanged, this);
    _ptrEntity->addComponent(testComponent);
    
    auto ptrBvrLog = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrMsgLog, this));
    auto ptrBvrEnter = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrEnterState, this));
    auto ptrBvrExit = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrExitState, this));
    
    SC_BEGIN_FSM(&_ptrFSMRunner, TestStateComponent)
        AT_STATE(kTestStateID2)
            ON_ENTER_STATE(ptrBvrEnter)
            ON_MSG_NEXT_STATE(kTestMsgIDNextState, kTestStateID3)
        ENDAT_STATE

        AT_STATE(kTestStateID3)
            ON_ENTER_STATE(ptrBvrEnter)
            ON_EXIT_STATE(ptrBvrExit)
            ON_MSG_NEXT_STATE(kTestMsgIDNextState, kTestStateID4)
    
            ON_MSG_BEHAVIOR(kTestMsgIDLog,ptrBvrLog)
            ON_CMD_BEHAVIOR(kTestCmdLog, ptrBvrLog)
        ENDAT_STATE
    
        AT_STATE(kTestStateID4)
            ON_ENTER_STATE(ptrBvrEnter)
            ON_EXIT_STATE(ptrBvrExit)
            ON_MSG_NEXT_STATE(kTestMsgIDNextState, kTestStateID1)
    
            ON_MSG_BEHAVIOR(kTestMsgIDLog,ptrBvrLog)
            ON_CMD_BEHAVIOR(kTestCmdLog, ptrBvrLog)
        ENDAT_STATE
    
		AT_STATE(kTestStateID1)
			ON_ENTER_STATE(ptrBvrEnter)
			ON_EXIT_STATE(ptrBvrExit)
			ON_MSG_BEHAVIOR(kTestMsgIDLog, ptrBvrLog)
			ON_CMD_BEHAVIOR(kTestCmdLog, ptrBvrLog)
			ON_MSG_NEXT_STATE(kTestMsgIDNextState, kTestStateID2)
		ENDAT_STATE
        
    SC_END_FSM
}

void TestFSMController::onBvrEnterState(const SCDictionary& par)
{
    auto ptrEntity = par.getValue(SC_KEY_ENTITY).getObject<SCEntity::Ptr>();
    auto ptrProperty = ptrEntity->getComponent<TestStateComponent>();
    
    SCLog("Enter State Called. ID: %s",this->getStateName(ptrProperty->nCurrentState).c_str());
}

void TestFSMController::onBvrExitState(const SCDictionary& par)
{
    auto ptrEntity = par.getValue(SC_KEY_ENTITY).getObject<SCEntity::Ptr>();
    auto ptrProperty = ptrEntity->getComponent<TestStateComponent>();
    
    SCLog("Exit State Called. ID: %s",this->getStateName(ptrProperty->nCurrentState).c_str());
}

void TestFSMController::onBvrMsgLog(const SCDictionary& par)
{
    auto ptrEntity = par.getValue(SC_KEY_ENTITY).getObject<SCEntity::Ptr>();
    auto ptrMsg = par.getValue(SC_KEY_MESSAGE).getObject<SCMessage::Ptr>();
    
    SCString strName;
    
    if(ptrMsg->nMsgID==kTestMsgIDLog)
    {
        strName = "Message";
    }
    else if(ptrMsg->nMsgID==SCID::Msg::kMsgCommand)
    {
        strName = "Command";
    }
    
    auto ptrProperty = ptrEntity->getComponent<TestStateComponent>();
    SCLog("Behavior Log From [%s]. Current State ID: %s",strName.c_str(),this->getStateName(ptrProperty->nCurrentState).c_str());
}

void TestFSMController::onSchedule(float fDelta)
{
    if(*(_ptrTrigger->getWatch()))
    {
        SCMsgDisp()->postMessage(kTestMsgIDNextState);
    }
}

bool TestFSMController::onSCMessageProcess(SCMessage::Ptr ptrMsg)
{
    _ptrFSMRunner->execute(_ptrEntity, ptrMsg);
    return SCViewController::onSCMessageProcess(ptrMsg);
}

SCString TestFSMController::getStateName(const int nID)
{
    switch(nID)
    {
        case kTestStateID1: return "kTestStateID1";
        case kTestStateID2: return "kTestStateID2";
        case kTestStateID3: return "kTestStateID3";
        case kTestStateID4: return "kTestStateID4";
    }
    
    return "Unknown State ID";
}


