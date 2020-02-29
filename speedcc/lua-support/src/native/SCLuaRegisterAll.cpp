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

#include "SCLuaRegisterAll.h"
#include "../../../base/SCObject.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

NAMESPACE_SPEEDCC_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

int lua_register_speedcc_SCObject(lua_State* tolua_S);
int lua_register_speedcc_SCDateTime(lua_State* tolua_S);
int lua_register_speedcc_SCDataBlock(lua_State* tolua_S);
int lua_register_speedcc_SCValue(lua_State* tolua_S);
int lua_register_speedcc_SCDictionary(lua_State* tolua_S);
int lua_register_speedcc_SCDateTimeDate(lua_State* tolua_S);
int lua_register_speedcc_SCPerformObject(lua_State* tolua_S);
int lua_register_speedcc_SCBehavior(lua_State* tolua_S);
int lua_register_speedcc_SCRole(lua_State* tolua_S);
int lua_register_speedcc_SCStage(lua_State* tolua_S);

void scLuaSupportRegisterAll(lua_State* tolua_S)
{
	tolua_open(tolua_S);

	tolua_module(tolua_S, "sc", 0);
	tolua_beginmodule(tolua_S, "sc");

		lua_register_speedcc_SCObject(tolua_S); // SCObject
		lua_register_speedcc_SCDateTime(tolua_S); // SCDateTime
		lua_register_speedcc_SCDataBlock(tolua_S); // SCDataBlock
		lua_register_speedcc_SCValue(tolua_S); // SCValue
		lua_register_speedcc_SCDictionary(tolua_S); // SCDictionary
		lua_register_speedcc_SCPerformObject(tolua_S); // SCPerformObject
		lua_register_speedcc_SCBehavior(tolua_S); // SCBehavior
		lua_register_speedcc_SCRole(tolua_S); // SCRole
		lua_register_speedcc_SCStage(tolua_S); // SCStage

	tolua_endmodule(tolua_S);
}

#ifdef __cplusplus
}
#endif

NAMESPACE_SPEEDCC_END