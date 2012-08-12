#ifndef luaVectorWrapper_h__
#define luaVectorWrapper_h__

/*
* time: 2012/07/18
* author: kid
*/

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include "scTypeDefine.h"

/// 辅助方法，输出lua错误信息
void scPrintLuaError(luabind::error& e);
/// 辅助方法，查找对应名称脚本的路径
string const getScriptPath(string const& name);

void exportScError(lua_State* L);
void exportScEvent(lua_State* L);
void exportScAnimation(lua_State* L);
void exportScTimeLine(lua_State* L);
void exportOgreMath(lua_State* L);
void exportOgreCamera(lua_State* L);
void exportOISMouseEvent(lua_State* L);
void exportOISKeyboardEvent(lua_State* L);
void exportMyGuiWidget(lua_State* L);


#endif // luaVectorWrapper_h__
