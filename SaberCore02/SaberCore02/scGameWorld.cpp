#include "scGameWorld.h"
#include "scGameWorldManager.h"
#include "scError.h"
#include "scRenderer.h"
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "luaVectorWrapper.h"

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
	//////////////////////////////////////////////////////////////////////////
	// test
	Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();
	Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();
	
	Ogre::Camera* mCamera = mSceneManager->createCamera("PlayerCam");
	//mCameras.insert(std::make_pair("test", mCamera));
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(1);
	mCamera->setAutoAspectRatio(true);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp = mWindow->addViewport(mCamera, vp->getZOrder() + 1, 0.5f, .5f, .5f, .5f);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	loadScene("../../Media/lua/testscene.lua");
}

void scGameWorld::release()
{
	Ogre::Root* ogreRoot = Ogre::Root::getSingletonPtr();
	// �����ӿ�
	ogreRoot->getAutoCreatedWindow()->removeAllViewports();
	mViewports.clear();

	// �ͷų�����Դ
	mSceneManager->clearScene();

	// ɾ������������
	ogreRoot->destroySceneManager(mSceneManager);
	mSceneManager = 0;
}

bool scGameWorld::_run( u32 dtms )
{
	//std::cout<<"testing jump to..."<<std::endl;
	//scGameWorldManager::getSingletonPtr()->jumpTo("test");
	return true;
}

void scGameWorld::loadScene( string const& fileName, string const& entry /*= "createScene"*/ )
{
	try
	{
		using namespace luabind;
		lua_State* L = lua_open();
		luaL_openlibs(L);
		luabind::open(L);

		// ����Ogre��������Ԫ��
		//exportVectorAndQuaternion(L);
		exportOgreMath(L);

		// ������
		module(L)
			[
				class_<scGameWorld>("World")
				.def("placeStatic", &scGameWorld::addStatic)
			];

		// ���ص�ͼ�ļ�
		luaL_dofile(L, fileName.c_str());
		// ��������
		call_function<void>(L, entry.c_str(), this);
	}
	catch (luabind::error& e)
	{
		scErrMsg("---------------------------------------------");
		scErrMsg(e.what());
		scErrMsg(lua_tostring(e.state(), -1));
		scErrMsg("---------------------------------------------");
	}
}

void scGameWorld::addStatic(string const& meshName, Ogre::Vector3 const& position, Ogre::Quaternion const& orientation, Ogre::Vector3 const& scale)
{
	Ogre::Entity* ent = mSceneManager->createEntity(meshName);
	Ogre::StaticGeometry* sg = mSceneManager->createStaticGeometry("Heads");
	sg->addEntity(ent, position, orientation, scale);
	sg->build();
}

void scGameWorld::addCamera( string const& camName )
{
	Ogre::Camera* camera = mSceneManager->createCamera(camName);
    camera->setNearClipDistance(1);
	camera->setAutoAspectRatio(true);
}
