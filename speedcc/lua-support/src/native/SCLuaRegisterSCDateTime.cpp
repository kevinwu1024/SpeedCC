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

#define SCLUA_MODULE "SCDateTime"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCDateTime 
#define SCLUA_MODULE_BASE "sc.SCObject"

#ifdef __cplusplus
extern "C" {
#endif

int lua_register_speedcc_SCDateTimeDate(lua_State* tolua_S);
int lua_register_speedcc_SCDateTimeTime(lua_State* tolua_S);

int lua_speedcc_SCDateTime_addMilliSeconds(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2,&arg0, "sc.SCDateTime:addMilliSeconds");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->addMilliSeconds(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_addSeconds(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:addSeconds");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->addSeconds(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_addMinute(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:addMinute");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->addMinute(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_addHour(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:addHour");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->addHour(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_addDay(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:addDay");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->addDay(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCDateTime_addMonth(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:addMonth");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->addMonth(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCDateTime_addYear(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:addYear");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->addYear(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_setMilliSeconds(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:setMilliSeconds");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		bool b = pInstance->setMilliSeconds(arg0);
		lua_pushboolean(tolua_S, b);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCDateTime_setSeconds(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:setSeconds");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		bool b = pInstance->setSeconds(arg0);
		lua_pushboolean(tolua_S, b);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_setMinute(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:setMinute");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		bool b = pInstance->setMinute(arg0);
		lua_pushboolean(tolua_S, b);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_setHour(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:setHour");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		bool b = pInstance->setHour(arg0);
		lua_pushboolean(tolua_S, b);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_setDayOfMonth(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:setDayOfMonth");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		bool b = pInstance->setDayOfMonth(arg0);
		lua_pushboolean(tolua_S, b);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_setMonth(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:setMonth");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		bool b = pInstance->setMonth(arg0);
		lua_pushboolean(tolua_S, b);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_setYear(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:setYear");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		bool b = pInstance->setYear(arg0);
		lua_pushboolean(tolua_S, b);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_getYear(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int result = pInstance->getYear();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getMonth(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int result = pInstance->getMonth();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getHour(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int result = pInstance->getHour();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getMinute(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int result = pInstance->getMinute();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCDateTime_getSeconds(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int result = pInstance->getSeconds();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCDateTime_getMilleSeconds(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int result = pInstance->getMilleSeconds();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCDateTime_getDate(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto date = pInstance->getDate();

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP::Date>(date);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.DateTime.Date");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getTime(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto time = pInstance->getTime();

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP::Time>(time);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.DateTime.Time");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_setDate(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCDateTime::Date arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2Date(tolua_S, 2, arg0, "sc.SCDateTime:setDate");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setDate(arg0);

		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_setTime(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCDateTime::Time arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2Time(tolua_S, 2, arg0, "sc.SCDateTime:setTime");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setTime(arg0);

		lua_settop(tolua_S,1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCDateTime_getMonthName(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getMonthName();
		lua_pushstring(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCDateTime_getWeekName(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getWeekName();
		lua_pushstring(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getDayOfWeek(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getDayOfWeek();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getDayOfMonth(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getDayOfMonth();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getDayOfYear(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getDayOfYear();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getWeekCountOfYear(lua_State* tolua_S)
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

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getDayCountOfMonth(lua_State* tolua_S)
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

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getDayCountOfYear(lua_State* tolua_S)
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

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCDateTime_setDatetime(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		double arg0;
		bool ok = true;

		ok = luaval_to_number(tolua_S, 2, &arg0, "sc.SCDateTime:setDatetime");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		bool b = pInstance->setDatetime(arg0);
		lua_pushboolean(tolua_S, b);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_getStamp(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		double result = pInstance->getStamp();
		lua_pushnumber(tolua_S,result);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_toUTC(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->toUTC();
		lua_settop(tolua_S,1);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_toLocal(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		pInstance->toLocal();
		lua_settop(tolua_S, 1);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_getDSTStatus(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getDSTStatus();
		lua_pushinteger(tolua_S, result);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDateTime_now(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		pInstance->now();
		lua_settop(tolua_S, 1);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCDateTime_getFormatString(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
	SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto result = pInstance->getFormatString("");
		lua_pushstring(tolua_S,result.c_str());
		return 1;
	}
	else if (nArgc == 1)
	{
		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCDateTime:getFormatString");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto result = pInstance->getFormatString(arg0);
		lua_pushstring(tolua_S, result.c_str());
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDateTime_isLeapYear(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
	SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCDateTime:isLeapYear");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		bool result = SCDateTime::isLeapYear(arg0);
		lua_pushboolean(tolua_S, result);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

SCLUA_SCCREATE_FUNC_IMPLEMENT(SCDateTime)
SCLUA_SCCLONE_FUNC_IMPLEMENT(SCDateTime)
SCLUA_SCOBJREF_FUNC_IMPLEMENT(SCDateTime)
SCLUA_SCDESTRUCT_FUNC_IMPLEMENT(SCDateTime)

///------------ SCDateTime

int lua_register_speedcc_SCDateTime(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCDateTime_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "create", lua_speedcc_SCDateTime_create);
		tolua_function(tolua_S, "clone", lua_speedcc_SCDateTime_clone);

		tolua_function(tolua_S, "addMilliSeconds", lua_speedcc_SCDateTime_addMilliSeconds);
		tolua_function(tolua_S, "addSeconds", lua_speedcc_SCDateTime_addSeconds);
		tolua_function(tolua_S, "addMinute", lua_speedcc_SCDateTime_addMinute);

		tolua_function(tolua_S, "addHour", lua_speedcc_SCDateTime_addHour);
		tolua_function(tolua_S, "addDay", lua_speedcc_SCDateTime_addDay);
		tolua_function(tolua_S, "addMonth", lua_speedcc_SCDateTime_addMonth);
		tolua_function(tolua_S, "addYear", lua_speedcc_SCDateTime_addYear);

		tolua_function(tolua_S, "setMilliSeconds", lua_speedcc_SCDateTime_setMilliSeconds);
		tolua_function(tolua_S, "setSeconds", lua_speedcc_SCDateTime_setSeconds);
		tolua_function(tolua_S, "setMinute", lua_speedcc_SCDateTime_setMinute);
		tolua_function(tolua_S, "setHour", lua_speedcc_SCDateTime_setHour);

		tolua_function(tolua_S, "setDayOfMonth", lua_speedcc_SCDateTime_setDayOfMonth);
		tolua_function(tolua_S, "setMonth", lua_speedcc_SCDateTime_setMonth);
		tolua_function(tolua_S, "setYear", lua_speedcc_SCDateTime_setYear);

		tolua_function(tolua_S, "getYear", lua_speedcc_SCDateTime_getYear);
		tolua_function(tolua_S, "getMonth", lua_speedcc_SCDateTime_getMonth);

		tolua_function(tolua_S, "getHour", lua_speedcc_SCDateTime_getHour);
		tolua_function(tolua_S, "getMinute", lua_speedcc_SCDateTime_getMinute);
		tolua_function(tolua_S, "getSeconds", lua_speedcc_SCDateTime_getSeconds);
		tolua_function(tolua_S, "getMilleSeconds", lua_speedcc_SCDateTime_getMilleSeconds);

		tolua_function(tolua_S, "getDate", lua_speedcc_SCDateTime_getDate);
		tolua_function(tolua_S, "getTime", lua_speedcc_SCDateTime_getTime);
		tolua_function(tolua_S, "setDate", lua_speedcc_SCDateTime_setDate);
		tolua_function(tolua_S, "setTime", lua_speedcc_SCDateTime_setTime);

		tolua_function(tolua_S, "getMonthName", lua_speedcc_SCDateTime_getMonthName);
		tolua_function(tolua_S, "getWeekName", lua_speedcc_SCDateTime_getWeekName);

		tolua_function(tolua_S, "getDayOfWeek", lua_speedcc_SCDateTime_getDayOfWeek);
		tolua_function(tolua_S, "getDayOfMonth", lua_speedcc_SCDateTime_getDayOfMonth);
		tolua_function(tolua_S, "getDayOfYear", lua_speedcc_SCDateTime_getDayOfYear);

		tolua_function(tolua_S, "getWeekCountOfYear", lua_speedcc_SCDateTime_getWeekCountOfYear);
		tolua_function(tolua_S, "getDayCountOfMonth", lua_speedcc_SCDateTime_getDayCountOfMonth);
		tolua_function(tolua_S, "getDayCountOfYear", lua_speedcc_SCDateTime_getDayCountOfYear);
		tolua_function(tolua_S, "setDatetime", lua_speedcc_SCDateTime_setDatetime);
		tolua_function(tolua_S, "getStamp", lua_speedcc_SCDateTime_getStamp);

		tolua_function(tolua_S, "toUTC", lua_speedcc_SCDateTime_toUTC);
		tolua_function(tolua_S, "toLocal", lua_speedcc_SCDateTime_toLocal);

		tolua_function(tolua_S, "getDSTStatus", lua_speedcc_SCDateTime_getDSTStatus);
		tolua_function(tolua_S, "now", lua_speedcc_SCDateTime_now);
		tolua_function(tolua_S, "getFormatString", lua_speedcc_SCDateTime_getFormatString);
		tolua_function(tolua_S, "isLeapYear", lua_speedcc_SCDateTime_isLeapYear);

		SCLUA_SCOBJREF_FUNC_DECLARE(SCDateTime)

		lua_register_speedcc_SCDateTimeDate(tolua_S); // SCDateTime::Date
		lua_register_speedcc_SCDateTimeTime(tolua_S); // SCDateTime:Time
	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END