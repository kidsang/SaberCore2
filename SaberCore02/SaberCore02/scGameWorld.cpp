#include "scGameWorld.h"
#include "scGameWorldManager.h"
#include "scError.h"

scGameWorld::scGameWorld(string const& name)
	: mName(name)
{
}


scGameWorld::~scGameWorld(void)
{
}

void scGameWorld::initialize()
{
	Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();
	//////////////////////////////////////////////////////////////////////////
	// test
	Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();
	Ogre::SceneManager* mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	mSceneManagers.insert(std::make_pair("test", mSceneMgr));
	
	Ogre::Camera* mCamera = mSceneMgr->createCamera("PlayerCam");
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
	
}

void scGameWorld::release()
{
	Ogre::Root* ogreRoot = Ogre::Root::getSingletonPtr();
	// 清理视口
	ogreRoot->getAutoCreatedWindow()->removeAllViewports();
	mViewports.clear();

	for (auto iter = mSceneManagers.begin(); iter != mSceneManagers.end(); ++iter)
	{
		Ogre::SceneManager *sm = iter->second;
		// 释放场景资源
		sm->clearScene();
		for (auto camIter = mCameras.begin(); camIter != mCameras.end(); ++camIter)
		{
			if (camIter->second->getSceneManager() == sm)
			{
				// 清理摄像机
				sm->destroyCamera(camIter->second->getName());
				camIter = mCameras.erase(camIter);
				if (camIter == mCameras.end())
					break; // break到SceneManager循环 
			}
		}
		// 删除场景管理器
		ogreRoot->destroySceneManager(sm);
	}
	mSceneManagers.clear();
	scAssert(mCameras.empty(), "Not all cameras in game world " + mName + " are destroyed, what happens?");	
}

bool scGameWorld::_run( u32 dtms )
{
	//std::cout<<"testing jump to..."<<std::endl;
	//scGameWorldManager::getSingletonPtr()->jumpTo("test");
	return true;
}
