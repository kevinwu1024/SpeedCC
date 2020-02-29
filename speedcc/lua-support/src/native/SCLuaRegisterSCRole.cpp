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

#include "platform/CCPlatformConfig.h"

#include "../../../stage/SCRole.h"
#include "../../../stage/SCStage.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

	
#define SCLUA_MODULE "SCRole"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCRole::Ptr
#define SCLUA_OBJ_CONTAINER SMessageMatchContainer
#define SCLUA_MODULE_BASE "sc.SCPropertyHolder"

///------------ SCRole
int lua_speedcc_SCRole_addActor(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		SCActor::Ptr arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2Actor(tolua_S, 2, arg0, "sc.SCRole:addActor");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->addActor(arg0);
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCRole_removeActor(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:removeActor");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pRawInstance->removeActor(arg0);
		lua_settop(tolua_S,1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCRole_hasActor(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:hasActor");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->hasActor(arg0);
		lua_pushinteger(tolua_S,result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCRole_getActor(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:getActor");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->getActor(arg0);
		auto obj = SCMemAllocator::newObject<SCObject::Ptr>();
		(*obj) = result;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.SCActor");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCRole_setInitStrategyID(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:setInitStrategyID");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->setInitStrategyID(arg0);
		lua_pushboolean(tolua_S,result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCRole_addStrategy(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		SCStrategy::Ptr arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2Strategy(tolua_S, 2, arg0, "sc.SCRole:addStrategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pRawInstance->addStrategy(arg0);
		lua_settop(tolua_S,1);

		return 1;
	}
	else if (nArgc == 2)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		SCStrategy::Ptr arg0;
		int arg1;
		bool ok = true;

		ok = SCLuaUtils::luaValue2Strategy(tolua_S, 2, arg0, "sc.SCRole:addStrategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = luaval_to_int32(tolua_S, 3, &arg1, "sc.SCRole:addStrategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pRawInstance->addStrategy(arg0, arg1);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCRole_getStrategy(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:getStrategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->getStrategy(arg0);
		auto obj = SCMemAllocator::newObject<SCObject::Ptr>();
		(*obj) = result;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.SCStrategy");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCRole_getStrategyInfo(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:getStrategyInfo");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->getStrategyInfo(arg0);
		auto obj = SCMemAllocator::newObject<SCObject::Ptr>();
		(*obj) = result;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.SCStrategyInfo");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCRole_hasStrategy(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:hasStrategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->hasStrategy(arg0);
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCRole_forEach(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int handler = toluafix_ref_function(tolua_S, 2, 0);
		SCLUA_CHECK_LUA_ARG(tolua_S, handler);

		pRawInstance->forEach([tolua_S, handler](SCActor::Ptr& ptrActor) -> bool
		{
			toluafix_get_function_by_refid(tolua_S, handler);                  /* L: ... func */
			if (!lua_isfunction(tolua_S, -1))
			{
				luaL_error(tolua_S, " function refid '%d' does not reference a Lua function\n ", handler);
				lua_pop(tolua_S, 1);
				return false;
			}

			tolua_pushusertype(tolua_S, (void*)&ptrActor, "sc.SCActor");
			int ret = lua_pcall(tolua_S, 1, 1, 0);
			if (ret != 0) 
			{
				lua_error(tolua_S);
			}

			return lua_toboolean(tolua_S, 1);
		});
		lua_settop(tolua_S,0);

		return 0;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCRole_addBehavior2Strategy(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 3)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		SCMessageMatcher::Ptr arg1;
		SCBehavior::Ptr arg2;
		bool ok;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:addBehavior2Strategy"); //SCLuaUtils::luaValue2MessageMatcher(tolua_S, 2, arg1, "sc.SCRole:addBehavior2Strategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2MessageMatcher(tolua_S, 3, arg1, "sc.SCRole:addBehavior2Strategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2Behavior(tolua_S, 4, arg2, "sc.SCRole:addBehavior2Strategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->addBehavior2Strategy(arg0, arg1, arg2);
		lua_pushboolean(tolua_S, result);

		return 1;

	}
	else if (nArgc == 4)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		SCBehavior::Ptr arg2;
		SCMessageMatcher::Ptr arg3;
		bool ok;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:addBehavior2Strategy"); 
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2Behavior(tolua_S, 4, arg2, "sc.SCRole:addBehavior2Strategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2MessageMatcher(tolua_S, 5, arg3, "sc.SCRole:addBehavior2Strategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		if (lua_isstring(tolua_S, 3))
		{
			SCString arg1;
			ok = SCLuaUtils::luaValue2String(tolua_S, 3, arg1, "sc.SCRole:addBehavior2Strategy");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			
			auto result = pRawInstance->addBehavior2Strategy(arg0, arg1, arg2, arg3);
			lua_pushboolean(tolua_S, result);

			return 1;
		}
		else if (lua_isnumber(tolua_S, 3))
		{
			int arg1;
			ok = luaval_to_int32(tolua_S, 3, &arg1, "sc.SCRole:addBehavior2Strategy");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			
			auto result = pRawInstance->addBehavior2Strategy(arg0, arg1, arg2, arg3);
			lua_pushboolean(tolua_S, result);

			return 1;
		}
		
		SCLUA_CHECK_LUA_ARG(tolua_S, false);
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting 3 or 4\n ", SCLUA_CLASSTYPE_LUA, nArgc);
	return 0;
}


int lua_speedcc_SCRole_addEnterBehavior2Strategy(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 2)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		SCBehavior::Ptr arg1;
		bool ok;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:addEnterBehavior2Strategy"); 
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2Behavior(tolua_S, 3, arg1, "sc.SCRole:addEnterBehavior2Strategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->addEnterBehavior2Strategy(arg0, arg1);

		lua_pushboolean(tolua_S, result);

		return 1;

	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 2);
	return 0;
}


int lua_speedcc_SCRole_addExitBehavior2Strategy(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 2)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		int arg0;
		SCBehavior::Ptr arg1;
		bool ok;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:addExitBehavior2Strategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2Behavior(tolua_S, 3, arg1, "sc.SCRole:addExitBehavior2Strategy");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->addExitBehavior2Strategy(arg0, arg1);

		lua_pushboolean(tolua_S, result);

		return 1;

	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 2);
	return 0;
}

int lua_speedcc_SCRole_getStage(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 0)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		SCStage* pStage = pRawInstance->getStage();

		auto obj = SCMemAllocator::newObject<SLuaObjectContainer>();
		obj->pWeakObj = pStage;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.SCStage");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCRole_update(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		SCMessage::Ptr arg0;
		bool ok;

		ok = SCLuaUtils::luaValue2Message(tolua_S, 2, arg0, "sc.SCRole:update");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->update(arg0);
		lua_pushboolean(tolua_S,result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCRole_getMsgFilterEnabled(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 0)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		auto result = pRawInstance->getMsgFilterEnabled();
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCRole_setMsgFilterEnabled(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 1)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer->ptrObj != nullptr || pContainer->pWeakObj != nullptr);
		SCLUA_CLASSTYPE_CPP::type* pRawInstance = nullptr;
		if (pContainer->ptrObj != nullptr)
		{
			auto ptr = pContainer->ptrObj.cast<SCLUA_CLASSTYPE_CPP>();
			pRawInstance = ptr.getRawPointer();
		}
		else if (pContainer->pWeakObj)
		{
			pRawInstance = dynamic_cast<SCLUA_CLASSTYPE_CPP::type*>(pContainer->pWeakObj);
		}
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pRawInstance != nullptr);

		bool arg0;
		bool ok;

		ok = luaval_to_boolean(tolua_S, 2, &arg0, "sc.SCRole:setMsgFilterEnabled");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pRawInstance->setMsgFilterEnabled(arg0);
		lua_settop(tolua_S,1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCRole_create(lua_State* tolua_S) 
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 2)
	{
		int arg0;
		SCStage::Ptr arg1;
		bool ok;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCRole:create");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2Stage(tolua_S, 3, arg1, "sc.SCRole:create");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_OBJ_CONTAINER>();
		obj->ptrObj = SCRole::create(arg0, arg1.getRawPointer());
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 2);
	return 0;
}


SCLUA_SCDESTRUCT_PTR_FUNC_IMPLEMENT(SCRole)

int lua_register_speedcc_SCRole(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCRole_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "create", lua_speedcc_SCRole_create);

		tolua_function(tolua_S, "addActor", lua_speedcc_SCRole_addActor);
		tolua_function(tolua_S, "removeActor", lua_speedcc_SCRole_removeActor);
		tolua_function(tolua_S, "hasActor", lua_speedcc_SCRole_hasActor);
		tolua_function(tolua_S, "getActor", lua_speedcc_SCRole_getActor);

		tolua_function(tolua_S, "setInitStrategyID", lua_speedcc_SCRole_setInitStrategyID);
		tolua_function(tolua_S, "addStrategy", lua_speedcc_SCRole_addStrategy);
		tolua_function(tolua_S, "getStrategy", lua_speedcc_SCRole_getStrategy);
		tolua_function(tolua_S, "getStrategyInfo", lua_speedcc_SCRole_getStrategyInfo);
		tolua_function(tolua_S, "hasStrategy", lua_speedcc_SCRole_hasStrategy);

		tolua_function(tolua_S, "forEach", lua_speedcc_SCRole_forEach);

		tolua_function(tolua_S, "addBehavior2Strategy", lua_speedcc_SCRole_addBehavior2Strategy);
		tolua_function(tolua_S, "addEnterBehavior2Strategy", lua_speedcc_SCRole_addEnterBehavior2Strategy);
		tolua_function(tolua_S, "addExitBehavior2Strategy", lua_speedcc_SCRole_addExitBehavior2Strategy);

		tolua_function(tolua_S, "getStage", lua_speedcc_SCRole_getStage);
		tolua_function(tolua_S, "update", lua_speedcc_SCRole_update);
		tolua_function(tolua_S, "getMsgFilterEnabled", lua_speedcc_SCRole_getMsgFilterEnabled);
		tolua_function(tolua_S, "setMsgFilterEnabled", lua_speedcc_SCRole_setMsgFilterEnabled);

	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END