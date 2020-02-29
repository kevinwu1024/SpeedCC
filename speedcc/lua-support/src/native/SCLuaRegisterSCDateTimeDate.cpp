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

#define SCLUA_MODULE "Date"
#define SCLUA_CLASSTYPE_LUA "sc.SCDateTime." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCDateTime::Date 
#define SCLUA_MODULE_BASE ""

#ifdef __cplusplus
extern "C" {
#endif

SCLUA_SCCREATE_FUNC_IMPLEMENT(SCDateTimeDate)
SCLUA_SCCLONE_FUNC_IMPLEMENT(SCDateTimeDate)

int lua_speedcc_SCDateTimeDate_createYMD(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 3)
	{
		int arg0,arg1,arg2;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime.Date:createYMD");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = luaval_to_int32(tolua_S, 3, &arg1, "sc.SCDateTime.Date:createYMD");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = luaval_to_int32(tolua_S, 4, &arg2, "sc.SCDateTime.Date:createYMD");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0, arg1, arg2);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 3);
	return 0;
}

int lua_speedcc_SCDateTimeDate_createWithJD(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		INT64 arg0;
		bool ok = true;

		ok = luaval_to_long_long(tolua_S, 2, &arg0, "sc.SCDateTime.Date:createWithJD");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeDate_isValid(lua_State* tolua_S)
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

int lua_speedcc_SCDateTimeDate_getWeekCountOfYear(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getWeekCountOfYear();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeDate_getDayCountOfMonth(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getDayCountOfMonth();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeDate_getDayCountOfYear(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getDayCountOfYear();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeDate_getYear(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		lua_pushinteger(tolua_S, pInstance->nYear);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTimeDate_setYear(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime.Date:createWithJD");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->nYear = arg0;
		lua_pushinteger(tolua_S, arg0);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeDate_getMonth(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		lua_pushinteger(tolua_S, pInstance->nMonth);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeDate_setMonth(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime.Date:createWithJD");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->nMonth = arg0;
		lua_pushinteger(tolua_S, arg0);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeDate_getDay(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		lua_pushinteger(tolua_S, pInstance->nDay);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTimeDate_setDay(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime.Date:createWithJD");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->nDay = arg0;
		lua_pushinteger(tolua_S, arg0);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


SCLUA_SCDESTRUCT_FUNC_IMPLEMENT(SCDateTimeDate)

///------------ SCDateTime::Date

int lua_register_speedcc_SCDateTimeDate(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCDateTimeDate_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "create", lua_speedcc_SCDateTimeDate_create);
		tolua_function(tolua_S, "clone", lua_speedcc_SCDateTimeDate_clone);
		tolua_function(tolua_S, "createYMD", lua_speedcc_SCDateTimeDate_createYMD);
		tolua_function(tolua_S, "createWithJD", lua_speedcc_SCDateTimeDate_createWithJD);
		tolua_function(tolua_S, "isValid", lua_speedcc_SCDateTimeDate_isValid);
		tolua_function(tolua_S, "getWeekCountOfYear", lua_speedcc_SCDateTimeDate_getWeekCountOfYear);
		tolua_function(tolua_S, "getDayCountOfMonth", lua_speedcc_SCDateTimeDate_getDayCountOfMonth);
		tolua_function(tolua_S, "getDayCountOfYear", lua_speedcc_SCDateTimeDate_getDayCountOfYear);

		tolua_variable(tolua_S, "year", lua_speedcc_SCDateTimeDate_getYear, lua_speedcc_SCDateTimeDate_setYear);
		tolua_variable(tolua_S, "month", lua_speedcc_SCDateTimeDate_getMonth, lua_speedcc_SCDateTimeDate_setMonth);
		tolua_variable(tolua_S, "day", lua_speedcc_SCDateTimeDate_getDay, lua_speedcc_SCDateTimeDate_setDay);
	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END