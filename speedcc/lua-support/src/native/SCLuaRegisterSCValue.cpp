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

#include "../../../cocos/SCRefHolder.h"
#include "../../../base/SCValue.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#define SCLUA_MODULE "SCValue"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCValue
#define SCLUA_MODULE_BASE "sc.SCObject"


#ifdef __cplusplus
extern "C" {
#endif


int lua_speedcc_SCValue_createWithChar(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCValue:createWithChar");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);
		SCASSERT(arg0 >= -255 && arg0 <= 255*2);

		if (arg0 > 255) 
		{
			arg0 = 255 - arg0;
		}
		const char a = (char)arg0;
		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(a);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithByte(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCValue:createWithByte");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);
		SCASSERT(arg0 >= 0 && arg0 < 512);

		const unsigned char a = (unsigned char)arg0;
		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(a);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithUnsignedInt(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		double arg0;
		bool ok = true;

		ok = luaval_to_number(tolua_S, 2, &arg0, "sc.SCValue:createWithUnsignedInt");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		const unsigned int a = (unsigned int)arg0;
		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(a);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCValue_createWithInt(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCValue:createWithInt");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithBool(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		bool arg0;
		bool ok = true;

		ok = luaval_to_boolean(tolua_S, 2, &arg0, "sc.SCValue:createWithBool");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithDouble(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		double arg0;
		bool ok = true;

		ok = luaval_to_number(tolua_S, 2, &arg0, "sc.SCValue:createWithDouble");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithInt64(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		double arg0;
		bool ok = true;

		ok = luaval_to_number(tolua_S, 2, &arg0, "sc.SCValue:createWithInt64");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		const INT64 a = (INT64)arg0;
		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(a);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithLong(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		long arg0;
		bool ok = true;

		ok = luaval_to_long(tolua_S, 2, &arg0, "sc.SCValue:createWithLong");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithString(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCValue:createWithString");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithDateTime(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		SCDateTime arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2DateTime(tolua_S, 2, arg0, "sc.SCValue:createWithDateTime");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithDataBlock(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		SCDataBlock arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2DataBlock(tolua_S, 2, arg0, "sc.SCValue:createWithDataBlock");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithArray(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		std::vector<SCValue> arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2ValueArray(tolua_S, 2, arg0, "sc.SCValue:createWithArray");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_createWithObject(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		cocos2d::Ref* arg0 = nullptr;
		bool ok = true;

		ok = luaval_to_object(tolua_S, 2, "cc.Ref", &arg0, "sc.SCValue:createWithObject");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);
		
		auto objContainer = SCRef2Ptr::create(arg0);
		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(objContainer);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_isNumberType(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->isNumberType();
		lua_pushboolean(tolua_S,result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getType(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getType();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_isUnknown(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->isUnknown();
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getChar(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getChar();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getByte(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getByte();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getUnsignedInt(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getUnsignedInt();
		lua_pushnumber(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getInt(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getInt();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getLong(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getLong();
		lua_pushnumber(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getBool(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getBool();
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getDouble(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getDouble();
		lua_pushnumber(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getInt64(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getInt64();
		lua_pushnumber(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getString(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getString();
		lua_pushstring(tolua_S,result.c_str());

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getDataBlock(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getDataBlock();

		auto obj = SCMemAllocator::newObject<SCDataBlock>();
		(*obj) = result;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.SCDataBlock");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getDateTime(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getDateTime();

		auto obj = SCMemAllocator::newObject<SCDateTime>();
		(*obj) = result;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.SCDateTime");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getDictionary(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getDictionary();
		auto obj = SCMemAllocator::newObject<SCDictionary>();
		(*obj) = result;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, "sc.SCDictionary");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getArray(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto array = pInstance->getArray();
		SCLuaUtils::pushArray2LuaStack(tolua_S, array,"sc.SCValue:getArray");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


///=======================

int lua_speedcc_SCValue_getRefDataBlock(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getRefDataBlock();
		if (result == nullptr)
		{
			tolua_error(tolua_S, "invalid 'object ref' in function '" __FUNCTION__ "'", nullptr);
			return 0;
		}
		tolua_pushusertype_and_takeownership(tolua_S, (void*)result, "sc.SCDataBlock");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getRefDateTime(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getRefDateTime();
		if (result == nullptr)
		{
			tolua_error(tolua_S, "invalid 'object ref' in function '" __FUNCTION__ "'", nullptr);
			return 0;
		}

		tolua_pushusertype(tolua_S, (void*)result, "sc.SCDateTime");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCValue_getRefDictionary(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getRefDictionary();
		if (result == nullptr)
		{
			tolua_error(tolua_S, "invalid 'object ref' in function '" __FUNCTION__ "'", nullptr);
			return 0;
		}
		tolua_pushusertype(tolua_S, (void*)result, "sc.SCDictionary");

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}



///======================
int lua_speedcc_SCValue_getObject(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCValue:getObject");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		if (arg0.find("cc.") == 0)
		{// cocos2d object
			for (const auto& pair : g_luaType)
			{
				SC_CONTINUE_IF(pair.second.compare(arg0.c_str()));

				auto pObjContainer = pInstance->getObject<SCRef2Ptr::Ptr>();
				auto pRef = pObjContainer->getRef();
				int* luaID = &(pRef->_luaID);
				int ID = (int)pRef->_ID;
				
				toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)pRef, arg0.c_str());

				return 1;
			}

			luaL_error(tolua_S, "%s has wrong argument: object doesnot match class type '%s'\n ", SCLUA_CLASSTYPE_LUA, arg0.c_str());
			return 0;
		}
		else
		{
			if (arg0.isEmpty())
			{
				luaL_error(tolua_S, "%s objuect type is empty \n", SCLUA_CLASSTYPE_LUA);
			}
			else
			{
				luaL_error(tolua_S, "%s unsupport object type: %s \n", SCLUA_CLASSTYPE_LUA, arg0.c_str());
			}
			return 0;
		}
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setChar(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCValue:setChar");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);
		SCASSERT(arg0 >= -255 && arg0 <= 255 * 2);

		if (arg0 > 255) 
		{
			arg0 = 255 - arg0;
		}

		const char a = (char)arg0;
		pInstance->setChar(a);
		lua_settop(tolua_S,1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setByte(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCValue:setByte");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);
		SCASSERT(arg0 >= 0 && arg0 < 512);

		const unsigned char a = (unsigned char)arg0;
		pInstance->setByte(a);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setUnsignedInt(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		double arg0;
		bool ok = true;

		ok = luaval_to_number(tolua_S, 2, &arg0, "sc.SCValue:setUnsignedInt");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		const unsigned int a = (unsigned int)arg0;
		pInstance->setUnsignedInt(a);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setInt(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCValue:setInt");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		const unsigned int a = (unsigned int)arg0;
		pInstance->setUnsignedInt(a);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setLong(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		long arg0;
		bool ok = true;

		ok = luaval_to_long(tolua_S, 2, &arg0, "sc.SCValue:setLong");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setLong(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setBool(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		bool arg0;
		bool ok = true;

		ok = luaval_to_boolean(tolua_S, 2, &arg0, "sc.SCValue:setBool");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setBool(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setDouble(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		double arg0;
		bool ok = true;

		ok = luaval_to_number(tolua_S, 2, &arg0, "sc.SCValue:setDouble");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setDouble(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setInt64(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		double arg0;
		bool ok = true;

		ok = luaval_to_number(tolua_S, 2, &arg0, "sc.SCValue:setInt64");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setInt64((INT64)arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setString(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCValue:setString");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setString(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setDataBlock(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCDataBlock arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2DataBlock(tolua_S, 2, arg0, "sc.SCValue:setDataBlock");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setDataBlock(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setDateTime(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCDateTime arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2DateTime(tolua_S, 2, arg0, "sc.SCValue:setDateTime");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setDateTime(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setArray(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		std::vector<SCValue> arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2ValueArray(tolua_S, 2, arg0, "sc.SCValue:setArray");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setArray(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setDictionary(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCDictionary arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2Dictionary(tolua_S, 2, arg0, "sc.SCValue:setDictionary");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->setDictionary(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCValue_assign(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		bool ok = true;

		tolua_Error tolua_err;
		if (tolua_isusertype(tolua_S, 2, "sc.SCDictionary", 0, &tolua_err))
		{// for SCDictionary
			SCDictionary arg0;
			ok = SCLuaUtils::luaValue2Dictionary(tolua_S, 2, arg0, "sc.SCValue:assign");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			(*pInstance) = (arg0);
		}
		else if (tolua_isusertype(tolua_S, 2, "sc.SCValue", 0, &tolua_err))
		{// for SCValue
			SCValue arg0;
			ok = SCLuaUtils::luaValue2Value(tolua_S, 2, arg0, "sc.SCValue:assign");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			*pInstance = (arg0);
		}
		else if (tolua_isusertype(tolua_S, 2, "sc.SCDataBlock", 0, &tolua_err))
		{// for SCDataBlock
			SCDataBlock arg0;
			ok = SCLuaUtils::luaValue2DataBlock(tolua_S, 2, arg0, "sc.SCValue:assign");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			(*pInstance) = (arg0);
		}
		else if (tolua_isusertype(tolua_S, 2, "sc.SCDateTime", 0, &tolua_err))
		{// for SCDateTime
			SCDateTime arg0;
			ok = SCLuaUtils::luaValue2DateTime(tolua_S, 2, arg0, "sc.SCValue:assign");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			(*pInstance) = (arg0);
		}
		else if (tolua_isboolean(tolua_S, 2, 0, &tolua_err))
		{// for bool
			bool arg0;
			ok = luaval_to_boolean(tolua_S, 2, &arg0, "sc.SCValue:assign");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			(*pInstance) = (arg0);
		}
		else if (tolua_isstring(tolua_S, 2, 0, &tolua_err))
		{// for string
			SCString arg0;
			ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCValue:assign");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			(*pInstance) = (arg0);
		}
		else if (tolua_isnumber(tolua_S, 2, 0, &tolua_err))
		{// for number
			double arg0;
			ok = luaval_to_number(tolua_S, 2, &arg0, "sc.SCValue:assign");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
			(*pInstance) = (arg0);
		}

		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCValue_setObject(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		cocos2d::Ref* arg0 = nullptr;
		bool ok = true;

		ok = luaval_to_object(tolua_S, 2, "cc.Ref", &arg0, "sc.SCValue:setObject");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto objContainer = SCRef2Ptr::create(arg0);
		pInstance->setObject(objContainer);

		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


SCLUA_SCCREATE_FUNC_IMPLEMENT(SCValue)
SCLUA_SCCLONE_FUNC_IMPLEMENT(SCValue)
SCLUA_SCOBJREF_FUNC_IMPLEMENT(SCValue)
SCLUA_SCDESTRUCT_FUNC_IMPLEMENT(SCValue)

int lua_register_speedcc_SCValue(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCValue_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);

		tolua_function(tolua_S, "create", lua_speedcc_SCValue_create);
		tolua_function(tolua_S, "clone", lua_speedcc_SCValue_clone);
		tolua_function(tolua_S, "createWithChar", lua_speedcc_SCValue_createWithChar);
		tolua_function(tolua_S, "createWithByte", lua_speedcc_SCValue_createWithByte);
		tolua_function(tolua_S, "createWithUnsignedInt", lua_speedcc_SCValue_createWithUnsignedInt);
		tolua_function(tolua_S, "createWithInt", lua_speedcc_SCValue_createWithInt);
		tolua_function(tolua_S, "createWithLong", lua_speedcc_SCValue_createWithLong);
		tolua_function(tolua_S, "createWithBool", lua_speedcc_SCValue_createWithBool);
		tolua_function(tolua_S, "createWithDouble", lua_speedcc_SCValue_createWithDouble);
		tolua_function(tolua_S, "createWithInt64", lua_speedcc_SCValue_createWithInt64);
		tolua_function(tolua_S, "createWithString", lua_speedcc_SCValue_createWithString);
		tolua_function(tolua_S, "createWithDateTime", lua_speedcc_SCValue_createWithDateTime);
		tolua_function(tolua_S, "createWithDataBlock", lua_speedcc_SCValue_createWithDataBlock);
		tolua_function(tolua_S, "createWithArray", lua_speedcc_SCValue_createWithArray);
		tolua_function(tolua_S, "createWithObject", lua_speedcc_SCValue_createWithObject);

		tolua_function(tolua_S, "isNumberType", lua_speedcc_SCValue_isNumberType);
		tolua_function(tolua_S, "getType", lua_speedcc_SCValue_getType);
		tolua_function(tolua_S, "isUnknown", lua_speedcc_SCValue_isUnknown);

		tolua_function(tolua_S, "getChar", lua_speedcc_SCValue_getChar);
		tolua_function(tolua_S, "getByte", lua_speedcc_SCValue_getByte);
		tolua_function(tolua_S, "getUnsignedInt", lua_speedcc_SCValue_getUnsignedInt);
		tolua_function(tolua_S, "getInt", lua_speedcc_SCValue_getInt);
		tolua_function(tolua_S, "getLong", lua_speedcc_SCValue_getLong);
		tolua_function(tolua_S, "getBool", lua_speedcc_SCValue_getBool);
		tolua_function(tolua_S, "getDouble", lua_speedcc_SCValue_getDouble);
		tolua_function(tolua_S, "getInt64", lua_speedcc_SCValue_getInt64);
		tolua_function(tolua_S, "getString", lua_speedcc_SCValue_getString);
		tolua_function(tolua_S, "getDataBlock", lua_speedcc_SCValue_getDataBlock);
		tolua_function(tolua_S, "getDateTime", lua_speedcc_SCValue_getDateTime);
		tolua_function(tolua_S, "getArray", lua_speedcc_SCValue_getArray);
		tolua_function(tolua_S, "getDictionary", lua_speedcc_SCValue_getDictionary);
		tolua_function(tolua_S, "getObject", lua_speedcc_SCValue_getObject);

		//tolua_function(tolua_S, "getRefString", lua_speedcc_SCValue_getRefString);
		//tolua_function(tolua_S, "getRefArray", lua_speedcc_SCValue_getRefArray);
		tolua_function(tolua_S, "getRefDataBlock", lua_speedcc_SCValue_getRefDataBlock);
		tolua_function(tolua_S, "getRefDateTime", lua_speedcc_SCValue_getRefDateTime);
		tolua_function(tolua_S, "getRefDictionary", lua_speedcc_SCValue_getRefDictionary);

		tolua_function(tolua_S, "setChar", lua_speedcc_SCValue_setChar);
		tolua_function(tolua_S, "setByte", lua_speedcc_SCValue_setByte);
		tolua_function(tolua_S, "setUnsignedInt", lua_speedcc_SCValue_setUnsignedInt);
		tolua_function(tolua_S, "setInt", lua_speedcc_SCValue_setInt);
		tolua_function(tolua_S, "setLong", lua_speedcc_SCValue_setLong);
		tolua_function(tolua_S, "setBool", lua_speedcc_SCValue_setBool);
		tolua_function(tolua_S, "setDouble", lua_speedcc_SCValue_setDouble);
		tolua_function(tolua_S, "setInt64", lua_speedcc_SCValue_setInt64);
		tolua_function(tolua_S, "setString", lua_speedcc_SCValue_setString);
		tolua_function(tolua_S, "setDataBlock", lua_speedcc_SCValue_setDataBlock);
		tolua_function(tolua_S, "setDateTime", lua_speedcc_SCValue_setDateTime);
		tolua_function(tolua_S, "setArray", lua_speedcc_SCValue_setArray);
		tolua_function(tolua_S, "setDictionary", lua_speedcc_SCValue_setDictionary);
		tolua_function(tolua_S, "setObject", lua_speedcc_SCValue_setObject);

		tolua_function(tolua_S, "assign", lua_speedcc_SCValue_assign);

		SCLUA_SCOBJREF_FUNC_DECLARE(SCValue)

	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END
