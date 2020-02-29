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

#include "SCBehaviorStage.h"
#include "SCStage.h"
#include "SCStageMacros.h"

NAMESPACE_SPEEDCC_BEGIN

///--------------- SCBehaviorEntityActive
void SCBehaviorEntityActive::execute(const SCDictionary& par)
{
    SC_RETURN_V_IF(!this->getActive());
    
    auto actorValue = par.getValue(SC_KEY_ENTITY);
    SCASSERT(actorValue.isValidObject<SCEntity::Ptr>());
    SC_RETURN_V_IF(!actorValue.isValidObject<SCEntity::Ptr>());
    auto ptrEntity = actorValue.getObject<SCEntity::Ptr>();
    
    std::list<int>* pActorIDList = (_pEntIDList == nullptr ? &_entIDList : _pEntIDList);
    auto pStage = ptrEntity->getStage();
    
    for (const auto nActorID : *pActorIDList)
    {
        auto ptrEntity = pStage->getEntityByID(nActorID);
        SCASSERT(ptrEntity != nullptr);
        if(ptrEntity != nullptr)
        {
            ptrEntity->setActive(_bActive);
        }
    }
}


///--------------- SCBehaviorStrategyActive
void SCBehaviorStrategyActive::execute(const SCDictionary& par)
{
    SC_RETURN_V_IF(!this->getActive());
    
    auto stageValue = par.getValue(SC_KEY_STAGE);
    SCASSERT(stageValue.isValidObject<SCStage::Ptr>());
    SC_RETURN_V_IF(!stageValue.isValidObject<SCStage::Ptr>());
    auto ptrStage = stageValue.getObject<SCStage::Ptr>();
    
    std::list<int>* pStrategyIDList = (_pStrategyIDList == nullptr ? &_strategyIDList : _pStrategyIDList);
    
    for (const auto nStrategyID : *pStrategyIDList)
    {
        auto ptrStrategy = ptrStage->getStrategy(nStrategyID);
        SCASSERT(ptrStrategy != nullptr);
        if(ptrStrategy != nullptr)
        {
            ptrStrategy->setActive(_bActive);
        }
    }
}

///--------------- SCBehaviorDeliverMessage
SCBehaviorDeliverMessage::SCBehaviorDeliverMessage(const bool bSend,SCMessage::Ptr ptrMsg)
:_bSend(bSend)
{
    SCASSERT(ptrMsg!=nullptr);
    _ptrMsg = ptrMsg->clone();
}
    
SCBehaviorDeliverMessage::SCBehaviorDeliverMessage(const bool bSend,const int nMsgID)
:_bSend(bSend)
{
    _ptrMsg = SCMessage::create(nMsgID);
}
    
SCBehaviorDeliverMessage::SCBehaviorDeliverMessage(const bool bSend,const SCString& strCmd)
:_bSend(bSend)
{
    _ptrMsg = SCMessage::create(strCmd);
}
    
void SCBehaviorDeliverMessage::execute(const SCDictionary& par)
{
    SCASSERT(_ptrMsg!=nullptr);
        
    if(_bSend)
    {
        SCMsgDisp()->sendMessage(_ptrMsg);
    }
    else
    {
        SCMsgDisp()->postMessage(_ptrMsg);
    }
}

NAMESPACE_SPEEDCC_END
