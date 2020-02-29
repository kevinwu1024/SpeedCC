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

#include "../../../base/SCDateTime.h"
#include "../../../base/SCString.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#define SCLUA_MODULE "Time"
#define SCLUA_CLASSTYPE_LUA "sc.SCDateTime." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCDateTime::Time 
#define SCLUA_MODULE_BASE ""

#ifdef __cplusplus
extern "C" {
#endif


int lua_speedcc_SCDateTimeTime_createWithTime(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 4)
	{
		int arg0,arg1,arg2, arg3;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime.Time:createWithTime");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = luaval_to_int32(tolua_S, 3, &arg1, "sc.SCDateTime.Time:createWithTime");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = luaval_to_int32(tolua_S, 4, &arg2, "sc.SCDateTime.Time:createWithTime");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = luaval_to_int32(tolua_S, 5, &arg3, "sc.SCDateTime.Time:createWithTime");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0, arg1, arg2, arg3);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 4);
	return 0;
}

int lua_speedcc_SCDateTimeTime_createWithMillSecOfDay(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		INT64 arg0;
		bool ok = true;

		ok = luaval_to_long_long(tolua_S, 2, &arg0, "sc.SCDateTime.Time:createWithMillSecOfDay");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeTime_isValid(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->isValid();
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeTime_getMillSecOfDay(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getMillSecOfDay();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeTime_getSecOfDay(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getSecOfDay();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCDateTimeTime_getHour(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		lua_pushinteger(tolua_S, pInstance->nHour);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeTime_setHour(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime.Time:setHour");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->nHour = arg0;
		lua_pushinteger(tolua_S, arg0);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeTime_getMinute(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		lua_pushinteger(tolua_S, pInstance->nMinute);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeTime_setMinute(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime.Time:setMinute");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->nMinute = arg0;
		lua_pushinteger(tolua_S, arg0);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeTime_getSeconds(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		lua_pushinteger(tolua_S, pInstance->nSeconds);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeTime_setSeconds(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime.Time:setSeconds");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->nSeconds = arg0;
		lua_pushinteger(tolua_S, arg0);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCDateTimeTime_getMillSec(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		lua_pushinteger(tolua_S, pInstance->nMillSeconds);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeTime_setMillSec(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime.Time:setMillSec");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->nMillSeconds = arg0;
		lua_pushinteger(tolua_S, arg0);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

SCLUA_SCCREATE_FUNC_IMPLEMENT(SCDateTimeTime)
SCLUA_SCCLONE_FUNC_IMPLEMENT(SCDateTimeTime)
SCLUA_SCDESTRUCT_FUNC_IMPLEMENT(SCDateTimeTime)

///------------ SCDateTime::Time

int lua_register_speedcc_SCDateTimeTime(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCDateTimeTime_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "create", lua_speedcc_SCDateTimeTime_create);
		tolua_function(tolua_S, "clone", lua_speedcc_SCDateTimeTime_clone);
		tolua_function(tolua_S, "createWithTime", lua_speedcc_SCDateTimeTime_createWithTime);
		tolua_function(tolua_S, "createWithMillSecOfDay", lua_speedcc_SCDateTimeTime_createWithMillSecOfDay);
		tolua_function(tolua_S, "isValid", lua_speedcc_SCDateTimeTime_isValid);
		tolua_function(tolua_S, "getMillSecOfDay", lua_speedcc_SCDateTimeTime_getMillSecOfDay);
		tolua_function(tolua_S, "getSecOfDay", lua_speedcc_SCDateTimeTime_getSecOfDay);

		tolua_variable(tolua_S, "nHour", lua_speedcc_SCDateTimeTime_getHour, lua_speedcc_SCDateTimeTime_setHour);
		tolua_variable(tolua_S, "nMinute", lua_speedcc_SCDateTimeTime_getMinute, lua_speedcc_SCDateTimeTime_setMinute);
		tolua_variable(tolua_S, "nSeconds", lua_speedcc_SCDateTimeTime_getSeconds, lua_speedcc_SCDateTimeTime_setSeconds);
		tolua_variable(tolua_S, "nMillSeconds", lua_speedcc_SCDateTimeTime_getMillSec, lua_speedcc_SCDateTimeTime_setMillSec);
	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END