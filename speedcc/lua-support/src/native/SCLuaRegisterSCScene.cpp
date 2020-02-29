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

#include "../../../cocos/SCView.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

	
#define SCLUA_MODULE "SCScene"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCScene
#define SCLUA_OBJ_CONTAINER SCScene
#define SCLUA_MODULE_BASE "cc.Scene"

///------------ SCScene
int lua_speedcc_SCScene_create(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 0)
	{
		auto ret = SCLUA_CLASSTYPE_CPP::create();
		object_to_luaval<SCLUA_CLASSTYPE_CPP>(tolua_S, "sc.SCScene", ret);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCScene_getView(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_USERTYPE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 0)
	{
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);
		SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance != nullptr);

		auto result = pInstance->getView();

		//object_to_luaval<SCView>(tolua_S, "sc.SCView", result);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_register_speedcc_SCScene(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, nullptr);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "create", lua_speedcc_SCScene_create);
		tolua_function(tolua_S, "getView", lua_speedcc_SCScene_getView);
	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END