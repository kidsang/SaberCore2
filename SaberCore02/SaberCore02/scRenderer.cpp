#include "scRenderer.h"
#include <assert.h>


scRenderer::scRenderer( string const& resourceCfgPath, string const& pluginCfgPath )
	: mRoot(0)
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

	// ��ʾ���ô���
	// TODO: �ĳ��Լ������ô���
    if(!mRoot->restoreConfig())
		mRoot->showConfigDialog();

	// ��������
	mRoot->initialise(true, "TinyOgre Render Window");

	// Ĭ��mipmap����Ϊ5
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// ��ʼ��������Դ(����load���ڴ�)
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

scRenderer::~scRenderer(void)
{
	if (mRoot)
	{
		delete mRoot;
		mRoot = 0;
	}
}

bool scRenderer::_run( u32 dtms )
{
	Ogre::WindowEventUtilities::messagePump();
	// ��ʾFPS
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
