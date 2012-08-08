#include "scLuaWrapper.h"
#include "MyGUI/MyGUI.h"

void myguiExportDefines(lua_State* L);
void myguiExportInputs(lua_State*);
void myguiExportMangers(lua_State*);
void myguiExportWidgets(lua_State*);


void exportMyGuiWidget(lua_State* L)
{
	using namespace MyGUI;
	using namespace luabind;
	myguiExportDefines(L);
	myguiExportInputs(L);
	myguiExportMangers(L);
	myguiExportWidgets(L);
}

void myguiExportDefines(lua_State* L)
{
	using namespace luabind;
	using namespace MyGUI;
	module(L)
		[
			class_<VectorWidgetPtr>("VectorWidgetPtr"),
			class_<MapWidgetPtr>("MapWidgetPtr"),
			class_<EnumeratorWidgetPtr>("EnumeratorWidgetPtr")
		];
}

void myguiExportInputs(lua_State* L)
{
	using namespace luabind;
	using namespace MyGUI;
	//---->>include/MyGUI/MyGUI_KeyCode.h 
	module(L)
		[
			//--KeyCode
			class_<KeyCode>("KeyCode")
			.def(constructor<MyGUI::KeyCode::Enum>())
			.def("toValue", (int (KeyCode::*)())&KeyCode::toValue)
			//----> Enum
			.enum_("constants")
			[
				value("None", 0),
				value("Escape", 1),
				value("One", 2),
				value("Two", 3),
				value("Three", 4),
				value("Four", 5),
				value("Five", 6),
				value("Six", 7),
				value("Seven", 8),
				value("Eight", 9),
				value("Nine", 10),
				value("Zero", 11),
				value("Minus", 12),
				value("Equals", 13),
				value("Backspace", 14),
				value("Tab", 15),
				value("Q", 16),
				value("W", 17),
				value("E", 18),
				value("R", 19),
				value("T", 20),
				value("Y", 21),
				value("U", 22),
				value("I", 23),
				value("O", 24),
				value("P", 25),
				value("LeftBracket", 26),
				value("RightBracket", 27),
				value("Return", 28),
				value("LeftControl", 29),
				value("A", 30),
				value("S", 31),
				value("D", 32),
				value("F", 33),
				value("G", 34),
				value("H", 35),
				value("J", 36),
				value("K", 37),
				value("L", 38),
				value("Semicolon", 39),
				value("Apostrophe", 40),
				value("Grave", 41),
				value("LeftShift", 42),
				value("Backslash", 43),
				value("Z", 44),
				value("X", 45),
				value("C", 46),
				value("V", 47),
				value("B", 48),
				value("N", 49),
				value("M", 50),
				value("Comma", 51),
				value("Period", 52),
				value("Slash", 53),
				value("RightShift", 54),
				value("Multiply", 55),
				value("LeftAlt", 56),
				value("Space", 57),
				value("Capital", 58),
				value("F1", 59),
				value("F2", 60),
				value("F3", 61),
				value("F4", 62),
				value("F5", 63),
				value("F6", 64),
				value("F7", 65),
				value("F8", 66),
				value("F9", 67),
				value("F10", 68),
				value("NumLock", 69),
				value("ScrollLock", 70),
				value("Numpad7", 71),
				value("Numpad8", 72),
				value("Numpad9", 73),
				value("Subtract", 74),
				value("Numpad4", 75),
				value("Numpad5", 76),
				value("Numpad6", 77),
				value("Add", 78),
				value("Numpad1", 79),
				value("Numpad2", 80),
				value("Numpad3", 81),
				value("Numpad0", 82),
				value("Decimal", 83),
				value("OEM_102", 86),
				value("F11", 87),
				value("F12", 88),
				value("F13", 100),
				value("F14", 101),
				value("F15", 102),
				value("Kana", 112),
				value("ABNT_C1", 115),
				value("Convert", 121),
				value("NoConvert", 123),
				value("Yen", 125),
				value("ABNT_C2", 126),
				value("NumpadEquals", 141),
				value("PrevTrack", 144),
				value("At", 145),
				value("Colon", 146),
				value("Underline", 147),
				value("Kanji", 148),
				value("Stop", 149),
				value("AX", 150),
				value("Unlabeled", 151),
				value("NextTrack", 153),
				value("NumpadEnter", 156),
				value("RightControl", 157),
				value("Mute", 160),
				value("Calculator", 161),
				value("PlayPause", 162),
				value("MediaStop", 164),
				value("VolumeDown", 174),
				value("VolumeUp", 176),
				value("WebHome", 178),
				value("NumpadComma", 179),
				value("Divide", 181),
				value("SysRq", 183),
				value("RightAlt", 184),
				value("Pause", 197),
				value("Home", 199),
				value("ArrowUp", 200),
				value("PageUp", 201),
				value("ArrowLeft", 203),
				value("ArrowRight", 205),
				value("End", 207),
				value("ArrowDown", 208),
				value("PageDown", 209),
				value("Insert", 210),
				value("Delete", 211),
				value("LeftWindows", 219),
				value("RightWindow", 220),
				value("RightWindows", 220),
				value("AppMenu", 221),
				value("Power", 222),
				value("Sleep", 223),
				value("Wake", 227),
				value("WebSearch", 229),
				value("WebFavorites", 230),
				value("WebRefresh", 231),
				value("WebStop", 232),
				value("WebForward", 233),
				value("WebBack", 234),
				value("MyComputer", 235),
				value("Mail", 236),
				value("MediaSelect", 237)
			]
			//<---- Enum
		];
	//<<----include/MyGUI/MyGUI_KeyCode.h

	//---->>include/MyGUI/MyGUI_MouseButton.h 
	module(L)
		[
			//--MouseButton
			class_<MouseButton>("MouseButton")
			.def(constructor<MyGUI::MouseButton::Enum>())
			.def("toValue", (int (MouseButton::*)())&MouseButton::toValue)
			//----> Enum
			.enum_("constants")
			[
				value("None", -1),
				value("Left", 0),
				value("Right", 1),
				value("Middle", 2),
				value("Button0", 0),
				value("Button1", 1),
				value("Button2", 2),
				value("Button3", 3),
				value("Button4", 4),
				value("Button5", 5),
				value("Button6", 6),
				value("Button7", 7),
				value("MAX", 8)
			]
			//<---- Enum
		];
	//<<----include/MyGUI/MyGUI_MouseButton.h
}

void myguiExportWidgets(lua_State* L)
{
	using namespace luabind;
	using namespace MyGUI;

	//---->>include/MyGUI/MyGUI_Widget.h 
	module(L)
		[
			//--Widget
			class_<Widget>("Widget")
			.def("createWidgetT", (Widget* (Widget::*)(const std::string &,  const std::string &,  const IntCoord &,  MyGUI::Align,  const std::string &))&Widget::createWidgetT)
			.def("createWidgetT", (Widget* (Widget::*)(const std::string &,  const std::string &,  int,  int,  int,  int,  MyGUI::Align,  const std::string &))&Widget::createWidgetT)
			.def("createWidgetRealT", (Widget* (Widget::*)(const std::string &,  const std::string &,  const FloatCoord &,  MyGUI::Align,  const std::string &))&Widget::createWidgetRealT)
			.def("createWidgetRealT", (Widget* (Widget::*)(const std::string &,  const std::string &,  float,  float,  float,  float,  MyGUI::Align,  const std::string &))&Widget::createWidgetRealT)
			.def("createWidgetT", (Widget* (Widget::*)(MyGUI::WidgetStyle,  const std::string &,  const std::string &,  const IntCoord &,  MyGUI::Align,  const std::string &,  const std::string &))&Widget::createWidgetT)
			.def("setPosition", (void (Widget::*)(const IntPoint &))&Widget::setPosition)
			.def("setSize", (void (Widget::*)(const IntSize &))&Widget::setSize)
			.def("setCoord", (void (Widget::*)(const IntCoord &))&Widget::setCoord)
			.def("setPosition", (void (Widget::*)(int,  int))&Widget::setPosition)
			.def("setSize", (void (Widget::*)(int,  int))&Widget::setSize)
			.def("setCoord", (void (Widget::*)(int,  int,  int,  int))&Widget::setCoord)
			.def("setRealPosition", (void (Widget::*)(const FloatPoint &))&Widget::setRealPosition)
			.def("setRealSize", (void (Widget::*)(const FloatSize &))&Widget::setRealSize)
			.def("setRealCoord", (void (Widget::*)(const FloatCoord &))&Widget::setRealCoord)
			.def("setRealPosition", (void (Widget::*)(float,  float))&Widget::setRealPosition)
			.def("setRealSize", (void (Widget::*)(float,  float))&Widget::setRealSize)
			.def("setRealCoord", (void (Widget::*)(float,  float,  float,  float))&Widget::setRealCoord)
			.def("getName", (const std::string& (Widget::*)())&Widget::getName)
			.def("setVisible", (void (Widget::*)(bool))&Widget::setVisible)
			.def("getVisible", (bool (Widget::*)())&Widget::getVisible)
			.def("getInheritedVisible", (bool (Widget::*)())&Widget::getInheritedVisible)
			.def("setAlign", (void (Widget::*)(MyGUI::Align))&Widget::setAlign)
			.def("getAlign", (Align (Widget::*)())&Widget::getAlign)
			.def("setAlpha", (void (Widget::*)(float))&Widget::setAlpha)
			.def("getAlpha", (float (Widget::*)())&Widget::getAlpha)
			.def("setInheritsAlpha", (void (Widget::*)(bool))&Widget::setInheritsAlpha)
			.def("getInheritsAlpha", (bool (Widget::*)())&Widget::getInheritsAlpha)
			.def("setColour", (void (Widget::*)(const MyGUI::Colour &))&Widget::setColour)
			.def("isRootWidget", (bool (Widget::*)())&Widget::isRootWidget)
			.def("getParent", (Widget* (Widget::*)())&Widget::getParent)
			.def("getParentSize", (IntSize (Widget::*)())&Widget::getParentSize)
			.def("getEnumerator", (EnumeratorWidgetPtr (Widget::*)())&Widget::getEnumerator)
			.def("getChildCount", (size_t (Widget::*)())&Widget::getChildCount)
			.def("getChildAt", (Widget* (Widget::*)(size_t))&Widget::getChildAt)
			.def("findWidget", (Widget* (Widget::*)(const std::string &))&Widget::findWidget)
			.def("findWidgets", (void (Widget::*)(const std::string &,  VectorWidgetPtr &))&Widget::findWidgets)
			.def("setEnabled", (void (Widget::*)(bool))&Widget::setEnabled)
			.def("setEnabledSilent", (void (Widget::*)(bool))&Widget::setEnabledSilent)
			.def("getEnabled", (bool (Widget::*)())&Widget::getEnabled)
			.def("getInheritedEnabled", (bool (Widget::*)())&Widget::getInheritedEnabled)
			.def("getClientCoord", (IntCoord (Widget::*)())&Widget::getClientCoord)
			.def("getClientWidget", (Widget* (Widget::*)())&Widget::getClientWidget)
			.def("detachFromWidget", (void (Widget::*)(const std::string &))&Widget::detachFromWidget)
			.def("attachToWidget", (void (Widget::*)(MyGUI::Widget *,  MyGUI::WidgetStyle,  const std::string &))&Widget::attachToWidget)
			.def("changeWidgetSkin", (void (Widget::*)(const std::string &))&Widget::changeWidgetSkin)
			.def("setWidgetStyle", (void (Widget::*)(MyGUI::WidgetStyle,  const std::string &))&Widget::setWidgetStyle)
			.def("getWidgetStyle", (WidgetStyle (Widget::*)())&Widget::getWidgetStyle)
			.def("setProperty", (void (Widget::*)(const std::string &,  const std::string &))&Widget::setProperty)
		];
	//<<----include/MyGUI/MyGUI_Widget.h
	//---->>include/MyGUI/MyGUI_TextBox.h 
	module(L)
		[
			//--TextBox
			class_<TextBox, Widget>("TextBox")
			.def("getTextRegion", (IntCoord (TextBox::*)())&TextBox::getTextRegion)
			.def("getTextSize", (IntSize (TextBox::*)())&TextBox::getTextSize)
			.def("setCaption", (void (TextBox::*)(const MyGUI::UString &))&TextBox::setCaption)
			.def("getCaption", (const UString& (TextBox::*)())&TextBox::getCaption)
			.def("setFontName", (void (TextBox::*)(const std::string &))&TextBox::setFontName)
			.def("getFontName", (const std::string& (TextBox::*)())&TextBox::getFontName)
			.def("setFontHeight", (void (TextBox::*)(int))&TextBox::setFontHeight)
			.def("getFontHeight", (int (TextBox::*)())&TextBox::getFontHeight)
			.def("setTextAlign", (void (TextBox::*)(MyGUI::Align))&TextBox::setTextAlign)
			.def("getTextAlign", (Align (TextBox::*)())&TextBox::getTextAlign)
			.def("setTextColour", (void (TextBox::*)(const MyGUI::Colour &))&TextBox::setTextColour)
			.def("getTextColour", (const Colour& (TextBox::*)())&TextBox::getTextColour)
			.def("setCaptionWithReplacing", (void (TextBox::*)(const std::string &))&TextBox::setCaptionWithReplacing)
			.def("setTextShadowColour", (void (TextBox::*)(const MyGUI::Colour &))&TextBox::setTextShadowColour)
			.def("getTextShadowColour", (const Colour& (TextBox::*)())&TextBox::getTextShadowColour)
			.def("setTextShadow", (void (TextBox::*)(bool))&TextBox::setTextShadow)
			.def("getTextShadow", (bool (TextBox::*)())&TextBox::getTextShadow)
		];
	//<<----include/MyGUI/MyGUI_TextBox.h
	//---->>include/MyGUI/MyGUI_Button.h 
	module(L)
		[
			//--Button
			class_<Button, TextBox>("Button")
			.def("setStateSelected", (void (Button::*)(bool))&Button::setStateSelected)
			.def("getStateSelected", (bool (Button::*)())&Button::getStateSelected)
			.def("setModeImage", (void (Button::*)(bool))&Button::setModeImage)
			.def("getModeImage", (bool (Button::*)())&Button::getModeImage)
			.def("setImageResource", (void (Button::*)(const std::string &))&Button::setImageResource)
			.def("setImageGroup", (void (Button::*)(const std::string &))&Button::setImageGroup)
			.def("setImageName", (void (Button::*)(const std::string &))&Button::setImageName)
		];
	//<<----include/MyGUI/MyGUI_Button.h
	//---->>include/MyGUI/MyGUI_ImageBox.h 
	module(L)
		[
			//--ImageBox
			class_<ImageBox, Widget>("ImageBox")
			.def("setImageInfo", (void (ImageBox::*)(const std::string &,  const IntCoord &,  const IntSize &))&ImageBox::setImageInfo)
			.def("setImageTexture", (void (ImageBox::*)(const std::string &))&ImageBox::setImageTexture)
			.def("setImageRect", (void (ImageBox::*)(const IntRect &))&ImageBox::setImageRect)
			.def("setImageCoord", (void (ImageBox::*)(const IntCoord &))&ImageBox::setImageCoord)
			.def("setImageTile", (void (ImageBox::*)(const IntSize &))&ImageBox::setImageTile)
			.def("setImageIndex", (void (ImageBox::*)(size_t))&ImageBox::setImageIndex)
			.def("getImageIndex", (size_t (ImageBox::*)())&ImageBox::getImageIndex)
			.def("getItemCount", (size_t (ImageBox::*)())&ImageBox::getItemCount)
			.def("setItemSelect", (void (ImageBox::*)(size_t))&ImageBox::setItemSelect)
			.def("getItemSelect", (size_t (ImageBox::*)())&ImageBox::getItemSelect)
			.def("resetItemSelect", (void (ImageBox::*)())&ImageBox::resetItemSelect)
			.def("insertItem", (void (ImageBox::*)(size_t,  const IntCoord &))&ImageBox::insertItem)
			.def("addItem", (void (ImageBox::*)(const IntCoord &))&ImageBox::addItem)
			.def("setItem", (void (ImageBox::*)(size_t,  const IntCoord &))&ImageBox::setItem)
			.def("deleteItem", (void (ImageBox::*)(size_t))&ImageBox::deleteItem)
			.def("deleteAllItems", (void (ImageBox::*)())&ImageBox::deleteAllItems)
			.def("addItemFrame", (void (ImageBox::*)(size_t,  const IntCoord &))&ImageBox::addItemFrame)
			.def("insertItemFrame", (void (ImageBox::*)(size_t,  size_t,  const IntCoord &))&ImageBox::insertItemFrame)
			.def("addItemFrameDublicate", (void (ImageBox::*)(size_t,  size_t))&ImageBox::addItemFrameDublicate)
			.def("insertItemFrameDublicate", (void (ImageBox::*)(size_t,  size_t,  size_t))&ImageBox::insertItemFrameDublicate)
			.def("setItemFrame", (void (ImageBox::*)(size_t,  size_t,  const IntCoord &))&ImageBox::setItemFrame)
			.def("deleteItemFrame", (void (ImageBox::*)(size_t,  size_t))&ImageBox::deleteItemFrame)
			.def("deleteAllItemFrames", (void (ImageBox::*)(size_t))&ImageBox::deleteAllItemFrames)
			.def("setItemFrameRate", (void (ImageBox::*)(size_t,  float))&ImageBox::setItemFrameRate)
			.def("getItemFrameRate", (float (ImageBox::*)(size_t))&ImageBox::getItemFrameRate)
			.def("setItemResource", (bool (ImageBox::*)(const std::string &))&ImageBox::setItemResource)
			.def("setItemGroup", (void (ImageBox::*)(const std::string &))&ImageBox::setItemGroup)
			.def("setItemName", (void (ImageBox::*)(const std::string &))&ImageBox::setItemName)
			.def("setItemResourcePtr", (void (ImageBox::*)(ResourceImageSetPtr))&ImageBox::setItemResourcePtr)
			.def("setItemResourceInfo", (void (ImageBox::*)(const MyGUI::ImageIndexInfo &))&ImageBox::setItemResourceInfo)
			.def("getItemResource", (ResourceImageSetPtr (ImageBox::*)())&ImageBox::getItemResource)
			.def("setItemResourceInfo", (void (ImageBox::*)(ResourceImageSetPtr,  const std::string &,  const std::string &))&ImageBox::setItemResourceInfo)
		];
	//<<----include/MyGUI/MyGUI_ImageBox.h
}

MyGUI::LayoutManager* getLayoutManager()
{ return MyGUI::LayoutManager::getInstancePtr(); }

void myguiExportMangers(lua_State* L)
{
	using namespace luabind;
	using namespace MyGUI;

	//---->>include/MyGUI/MyGUI_Gui.h 
	module(L)
		[
			//--Gui
			class_<Gui>("Gui")
			.def("createWidgetT", (Widget* (Gui::*)(const std::string &,  const std::string &,  const IntCoord &,  MyGUI::Align,  const std::string &,  const std::string &))&Gui::createWidgetT)
			.def("createWidgetT", (Widget* (Gui::*)(const std::string &,  const std::string &,  int,  int,  int,  int,  MyGUI::Align,  const std::string &,  const std::string &))&Gui::createWidgetT)
			.def("createWidgetRealT", (Widget* (Gui::*)(const std::string &,  const std::string &,  const FloatCoord &,  MyGUI::Align,  const std::string &,  const std::string &))&Gui::createWidgetRealT)
			.def("createWidgetRealT", (Widget* (Gui::*)(const std::string &,  const std::string &,  float,  float,  float,  float,  MyGUI::Align,  const std::string &,  const std::string &))&Gui::createWidgetRealT)
			.def("destroyWidget", (void (Gui::*)(MyGUI::Widget *))&Gui::destroyWidget)
			.def("destroyWidgets", (void (Gui::*)(const VectorWidgetPtr &))&Gui::destroyWidgets)
			.def("destroyWidgets", (void (Gui::*)(EnumeratorWidgetPtr &))&Gui::destroyWidgets)
			.def("findWidgetT", (Widget* (Gui::*)(const std::string &,  bool))&Gui::findWidgetT)
			.def("findWidgetT", (Widget* (Gui::*)(const std::string &,  const std::string &,  bool))&Gui::findWidgetT)
			.def("destroyChildWidget", (void (Gui::*)(MyGUI::Widget *))&Gui::destroyChildWidget)
			.def("destroyAllChildWidget", (void (Gui::*)())&Gui::destroyAllChildWidget)
			.def("getEnumerator", (EnumeratorWidgetPtr (Gui::*)())&Gui::getEnumerator)
			.def("frameEvent", (void (Gui::*)(float))&Gui::frameEvent)
			.def_readonly("eventFrameStart", &Gui::eventFrameStart)
		];
	//<<----include/MyGUI/MyGUI_Gui.h
	//---->>include/MyGUI/MyGUI_LayoutManager.h 
	module(L)
		[
			//--LayoutManager
			class_<LayoutManager>("LayoutManager")
			.def("loadLayout", (VectorWidgetPtr (LayoutManager::*)(const std::string &,  const std::string &,  MyGUI::Widget *))&LayoutManager::loadLayout)
			.def("unloadLayout", (void (LayoutManager::*)(VectorWidgetPtr &))&LayoutManager::unloadLayout)
			.def("getByName", (ResourceLayout* (LayoutManager::*)(const std::string &,  bool))&LayoutManager::getByName)
			.def("isExist", (bool (LayoutManager::*)(const std::string &))&LayoutManager::isExist)
			.def("getCurrentLayout", (const std::string& (LayoutManager::*)())&LayoutManager::getCurrentLayout)
			.def_readonly("eventAddUserString", &LayoutManager::eventAddUserString)
		];
	//<<----include/MyGUI/MyGUI_LayoutManager.h

	//---->>Helper Func
	module(L)
		[
			def("getLayoutManager", getLayoutManager)
		];
	//<<----Helper Func
}