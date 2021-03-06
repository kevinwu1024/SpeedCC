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

#include "../../../base/SCObject.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

	
#define SCLUA_MODULE "SCObject"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCObject::Ptr
#define SCLUA_OBJ_CONTAINER SLuaObjectContainer
#define SCLUA_MODULE_BASE ""

///------------ SCObject
int lua_speedcc_SCObject_addObject(lua_State* tolua_S)
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


		SCObject::Ptr arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2Object(tolua_S, 2, arg0, "sc.SCObject:addObject");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto ptrObj = arg0->makeObjPtr<SCObject::Ptr>();
		pRawInstance->addObject(ptrObj);

		lua_settop(tolua_S, 1);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCObject_removeObject(lua_State* tolua_S)
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

		SCObject::Ptr arg0;
		bool ok = true;

		ok = SCLuaUtils::luaValue2Object(tolua_S, 2, arg0, "sc.SCObject:addObject");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		auto ptrObj = arg0->makeObjPtr<SCObject::Ptr>();
		pRawInstance->removeObject(ptrObj);

		lua_settop(tolua_S, 1);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}

int lua_speedcc_SCObject_frameRetain(lua_State* tolua_S)
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

		pRawInstance->frameRetain();
		lua_settop(tolua_S, 1);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_register_speedcc_SCObject(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, nullptr);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "addObject", lua_speedcc_SCObject_addObject);
		tolua_function(tolua_S, "removeObject", lua_speedcc_SCObject_removeObject);
		tolua_function(tolua_S, "frameRetain", lua_speedcc_SCObject_frameRetain);
	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END