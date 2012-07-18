//#include "scServerGameWorld.h"
//#include <lua.hpp>
//#include <luabind/luabind.hpp>
//#include "scError.h"
////#include "luaVectorWrapper.h"
//
//scServerGameWorld::scServerGameWorld(string const& worldName, string const& mapName)
//	: scGameWorld(worldName), mMapName(mapName)
//{
//}
//
//
//scServerGameWorld::~scServerGameWorld(void)
//{
//}
//
//void scServerGameWorld::initialize()
//{
//	scGameWorld::initialize();
//	//////////////////////////////////////////////////////////////////////////
//	// test
//	Ogre::Root* mRoot = Ogre::Root::getSingletonPtr();
//	Ogre::RenderWindow* mWindow = mRoot->getAutoCreatedWindow();
//	
//	Ogre::Camera* mCamera = mSceneManager->createCamera("PlayerCam");
//    mCamera->setPosition(Ogre::Vector3(0,0,80));
//    mCamera->lookAt(Ogre::Vector3(0,0,-300));
//    mCamera->setNearClipDistance(1);
//	mCamera->setAutoAspectRatio(true);
//
//	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
//	vp = mWindow->addViewport(mCamera, vp->getZOrder() + 1, 0.5f, .5f, .5f, .5f);
//
//	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
//
//	//////////////////////////////////////////////////////////////////////////
//	// 以下的应该移动至GameArea
//	//Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
//	//Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
//	//headNode->attachObject(ogreHead);
//	//// Set ambient light
//	//mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
//	//// Create a light
//	//Ogre::Light* l = mSceneMgr->createLight("MainLight");
//	//l->setPosition(20,80,50);
//	
//
//	// test static geometry
//	//Ogre::Entity* ogreHead = mSceneManager->createEntity("Head", "ogrehead.mesh");
//	//Ogre::StaticGeometry* sg = mSceneManager->createStaticGeometry("Heads");
//	//sg->addEntity(ogreHead, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY, Ogre::Vector3(0.1f));
//	//sg->build();
//	loadScene("../../Media/lua/testscene.lua");
//}
//
//void scServerGameWorld::release()
//{
//	scGameWorld::release();
//}
//
//bool scServerGameWorld::_run( u32 dtms )
//{
//	//scGameWorld::_run(dtms);
//	return true;
//}
//
//void scServerGameWorld::loadScene( string const& fileName, string const& entry /*= "createScene"*/ )
//{
//	try
//	{
//		using namespace luabind;
//		lua_State* L = lua_open();
//		luaL_openlibs(L);
//		luabind::open(L);
//
//		// 导出Ogre向量和四元数
//		//exportVectorAndQuaternion(L);
//
//		// 导出类
//		module(L)
//			[
//				class_<scServerGameWorld>("World")
//				.def("placeStatic", &scServerGameWorld::addStatic)
//			];
//
//		// 加载地图文件
//		luaL_dofile(L, fileName.c_str());
//		// 创建场景
//		call_function<void>(L, entry.c_str(), this);
//	}
//	catch (luabind::error& e)
//	{
//		scErrMsg("---------------------------------------------");
//		scErrMsg(e.what());
//		scErrMsg(lua_tostring(e.state(), -1));
//		scErrMsg("---------------------------------------------");
//	}
//}
//
//void scServerGameWorld::addStatic(string const& meshName, Ogre::Vector3 const& position, Ogre::Quaternion const& orientation, Ogre::Vector3 const& scale)
//{
//	Ogre::Entity* ent = mSceneManager->createEntity(meshName);
//	Ogre::StaticGeometry* sg = mSceneManager->createStaticGeometry("Heads");
//	sg->addEntity(ent, position, orientation, scale);
//	sg->build();
//}
//