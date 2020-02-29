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

#ifndef __SPEEDCC__SCENTITY_H__
#define __SPEEDCC__SCENTITY_H__

#include "SCPlayObject.h"
#include "SCMessage.h"

NAMESPACE_SPEEDCC_BEGIN

class SCEntity;

class SCComponent : public SCObject
{
	friend SCEntity;

public:
	SC_DEFINE_CLASS_PTR(SCComponent)

	SCComponent()
	:_bActive(true)
	,_pEntity(nullptr)
	{}

	inline bool getActive() const { return _bActive; }
	void setActive(const bool bActive) 
	{
		_bActive = bActive;
	}

	SCEntity* getEntity() const { return _pEntity; }

private:
	void setEntity(SCEntity* pEntity) 
	{
		_pEntity = pEntity;
	}

private:
	bool		_bActive;
	SCEntity*	_pEntity;
};

class SCStrategy;
class SCStage;
    
class SCEntity : public SCPlayObject
{
public:
    SC_AVOID_CLASS_COPY(SCEntity)
    SC_DEFINE_CLASS_PTR(SCEntity)
    
	SC_DEFINE_CREATE_FUNC_2(SCEntity, SCStage*, int)
	SC_DEFINE_CREATE_FUNC_1(SCEntity, SCStage*)

    template<typename T, typename = typename std::enable_if<std::is_base_of<SCComponent,T>::value, T>::type>
    void addComponent(const T& component)
    {
        SC_RETURN_V_IF(this->hasComponent<T>());
        
		SCASSERT(component.getEntity() == nullptr);

        SCObjPtrT<T> ptrCmd;
        ptrCmd.createInstance();
        *ptrCmd = component;
		ptrCmd->setEntity(this);
        
        _id2PropertyMap[std::type_index(typeid(T))] = SCValue(ptrCmd);
    }
    
    template<typename T1,typename T2,typename ...Ts>
    void addComponent(const T1& arg1,const T2& arg2,Ts... args)
    {
        this->addComponent<T1>(arg1);
        this->addComponent<T2,Ts...>(arg2,args...);
    }
    
    template<typename T, typename = typename std::enable_if<std::is_base_of<SCComponent,T>::value, T>::type>
    void addComponent()
    {
        SC_RETURN_V_IF(this->hasComponent<T>());
        
        SCObjPtrT<T> ptrCmd;
        ptrCmd.createInstance();
        *ptrCmd = T();
		ptrCmd->setEntity(this);
        
        _id2PropertyMap[std::type_index(typeid(T))] = SCValue(ptrCmd);
    }
    
    template<typename T1,typename T2,typename ...Ts>
    void addComponent()
    {
        this->addComponent<T1>();
        this->addComponent<T2,Ts...>();
    }
    
    template<typename T, typename = typename std::enable_if<std::is_base_of<SCComponent, T>::value, T>::type>
    SCObjPtrT<T> getComponent(const bool bForce = false)
    {
        auto it = _id2PropertyMap.find(std::type_index(typeid(T)));
        SC_RETURN_IF(it==_id2PropertyMap.end(),nullptr);
        SC_RETURN_IF(!(*it).second.isValidObject<SCObjPtrT<T>>(),nullptr);
        auto ptrComponent = (*it).second.getObject<SCObjPtrT<T>>();
		SC_RETURN_IF(bForce, ptrComponent);

		return (ptrComponent == nullptr || !ptrComponent->getActive()) ? nullptr : ptrComponent;
    }
    
    template<typename T>
    bool hasComponent() const
    {
        return (_id2PropertyMap.find(std::type_index(typeid(T)))!=_id2PropertyMap.end());
    }
    
    template<typename T>
    void removeComponent()
    {
		auto ptrComp = this->getComponent<T>(true);
		if (ptrComp != nullptr)
		{
			ptrComp->setEntity(nullptr);
			_id2PropertyMap.erase(std::type_index(typeid(T)));
		}
    }

	template<typename T, typename = typename std::enable_if<std::is_base_of<SCComponent, T>::value, T>::type>
	bool setComponentActive(bool bActive)
	{
		auto it = _id2PropertyMap.find(std::type_index(typeid(T)));
		SC_RETURN_IF(it == _id2PropertyMap.end(), false);
		SC_RETURN_IF(!(*it).second.isValidObject<SCObjPtrT<T>>(), false);
		auto ptrComponent = (*it).second.getObject<SCObjPtrT<T>>();
		SC_RETURN_IF(ptrComponent == nullptr, false);

		ptrComponent->setActive(bActive);
		return true;
	}

	template<typename T, typename = typename std::enable_if<std::is_base_of<SCComponent, T>::value, T>::type>
	bool getComponentActive() const
	{
		auto it = _id2PropertyMap.find(std::type_index(typeid(T)));
		SC_RETURN_IF(it == _id2PropertyMap.end(), false);
		SC_RETURN_IF(!(*it).second.isValidObject<SCObjPtrT<T>>(), false);
		auto ptrComponent = (*it).second.getObject<SCObjPtrT<T>>();
		SC_RETURN_IF(ptrComponent == nullptr, false);

		return ptrComponent->getActive();
	}
    
    int getComponentCount() const
    {
        return (int)_id2PropertyMap.size();
    }
    
    void removeFromStage();
	void removeAllComponents();
    
	int autoAssignID();

    SCStage* getStage() const { return _pStage; }

protected:
	virtual void onActiveChanged(const bool bNewActive);
    
protected:
    SCEntity(SCStage* pStage,int nID);
    SCEntity(SCStage* pStage);
    
private:
    static int                          _nAutoIDCounter;
    std::map<std::type_index,SCValue>   _id2PropertyMap;
    SCStage*                            _pStage;
};
    
NAMESPACE_SPEEDCC_END

#endif // __SPEEDCC__SCENTITY_H__
