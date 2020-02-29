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

#include "../../../stage/SCPerformObject.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

	
#define SCLUA_MODULE "SCPropertyHolder"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCPropertyHolder::Ptr
#define SCLUA_OBJ_CONTAINER SMessageMatchContainer
#define SCLUA_MODULE_BASE "sc.SCPerformObject"


int lua_speedcc_SCPropertyHolder_addComponent(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc > 0)
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

		std::list<SCString> argList;
		SCString arg0;
		bool ok = true;

		for (int i = 0; i < nArgc; ++i)
		{
			ok = SCLuaUtils::luaValue2String(tolua_S, 2+i, arg0, "sc.SCPropertyHolder:addComponent");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			argList.push_back(arg0);
		}

		if (!pRawInstance->hasComponent<SLuaActorProperty>())
		{
			pRawInstance->addComponent<SLuaActorProperty>();
		}

		auto ptrProperty = pRawInstance->getComponent<SLuaActorProperty>();
		for (const auto str : argList)
		{
			ptrProperty->dic.setValue(str,SCDictionary());
		}
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting more than %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

/*
	For Lua, the property is name in string is provided in lua, and return pointer of sc.SCDictionary to lua
*/
int lua_speedcc_SCPropertyHolder_getComponent(lua_State* tolua_S)
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

		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCPropertyHolder:getComponent");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		if (!pRawInstance->hasComponent<SLuaActorProperty>())
		{
			lua_pushnil(tolua_S);
			return 1;
		}

		auto ptrProperty = pRawInstance->getComponent<SLuaActorProperty>();
		do
		{
			SC_BREAK_IF(!ptrProperty->dic.hasKey(arg0));

			auto& value = ptrProperty->dic[arg0];
			SC_BREAK_IF(value.getType() != SCValue::EType::kTypeDictionary);

			SCDictionary* result = value.getRefDictionary();
			SC_BREAK_IF(result == nullptr);

			tolua_pushusertype(tolua_S, (void*)result, "sc.SCDictionary");
			return 1;
		} 
		while (0);

		luaL_error(tolua_S, "%s argument is invalid ", SCLUA_CLASSTYPE_LUA);

		return 0;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

/*
	For Lua, the property is name in string
*/
int lua_speedcc_SCPropertyHolder_hasComponent(lua_State* tolua_S)
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

		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCPropertyHolder:hasComponent");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		if (!pRawInstance->hasComponent<SLuaActorProperty>())
		{
			lua_pushboolean(tolua_S, false);
			return 1;
		}

		auto ptrProperty = pRawInstance->getComponent<SLuaActorProperty>();
		lua_pushboolean(tolua_S, ptrProperty->dic.hasKey(arg0));

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCPropertyHolder_removeComponent(lua_State* tolua_S)
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

		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCPropertyHolder:removeComponent");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		if (pRawInstance->hasComponent<SLuaActorProperty>())
		{
			auto ptrProperty = pRawInstance->getComponent<SLuaActorProperty>();
			ptrProperty->dic.removeKey(arg0);
		}

		lua_settop(tolua_S, 1);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

SCLUA_SCCREATE_PTR_FUNC_IMPLEMENT(SCPropertyHolder)
SCLUA_SCDESTRUCT_PTR_FUNC_IMPLEMENT(SCPropertyHolder)

int lua_register_speedcc_SCPropertyHolder(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCPropertyHolder_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "create", lua_speedcc_SCPropertyHolder_create);
		tolua_function(tolua_S, "addComponent", lua_speedcc_SCPropertyHolder_addComponent);
		tolua_function(tolua_S, "getComponent", lua_speedcc_SCPropertyHolder_getComponent);
		tolua_function(tolua_S, "hasComponent", lua_speedcc_SCPropertyHolder_hasComponent);
		tolua_function(tolua_S, "removeComponent", lua_speedcc_SCPropertyHolder_removeComponent);
	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END