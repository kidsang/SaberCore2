#include "scRenderer.h"
#include "scLuaWrapper.h"

scRenderer::scRenderer( string const& resourceCfgPath, string const& pluginCfgPath )
	: mRoot(0),mPlatform(0), mGui(0), mIsGuiInitialized(false), mGuiL(0)
{
	mRoot = new Ogre::Root(pluginCfgPath);

//-------------------------------------------------------------------------------------
    // set up resources
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(resourceCfgPath);
 
    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
 
    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }

	// 显示配置窗口
	// TODO: 改成自己的配置窗口
    if(!mRoot->restoreConfig())
		mRoot->showConfigDialog();

	// 创建窗口
	mRoot->initialise(true, "TinyOgre Render Window");

	// 默认mipmap数量为5
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// 初始化所有资源(并非load进内存)
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//--------------------------
	//MyGUI
	mPlatform = new MyGUI::OgrePlatform();
	mGui = new MyGUI::Gui();
}

scRenderer::~scRenderer(void)
{
	if (mGui)
	{ delete mGui; mGui = 0; }
	if (mPlatform)
	{ delete mPlatform; mPlatform = 0; }
	if (mRoot)
	{ delete mRoot; mRoot = 0; }
}

bool scRenderer::_run( u32 dtms )
{
	Ogre::WindowEventUtilities::messagePump();
	// 显示FPS
	HWND hwnd;
	Ogre::RenderWindow* window = mRoot->getAutoCreatedWindow();
	window->getCustomAttribute("WINDOW", (void*)&hwnd);
	char buff[64];
	sprintf(buff, "FPS: %f", window->getLastFPS());
	SetWindowTextA(hwnd, buff);
	return mRoot->renderOneFrame((float)dtms / 1000.f);
}

template<> scRenderer* Ogre::Singleton<scRenderer>::ms_Singleton = 0;
scRenderer& scRenderer::getSingleton( void )
{
	assert(ms_Singleton); return (*ms_Singleton);
}
scRenderer* scRenderer::getSingletonPtr( void )
{
	return ms_Singleton;
}

void scRenderer::initializeGui(Ogre::SceneManager* mgr, string const& callbackScript, string const& registerScript)
{
	scAssert(!mIsGuiInitialized, "GUI has already be initialized!");
	mPlatform->initialise(mRoot->getAutoCreatedWindow(), mgr);
	mGui->initialise();

	try
	{
		using namespace luabind;
		mGuiL = lua_open();
		luaL_openlibs(mGuiL);
		luabind::open(mGuiL);

		exportScError(mGuiL);
		exportMyGuiWidget(mGuiL);

		int err;
		err = luaL_dofile(mGuiL, callbackScript.c_str());
		if (err) throw luabind::error(mGuiL);
		err = luaL_dofile(mGuiL, registerScript.c_str());
		if (err) throw luabind::error(mGuiL);
	}
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
	mIsGuiInitialized = true;
}

void scRenderer::shutdownGui()
{
	scAssert(mIsGuiInitialized, "GUI not initialized! You must first call initializeGui()");
	if (mGuiL)
	{ lua_close(mGuiL); mGuiL = 0; }
	mGui->shutdown(); 
	mPlatform->shutdown();
	mIsGuiInitialized = false;
}

void scRenderer::registerGuiEvent(string const& widgetName, GuiEventType eventType, string const& callbackName)
{
	using namespace MyGUI;
	Widget* widget = mGui->findWidgetT(widgetName);
	
	switch (eventType)
	{
	case UI_KEY_GET_FOCUS:
		widget->eventKeySetFocus += newDelegate(this, &scRenderer::onGuiKeyGetFocus);
		break;
	case UI_KEY_LOSE_FOCUS:
		widget->eventKeyLostFocus += newDelegate(this, &scRenderer::onGuiKeyLoseFocus);
		break;
	case UI_KEY_PRESSED:
		widget->eventKeyButtonPressed += newDelegate(this, &scRenderer::onGuiKeyPressed);
		break;
	case UI_KEY_RELEASED:
		widget->eventKeyButtonReleased += newDelegate(this, &scRenderer::onGuiKeyReleased);
		break;
	case UI_MOUSE_GET_FOCUS:
		widget->eventMouseSetFocus += newDelegate(this, &scRenderer::onGuiMouseGetFocus);
		break;
	case UI_MOUSE_LOSE_FOCUS:
		widget->eventMouseLostFocus += newDelegate(this, &scRenderer::onGuiMouseLoseFocus);
		break;
	case UI_MOUSE_MOVE:
		widget->eventMouseMove += newDelegate(this, &scRenderer::onGuiMouseMove);
		break;
	case UI_MOUSE_WHEEL:
		widget->eventMouseWheel += newDelegate(this, &scRenderer::onGuiMouseWheel);
		break;
	case UI_MOUSE_DRAG:
		widget->eventMouseDrag += newDelegate(this, &scRenderer::onGuiMouseDrag);
		break;
	case UI_MOUSE_PRESSED:
		widget->eventMouseButtonPressed += newDelegate(this, &scRenderer::onGuiMousePressed);
		break;
	case UI_MOUSE_RELEASED:
		widget->eventMouseButtonReleased += newDelegate(this, &scRenderer::onGuiMouseReleased);
		break;
	case UI_MOUSE_CLICK:
		widget->eventMouseButtonClick += newDelegate(this, &scRenderer::onGuiMouseClick);
		break;
	case UI_MOUSE_DOUBLE_CLICK:
		widget->eventMouseButtonDoubleClick += newDelegate(this, &scRenderer::onGuiMouseDoubleClick);
		break;
	default:
		scAssert(0, "Gui event type do not exist!");
	}

	string name = widgetName + scToString(eventType);
	scAssert(mUIEventCallbackMap.find(name) == mUIEventCallbackMap.end(), "UI widget " + widgetName + "has already register event " + scToString(eventType));
	mUIEventCallbackMap.insert(std::make_pair(name, callbackName));
}

void scRenderer::onGuiMouseMove( MyGUI::Widget* sender, int left, int top )
{
	string cb = findWidgetCallback(sender->getName(), UI_MOUSE_MOVE);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, left, top);	}
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiMousePressed( MyGUI::Widget* sender, int left, int top, MyGUI::MouseButton id )
{
	string cb = findWidgetCallback(sender->getName(), UI_MOUSE_PRESSED);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, left, top, id); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiMouseReleased( MyGUI::Widget* sender, int left, int top, MyGUI::MouseButton id )
{
	string cb = findWidgetCallback(sender->getName(), UI_MOUSE_RELEASED);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, left, top, id); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiMouseClick( MyGUI::Widget* sender )
{
	string cb = findWidgetCallback(sender->getName(), UI_MOUSE_CLICK);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiMouseDoubleClick( MyGUI::Widget* sender )
{
	string cb = findWidgetCallback(sender->getName(), UI_MOUSE_DOUBLE_CLICK);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiKeyPressed( MyGUI::Widget* sender, MyGUI::KeyCode key, MyGUI::Char ch )
{
	string cb = findWidgetCallback(sender->getName(), UI_KEY_PRESSED);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, key, ch); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiKeyReleased( MyGUI::Widget* sender, MyGUI::KeyCode key )
{
	string cb = findWidgetCallback(sender->getName(), UI_KEY_RELEASED);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, key); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiKeyGetFocus( MyGUI::Widget* sender, MyGUI::Widget* old )
{
	string cb = findWidgetCallback(sender->getName(), UI_KEY_GET_FOCUS);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, old); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiKeyLoseFocus( MyGUI::Widget* sender, MyGUI::Widget* _new )
{
	string cb = findWidgetCallback(sender->getName(), UI_KEY_LOSE_FOCUS);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, _new); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiMouseGetFocus( MyGUI::Widget* sender, MyGUI::Widget* old )
{
	string cb = findWidgetCallback(sender->getName(), UI_MOUSE_GET_FOCUS);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, old); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiMouseLoseFocus( MyGUI::Widget* sender, MyGUI::Widget* _new )
{
	string cb = findWidgetCallback(sender->getName(), UI_MOUSE_LOSE_FOCUS);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, _new); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiMouseWheel( MyGUI::Widget* sender, int rel )
{
	string cb = findWidgetCallback(sender->getName(), UI_MOUSE_WHEEL);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, rel); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scRenderer::onGuiMouseDrag( MyGUI::Widget* sender, int left, int top, MyGUI::MouseButton id )
{
	string cb = findWidgetCallback(sender->getName(), UI_MOUSE_DRAG);
	try
	{ luabind::call_function<void>(mGuiL, cb.c_str(), sender, left, top, id); }
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

