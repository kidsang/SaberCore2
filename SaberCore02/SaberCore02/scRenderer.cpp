#include "scRenderer.h"

scRenderer::scRenderer( string const& resourceCfgPath, string const& pluginCfgPath )
	: mRoot(0),mPlatform(0), mGui(0), mIsGuiInitialized(false)
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

void scRenderer::initializeGui( Ogre::SceneManager* mgr )
{
	scAssert(!mIsGuiInitialized, "GUI has already be initialized!");
	mPlatform->initialise(mRoot->getAutoCreatedWindow(), mgr);
	mGui->initialise();
	mIsGuiInitialized = true;
}

void scRenderer::shutdownGui()
{
	scAssert(mIsGuiInitialized, "GUI not initialized! You must first call initializeGui()");
	mGui->shutdown(); 
	mPlatform->shutdown();
	mIsGuiInitialized = false;
}
