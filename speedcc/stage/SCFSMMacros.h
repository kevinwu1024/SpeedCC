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

#ifndef __SPEEDCC__SCFLOWMACROS_H__
#define __SPEEDCC__SCFLOWMACROS_H__

#include "SCFSMRunner.h"

#define SC_BEGIN_FSM(_runner_,_state_comp_) \
do{\
    _state_comp_* pSCMacroFSMProperty = nullptr;\
    auto ptrSCMacroFSMBuilder = SpeedCC::SCFSMBuilder::create(); \
    auto ptrSCRunner = ptrSCMacroFSMBuilder->begin<_state_comp_>((SCID::State::kStateInvalid)); \
    (*_runner_) = ptrSCRunner; \
    pSCMacroFSMProperty = nullptr;

#define SC_BEGIN_FSM_LITE(_runner_) \
do{\
    auto ptrSCMacroFSMBuilder = SpeedCC::SCFSMBuilder::create(); \
    auto ptrSCRunner = ptrSCMacroFSMBuilder->beginSingle(); \
    (*_runner_) = ptrSCRunner; \


#define AT_STATE(_state_id_) \
do{\
    pSCMacroFSMProperty = nullptr; \
    ptrSCMacroFSMBuilder->beginState((_state_id_));


#define ENDAT_STATE \
    ptrSCMacroFSMBuilder->endState();\
}while(0);


#define SC_END_FSM \
    ptrSCMacroFSMBuilder->end();\
}while(0);


#define ON_ENTER_STATE(_state_id_) \
    ptrSCMacroFSMBuilder->insertEnterBehavior((_state_id_));


#define ON_EXIT_STATE(_state_id_) \
    ptrSCMacroFSMBuilder->insertExitBehavior((_state_id_));

#define ON_MSG_NEXT_STATE(_msg_,_state_id_) \
do{\
    auto bvrPtr = SpeedCC::SCBehaviorSwitchFSMStateT<std::remove_pointer<decltype(pSCMacroFSMProperty)>::type>::create((_state_id_));\
    ON_MSG_BEHAVIOR(_msg_,bvrPtr)\
}while(0);

#define ON_MSG_BEHAVIOR(_msg_,_behavior_) \
    ptrSCMacroFSMBuilder->insertBehaviorWithMsg((_msg_),(_behavior_));

#define ON_CMD_BEHAVIOR(_cmd_,_behavior_) \
    ptrSCMacroFSMBuilder->insertBehaviorWithCmd((_cmd_),(_behavior_));

#define ON_MSG_ENTITY_ACTIVE(_msg_,_entity_id_,_active_) \
do{\
    auto ptrBvr = SpeedCC::SCBehaviorEntityActive::create((_entity_id_),(_active_)); \
    ON_MSG_BEHAVIOR((_msg_),ptrBvr)\
}while(0);

#define ON_MSG_STRATEGY_ACTIVE(_msg_,_strategy_id_,_active_) \
do{\
    auto ptrBvr = SpeedCC::SCBehaviorStrategyActive::create((_strategy_id_),(_active_)); \
    ON_MSG_BEHAVIOR((_msg_),ptrBvr)\
}while(0);

#define ON_MSG_SCENE(_msg_,_scene_class_,_switch_type_,_trans_class_) \
do{\
    auto ptrBvr = SpeedCC::SCBehaviorSceneSwitch::create<_scene_class_,_trans_class_>((_switch_type_));\
    ON_MSG_BEHAVIOR((_msg_),ptrBvr)\
}while(0);

#define ON_CMD_SCENE(_cmd_,_scene_class_,_switch_type_,_trans_class_) \
do{\
    auto ptrBvr = SpeedCC::SCBehaviorSceneSwitch::create<_scene_class_,_trans_class_>((_switch_type_));\
    ON_CMD_BEHAVIOR((_cmd_),ptrBvr)\
}while(0);

#define ON_MSG(_msg_) \
    ON_MSG_BEHAVIOR((_msg_),nullptr)


#endif // __SPEEDCC__SCFLOWMACROS_H__
