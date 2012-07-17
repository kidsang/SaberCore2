#include "scGameWorld.h"
#include "scGameWorldManager.h"
#include "scError.h"

scGameWorld::scGameWorld(string const& name)
	: mName(name), mSceneManager(0)
{
}


scGameWorld::~scGameWorld(void)
{
}

void scGameWorld::initialize()
{
	// 创建场景管理器
	mSceneManager = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC);
}

void scGameWorld::release()
{
	Ogre::Root* ogreRoot = Ogre::Root::getSingletonPtr();
	// 清理视口
	ogreRoot->getAutoCreatedWindow()->removeAllViewports();
	mViewports.clear();

	// 释放场景资源
	mSceneManager->clearScene();
	for (auto camIter = mCameras.begin(); camIter != mCameras.end(); ++camIter)
		// 清理摄像机
		mSceneManager->destroyCamera(camIter->second->getName());
	mCameras.clear();

	// 删除场景管理器
	ogreRoot->destroySceneManager(mSceneManager);
	mSceneManager = 0;
}

bool scGameWorld::_run( u32 dtms )
{
	std::cout<<"testing jump to..."<<std::endl;
	scGameWorldManager::getSingletonPtr()->jumpTo("test");
	return true;
}
