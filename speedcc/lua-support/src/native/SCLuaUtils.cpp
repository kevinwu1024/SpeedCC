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

#include "SCLuaUtils.h"
#include "../../../base/SCBaseMacros.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

//#include "scripting/lua-bindings/manual/tolua_fix.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

bool SCLuaUtils::luaValue2String(lua_State* L, int lo, SCString& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_iscppstring(L, lo, 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}


	size_t size;
	auto rawString = lua_tolstring(L, lo, &size);
	outValue = SCString(rawString, size);

	return true;
}

bool SCLuaUtils::luaValue2DateTime(lua_State* L, int lo, SCDateTime& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCDateTime", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SCDateTime*)tolua_tousertype(L, lo, 0);
	outValue = *cobj;
	
	return true;
}

bool SCLuaUtils::luaValue2Date(lua_State* L, int lo, SCDateTime::Date& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCDateTime.Date", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SCDateTime::Date*)tolua_tousertype(L, lo, 0);
	outValue = *cobj;

	return true;
}

bool SCLuaUtils::luaValue2Time(lua_State* L, int lo, SCDateTime::Time& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCDateTime.Time", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SCDateTime::Time*)tolua_tousertype(L, lo, 0);
	outValue = *cobj;

	return true;
}

bool SCLuaUtils::luaValue2DataBlock(lua_State* L, int lo, SCDataBlock& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCDataBlock", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SCDataBlock*)tolua_tousertype(L, lo, 0);
	outValue = *cobj;

	return true;
}

bool SCLuaUtils::luaValue2Value(lua_State* L, int lo, SCValue& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCValue", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SCValue*)tolua_tousertype(L, lo, 0);
	outValue = *cobj;

	return true;
}

bool SCLuaUtils::luaValue2Dictionary(lua_State* L, int lo, SCDictionary& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCDictionary", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SCDictionary*)tolua_tousertype(L, lo, 0);
	outValue = *cobj;

	return true;
}

bool SCLuaUtils::luaValue2ValueArray(lua_State* L, int lo, std::vector<SCValue>& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_istable(L, lo, 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	size_t len = lua_objlen(L, lo);
	for (size_t i = 0; i < len; i++)
	{
		lua_pushnumber(L, i + 1);
		lua_gettable(L, lo);
		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);
			break;
		}

		if (!tolua_isusertype(L, -1, "sc.SCValue", 0, &tolua_err))
		{
#if COCOS2D_DEBUG >=1
			luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
			lua_pop(L, 1);
			break;
		}

		auto cobj = (SCValue*)tolua_tousertype(L, -1, 0);
		outValue.push_back(*cobj);

		lua_pop(L, 1);
	}

	return true;
}

bool SCLuaUtils::luaValue2KVPair(lua_State* L, int lo, SCDictionary::SKVPair& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_istable(L, lo, 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	bool bRet = true;

	lua_pushstring(L, "key");  
	lua_gettable(L, lo);
	outValue.strKey = lua_isnil(L, -1) ? "" : lua_tostring(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "value");
	lua_gettable(L, lo);
	if (lua_isnil(L, -1))
	{
		outValue.value = SCValue();
	}
	else
	{
		bRet = SCLuaUtils::luaValue2Value(L, -1, outValue.value, funcName);
	}
	lua_pop(L, 1);

	return bRet;
}

bool SCLuaUtils::luaValue2KVPairArray(lua_State* L, int lo, std::vector<SCDictionary::SKVPair>& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_istable(L, lo, 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	SCDictionary::SKVPair pair;
	size_t len = lua_objlen(L, lo);
	for (size_t i = 0; i < len; i++)
	{
		lua_pushnumber(L, i + 1);
		lua_gettable(L, lo);
		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);
			continue;
		}

		if(!tolua_istable(L, -1, 0, &tolua_err))
		{
#if COCOS2D_DEBUG >=1
			luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
			lua_pop(L, 1);
			continue;
		}

		bool bRet = true;

		lua_pushstring(L, "key");
		lua_gettable(L, lo);
		pair.strKey = lua_isnil(L, -1) ? "" : lua_tostring(L, -1);
		lua_pop(L, 1);

		lua_pushstring(L, "value");
		lua_gettable(L, lo);
		if (lua_isnil(L, -1))
		{
			pair.value = SCValue();
		}
		else
		{
			bRet = SCLuaUtils::luaValue2Value(L, -1, pair.value, funcName);
		}

		lua_pop(L, 1);

		SC_RETURN_IF(false, !bRet);

		outValue.push_back(pair);
	}

	return true;
}

bool SCLuaUtils::luaValue2Object(lua_State* L, int lo, SCObject::Ptr& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCObject", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SLuaObjectContainer*)tolua_tousertype(L, lo, 0);
	if (cobj)
	{
		luaL_error(L, "user type pointer is null in %s\n ", funcName);
		return false;
	}
	outValue = cobj->ptrObj.cast<SCObject::Ptr>();

	return true;
}

bool SCLuaUtils::luaValue2Role(lua_State* L, int lo, SCRole::Ptr& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCRole", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SLuaObjectContainer*)tolua_tousertype(L, lo, 0);
	if (cobj)
	{
		luaL_error(L, "user type pointer is null in %s\n ", funcName);
		return false;
	}
	outValue = cobj->ptrObj.cast<SCRole::Ptr>();

	return true;
}

bool SCLuaUtils::luaValue2Actor(lua_State* L, int lo, SCActor::Ptr& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCActor", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SLuaObjectContainer*)tolua_tousertype(L, lo, 0);
	if (cobj)
	{
		luaL_error(L, "user type pointer is null in %s\n ", funcName);
		return false;
	}
	outValue = cobj->ptrObj.cast<SCActor::Ptr>();

	return true;
}

bool SCLuaUtils::luaValue2Strategy(lua_State* L, int lo, SCStrategy::Ptr& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCStrategy", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SLuaObjectContainer*)tolua_tousertype(L, lo, 0);
	if (cobj)
	{
		luaL_error(L, "user type pointer is null in %s\n ", funcName);
		return false;
	}
	outValue = cobj->ptrObj.cast<SCStrategy::Ptr>();

	return true;
}

bool SCLuaUtils::luaValue2Behavior(lua_State* L, int lo, SCBehavior::Ptr& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCBehavior", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SLuaObjectContainer*)tolua_tousertype(L, lo, 0);
	if (cobj)
	{
		luaL_error(L, "user type pointer is null in %s\n ", funcName);
		return false;
	}
	outValue = cobj->ptrObj.cast<SCBehavior::Ptr>();

	return true;
}

bool SCLuaUtils::luaValue2MessageMatcher(lua_State* L, int lo, SCMessageMatcher::Ptr& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCMessageMatcher", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SMessageMatchContainer*)tolua_tousertype(L, lo, 0);
	SC_RETURN_IF(cobj == nullptr, false);
	outValue = cobj->ptrObj.cast<SCMessageMatcher::Ptr>();

	return true;
}

bool SCLuaUtils::luaValue2Message(lua_State* L, int lo, SCMessage::Ptr& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCMessage", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SLuaObjectContainer*)tolua_tousertype(L, lo, 0);
	if (cobj)
	{
		luaL_error(L, "user type pointer is null in %s\n ", funcName);
		return false;
	}
	outValue = cobj->ptrObj.cast<SCMessage::Ptr>();

	return true;
}

bool SCLuaUtils::luaValue2Stage(lua_State* L, int lo, SCStage::Ptr& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCStage", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SLuaObjectContainer*)tolua_tousertype(L, lo, 0);
	if (cobj)
	{
		luaL_error(L, "user type pointer is null in %s\n ", funcName);
		return false;
	}
	outValue = cobj->ptrObj.cast<SCStage::Ptr>();

	return true;
}

bool SCLuaUtils::luaValue2ViewController(lua_State* L, int lo, SCViewController::Ptr& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCViewController", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SLuaObjectContainer*)tolua_tousertype(L, lo, 0);
	if (cobj)
	{
		luaL_error(L, "user type pointer is null in %s\n ", funcName);
		return false;
	}
	outValue = cobj->ptrObj.cast<SCViewController::Ptr>();

	return true;
}

bool SCLuaUtils::luaValue2Version(lua_State* L, int lo, SCVersion& outValue, const char* funcName)
{
	SC_RETURN_IF(NULL == L, false);

	tolua_Error tolua_err;
	if (!tolua_isusertype(L, lo, "sc.SCViewController", 0, &tolua_err))
	{
#if COCOS2D_DEBUG >=1
		luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
		return false;
	}

	auto cobj = (SCVersion*)tolua_tousertype(L, lo, 0);
	if (cobj)
	{
		luaL_error(L, "user type pointer is null in %s\n ", funcName);
		return false;
	}
	outValue = *cobj;

	return true;
}

/*
bool SCLuaUtils::pushDictionary2LuaTable(lua_State* L, const SCDictionary& dic, const char* funcName)
{
	SCLuaUtils::startTable(L);
	
	dic.forEach([=](const SCString& strKey, const SCValue& value) -> bool
	{
		SCLuaUtils::insertTableField(L,strKey.c_str(), value);
		return true;
	});
	return true;
}
*/

bool SCLuaUtils::pushArray2LuaStack(lua_State* L, const std::vector<SCValue>& array, const char* funcName)
{
	SCLuaUtils::startTable(L);

	for (size_t i = 0; i < array.size(); i++)
	{
		SCLuaUtils::insertTableField(L, i + 1, array[i]);
	}

	return true;
}

//void SCLuaUtils::pushStage2LuaStack(lua_State* L, SCStage* pStage)
//{
//	SCASSERT(pStage!=nullptr);
//
//	auto obj = SCMemAllocator::newObject<SLuaObjectContainer>();
//	obj->pWeakObj = pStage;
//	tolua_pushusertype_and_takeownership(L, (void*)obj, "sc.SCStage");
//}

void SCLuaUtils::startTable(lua_State* L)
{
	lua_newtable(L);
}

bool SCLuaUtils::insertTableField(lua_State* L, const char* szKey, const SCValue& value)
{
	switch (value.getByte())
	{
	case SCValue::EType::kTypeArray:
	{
		lua_pushstring(L, szKey);

		const auto array = value.getArray();
		for (size_t i = 0; i < array.size(); i++)
		{
			SCLuaUtils::insertTableField(L, i + 1, array[i]);
		}
	}
	break;

	case SCValue::EType::kTypeChar:
	{
		lua_pushstring(L, szKey);
		lua_pushinteger(L, value.getChar());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeInt:
	{
		lua_pushstring(L, szKey);
		lua_pushinteger(L, value.getInt());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeByte:
	{
		lua_pushstring(L, szKey);
		lua_pushinteger(L, value.getByte());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeUInt:
	{
		lua_pushstring(L, szKey);
		lua_pushnumber(L, value.getUnsignedInt());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeLong:
	{
		lua_pushstring(L, szKey);
		lua_pushnumber(L, value.getLong());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeInt64:
	{
		lua_pushstring(L, szKey);
		lua_pushnumber(L, value.getInt64());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeFloat:
	{
		lua_pushstring(L, szKey);
		lua_pushnumber(L, value.getFloat());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeDouble:
	{
		lua_pushstring(L, szKey);
		lua_pushnumber(L, value.getDouble());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeString:
	{
		lua_pushstring(L, szKey);
		lua_pushstring(L, value.getString());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeDateTime:
	{
		lua_pushstring(L, szKey);
		auto obj = SCMemAllocator::newObject<SCDateTime>();
		*obj = value.getDateTime();
		tolua_pushusertype_and_takeownership(L, (void*)obj, "sc.SCDateTime");
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeDataBlock:
	{
		lua_pushstring(L, szKey);
		auto obj = SCMemAllocator::newObject<SCDataBlock>();
		*obj = value.getDataBlock();
		tolua_pushusertype_and_takeownership(L, (void*)obj, "sc.SCDataBlock");
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeDictionary:
	{
		lua_pushstring(L, szKey);
		auto dic = value.getDictionary();
		dic.forEach([=](const SCString& strKey, const SCValue& value) -> bool
		{
			SCLuaUtils::insertTableField(L, strKey.c_str(), value);
			return true;
		});

		return true;
	}
	break;
	}

	return false;
}

bool SCLuaUtils::insertTableField(lua_State* L, const int nIndex, const SCValue& value)
{
	switch (value.getByte())
	{
	case SCValue::EType::kTypeArray:
	{
		lua_pushinteger(L, nIndex);
		const auto array = value.getArray();
		for (size_t i = 0; i < array.size(); i++)
		{
			SCLuaUtils::insertTableField(L, i + 1, array[i]);
		}
	}
	break;

	case SCValue::EType::kTypeChar:
	{
		lua_pushinteger(L, nIndex);
		lua_pushinteger(L, value.getChar());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeInt:
	{
		lua_pushinteger(L, nIndex);
		lua_pushinteger(L, value.getInt());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeByte:
	{
		lua_pushinteger(L, nIndex);
		lua_pushinteger(L, value.getByte());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeUInt:
	{
		lua_pushinteger(L, nIndex);
		lua_pushnumber(L, value.getUnsignedInt());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeLong:
	{
		lua_pushinteger(L, nIndex);
		lua_pushnumber(L, value.getLong());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeInt64:
	{
		lua_pushinteger(L, nIndex);
		lua_pushnumber(L, value.getInt64());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeFloat:
	{
		lua_pushinteger(L, nIndex);
		lua_pushnumber(L, value.getFloat());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeDouble:
	{
		lua_pushinteger(L, nIndex);
		lua_pushnumber(L, value.getDouble());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeString:
	{
		lua_pushinteger(L, nIndex);
		lua_pushstring(L, value.getString());
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeDateTime:
	{
		lua_pushinteger(L, nIndex);
		auto obj = SCMemAllocator::newObject<SCDateTime>();
		*obj = value.getDateTime();
		tolua_pushusertype_and_takeownership(L, (void*)obj, "sc.SCDateTime");
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeDataBlock:
	{
		lua_pushinteger(L, nIndex);
		auto obj = SCMemAllocator::newObject<SCDataBlock>();
		*obj = value.getDataBlock();
		tolua_pushusertype_and_takeownership(L, (void*)obj, "sc.SCDataBlock");
		lua_settable(L, -3);
		return true;
	}
	break;

	case SCValue::EType::kTypeDictionary:
	{
		lua_pushinteger(L,nIndex);
		auto dic = value.getDictionary();
		dic.forEach([=](const SCString& strKey, const SCValue& value) -> bool
		{
			SCLuaUtils::insertTableField(L, strKey.c_str(), value);
			return true;
		});

		return true;
	}
	break;
	}

	return false;
}


NAMESPACE_SPEEDCC_END