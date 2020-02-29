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

#include "../../../base/SCDataBlock.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

	
#define SCLUA_MODULE "SCDataBlock"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCDataBlock
#define SCLUA_MODULE_BASE "sc.SCObject"


int lua_speedcc_SCDataBlock_createWithString(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		SCString arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCDataBlock:createWithString");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(arg0);
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCDataBlock_createWithDataBlock(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		SCDataBlock arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2DataBlock(tolua_S, 2, arg0, "sc.SCDataBlock:createWithDataBlock");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>();
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

//int lua_speedcc_SCDataBlock_createWithData(lua_State* tolua_S)
//{
//	SCLUA_CHECK_LUA_TABLE(tolua_S);
//	return 0;
//}

int lua_speedcc_SCDataBlock_getSize(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		auto result = pInstance->getSize();
		lua_pushinteger(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDataBlock_isEmpty(lua_State* tolua_S)
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

int lua_speedcc_SCDataBlock_clear(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		pInstance->clear();
		lua_settop(tolua_S,1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDataBlock_assign(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCDataBlock arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2DataBlock(tolua_S, 2, arg0, "sc.SCDataBlock:assign");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->assign(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCDataBlock_append(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);

	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);

		SCDataBlock arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2DataBlock(tolua_S, 2, arg0, "sc.SCDataBlock:append");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pInstance->append(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


SCLUA_SCCREATE_FUNC_IMPLEMENT(SCDataBlock)
SCLUA_SCCLONE_FUNC_IMPLEMENT(SCDataBlock)
SCLUA_SCOBJREF_FUNC_IMPLEMENT(SCDataBlock)
SCLUA_SCDESTRUCT_FUNC_IMPLEMENT(SCDataBlock)

int lua_register_speedcc_SCDataBlock(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCDataBlock_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "create", lua_speedcc_SCDataBlock_create);
		tolua_function(tolua_S, "clone", lua_speedcc_SCDataBlock_clone);
		tolua_function(tolua_S, "createWithString", lua_speedcc_SCDataBlock_createWithString);
		tolua_function(tolua_S, "createWithDataBlock", lua_speedcc_SCDataBlock_createWithDataBlock);
		//tolua_function(tolua_S, "createWithData", lua_speedcc_SCDataBlock_createWithData);

		tolua_function(tolua_S, "getSize", lua_speedcc_SCDataBlock_getSize);
		tolua_function(tolua_S, "isEmpty", lua_speedcc_SCDataBlock_isEmpty);
		tolua_function(tolua_S, "clear", lua_speedcc_SCDataBlock_clear);
		//tolua_function(tolua_S, "getDataPtr", lua_speedcc_SCDataBlock_getDataPtr);

		tolua_function(tolua_S, "assign", lua_speedcc_SCDataBlock_assign);
		tolua_function(tolua_S, "append", lua_speedcc_SCDataBlock_append);

		SCLUA_SCOBJREF_FUNC_DECLARE(SCDataBlock)
	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END