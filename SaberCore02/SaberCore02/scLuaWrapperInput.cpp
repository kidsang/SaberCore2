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
			.enum_("constants")
			[
				//----> MouseButtonID
				value("MB_Left", 0),
				value("MB_Right", 1),
				value("MB_Middle", 2),
				value("MB_Button3", 3),
				value("MB_Button4", 4),
				value("MB_Button5", 5),
				value("MB_Button6", 6),
				value("MB_Button7", 7)
				//<---- MouseButtonID
			]
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
			.enum_("constants")
			[
				value("KC_UNASSIGNED", 0),
				value("KC_ESCAPE", 1),
				value("KC_1", 2),
				value("KC_2", 3),
				value("KC_3", 4),
				value("KC_4", 5),
				value("KC_5", 6),
				value("KC_6", 7),
				value("KC_7", 8),
				value("KC_8", 9),
				value("KC_9", 10),
				value("KC_0", 11),
				value("KC_MINUS", 12),
				value("KC_EQUALS", 13),
				value("KC_BACK", 14),
				value("KC_TAB", 15),
				value("KC_Q", 16),
				value("KC_W", 17),
				value("KC_E", 18),
				value("KC_R", 19),
				value("KC_T", 20),
				value("KC_Y", 21),
				value("KC_U", 22),
				value("KC_I", 23),
				value("KC_O", 24),
				value("KC_P", 25),
				value("KC_LBRACKET", 26),
				value("KC_RBRACKET", 27),
				value("KC_RETURN", 28),
				value("KC_LCONTROL", 29),
				value("KC_A", 30),
				value("KC_S", 31),
				value("KC_D", 32),
				value("KC_F", 33),
				value("KC_G", 34),
				value("KC_H", 35),
				value("KC_J", 36),
				value("KC_K", 37),
				value("KC_L", 38),
				value("KC_SEMICOLON", 39),
				value("KC_APOSTROPHE", 40),
				value("KC_GRAVE", 41),
				value("KC_LSHIFT", 42),
				value("KC_BACKSLASH", 43),
				value("KC_Z", 44),
				value("KC_X", 45),
				value("KC_C", 46),
				value("KC_V", 47),
				value("KC_B", 48),
				value("KC_N", 49),
				value("KC_M", 50),
				value("KC_COMMA", 51),
				value("KC_PERIOD", 52),
				value("KC_SLASH", 53),
				value("KC_RSHIFT", 54),
				value("KC_MULTIPLY", 55),
				value("KC_LMENU", 56),
				value("KC_SPACE", 57),
				value("KC_CAPITAL", 58),
				value("KC_F1", 59),
				value("KC_F2", 60),
				value("KC_F3", 61),
				value("KC_F4", 62),
				value("KC_F5", 63),
				value("KC_F6", 64),
				value("KC_F7", 65),
				value("KC_F8", 66),
				value("KC_F9", 67),
				value("KC_F10", 68),
				value("KC_NUMLOCK", 69),
				value("KC_SCROLL", 70),
				value("KC_NUMPAD7", 71),
				value("KC_NUMPAD8", 72),
				value("KC_NUMPAD9", 73),
				value("KC_SUBTRACT", 74),
				value("KC_NUMPAD4", 75),
				value("KC_NUMPAD5", 76),
				value("KC_NUMPAD6", 77),
				value("KC_ADD", 78),
				value("KC_NUMPAD1", 79),
				value("KC_NUMPAD2", 80),
				value("KC_NUMPAD3", 81),
				value("KC_NUMPAD0", 82),
				value("KC_DECIMAL", 83),
				value("KC_OEM_102", 86),
				value("KC_F11", 87),
				value("KC_F12", 88),
				value("KC_F13", 100),
				value("KC_F14", 101),
				value("KC_F15", 102),
				value("KC_KANA", 112),
				value("KC_ABNT_C1", 115),
				value("KC_CONVERT", 121),
				value("KC_NOCONVERT", 123),
				value("KC_YEN", 125),
				value("KC_ABNT_C2", 126),
				value("KC_NUMPADEQUALS", 141),
				value("KC_PREVTRACK", 144),
				value("KC_AT", 145),
				value("KC_COLON", 146),
				value("KC_UNDERLINE", 147),
				value("KC_KANJI", 148),
				value("KC_STOP", 149),
				value("KC_AX", 150),
				value("KC_UNLABELED", 151),
				value("KC_NEXTTRACK", 153),
				value("KC_NUMPADENTER", 156),
				value("KC_RCONTROL", 157),
				value("KC_MUTE", 160),
				value("KC_CALCULATOR", 161),
				value("KC_PLAYPAUSE", 162),
				value("KC_MEDIASTOP", 164),
				value("KC_VOLUMEDOWN", 174),
				value("KC_VOLUMEUP", 176),
				value("KC_WEBHOME", 178),
				value("KC_NUMPADCOMMA", 179),
				value("KC_DIVIDE", 181),
				value("KC_SYSRQ", 183),
				value("KC_RMENU", 184),
				value("KC_PAUSE", 197),
				value("KC_HOME", 199),
				value("KC_UP", 200),
				value("KC_PGUP", 201),
				value("KC_LEFT", 203),
				value("KC_RIGHT", 205),
				value("KC_END", 207),
				value("KC_DOWN", 208),
				value("KC_PGDOWN", 209),
				value("KC_INSERT", 210),
				value("KC_DELETE", 211),
				value("KC_LWIN", 219),
				value("KC_RWIN", 220),
				value("KC_APPS", 221),
				value("KC_POWER", 222),
				value("KC_SLEEP", 223),
				value("KC_WAKE", 227),
				value("KC_WEBSEARCH", 229),
				value("KC_WEBFAVORITES", 230),
				value("KC_WEBREFRESH", 231),
				value("KC_WEBSTOP", 232),
				value("KC_WEBFORWARD", 233),
				value("KC_WEBBACK", 234),
				value("KC_MYCOMPUTER", 235),
				value("KC_MAIL", 236),
				value("KC_MEDIASELECT", 237)
				//<---- KeyCode
			]
		];
	//<<----include/OIS/OISKeyboard.h
}