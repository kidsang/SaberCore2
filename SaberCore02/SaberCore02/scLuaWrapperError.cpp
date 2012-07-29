#include "scLuaWrapper.h"
#include "scError.h"


void scErrMsgWrapper(string const& str)
{
	scErrMsg(str);
}

void scPrintLuaError(luabind::error& e)
{
	scErrMsg("---------------------------------------------");
	scErrMsg(e.what());
	scErrMsg(lua_tostring(e.state(), -1));
	scErrMsg("---------------------------------------------");
}
	

void exportScError(lua_State* L)
{
	using namespace luabind;
	module(L)
		[
			def("scErrMsg", scErrMsgWrapper)
		];
}