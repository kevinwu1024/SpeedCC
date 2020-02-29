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

#ifndef __SPEEDCC__SCSTAGE_H__
#define __SPEEDCC__SCSTAGE_H__

#include "SCPlayObject.h"
#include "SCMessage.h"
#include "SCMessageDispatch.h"
#include "SCEntity.h"
#include "SCStrategy.h"

NAMESPACE_SPEEDCC_BEGIN

class SCStage
:public SCObject
,public SCMessageListener
{
public:
	enum EPriority
	{
		kPriorityHighest = 0,
		kPriorityDefault = 128,
		kPriorityLowest = 255,
	};

public:
    SC_AVOID_CLASS_COPY(SCStage)
    SC_DEFINE_CLASS_PTR(SCStage)
        
    SC_DEFINE_CREATE_FUNC_0(SCStage)
    
    virtual ~SCStage();
    
    virtual bool onSCMessageProcess(SCMessage::Ptr ptrMsg) override;
    
	SCEntity::Ptr newEntity(int nID = SCID::Ent::kEntAuto);
    bool addEntity(SCEntity::Ptr ptrEntity);
    bool removeEntity(const int nID);
    void removeAllEntities();
    bool hasEntity(const int nID) const;
    SCEntity::Ptr getEntityByID(const int nID);
    int getEntityCount() const;
    
    template<typename T>
    std::list<SCEntity::Ptr> getEntityByComponent()
    {
        std::list<SCEntity::Ptr> entityList;
        
        for(auto& it : _workingEntityList)
        {
            SC_CONTINUE_IF(!it->hasComponent<T>());
			entityList.push_back(it);
        }
        
        return entityList;
    }

	template<typename T>
	int getEntityCountByComponent() const
	{
		int nRet = 0;

		for (auto& it : _workingEntityList)
		{
			SC_CONTINUE_IF(!it->hasComponent<T>());
			++nRet;
		}

		return nRet;
	}
    
    void foreachEntity(const std::function<bool(const SCEntity::Ptr& ptrEntity)>& func) const;
    void foreachEntity(const std::function<bool(SCEntity::Ptr& ptrEntity)>& func);
    
    void addStrategy(SCStrategy::Ptr ptrStrategy,const unsigned char nPriority = kPriorityDefault);
	void removeStrategy(const int nID);
    SCStrategy::Ptr getStrategy(const int nID) const;
    
    inline bool getActive() const {return _bActive;}
    void setActive(const bool bActive);

private:
	struct SStrategyInfo
	{
		unsigned char                   byPriority; // 0: highest; 255: lowest
		SCStrategy::Ptr					ptrStrategy;

		SStrategyInfo()
		:byPriority(kPriorityDefault)
		{}

		inline bool operator<(const SStrategyInfo& info) const { return byPriority<info.byPriority; }
		inline bool operator>(const SStrategyInfo& info) const { return byPriority>info.byPriority; }
	};

	struct SMutabelStrategyInfo
	{
		bool                    bAdd;
		SStrategyInfo           stgyInfo;
		int						nID;

		bool operator==(const SMutabelStrategyInfo& info) const
		{
			return (nID == info.nID);
		}

		SMutabelStrategyInfo()
		:bAdd(true)
		,nID(0)
		{}
	};
    
private:
    bool isEntityInRemovedList(const int nID) const;
    void updateVariationEntity();
	void updateMutableStrategy();
	void recycleFreeEntity();
        
protected:
    SCStage();
        
private:
    bool                                    _bActive;
    bool                                    _bUpdating;
    
    std::list<int>                          _removeEntityList;
    std::list<SCEntity::Ptr>                _addEntityList;
	std::list<SMutabelStrategyInfo>         _mutableStrategyList;
	std::list<SStrategyInfo>                _strategyList;

	std::list<SCEntity::Ptr>                _workingEntityList; // working entity buffer
	std::list<SCEntity::Ptr>				_freeEntityList; // free entity pool
	std::list<SCEntity::Ptr>				_pendingFreeEntityList; // remove entity from working buffer to here
};

NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCSTAGE_H__
