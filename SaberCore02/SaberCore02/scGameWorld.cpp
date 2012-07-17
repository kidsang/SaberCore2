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
	// ��������������
	mSceneManager = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC);
}

void scGameWorld::release()
{
	Ogre::Root* ogreRoot = Ogre::Root::getSingletonPtr();
	// �����ӿ�
	ogreRoot->getAutoCreatedWindow()->removeAllViewports();
	mViewports.clear();

	// �ͷų�����Դ
	mSceneManager->clearScene();
	for (auto camIter = mCameras.begin(); camIter != mCameras.end(); ++camIter)
		// ���������
		mSceneManager->destroyCamera(camIter->second->getName());
	mCameras.clear();

	// ɾ������������
	ogreRoot->destroySceneManager(mSceneManager);
	mSceneManager = 0;
}

bool scGameWorld::_run( u32 dtms )
{
	std::cout<<"testing jump to..."<<std::endl;
	scGameWorldManager::getSingletonPtr()->jumpTo("test");
	return true;
}
