#include "scServerGameWorld.h"


scServerGameWorld::scServerGameWorld(string const& worldName, string const& mapName)
	: scGameWorld(worldName), mMapName(mapName)
{
}


scServerGameWorld::~scServerGameWorld(void)
{
}

void scServerGameWorld::initialize()
{
	scGameWorld::initialize();
	//////////////////////////////////////////////////////////////////////////
	// test
	Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();
	Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();
	
	Ogre::Camera* mCamera = mSceneManager->createCamera("PlayerCam");
	mCameras.insert(std::make_pair("test", mCamera));
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(1);
	mCamera->setAutoAspectRatio(true);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	//vp = mWindow->addViewport(mCamera, 1, 0.5f, .5f, .5f, .5f);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//////////////////////////////////////////////////////////////////////////
	// 以下的应该移动至GameArea
	//Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	//Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//headNode->attachObject(ogreHead);
	//// Set ambient light
	//mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	//// Create a light
	//Ogre::Light* l = mSceneMgr->createLight("MainLight");
	//l->setPosition(20,80,50);
	

	// test static geometry
	Ogre::Entity* ogreHead = mSceneManager->createEntity("Head", "ogrehead.mesh");
	Ogre::StaticGeometry* sg = mSceneManager->createStaticGeometry("Heads");
	sg->addEntity(ogreHead, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY, Ogre::Vector3(0.1f));
	sg->build();
}

void scServerGameWorld::release()
{
	scGameWorld::release();
}

bool scServerGameWorld::_run( u32 dtms )
{
	scGameWorld::_run(dtms);
	return true;
}
