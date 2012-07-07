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
//-------------------------------------------------------------------------------------
    // configure
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->restoreConfig() || mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        /*mWindow = */mRoot->initialise(true, "TinyOgre Render Window");
    }
    else
    {
        //return false;
    }

	//////////////////////////////////////////////////////////////////////////
	// test
	Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();
	Ogre::SceneManager* mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	
	Ogre::Camera* mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);
	// Set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	// Create a light
	Ogre::Light* l = mSceneMgr->createLight("MainLight");
	l->setPosition(20,80,50);
}

scRenderer::~scRenderer(void)
{
	if (mRoot)
	{
		delete mRoot;
		mRoot = 0;
	}
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
