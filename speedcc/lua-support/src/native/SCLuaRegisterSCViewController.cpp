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

#include "../../../cocos/SCViewController.h"
#include "../../../cocos/SCView.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "SCLuaUtils.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

	
#define SCLUA_MODULE "SCViewController"
#define SCLUA_CLASSTYPE_LUA "sc." SCLUA_MODULE
#define SCLUA_CLASSTYPE_CPP SCViewController::Ptr
#define SCLUA_OBJ_CONTAINER SLuaObjectContainer
#define SCLUA_MODULE_BASE "sc.SCStage"

//int lua_speedcc_SCViewController_create(lua_State* tolua_S)
//{
//	return 0;
//}


int lua_speedcc_SCViewController_isAllTouchEnabled(lua_State* tolua_S)
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

		auto result = pRawInstance->isAllTouchEnabled();
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

int lua_speedcc_SCViewController_isBlackMaskForModal(lua_State* tolua_S)
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

		auto result = pRawInstance->isBlackMaskForModal();
		lua_pushboolean(tolua_S, result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCViewController_setTouchAcceptable(lua_State* tolua_S)
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

		bool arg0;
		bool ok = true;

		ok = luaval_to_boolean(tolua_S, 2, &arg0, "sc.SCStage:createActor2Role");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pRawInstance->setTouchAcceptable(arg0);
		lua_settop(tolua_S,1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCViewController_showBlackMask(lua_State* tolua_S)
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

		bool arg0;
		bool ok = true;

		ok = luaval_to_boolean(tolua_S, 2, &arg0, "sc.SCStage:createActor2Role");
		SCLUA_CHECK_LUA_ARG(tolua_S, ok);

		pRawInstance->showBlackMask(arg0);
		lua_settop(tolua_S, 1);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);
	return 0;
}


int lua_speedcc_SCViewController_getView(lua_State* tolua_S)
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

		auto result = pRawInstance->getView();
		object_to_luaval<SCView>(tolua_S, "sc.SCView", result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCViewController_getScene(lua_State* tolua_S)
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

		auto result = pRawInstance->getScene();
		object_to_luaval<SCScene>(tolua_S, "sc.SCScene",result);

		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}


int lua_speedcc_SCViewController_pushModalController(lua_State* tolua_S)
{
	return 0;
}


int lua_speedcc_SCViewController_popModalFromParent(lua_State* tolua_S)
{
	return 0;
}


int lua_speedcc_SCViewController_ownLifecycle(lua_State* tolua_S)
{
	return 0;
}


int lua_speedcc_SCViewController_delayExecute(lua_State* tolua_S)
{
	return 0;
}


int lua_speedcc_SCViewController_listenMessage(lua_State* tolua_S)
{
	return 0;
}


int lua_speedcc_SCViewController_schedule(lua_State* tolua_S)
{
	return 0;
}


int lua_speedcc_SCViewController_unschedule(lua_State* tolua_S)
{
	return 0;
}


//int lua_speedcc_SCViewController_onSCMessageProcess(lua_State* tolua_S)
//{
//	return 0;
//}


int lua_speedcc_SCViewController_finish(lua_State* tolua_S)
{
	return 0;
}


int lua_speedcc_SCViewController_setBackButtonSceneEnabled(lua_State* tolua_S)
{
	return 0;
}


int lua_speedcc_SCViewController_getBackButtonSceneEnabled(lua_State* tolua_S)
{
	return 0;
}

bool lua_speedcc_SCViewControllerCB_onSCMessageProcess(void* pContainer, SCMessage::Ptr ptrMsg)
{
	LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	lua_State* tolua_S = stack->getLuaState();

	if (pContainer == nullptr)
	{
		luaL_error(tolua_S, "Instance container pointer is null in %s ", __FUNCTION__);
		return true;
	}

	tolua_pushusertype(tolua_S, pContainer, SCLUA_CLASSTYPE_LUA);

	auto par = SCMemAllocator::newObject<SLuaObjectContainer>();
	par->ptrObj = ptrMsg->clone();
	tolua_pushusertype_and_takeownership(tolua_S, (void*)par, "sc.SCMessage");

	bool bRet = true;
	int num = stack->executeGlobalFunction("scN2SViewControllerOnSCMessageProcess");
	if (num == 1)
	{
		bRet = tolua_toboolean(tolua_S, 1, 0);
	}

	stack->clean();

	return bRet;
}

void lua_speedcc_SCViewControllerCB_onCreate(void* pContainer, SCDictionary parameters)
{
	LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	lua_State* tolua_S = stack->getLuaState();

	if (pContainer == nullptr)
	{
		luaL_error(tolua_S, "Instance container pointer is null in %s ",__FUNCTION__);
		return;
	}
	
	tolua_pushusertype(tolua_S, pContainer, SCLUA_CLASSTYPE_LUA);

	auto par = SCMemAllocator::newObject<SCDictionary>();
	(*par) = parameters;
	tolua_pushusertype_and_takeownership(tolua_S, (void*)par, "sc.SCDictionary");

	stack->executeGlobalFunction("scN2SViewControllerOnCreate");
	stack->clean();
}

int lua_speedcc_SCViewController_create(lua_State* tolua_S)
{
	SCLUA_CHECK_LUA_TABLE(tolua_S);
	auto nArgc = lua_gettop(tolua_S) - 1;

	if (nArgc == 0)
	{
		auto obj = SCMemAllocator::newObject<SLuaObjectContainer>();
		auto ptrViewController = SCLUA_CLASSTYPE_CPP::type::create();
		obj->ptrObj = ptrViewController;
		obj->ptrObj->setScriptContainer(obj); 

		SScriptCBViewControllerInfo cbInfo;
		cbInfo.pfunOnCreate = lua_speedcc_SCViewControllerCB_onCreate;
		cbInfo.pfunOnMessageProcess = lua_speedcc_SCViewControllerCB_onSCMessageProcess;
		ptrViewController->setScriptCBInfo(cbInfo);

		tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);
		return 1;
	}

	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);
	return 0;
}

SCLUA_SCDESTRUCT_PTR_FUNC_IMPLEMENT(SCViewController)


int lua_register_speedcc_SCViewController(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, SCLUA_CLASSTYPE_LUA);
	tolua_cclass(tolua_S, SCLUA_MODULE, SCLUA_CLASSTYPE_LUA, SCLUA_MODULE_BASE, lua_speedcc_SCViewController_destruct);

	tolua_beginmodule(tolua_S, SCLUA_MODULE);
		tolua_function(tolua_S, "create", lua_speedcc_SCViewController_create);

		tolua_function(tolua_S, "isAllTouchEnabled", lua_speedcc_SCViewController_isAllTouchEnabled);
		tolua_function(tolua_S, "isBlackMaskForModal", lua_speedcc_SCViewController_isBlackMaskForModal);
		tolua_function(tolua_S, "setTouchAcceptable", lua_speedcc_SCViewController_setTouchAcceptable);
		tolua_function(tolua_S, "showBlackMask", lua_speedcc_SCViewController_showBlackMask);

		tolua_function(tolua_S, "getView", lua_speedcc_SCViewController_getView);
		tolua_function(tolua_S, "getScene", lua_speedcc_SCViewController_getScene);

		tolua_function(tolua_S, "pushModalController", lua_speedcc_SCViewController_pushModalController);
		tolua_function(tolua_S, "popModalFromParent", lua_speedcc_SCViewController_popModalFromParent);

		tolua_function(tolua_S, "ownLifecycle", lua_speedcc_SCViewController_ownLifecycle);
		tolua_function(tolua_S, "delayExecute", lua_speedcc_SCViewController_delayExecute);

		tolua_function(tolua_S, "listenMessage", lua_speedcc_SCViewController_listenMessage);

		tolua_function(tolua_S, "schedule", lua_speedcc_SCViewController_schedule);
		tolua_function(tolua_S, "unschedule", lua_speedcc_SCViewController_unschedule);

		//tolua_function(tolua_S, "onSCMessageProcess", lua_speedcc_SCViewController_onSCMessageProcess);

		tolua_function(tolua_S, "finish", lua_speedcc_SCViewController_finish);

		tolua_function(tolua_S, "setBackButtonSceneEnabled", lua_speedcc_SCViewController_setBackButtonSceneEnabled);
		tolua_function(tolua_S, "getBackButtonSceneEnabled", lua_speedcc_SCViewController_getBackButtonSceneEnabled);
		//SCLUA_SCOBJREF_FUNC_DECLARE(SCViewController)
	tolua_endmodule(tolua_S);

	return 1;
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END
