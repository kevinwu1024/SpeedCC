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

#include "../../../system/SCSystem.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

	
#define SCLUA_MODULE "SCSystem"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCSystem
//#define SCLUA_OBJ_CONTAINER SCLUA_CLASSTYPE_CPP
#define SCLUA_MODULE_BASE ""

///------------ SCSystem

int lua_speedcc_SCSystem_getOSVersion(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto result = SCSystem::getOSVersion();
		auto obj = SCMemAllocator::newObject<SCVersion>();
		(*obj) = result;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCSystem_getAppVersion(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto result = SCSystem::getAppVersion();
		auto obj = SCMemAllocator::newObject<SCVersion>();
		(*obj) = result;
		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCSystem_getFreeStorage(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		unsigned long ulInternal;
		unsigned long ulExternal;
		SCSystem::getFreeStorage(&ulInternal,&ulExternal);

		lua_pushnumber(tolua_S, ulInternal);
		lua_pushnumber(tolua_S, ulExternal);
		return 2;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCSystem_setMultipleTouch(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		bool arg0;
		bool ok = true;

		ok = luaval_to_boolean(tolua_S, 2, &arg0, "sc.SCSystem:setMultipleTouch");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		SCSystem::setMultipleTouch(arg0);
		return 0;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCSystem_getMultipleTouch(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto result = SCSystem::getMultipleTouch();

		lua_pushboolean(tolua_S, result);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCSystem_getSupportAssetSizeType(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 0)
	{
		auto result = SCSystem::getSupportAssetSizeType();

		lua_pushinteger(tolua_S, result);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCSystem_setSupportAssetSizeType(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		int arg0;
		bool ok = true;

		ok = luaval_to_int32(tolua_S, 2, &arg0, "sc.SCSystem:setSupportAssetSizeType");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		SCSystem::setSupportAssetSizeType(arg0);
		return 0;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCSystem_setGlobalDisableTouch(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;
	if (nArgc == 1)
	{
		bool arg0;
		bool ok = true;

		ok = luaval_to_boolean(tolua_S, 2, &arg0, "sc.SCSystem:setGlobalDisableTouch");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		SCSystem::setGlobalDisableTouch(arg0);
		return 0;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

//int lua_speedcc_SCSystem_getSupportAssetSizeType(lua_State* tolua_S)
//{
//	SCLUA_CHECK_LUA_TABLE(tolua_S);
//	auto nArgc = lua_gettop(tolua_S) - 1;
//	if (nArgc == 0)
//	{
//		auto result = SCSystem::getGlobalDisableTouch();
//
//		lua_pushboolean(tolua_S, result);
//		return 1;
//	}
//
//	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
//	return 0;
//}


int lua_speedcc_SCSystem_showAlertBox(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	tolua_Error tolua_err;
	SCString arg0,arg1,arg2,arg3,arg4;
	bool ok = true;
	int handler = 0;

	switch (nArgc)
	{
	case 6:
		// all of arguments are available
		handler = toluafix_ref_function(tolua_S, 7, 0);
		SCLUA_CHECK_LUA_ARG(tolua_S, handler);

	case 5:
		if (tolua_isstring(tolua_S, 6,0,&tolua_err))
		{// button1, button2, button3 are available and callback is null
		// this argument is button3 value
			ok = SCLuaUtils::luaValue2String(tolua_S, 6, arg4, "sc.SCSystem:showAlertBox");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
		}

		if(nArgc == 5 && lua_isfunction(tolua_S, 6))
		{// button1, button2, callback are available and button3 is null
		// this arguemnt is callback function
			handler = toluafix_ref_function(tolua_S, 6, 0);
			SCLUA_CHECK_LUA_ARG(tolua_S, handler);
		}
		else
		{
			luaL_error(tolua_S, "%s type of arguments %d is wrong: %d, was expecting string or function\n ", SCLUA_CLASSTYPE_LUA, nArgc);
			return 0;
		}
		

	case 4:
		if (tolua_isstring(tolua_S, 5, 0, &tolua_err))
		{// button1, button2 are available and button3,callback is null
		 // this argument is button2 value
			ok = SCLuaUtils::luaValue2String(tolua_S, 5, arg3, "sc.SCSystem:showAlertBox");
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);
		}
		else if (nArgc == 4 && lua_isfunction(tolua_S, 5))
		{// button1, callback are available and button2, button3 is null
		 // this arguemnt is callback function
			handler = toluafix_ref_function(tolua_S, 5, 0);
			SCLUA_CHECK_LUA_ARG(tolua_S, handler);
		}
		else
		{
			luaL_error(tolua_S, "%s type of arguments %d is wrong: %d, was expecting string or function\n ", SCLUA_CLASSTYPE_LUA, nArgc);
			return 0;
		}

	case 3:
		ok = SCLuaUtils::luaValue2String(tolua_S, 2, arg0, "sc.SCSystem:showAlertBox");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2String(tolua_S, 3, arg1, "sc.SCSystem:showAlertBox");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		ok = SCLuaUtils::luaValue2String(tolua_S, 4, arg2, "sc.SCSystem:showAlertBox");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		if (nArgc == 3 && lua_isfunction(tolua_S, 4))
		{// button1, callback are available and button2, button3 is null
		 // this arguemnt is callback function
			handler = toluafix_ref_function(tolua_S, 5, 0);
			SCLUA_CHECK_LUA_ARG(tolua_S, handler);
		}

		break;

	default:
		break;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_register_speedcc_SCSystem(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, nullptr);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "getOSVersion", lua_speedcc_SCSystem_getOSVersion);
		tolua_function(tolua_S, "getAppVersion", lua_speedcc_SCSystem_getAppVersion);
		tolua_function(tolua_S, "getFreeStorage", lua_speedcc_SCSystem_getFreeStorage);

		tolua_function(tolua_S, "setMultipleTouch", lua_speedcc_SCSystem_setMultipleTouch);
		tolua_function(tolua_S, "getMultipleTouch", lua_speedcc_SCSystem_getMultipleTouch);
		tolua_function(tolua_S, "getSupportAssetSizeType", lua_speedcc_SCSystem_getSupportAssetSizeType);
		tolua_function(tolua_S, "setSupportAssetSizeType", lua_speedcc_SCSystem_setSupportAssetSizeType);
		tolua_function(tolua_S, "setGlobalDisableTouch", lua_speedcc_SCSystem_setGlobalDisableTouch);
		//tolua_function(tolua_S, "getSupportAssetSizeType", lua_speedcc_SCSystem_getSupportAssetSizeType);
	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END
