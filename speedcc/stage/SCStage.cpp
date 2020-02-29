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

#include "SCStage.h"
#include "SCMessageDispatch.h"
#include "../system/SCSystem.h"

NAMESPACE_SPEEDCC_BEGIN

SCStage::SCStage()
:_bUpdating(false)
,_bActive(true)
{
    SCMessageDispatch::getInstance()->addListener(this);
}
    
SCStage::~SCStage()
{
    SCMessageDispatch::getInstance()->removeListener(this);
}


bool SCStage::addEntity(SCEntity::Ptr ptrEntity)
{
    SCASSERT(ptrEntity!=nullptr);
    SC_RETURN_IF(ptrEntity==nullptr,false);
    const int nID = ptrEntity->getID();
    
    if(this->isEntityInRemovedList(nID))
    {
        _removeEntityList.remove_if([nID](const int id)
                                   {
                                       return (nID==id);
                                   });
        
        _workingEntityList.remove_if([nID](SCEntity::Ptr ptrEntity)
                             {
                                 return (ptrEntity->getID()==nID);
                             });
    }
    else if (this->hasEntity(nID))
    {
		SCASSERT("entity id [%d] already exist.", nID);
		return false;
    }
    
    if(_bUpdating)
    {
        _addEntityList.push_back(ptrEntity);
    }
    else
    {
        _workingEntityList.push_back(ptrEntity);
    }
    
    return true;
}

bool SCStage::removeEntity(const int nID)
{
    auto ptrEntity = this->getEntityByID(nID);
    SC_RETURN_IF(ptrEntity == nullptr,false);
    
    if(_bUpdating)
    {
        ptrEntity->setActive(false);
        _removeEntityList.push_back(nID);
    }
    else
    {
        _workingEntityList.remove_if([nID,this](SCEntity::Ptr ptrEntity)
                             {
								if (ptrEntity->getID() == nID)
								{
									_pendingFreeEntityList.push_back(ptrEntity);
									return true;
								}

								return false;
                             });
    }
    
    return true;
}

void SCStage::removeAllEntities()
{
	if (_bUpdating)
	{
		for (auto ptrEntity : _workingEntityList)
		{
			_removeEntityList.push_back(ptrEntity->getID());
		}
	}
	else
	{
		for (auto ptrEntity : _workingEntityList)
		{
			_pendingFreeEntityList.push_back(ptrEntity);
		}
		_workingEntityList.clear();
	}
}

bool SCStage::hasEntity(const int nID) const
{
    SC_RETURN_IF(this->isEntityInRemovedList(nID),false);
    
    for(auto it : _workingEntityList)
    {
        SC_RETURN_IF(it->getID() == nID, true);
    }
    
    return false;
}

SCEntity::Ptr SCStage::getEntityByID(const int nID)
{
    SC_RETURN_IF(this->isEntityInRemovedList(nID),nullptr);
    
    for(auto it : _workingEntityList)
    {
        SC_RETURN_IF(it->getID()==nID, it);
    }
    
    return nullptr;
}

bool SCStage::isEntityInRemovedList(const int nID) const
{
    SC_RETURN_IF(_removeEntityList.empty(), false);
    
    for(const auto& it : _removeEntityList)
    {
        SC_RETURN_IF(it == nID, true);
    }
    
    return false;
}

void SCStage::foreachEntity(const std::function<bool(const SCEntity::Ptr& ptrEntity)>& func) const
{
    for(const auto& it : _workingEntityList)
    {
        SC_RETURN_V_IF(!func(it));
    }
}

void SCStage::foreachEntity(const std::function<bool(SCEntity::Ptr& ptrEntity)>& func)
{
    for(auto& it : _workingEntityList)
    {
        SC_RETURN_V_IF(!func(it));
    }
}

int SCStage::getEntityCount() const
{
    return (int)_workingEntityList.size();
}
    
void SCStage::addStrategy(SCStrategy::Ptr ptrStrategy, const unsigned char nPriority)
{
	SMutabelStrategyInfo info;

	info.bAdd = true;
	info.stgyInfo.ptrStrategy = ptrStrategy;
	info.stgyInfo.byPriority = nPriority;
	info.nID = ptrStrategy->getID();

	auto it = std::find(_mutableStrategyList.begin(), _mutableStrategyList.end(), info);

	if (it != _mutableStrategyList.end())
	{
		_mutableStrategyList.erase(it);
	}

	_mutableStrategyList.push_back(info);

	// if not updating, then updating mutable strategy immediately
	if (!_bUpdating)
	{
		this->updateMutableStrategy();
	}
}

void SCStage::removeStrategy(const int nID)
{
	SMutabelStrategyInfo info;

	info.bAdd = false;
	info.nID = nID;

	auto it = std::find(_mutableStrategyList.begin(), _mutableStrategyList.end(), info);

	if (it != _mutableStrategyList.end())
	{
		_mutableStrategyList.erase(it);
	}

	_mutableStrategyList.push_back(info);

	// if not updating, then updating mutable strategy immediately
	if (!_bUpdating)
	{
		this->updateMutableStrategy();
	}
}

void SCStage::updateMutableStrategy()
{
	SCASSERT(!_bUpdating);

	SC_RETURN_V_IF(_mutableStrategyList.empty());

	bool bAdded = false;
	std::for_each(_mutableStrategyList.begin(), _mutableStrategyList.end(),
		[this, &bAdded](const SMutabelStrategyInfo& info)-> void
	{
		SC_RETURN_V_IF(info.stgyInfo.ptrStrategy == nullptr);

		if (info.bAdd)
		{// add listener
			_strategyList.remove_if([&info](const SStrategyInfo& it) -> bool
			{
				return (it.ptrStrategy->getID() == info.nID);
			});

			SStrategyInfo listenerInfo = info.stgyInfo;
			_strategyList.push_back(listenerInfo);
			bAdded = true;
		}
		else
		{// remove listener
			_strategyList.remove_if([&info](const SStrategyInfo& it) -> bool
			{
				return (it.ptrStrategy->getID() == info.nID);
			});
		}
	});

	if (bAdded)
	{
		_strategyList.sort(std::greater<SStrategyInfo>());
	}

	_mutableStrategyList.clear();
}

SCStrategy::Ptr SCStage::getStrategy(const int nID) const
{
    for (auto strategeInfo : _strategyList)
    {
		auto ptrStratege = strategeInfo.ptrStrategy;
        SC_RETURN_IF(ptrStratege->getID() == nID, ptrStratege);
    }
    
    return nullptr;
}

void SCStage::updateVariationEntity()
{
    if(!_removeEntityList.empty())
    {
        for(auto it : _removeEntityList)
        {
            _workingEntityList.remove_if([it,this](const SCEntity::Ptr ptrEntity) -> bool
                                 {
									if (ptrEntity->getID() == it)
									{
										_pendingFreeEntityList.push_back(ptrEntity);
										return true;
									}

									return false;
                                 });
        }
		
        _removeEntityList.clear();
    }
    
    if(!_addEntityList.empty())
    {
        for(auto it : _addEntityList)
        {
            _workingEntityList.push_back(it);
        }
        
        _addEntityList.clear();
    }
}

void SCStage::recycleFreeEntity()
{
	SC_RETURN_V_IF(_pendingFreeEntityList.empty());
	
	_pendingFreeEntityList.remove_if([this](SCEntity::Ptr ptrEntity)
	{
		if (ptrEntity.getRefCount() == 2) // because reference [_pendingFreeEntityList] + [parameter] = 2
		{
			ptrEntity->removeAllComponents();
			ptrEntity->setID(SCID::Ent::kEntNull);
			ptrEntity->setActive(true);
			_freeEntityList.push_back(ptrEntity);

			return true;
		}

		return false;
	});
}

SCEntity::Ptr SCStage::newEntity(int nID)
{
	SCEntity::Ptr ptrRet;

	if (_freeEntityList.empty())
	{
		ptrRet = SCEntity::create(this, nID);
	}
	else
	{
		ptrRet = _freeEntityList.front();
		_freeEntityList.pop_front();

		if (nID == SCID::Ent::kEntAuto)
		{
			ptrRet->autoAssignID();
		}
		else
		{
			ptrRet->setID(nID);
		}
	}

	return ptrRet;
}

void SCStage::setActive(const bool bActive)
{
	_bActive = bActive;
}


bool SCStage::onSCMessageProcess(SCMessage::Ptr ptrMsg)
{
	SC_RETURN_IF(!_bActive, true);

	_bUpdating = true;

	for (auto strategeInfo : _strategyList)
	{
		auto ptrStratege = strategeInfo.ptrStrategy;
		SC_CONTINUE_IF(!ptrStratege->getActive());
		SC_BREAK_IF(!ptrStratege->onUpdate(this, ptrMsg));
		SC_BREAK_IF(!_bActive);
	}

	_bUpdating = false;

	this->updateVariationEntity();
	this->updateMutableStrategy();
	this->recycleFreeEntity();

	return true;
}


NAMESPACE_SPEEDCC_END


