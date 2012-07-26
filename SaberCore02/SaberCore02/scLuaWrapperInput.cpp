/*
 * time: 2012/07/26
 * author: kid
 */

#include "scLuaWrapper.h"
#include "ois/OIS.h"
#include "scInputManager.h"

void exportOISMouseEvent( lua_State* L )
{
	using namespace luabind;
	using namespace OIS;

	//---->>include/OIS/OISPrereqs.h 
	module(L)
		[
			//--Axis
			class_<Axis>("Axis")
			.def(constructor<>())
			.def("clear", (void (Axis::*)())&Axis::clear)
			.def_readwrite("abs", &Axis::abs)
			.def_readwrite("rel", &Axis::rel)
			.def_readwrite("absOnly", &Axis::absOnly)
		];
	//<<----include/OIS/OISPrereqs.h
	//---->>include/OIS/OISMouse.h 
	module(L)
		[
			//--MouseEvent
			class_<scMouseEventWrapper>("MouseEvent")
			.def(constructor<OIS::MouseState>())
			.def_readonly("state", &scMouseEventWrapper::state)
			,
			//--MouseState
			class_<MouseState>("MouseState")
			.def(constructor<>())
			.def("buttonDown", (bool (MouseState::*)(OIS::MouseButtonID))&MouseState::buttonDown)
			.def("clear", (void (MouseState::*)())&MouseState::clear)
			.def_readonly("width", &MouseState::width)
			.def_readonly("height", &MouseState::height)
			.def_readonly("X", &MouseState::X)
			.def_readonly("Y", &MouseState::Y)
			.def_readonly("Z", &MouseState::Z)
			.def_readonly("buttons", &MouseState::buttons)
		];
	//<<----include/OIS/OISMouse.h
}

void exportOISKeyboardEvent(lua_State* L)
{
	using namespace luabind;
	using namespace OIS;

	//---->>include/OIS/OISKeyboard.h 
	module(L)
		[
			//--KeyEvent
			class_<KeyEvent>("KeyEvent")
			.def(constructor<OIS::Object *,  OIS::KeyCode,  unsigned int>())
			.def_readonly("key", &KeyEvent::key)
			.def_readonly("text", &KeyEvent::text)
		];
	//<<----include/OIS/OISKeyboard.h
}