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

#include "../../../stage/SCStage.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

	
#define SCLUA_MODULE "SCStage"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCStage::Ptr
#define SCLUA_OBJ_CONTAINER SMessageMatchContainer
#define SCLUA_MODULE_BASE "SCObject"

///------------ SCStage
int lua_speedcc_SCStage_addRole(lua_State* tolua_S)
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

		SCRole::Ptr arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2Role(tolua_S, 2, arg0, "sc.SCStage:addRole");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);
		pRawInstance->addRole(arg0);
		
		lua_settop(tolua_S,1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCStage_removeRole(lua_State* tolua_S)
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

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCStage:removeRole");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pRawInstance->removeRole(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCStage_getRole(lua_State* tolua_S)
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

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCStage:removeRole");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->getRole(arg0);
		
		auto obj = SCMemAllocator::newObject<SCObject::Ptr>();
		(*obj) = result;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.SCRole");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCStage_createActor2Role(lua_State* tolua_S)
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

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCStage:createActor2Role");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pRawInstance->createActor2Role<SLuaActorProperty>(arg0);

		lua_settop(tolua_S, 1);

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

		int arg0, arg1;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCStage:createActor2Role");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = luaval_to_int32(tolua_S, 3, &arg1, "sc.SCStage:createActor2Role");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pRawInstance->createActor2Role<SLuaActorProperty>(arg0, arg1);

		lua_settop(tolua_S, 1);

		return 1;
	}
	else if (nArgc > 2)
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

		int arg0, arg1;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCStage:createActor2Role");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = luaval_to_int32(tolua_S, 3, &arg1, "sc.SCStage:createActor2Role");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		std::list<SCString> argList;
		SCString arg2;

		for (int i = 0; i < nArgc; ++i)
		{
			ok = SCLuaUtils::luaValue2String(tolua_S, 4 + i, arg2, "sc.SCPropertyHolder:addComponent");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			argList.push_back(arg0);
		}

		pRawInstance->createActor2Role<SLuaActorProperty>(arg0, arg1);
		auto ptrRole = pRawInstance->getRole(arg0);

		if (!ptrRole->hasComponent<SLuaActorProperty>())
		{
			ptrRole->addComponent<SLuaActorProperty>();
		}

		auto ptrProperty = ptrRole->getComponent<SLuaActorProperty>();
		for (const auto str : argList)
		{
			ptrProperty->dic.setValue(str, SCDictionary());
		}

		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting 1 or 2\n ", SCLUA_CLASSTYPE_LUA, nArgc);
	return 0;
}

int lua_speedcc_SCStage_onSCMessageProcess(lua_State* tolua_S)
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
		bool ok = true;

		ok = SCLuaUtils::luaValue2Message(tolua_S, 2, arg0, "sc.SCStage:onSCMessageProcess");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);
		auto result = pRawInstance->onSCMessageProcess(arg0);
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


SCLUA_SCCREATE_PTR_FUNC_IMPLEMENT(SCStage)
SCLUA_SCDESTRUCT_PTR_FUNC_IMPLEMENT(SCStage)

int lua_register_speedcc_SCStage(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCStage_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "create", lua_speedcc_SCStage_create);

		tolua_function(tolua_S, "addRole", lua_speedcc_SCStage_addRole);
		tolua_function(tolua_S, "removeRole", lua_speedcc_SCStage_removeRole);
		tolua_function(tolua_S, "getRole", lua_speedcc_SCStage_getRole);

		tolua_function(tolua_S, "createActor2Role", lua_speedcc_SCStage_createActor2Role);

		tolua_function(tolua_S, "onSCMessageProcess", lua_speedcc_SCStage_onSCMessageProcess);
	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END