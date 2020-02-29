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

#include "SCEntity.h"
#include "SCStage.h"
#include "SCStageMacros.h"

NAMESPACE_SPEEDCC_BEGIN

#define BASE_AUTO_NUMBER  -100

int SCEntity::_nAutoIDCounter = BASE_AUTO_NUMBER;

SCEntity::SCEntity(SCStage* pStage)
:_pStage(pStage)
{
    SCASSERT(_pStage != nullptr);
	this->autoAssignID();
}

SCEntity::SCEntity(SCStage* pStage,int nID)
:_pStage(pStage)
{
    SCASSERT(_pStage != nullptr);
    if(nID == SCID::Ent::kEntAuto)
    {
		this->autoAssignID();
    }
	else
	{
		this->setID(nID);
	}
}

int SCEntity::autoAssignID()
{
	if (--_nAutoIDCounter == std::numeric_limits<int>::min())
	{
		_nAutoIDCounter = BASE_AUTO_NUMBER;
	}

	this->setID(_nAutoIDCounter);

	return _nAutoIDCounter;
}

void SCEntity::removeFromStage()
{
    SCASSERT(_pStage != nullptr);
    _pStage->removeEntity(this->getID());
}

void SCEntity::removeAllComponents()
{
	for (auto it : _id2PropertyMap)
	{
		auto ptrComp = it.second.getObject<SCComponent::Ptr>();
		if (ptrComp != nullptr)
		{
			ptrComp->setEntity(nullptr);
		}
	}

	_id2PropertyMap.clear();
}

void SCEntity::onActiveChanged(const bool bNewActive)
{
	auto ptrMsg = SCMessage::create();

	ptrMsg->nMsgID = SCID::Msg::kMsgEntityActiveChanged;
	ptrMsg->parameters[SC_KEY_ID] = this->getID();
	ptrMsg->parameters[SC_KEY_RESULT] = bNewActive;

	SCMsgDisp()->postMessage(ptrMsg);
}

NAMESPACE_SPEEDCC_END


