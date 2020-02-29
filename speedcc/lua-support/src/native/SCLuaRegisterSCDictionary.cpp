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

#include "../../../base/SCDictionary.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#define SCLUA_MODULE "SCDictionary"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCDictionary
#define SCLUA_MODULE_BASE "sc.SCObject"


#ifdef __cplusplus
extern "C" {
#endif


int lua_speedcc_SCDictionary_createWithKeyValue(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		SCDictionary::SKVPair arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2KVPair(tolua_S, 2, arg0, "sc.SCDictionary:createWithKeyValue");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}
	else if (nArgc == 2)
	{
		SCString arg0;
		SCValue arg1;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCDictionary:createWithKeyValue");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2Value(tolua_S, 3, arg1, "sc.SCDictionary:createWithKeyValue");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0,arg1);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %s\n ", SCLUA_CLASSTYPE_LUA, nArgc, "1 or 2");
	return 0;
}

int lua_speedcc_SCDictionary_createWithKVPairArray(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		SCDictionary::SKVPair arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2KVPair(tolua_S, 2, arg0, "sc.SCDictionary:createWithKVPairArray");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCDictionary_createWithJson(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCDictionary:createWithJson");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDictionary_loadFromJsonString(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCDictionary:loadFromJsonString");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pInstance->loadFromJsonString(arg0);
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCDictionary_exportJson(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->exportJson();
		lua_pushstring(tolua_S, result);

		return 1;
	}
	else if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		bool arg0;
		bool ok = true;

		luaval_to_boolean(tolua_S, 2, &arg0, "sc.SCDictionary:exportJson");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pInstance->exportJson(arg0);
		lua_pushstring(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %s\n ", SCLUA_CLASSTYPE_LUA, nArgc, "0 or 1");
	return 0;
}

int lua_speedcc_SCDictionary_setValue(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCDictionary::SKVPair arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2KVPair(tolua_S, 2, arg0, "sc.SCDictionary:setValue");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setValue(arg0);

		lua_settop(tolua_S, 1);

		return 1;
	}
	else if (nArgc == 2)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCString arg0;
		SCValue arg1;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCDictionary:setValue");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2Value(tolua_S, 3, arg1, "sc.SCDictionary:setValue");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setValue(arg0,arg1);

		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %s\n ", SCLUA_CLASSTYPE_LUA, nArgc, "1 or 2");
	return 0;
}

//int lua_speedcc_SCDictionary_setDictionary(lua_State* tolua_S)
//{
//	return 0;
//}

int lua_speedcc_SCDictionary_assign(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCDictionary arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2Dictionary(tolua_S, 2, arg0, "sc.SCDictionary:assign");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		(*pInstance) = arg0;
		lua_settop(tolua_S,1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCDictionary_getValue(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCDictionary:getValue");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pInstance->getValue(arg0);

		auto obj = SCMemAllocator::newObject<SCValue>(result);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.SCValue");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

//int lua_speedcc_SCDictionary_getDictionary(lua_State* tolua_S)
//{
//	return 0;
//}

int lua_speedcc_SCDictionary_hasKey(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCDictionary:removeKey");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pInstance->hasKey(arg0);
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDictionary_removeKey(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCDictionary:removeKey");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->removeKey(arg0);
		lua_settop(tolua_S,1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDictionary_removeAllKeys(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		pInstance->removeAllKeys();
		lua_settop(tolua_S,1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDictionary_getCount(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getCount();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDictionary_isEmpty(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->isEmpty();
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

SCLUA_SCCREATE_FUNC_IMPLEMENT(SCDictionary)
SCLUA_SCCLONE_FUNC_IMPLEMENT(SCDictionary)
SCLUA_SCOBJREF_FUNC_IMPLEMENT(SCDictionary)
SCLUA_SCDESTRUCT_FUNC_IMPLEMENT(SCDictionary)

int lua_register_speedcc_SCDictionary(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCDictionary_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);

		tolua_function(tolua_S, "create", lua_speedcc_SCDictionary_create);
		tolua_function(tolua_S, "clone", lua_speedcc_SCDictionary_clone);
		tolua_function(tolua_S, "createWithKeyValue", lua_speedcc_SCDictionary_createWithKeyValue);
		tolua_function(tolua_S, "createWithKVPairArray", lua_speedcc_SCDictionary_createWithKVPairArray);
		tolua_function(tolua_S, "createWithJson", lua_speedcc_SCDictionary_createWithJson);

		tolua_function(tolua_S, "loadFromJsonString", lua_speedcc_SCDictionary_loadFromJsonString);
		tolua_function(tolua_S, "exportJson", lua_speedcc_SCDictionary_exportJson);

		tolua_function(tolua_S, "setValue", lua_speedcc_SCDictionary_setValue);
		//tolua_function(tolua_S, "setDictionary", lua_speedcc_SCDictionary_setDictionary);
		tolua_function(tolua_S, "assign", lua_speedcc_SCDictionary_assign);
		tolua_function(tolua_S, "getValue", lua_speedcc_SCDictionary_getValue);
		//tolua_function(tolua_S, "getDictionary", lua_speedcc_SCDictionary_getDictionary);

		tolua_function(tolua_S, "hasKey", lua_speedcc_SCDictionary_hasKey);
		tolua_function(tolua_S, "removeKey", lua_speedcc_SCDictionary_removeKey);
		tolua_function(tolua_S, "removeAllKeys", lua_speedcc_SCDictionary_removeAllKeys);
		tolua_function(tolua_S, "getCount", lua_speedcc_SCDictionary_getCount);
		tolua_function(tolua_S, "isEmpty", lua_speedcc_SCDictionary_isEmpty);

		SCLUA_SCOBJREF_FUNC_DECLARE(SCDictionary)

	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END
