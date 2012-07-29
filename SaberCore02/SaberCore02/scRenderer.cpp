#include "scRenderer.h"
#include "scUtils.h"
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

		int err;
		err = luaL_dofile(mGuiL, callbackScript.c_str());
		if (err) throw luabind::error(mGuiL);
		err = luaL_dofile(mGuiL, registerScript.c_str());
		if (err) throw luabind::error(mGuiL);
	}
	catch (luabind::error& e)
	{
		scPrintLuaError(e);
	}
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

void scRenderer::onGuiMousePressed( MyGUI::Widget* sender, int left, int top, MyGUI::MouseButton id )
{
	string name = sender->getName() + scToString(UI_MOUSE_PRESSED);
	auto iter = mUIEventCallbackMap.find(name);
	scAssert(iter != mUIEventCallbackMap.end(), "UI widget " + sender->getName() + "did not register event " + scToString(UI_MOUSE_PRESSED));
	scAssert(mGuiL, "Gui lua state not initialized!");
	try
	{
		using namespace luabind;
		//call_function<void>(mGuiL, iter->second.c_str(), scMouseEventWrapper(arg.state));
	}
	catch (luabind::error& e)
	{
		scPrintLuaError(e);
	}
}

void scRenderer::onGuiMouseReleased( MyGUI::Widget* sender, int left, int top, MyGUI::MouseButton id )
{
	string name = sender->getName() + scToString(UI_MOUSE_RELEASED);
	auto iter = mUIEventCallbackMap.find(name);
	scAssert(iter != mUIEventCallbackMap.end(), "UI widget " + sender->getName() + "did not register event " + scToString(UI_MOUSE_RELEASED));
	scErrMsg("Gui Mouse Released" + iter->second);
}

void scRenderer::onGuiMouseClick( MyGUI::Widget* sender )
{
	string name = sender->getName() + scToString(UI_MOUSE_CLICK);
	auto iter = mUIEventCallbackMap.find(name);
	scAssert(iter != mUIEventCallbackMap.end(), "UI widget " + sender->getName() + "did not register event " + scToString(UI_MOUSE_CLICK));
	scErrMsg("Gui Mouse Click" + iter->second);
}

void scRenderer::onGuiMouseDoubleClick( MyGUI::Widget* sender )
{
	string name = sender->getName() + scToString(UI_MOUSE_DOUBLE_CLICK);
	auto iter = mUIEventCallbackMap.find(name);
	scAssert(iter != mUIEventCallbackMap.end(), "UI widget " + sender->getName() + "did not register event " + scToString(UI_MOUSE_DOUBLE_CLICK));
	scErrMsg("Gui Mouse Double Click" + iter->second);
}
