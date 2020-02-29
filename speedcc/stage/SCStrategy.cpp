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

#include "SCStrategy.h"
#include "SCEntity.h"
#include "SCStage.h"
#include "SCStageMacros.h"

NAMESPACE_SPEEDCC_BEGIN
    
#define BASE_AUTO_NUMBER  -100

int SCStrategy::_nAutoIDCounter = BASE_AUTO_NUMBER;
    
SCStrategy::SCStrategy(SCStage* pStage)
:_pStage(pStage)
{
	if (--_nAutoIDCounter == std::numeric_limits<int>::min())
	{
		_nAutoIDCounter = BASE_AUTO_NUMBER;
	}

	auto nID = _nAutoIDCounter;

	this->setID(nID);
}

SCStrategy::SCStrategy(SCStage* pStage, int nID)
:SCPlayObject(nID)
, _pStage(pStage)
{
	if (nID == SCID::Stgy::kStgyAuto)
	{
		if (--_nAutoIDCounter == std::numeric_limits<int>::min())
		{
			_nAutoIDCounter = BASE_AUTO_NUMBER;
		}

		nID = _nAutoIDCounter;
	}

	this->setID(nID);
}

void SCStrategy::onActiveChanged(const bool bNewActive)
{
	auto ptrMsg = SCMessage::create();

	ptrMsg->nMsgID = SCID::Msg::kMsgEntityActiveChanged;
	ptrMsg->parameters[SC_KEY_ID] = this->getID();
	ptrMsg->parameters[SC_KEY_RESULT] = bNewActive;

	SCMsgDisp()->postMessage(ptrMsg);
}

///------------------ SCStrategyFunc
    
bool SCStrategyFunc::onUpdate(SCStage* pStage,SCMessage::Ptr ptrMsg)
{
    if(_func!=nullptr)
    {
        _func(pStage,ptrMsg);
    }
        
    return SCStrategy::onUpdate(pStage,ptrMsg);
}

///------------------ SCStrategyFSM

bool SCStrategyFSM::onUpdate(SCStage* pStage,SCMessage::Ptr ptrMsg)
{
    auto ptrEntity = pStage->getEntityByID(_nActorID);
    SCASSERT(ptrEntity != nullptr);
    
    if(ptrEntity != nullptr)
    {
        _ptrFSMRunner->execute(ptrEntity,ptrMsg);
    }
    
    return SCStrategy::onUpdate(pStage,ptrMsg);
}

NAMESPACE_SPEEDCC_END
