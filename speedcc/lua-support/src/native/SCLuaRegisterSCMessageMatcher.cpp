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

	
#define SCLUA_MODULE "SCMessageMatcher"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCMessageMatcher::Ptr
#define SCLUA_OBJ_CONTAINER SMessageMatchContainer
#define SCLUA_MODULE_BASE "sc.SCObject"

int lua_speedcc_SCMessageMatcher_createWithFunc(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 2)
	{
		auto arg0Type = lua_type(tolua_S, 2);
		SCLUA_CHECK_LUA_ARG(tolua_S, (arg0Type != LUA_TSTRING && arg0Type != LUA_TNUMBER));

		int handler = toluafix_ref_function(tolua_S, 3, 0);
		SCLUA_CHECK_LUA_ARG(tolua_S, handler);

		auto func = [handler, tolua_S](const SCMessage::Ptr ptrMsg) -> bool
		{
			toluafix_get_function_by_refid(tolua_S, handler);                  /* L: ... func */
			if (!lua_isfunction(tolua_S, -1))
			{
				luaL_error(tolua_S, " function refid '%d' does not reference a Lua function\n ", handler);
				lua_pop(tolua_S, 1);
				return false;
			}

			SCObject::Ptr ptrObj = ptrMsg;
			tolua_pushusertype(tolua_S, (void*)&ptrObj, "sc.SCMessage");

			int ret = lua_pcall(tolua_S, 1, 1, 0);
			if (ret != 0)
			{
				lua_error(tolua_S);
			}

			bool result = false;
			bool ok = luaval_to_boolean(tolua_S, 1, &result, "sc.SCMessageMatcher:lua_speedcc_SCMessageMatcher_createWithFunc");
			if (!ok)
			{
				tolua_error(tolua_S, "invalid return type in function '" __FUNCTION__ "'", nullptr);
			}
			return result;
		};

		SCLUA_OBJ_CONTAINER* obj = nullptr;
		if (arg0Type == LUA_TSTRING)
		{
			SCString arg0;
			bool ok;
			ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCMessageMatcher:createWithFunc");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			obj = SCMemAllocator::newObject<SCLUA_OBJ_CONTAINER>();
			obj->ptrObj = SCMessageMatcher::create(arg0, func);
			obj->extention = handler;
		}
		else if (arg0Type == LUA_TNUMBER)
		{
			int arg0;
			bool ok;
			ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCMessageMatcher:createWithFunc");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			obj = SCMemAllocator::newObject<SCLUA_OBJ_CONTAINER>();
			obj->ptrObj = SCMessageMatcher::create(arg0, func);
			obj->extention = handler;
		}

		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 2);
	return 0;
}

int lua_speedcc_SCMessageMatcher_createWithDic(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 2)
	{
		auto arg0Type = lua_type(tolua_S, 2);
		SCLUA_CHECK_LUA_ARG(tolua_S, (arg0Type != LUA_TSTRING && arg0Type != LUA_TNUMBER));

		int arg0;
		SCDictionary arg1;
		bool ok;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCMessageMatcher:createWithDic");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2Dictionary(tolua_S, 3, arg1, "sc.SCMessageMatcher:createWithDic");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		SCLUA_OBJ_CONTAINER* obj = nullptr;

		if (arg0Type == LUA_TSTRING)
		{
			SCString arg0;
			bool ok;
			ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCMessageMatcher:createWithDic");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			obj = SCMemAllocator::newObject<SCLUA_OBJ_CONTAINER>();
			obj->ptrObj = SCMessageMatcher::create(arg0, arg1);
			obj->extention = 0;
		}
		else if (arg0Type == LUA_TNUMBER)
		{
			int arg0;
			bool ok;
			ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCMessageMatcher:createWithDic");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			obj = SCMemAllocator::newObject<SCLUA_OBJ_CONTAINER>();
			obj->ptrObj = SCMessageMatcher::create(arg0, arg1);
			obj->extention = 0;
		}
		
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 2);
	return 0;
}

int lua_speedcc_SCMessageMatcher_isMatch(lua_State* tolua_S)
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

		ok = SCLuaUtils::luaValue2Message(tolua_S, 2, arg0, "sc.SCMessageMatcher:isMatch");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pRawInstance->isMatch(arg0);
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCMessageMatcher_getCommand(lua_State* tolua_S)
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

		auto result = pRawInstance->getCommand();
		lua_pushstring(tolua_S, result.c_str());

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCMessageMatcher_getMessageID(lua_State* tolua_S)
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

		auto result = pRawInstance->getMessageID();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCMessageMatcher_getParameter(lua_State* tolua_S)
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

		auto result = pRawInstance->getParameter();

		auto obj = SCMemAllocator::newObject<SCDictionary>();
		(*obj) = result;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.SCDictionary");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCMessageMatcher_getFunc(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pContainer = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pContainer != nullptr && pContainer->ptrObj != nullptr);

		if (pContainer->extention == 0)
		{
			lua_pushnil(tolua_S);
		}
		else
		{
			toluafix_get_function_by_refid(tolua_S, pContainer->extention);
		}

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCMessageMatcher_isCommand(lua_State* tolua_S)
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

		auto result = pRawInstance->isCommand();
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCMessageMatcher_destruct(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto pInstance = (SCLUA_OBJ_CONTAINER*)tolua_tousertype(tolua_S, 1, 0);
	if (pInstance->extention)
	{
		toluafix_remove_function_by_refid(tolua_S,pInstance->extention);
		pInstance->extention = 0;
	}

	SCMemAllocator::deleteObject(pInstance);
	return 0;
}

int lua_register_speedcc_SCMessageMatcher(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCMessageMatcher_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "createWithFunc", lua_speedcc_SCMessageMatcher_createWithFunc);
		tolua_function(tolua_S, "createWithDic", lua_speedcc_SCMessageMatcher_createWithDic);

		tolua_function(tolua_S, "isMatch", lua_speedcc_SCMessageMatcher_isMatch);
		tolua_function(tolua_S, "getCommand", lua_speedcc_SCMessageMatcher_getCommand);
		tolua_function(tolua_S, "getMessageID", lua_speedcc_SCMessageMatcher_getMessageID);
		tolua_function(tolua_S, "getParameter", lua_speedcc_SCMessageMatcher_getParameter);
		tolua_function(tolua_S, "getFunc", lua_speedcc_SCMessageMatcher_getFunc);

		tolua_function(tolua_S, "isCommand", lua_speedcc_SCMessageMatcher_isCommand);

	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END