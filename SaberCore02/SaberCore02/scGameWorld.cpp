#include "scGameWorld.h"
#include "scGameWorldManager.h"
#include "scError.h"
#include "scRenderer.h"
#include "scInputManager.h"
#include "scLuaWrapper.h"
#include "scEventRouter.h"
#include "scEvent.h"
#include "scEventQueue.h"
#include "scTimeLineManager.h"
#include "scAnimationTimeLine.h"
#include "scAnimationManager.h"
#include "scUiAnimationGroup.h"
#include "scUiRotateAnimation.h"
#include "scUiAlphaAnimation.h"
#include "scUiScaleAnimation.h"
#include "scUiTranslateAnimation.h"

u32 scGameWorld::sNextViewportZOder = 0;

scGameWorld::scGameWorld(string const& name, string const& scriptName, string const& scriptEntry)
	: mName(name), mScriptName(scriptName), mScriptEntry(scriptEntry),
	mSceneManager(0), mL(0)
{
}


scGameWorld::~scGameWorld(void)
{
}

void scGameWorld::initialize()
{
	scRenderer* renderer = scRenderer::getSingletonPtr();
	scInputManager* inputMgr = scInputManager::getSingletonPtr();

	// 创建场景管理器
	mSceneManager = renderer->getOgreRoot()->createSceneManager(Ogre::ST_GENERIC);
	// 初始化事件队列
	mEventQueue = scEventRouter::getSingleton().createEventQueue(mName);
	// 初始化lua
	try
	{
		using namespace luabind;
		mL = lua_open();
		luaL_openlibs(mL);
		luabind::open(mL);

		// 导出Ogre向量和四元数
		exportOgreMath(mL);
		// 导出Ogre Camera 
		exportOgreCamera(mL);
		// 导出事件系统
		exportScEvent(mL);
		// 导出错误
		exportScError(mL);
		// 导出类
		exportSelf(mL);

		// 加载地图文件
		int i = luaL_dofile(mL, getScriptPath(mScriptName).c_str());
		if (i) throw luabind::error(mL);
		// 创建场景
		call_function<void>(mL, mScriptEntry.c_str(), this);
	}
	catch (luabind::error& e)
	{ scPrintLuaError(e); }

	// 测试UI动画
	scTimeLineManager* tlmgr = scTimeLineManager::getSingletonPtr();
	scTimeLinePtr tl = tlmgr->getTimeLine("Animation");
	scAnimationTimeLine* anitl = static_cast<scAnimationTimeLine*>(tl.get());
	
	scAnimationManager* animgr = scAnimationManager::getSingletonPtr();
	scUiTranslateAnimationPtr ani = animgr->createUiTranslateAnimation(true);
	ani->createKeyFrame(0, 0, 0);
	ani->createKeyFrame(1000, 100, 0);
	ani->createKeyFrame(2000, 0, 0);
	scUiScaleAnimationPtr ani2 = animgr->createUiScaleAnimation(true);
	ani2->createKeyFrame(0, 1, 1);
	ani2->createKeyFrame(1000, 2, 2);
	ani2->createKeyFrame(2000, 1, 1);
	scUiAlphaAnimationPtr ani3 = animgr->createUiAlphaAnimation(true);
	ani3->createKeyFrame(0, 1);
	ani3->createKeyFrame(1000, 0.5);
	ani3->createKeyFrame(2000, 1);
	scUiAnimationGroupPtr anig = animgr->createUiAnimationGroup(true);
	anig->addAnimation(ani);
	anig->addAnimation(ani2);
	anig->addAnimation(ani3);
	renderer->bindGuiAnimation("testbutton", anig);
	anitl->addAnimation(anig);
	//scUiRotateAnimationPtr ani4 = animgr->createUiRotateAnimation(true);
	//ani4->createKeyFrame(0, 0);
	//ani4->createKeyFrame(1000, 1.57);
	//ani4->createKeyFrame(2000, 3.14);
	//renderer->bindGuiAnimation("testbutton", ani4);
	//anitl->addAnimation(ani4);
}

void scGameWorld::release()
{
	Ogre::Root* ogreRoot= scRenderer::getSingleton().getOgreRoot();
	// 清理GUI
	scInputManager::getSingleton().unregisterGuiEvents();
	scRenderer::getSingleton().shutdownGui();

	// 清理事件系统
	if (mL)
	{ lua_close(mL); mL = 0; }
	scEventRouter::getSingleton().unregisterEvents(mEventQueue->getName());
	scEventRouter::getSingleton().destroyEventQueue(mEventQueue->getName());

	// 清理视口
	ogreRoot->getAutoCreatedWindow()->removeAllViewports();
	mViewports.clear();

	// 释放场景资源
	mSceneManager->clearScene();

	// 删除场景管理器
	ogreRoot->destroySceneManager(mSceneManager);
	mSceneManager = 0;
}

bool scGameWorld::_run( u32 dtms )
{
	//scEvent evt("test2");
	//evt.putI32("time", dtms);
	//scEventRouter::getSingleton().putEvent(evt);

	std::vector<scEvent> evts;
	mEventQueue->fetchEvents(evts);
	if (mL)
	{
		try
		{
			for (auto iter = evts.begin(); iter != evts.end(); ++iter)
			{
				// TODO 修改名字
				luabind::call_function<void>(mL, "callbackEntry", (*iter));
			}
		}
		catch (luabind::error& e)
		{ scPrintLuaError(e); }
	}
	return true;
}

void scGameWorld::iniScene( string const& fileName, string const& entry )
{
	using namespace luabind;
	int i = luaL_dofile(mL, getScriptPath(fileName).c_str());
	if (i) throw luabind::error(mL);
	call_function<void>(mL, entry.c_str(), this);
}

void scGameWorld::iniGui(string const& scriptName, string const& entry)
{
	scRenderer::getSingleton().initializeGui(mSceneManager, scriptName, entry);
	scInputManager::getSingleton().registerGuiEvents(MyGUI::InputManager::getInstancePtr());
}

void scGameWorld::iniEvent(string const& callbackScript, string const& callbackEntry,
	string const& registerScript, string const& registerEntry)
{
	using namespace luabind;
	int i;
	i = luaL_dofile(mL, getScriptPath(registerScript).c_str());
	if (i) throw luabind::error(mL);
	call_function<void>(mL, registerEntry.c_str(), this);

	i = luaL_dofile(mL, getScriptPath(callbackScript).c_str());
	if (i) throw luabind::error(mL);
	mEventCallbackEntry = callbackEntry;
}

void scGameWorld::addStatic(string const& meshName, Ogre::Vector3 const& position, Ogre::Quaternion const& orientation, Ogre::Vector3 const& scale)
{
	Ogre::Entity* ent = mSceneManager->createEntity(meshName);
	Ogre::StaticGeometry* sg = mSceneManager->createStaticGeometry("Heads");
	sg->addEntity(ent, position, orientation, scale);
	sg->build();
}

Ogre::Camera* scGameWorld::addCamera( string const& camName )
{
	Ogre::Camera* camera = mSceneManager->createCamera(camName);
    camera->setNearClipDistance(1);
	camera->setAutoAspectRatio(true);
	return camera;
}

Ogre::Camera* scGameWorld::getCamera( string const& camName )
{
	return mSceneManager->getCamera(camName);
}

void scGameWorld::removeCamera( string const& camName )
{
	mSceneManager->destroyCamera(camName);
}

void scGameWorld::addViewport( string const& vpName, string const& camName )
{
	addViewport(vpName, camName, 0.0f, 0.0f, 1.0f, 1.0f);
}

void scGameWorld::addViewport( string const& vpName, string const& camName, float left, float top, float width, float height )
{
	Ogre::RenderWindow* window = scRenderer::getSingleton().getOgreRoot()->getAutoCreatedWindow();
	scAssert(mViewports.find(vpName) == mViewports.end(), "Viewport named \"" + vpName + "\" already exist!");
	Ogre::Viewport* vp = window->addViewport(mSceneManager->getCamera(camName), sNextViewportZOder++, left, top, width, height);
	mViewports.insert(std::make_pair(vpName, vp));
}

void scGameWorld::removeViewport( string const& vpName )
{
	auto iter = mViewports.find(vpName);
	scAssert(iter != mViewports.end(), "Viewport named \"" + vpName + "\" do not exist!");
	Ogre::RenderWindow* window = scRenderer::getSingleton().getOgreRoot()->getAutoCreatedWindow();
	window->removeViewport(iter->second->getZOrder());
	mViewports.erase(iter);
}

string const& scGameWorld::getEventQueueName()
{
	return mEventQueue->getName();
}

void scGameWorld::exportSelf( lua_State* L )
{
	using namespace luabind;
	//---->>../scGameWorld.h 
	module(L)
		[
			//--scGameWorld
			class_<scGameWorld>("scGameWorld")
			.def("iniScene", (void (scGameWorld::*)(const string &,  const string &))&scGameWorld::iniScene)
			.def("iniGui", (void (scGameWorld::*)(const string &,  const string &))&scGameWorld::iniGui)
			.def("iniEvent", (void (scGameWorld::*)(const string &,  const string &,  const string &,  const string &))&scGameWorld::iniEvent)
			.def("addStatic", (void (scGameWorld::*)(string const&, Ogre::Vector3 const&, Ogre::Quaternion const&, Ogre::Vector3 const&))&scGameWorld::addStatic)
			.def("addCamera", (Ogre::Camera* (scGameWorld::*)(const string &))&scGameWorld::addCamera)
			.def("getCamera", (Ogre::Camera* (scGameWorld::*)(const string &))&scGameWorld::getCamera)
			.def("removeCamera", (void (scGameWorld::*)(const string &))&scGameWorld::removeCamera)
			.def("addViewport", (void (scGameWorld::*)(const string &,  const string &))&scGameWorld::addViewport)
			.def("addViewport", (void (scGameWorld::*)(const string &,  const string &,  float,  float,  float,  float))&scGameWorld::addViewport)
			.def("removeViewport", (void (scGameWorld::*)(const string &))&scGameWorld::removeViewport)
			.def("import", (void (scGameWorld::*)(const string &))&scGameWorld::luaImport)
			.def("registerKeyPressed", (void (scGameWorld::*)(const string &,  const string &))&scGameWorld::registerKeyPressed)
			.def("registerKeyReleased", (void (scGameWorld::*)(const string &,  const string &))&scGameWorld::registerKeyReleased)
			.def("registerMouseMoved", (void (scGameWorld::*)(const string &,  const string &))&scGameWorld::registerMouseMoved)
			.def("registerMousePressed", (void (scGameWorld::*)(const string &,  const string &))&scGameWorld::registerMousePressed)
			.def("registerMouseReleased", (void (scGameWorld::*)(const string &,  const string &))&scGameWorld::registerMouseReleased)
			.def("getName", (string const& (scGameWorld::*)())&scGameWorld::getName)
			.def("getEventQueueName", (string const& (scGameWorld::*)())&scGameWorld::getEventQueueName)
		];
	//<<----../scGameWorld.h
}

//string const scGameWorld::getScriptPath(string const& name )
//{
//	Ogre::ResourceGroupManager* mgr = Ogre::ResourceGroupManager::getSingletonPtr();
//	string group;
//	try
//	{ group = mgr->findGroupContainingResource(name); }
//	catch (...)
//	{ scAssert(0, "Can not locate lua script \"" + name + "\" in any group.");}
//	Ogre::FileInfoListPtr infos = mgr->findResourceFileInfo(group, name);
//	return infos->at(0).archive->getName() + "/" + name;
//}
//
void scGameWorld::luaImport( string const& moduleName )
{
	using namespace luabind;
	luaL_dofile(mL, getScriptPath(moduleName + ".lua").c_str());
}

void scGameWorld::registerKeyPressed( string const& moduleName, string const& entry )
{
	scInputManager::getSingleton().registerKeyPressed(getScriptPath(moduleName + ".lua"), entry);
}

void scGameWorld::registerKeyReleased( string const& moduleName, string const& entry )
{
	scInputManager::getSingleton().registerKeyReleased(getScriptPath(moduleName + ".lua"), entry);
}

void scGameWorld::registerMouseMoved( string const& moduleName, string const& entry )
{ 
	scInputManager::getSingleton().registerMouseMoved(getScriptPath(moduleName + ".lua"), entry);
}

void scGameWorld::registerMousePressed( string const& moduleName, string const& entry )
{
	scInputManager::getSingleton().registerMousePressed(getScriptPath(moduleName + ".lua"), entry);
}

void scGameWorld::registerMouseReleased( string const& moduleName, string const& entry )
{
	scInputManager::getSingleton().registerMouseReleased(getScriptPath(moduleName + ".lua"), entry);
}
