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


#ifndef __SPEEDCC__SCLUAUTILS_H__
#define __SPEEDCC__SCLUAUTILS_H__

#include "../../../base/SCBaseMacros.h"
#include "../../../base/SCString.h"
#include "../../../base/SCDateTime.h"
#include "../../../base/SCDataBlock.h"
#include "../../../base/SCValue.h"
#include "../../../base/SCDictionary.h"
#include "../../../base/SCVersion.h"

#include "../../../stage/SCStage.h"
#include "../../../stage/SCRole.h"
#include "../../../stage/SCStrategy.h"

#include "../../../cocos/SCViewController.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"

#ifdef __cplusplus
}
#endif


#if COCOS2D_DEBUG >= 1
	#define SCLUA_CHECK_LUA_ARG(_L_,_ok_) \
		do{\
			if (!(_ok_)) { \
				tolua_error((_L_), "invalid arguments in function '" __FUNCTION__ "'", nullptr); \
				return 0;} \
		}while(0)

	#define SCLUA_CHECK_LUA_USERTYPE(_L_) \
		do{\
			tolua_Error tolua_err; \
			if (!tolua_isusertype((_L_), 1, SCLUA_CLASSTYPE_LUA, 0, &tolua_err)){ \
				tolua_error((_L_), "#ferror in function '" __FUNCTION__ "'.", &tolua_err); \
				return 0;} \
		}while(0)

	#define SCLUA_CHECK_LUA_TABLE(_L_) \
		do{\
			tolua_Error tolua_err; \
			if (!tolua_isusertable((_L_), 1, SCLUA_CLASSTYPE_LUA, 0, &tolua_err)){ \
				tolua_error((_L_), "#ferror in function '" __FUNCTION__ "'.", &tolua_err); \
				return 0;} \
		}while(0)
#else
	#define SCLUA_CHECK_LUA_ARG(_L_,_ok_)
	#define SCLUA_CHECK_LUA_CLASSTYPE(_L_)
	#define SCLUA_CHECK_LUA_TABLE(_L_)
#endif

#define SCLUA_CHECK_LUA_INSTANCE(_L_,_instance_) \
	do{\
		if (!(_instance_)){ \
			tolua_error((_L_), "invalid 'cobj' in function '" __FUNCTION__ "'", nullptr);\
			return 0;} \
	}while(0)

#define SCLUA_SCOBJREF_FUNC_DECLARE(_class_) \
	tolua_function(tolua_S, "getRefCount", lua_speedcc_##_class_##_getRefCount); \
	tolua_function(tolua_S, "isValid", lua_speedcc_##_class_##_isValid); \
	tolua_function(tolua_S, "increaseRef", lua_speedcc_##_class_##_increaseRef); \
	tolua_function(tolua_S, "decreaseRef", lua_speedcc_##_class_##_decreaseRef);


#define SCLUA_SCOBJREF_FUNC_IMPLEMENT(_class_) \
	int lua_speedcc_##_class_##_getRefCount(lua_State* tolua_S) \
	{\
		SCLUA_CHECK_LUA_USERTYPE(tolua_S); \
		auto nArgc = lua_gettop(tolua_S) - 1; \
		if (nArgc == 0) \
		{\
			auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0); \
			SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance); \
			auto result = pInstance->getRefCount(); \
			lua_pushinteger(tolua_S, result);\
			return 1;\
		}\
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);\
		return 0;\
	}\
	int lua_speedcc_##_class_##_isValid(lua_State* tolua_S)\
	{\
		SCLUA_CHECK_LUA_USERTYPE(tolua_S);\
		auto nArgc = lua_gettop(tolua_S) - 1;\
		if (nArgc == 0)\
		{\
			auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);\
			SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);\
			auto result = pInstance->isValid();\
			lua_pushboolean(tolua_S, result);\
			return 1;\
		}\
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);\
		return 0;\
	}\
	int lua_speedcc_##_class_##_increaseRef(lua_State* tolua_S)\
	{\
		SCLUA_CHECK_LUA_USERTYPE(tolua_S);\
		auto nArgc = lua_gettop(tolua_S) - 1;\
		if (nArgc == 0)\
		{\
			auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);\
			SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);\
			auto result = pInstance->increaseRef();\
			lua_pushinteger(tolua_S, result);\
			return 1;\
		}\
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);\
		return 0;\
	}\
	int lua_speedcc_##_class_##_decreaseRef(lua_State* tolua_S)\
	{\
		SCLUA_CHECK_LUA_USERTYPE(tolua_S);\
		auto nArgc = lua_gettop(tolua_S) - 1;\
		if (nArgc == 0)\
		{\
			auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);\
			SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);\
			auto result = pInstance->decreaseRef();\
			lua_pushinteger(tolua_S, result);\
			return 1;\
		}\
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);\
		return 0;\
	}

#define SCLUA_SCDESTRUCT_FUNC_IMPLEMENT(_class_) \
	int lua_speedcc_##_class_##_destruct(lua_State* tolua_S)\
	{\
		SCLUA_CHECK_LUA_USERTYPE(tolua_S);\
		auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0);\
		SCMemAllocator::deleteObject(pInstance);\
		return 0;\
	}

#define SCLUA_SCDESTRUCT_PTR_FUNC_IMPLEMENT(_class_) \
	int lua_speedcc_##_class_##_destruct(lua_State* tolua_S)\
	{\
		SCLUA_CHECK_LUA_USERTYPE(tolua_S);\
		auto pInstance = (SLuaObjectContainer*)tolua_tousertype(tolua_S, 1, 0);\
		SCMemAllocator::deleteObject(pInstance);\
		return 0;\
	}

#define SCLUA_SCCLONE_FUNC_IMPLEMENT(_class_) \
	int lua_speedcc_##_class_##_clone(lua_State* tolua_S)\
	{\
		SCLUA_CHECK_LUA_USERTYPE(tolua_S);\
		auto nArgc = lua_gettop(tolua_S) - 1;\
		if (nArgc == 0)\
		{\
			auto pInstance = (SCLUA_CLASSTYPE_CPP*)tolua_tousertype(tolua_S, 1, 0); \
			SCLUA_CHECK_LUA_INSTANCE(tolua_S, pInstance);\
			auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>(); \
			(*obj) = (*pInstance);\
			tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);\
			return 1;\
		}\
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);\
		return 0;\
	}

#define SCLUA_SCCREATE_FUNC_IMPLEMENT(_class_) \
	int lua_speedcc_##_class_##_create(lua_State* tolua_S) \
	{\
		SCLUA_CHECK_LUA_TABLE(tolua_S);\
		auto nArgc = lua_gettop(tolua_S) - 1;\
		if (nArgc == 0)\
		{\
			auto obj = SCMemAllocator::newObject<SCLUA_CLASSTYPE_CPP>();\
			tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);\
			return 1;\
		}\
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);\
		return 0;\
	}

#define SCLUA_SCCREATE_PTR_FUNC_IMPLEMENT(_class_) \
	int lua_speedcc_##_class_##_create(lua_State* tolua_S) \
	{\
		SCLUA_CHECK_LUA_TABLE(tolua_S);\
		auto nArgc = lua_gettop(tolua_S) - 1;\
		if (nArgc == 0)\
		{\
			auto obj = SCMemAllocator::newObject<SLuaObjectContainer>();\
			obj->ptrObj = SCLUA_CLASSTYPE_CPP::type::create();\
			obj->ptrObj->setScriptContainer(obj); \
			tolua_pushusertype_and_takeownership(tolua_S, (void*)obj, SCLUA_CLASSTYPE_LUA);\
			return 1;\
		}\
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 0);\
		return 0;\
	}

#define SCLUA_SCONMESSAGEPROC_FUNC_IMPLEMENT(_class_) \
	int lua_speedcc_##_class_##_onSCMessageProcess(lua_State* tolua_S) \
	{\
		SCLUA_CHECK_LUA_USERTYPE(tolua_S);\
		auto nArgc = lua_gettop(tolua_S) - 1;\
		if (nArgc == 1)\
		{\
			auto pObjPtr = (SCObject::Ptr*)tolua_tousertype(tolua_S, 1, 0);\
			SCLUA_CHECK_LUA_INSTANCE(tolua_S, pObjPtr && (*pObjPtr) != nullptr);\
			SCLUA_CLASSTYPE_CPP ptrInst = (*pObjPtr).cast<SCLUA_CLASSTYPE_CPP>();\
			SCLUA_CHECK_LUA_INSTANCE(tolua_S, ptrInst != nullptr);\
			SCMessage::Ptr arg0;\
			bool ok = true;\
			ok = SCLuaUtils::luaValue2Message(tolua_S, 2, arg0, "sc."#_class_":onSCMessageProcess");\
			SCLUA_CHECK_LUA_ARG(tolua_S, ok);\
			auto result = pObjPtr->onSCMessageProcess(arg0);\
			lua_pushboolean(tolua_S, result);\
			return 1;\
		}\
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", SCLUA_CLASSTYPE_LUA, nArgc, 1);\
		return 0;\
	}

NAMESPACE_SPEEDCC_BEGIN

struct SLuaActorProperty : public SCObject
{
	SCDictionary dic;
};

struct SLuaObjectContainer
{
	SCObject::Ptr	ptrObj;
	SCObject*		pWeakObj;

	SLuaObjectContainer():pWeakObj(nullptr)
	{
	}
};

template<typename T1>
struct SLuaObjectContainerEx : public SLuaObjectContainer
{
	T1				extention;
};

typedef SLuaObjectContainerEx<int>						SMessageMatchContainer;
typedef SLuaObjectContainerEx<std::vector<int>>			SViewControllerContainer;

class SCLuaUtils
{
public:
	static bool luaValue2String(lua_State* L, int lo, SCString& outValue, const char* funcName);
	static bool luaValue2DateTime(lua_State* L, int lo, SCDateTime& outValue, const char* funcName);
	static bool luaValue2Date(lua_State* L, int lo, SCDateTime::Date& outValue, const char* funcName);
	static bool luaValue2Time(lua_State* L, int lo, SCDateTime::Time& outValue, const char* funcName);
	static bool luaValue2DataBlock(lua_State* L, int lo, SCDataBlock& outValue, const char* funcName);
	static bool luaValue2Value(lua_State* L, int lo, SCValue& outValue, const char* funcName);
	static bool luaValue2ValueArray(lua_State* L, int lo, std::vector<SCValue>& outValue, const char* funcName);
	static bool luaValue2Dictionary(lua_State* L, int lo, SCDictionary& outValue, const char* funcName);
	static bool luaValue2KVPair(lua_State* L, int lo, SCDictionary::SKVPair& outValue, const char* funcName);
	static bool luaValue2KVPairArray(lua_State* L, int lo, std::vector<SCDictionary::SKVPair>& outValue, const char* funcName);
	static bool luaValue2Role(lua_State* L, int lo, SCRole::Ptr& outValue, const char* funcName);
	static bool luaValue2Actor(lua_State* L, int lo, SCActor::Ptr& outValue, const char* funcName);
	static bool luaValue2Strategy(lua_State* L, int lo, SCStrategy::Ptr& outValue, const char* funcName);
	static bool luaValue2Behavior(lua_State* L, int lo, SCBehavior::Ptr& outValue, const char* funcName);
	static bool luaValue2MessageMatcher(lua_State* L, int lo, SCMessageMatcher::Ptr& outValue, const char* funcName);
	static bool luaValue2Message(lua_State* L, int lo, SCMessage::Ptr& outValue, const char* funcName);
	static bool luaValue2Object(lua_State* L, int lo, SCObject::Ptr& outValue, const char* funcName);
	static bool luaValue2Stage(lua_State* L, int lo, SCStage::Ptr& outValue, const char* funcName);
	static bool luaValue2ViewController(lua_State* L, int lo, SCViewController::Ptr& outValue, const char* funcName);
	static bool luaValue2Version(lua_State* L, int lo, SCVersion& outValue, const char* funcName);

	//static bool pushDictionary2LuaTable(lua_State* L,const SCDictionary& dic, const char* funcName);
	static bool pushArray2LuaStack(lua_State* L, const std::vector<SCValue>& array, const char* funcName);
	//static void pushStage2LuaStack(lua_State* L,SCStage* pStage);

private:
	static void startTable(lua_State* L);
	static bool insertTableField(lua_State* L,const int nIndex,const SCValue& value);
	static bool insertTableField(lua_State* L,const char* szKey,const SCValue& value);
};

NAMESPACE_SPEEDCC_END

#endif //__SPEEDCC__SCLUAUTILS_H__
