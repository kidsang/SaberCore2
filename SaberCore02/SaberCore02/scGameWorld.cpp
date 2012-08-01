#include "scGameWorld.h"
#include "scGameWorldManager.h"
#include "scError.h"
#include "scRenderer.h"
#include "scInputManager.h"
#include "scLuaWrapper.h"
#include "scEventRouter.h"
#include "scEvent.h"
#include "scEventQueue.h"
#include "scAnEvent.h"

u32 scGameWorld::sNextViewportZOder = 0;

scGameWorld::scGameWorld(string const& name)
	: mName(name), mSceneManager(0), mEventL(0)
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
	// 测试一下事件路由
	iniEvent("../../Media/lua/testevent.lua", "callbackEntry", "../../Media/lua/testevent.lua", "registerEntry");

	// 测试装载场景
	iniScene("../../Media/lua/testscene.lua");

	// 测试初始化GUI
	iniGui("../../Media/lua/testguievent.lua", "../../Media/lua/testguievent.lua");

	// 测试GUI
	MyGUI::Gui* gui = renderer->getGui();
	MyGUI::ButtonPtr button = gui->createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main", "testbutton");
	button->setCaption("button");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_KEY_GET_FOCUS, "onKeyGetFocus");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_KEY_LOSE_FOCUS, "onKeyLoseFocus");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_KEY_PRESSED, "onKeyPressed");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_KEY_RELEASED, "onKeyReleased");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_MOUSE_GET_FOCUS, "onMouseGetFocus");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_MOUSE_LOSE_FOCUS, "onMouseLoseFocus");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_MOUSE_MOVE, "onMouseMove");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_MOUSE_DRAG, "onMouseDrag");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_MOUSE_PRESSED, "onMousePressed");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_MOUSE_RELEASED, "onMouseReleased");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_MOUSE_CLICK, "onMouseClick");
	renderer->registerGuiEvent("testbutton", scRenderer::UI_MOUSE_DOUBLE_CLICK, "onMouseDoubleClick");


}

void scGameWorld::release()
{
	Ogre::Root* ogreRoot= scRenderer::getSingleton().getOgreRoot();
	// 清理GUI
	scInputManager::getSingleton().unregisterGuiEvents();
	scRenderer::getSingleton().shutdownGui();

	// 清理事件系统
	if (mEventL)
	{ lua_close(mEventL); mEventL = 0; }
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
	std::vector<scEventPtr> evts;
	mEventQueue->fetchEvents(evts);
	if (mEventL)
	{
		try
		{
			for (auto iter = evts.begin(); iter != evts.end(); ++iter)
			{
				// TODO:这里直接强转为anEvent貌似有些不妥
				scAnEvent* evt = static_cast<scAnEvent*>(iter->get());
				luabind::call_function<void>(mEventL, mEventCallbackEntry.c_str(), evt);
			}
		}
		catch (luabind::error& e)
		{ scPrintLuaError(e); }
	}
	// 测试
	//std::vector<scEventPtr> evts;
	//apple->fetchEvents(evts);
	//for (auto iter = evts.begin(); iter != evts.end(); ++iter)
	//	scErrMsg((*iter)->getName());
	//evts.clear();
	//orange->fetchEvents(evts);
	//for (auto iter = evts.begin(); iter != evts.end(); ++iter)
	//{
	//	if ((*iter)->getName() == "t")
	//	{
	//		//shared_ptr<scTestEvent> e = shared_ptr<scTestEvent>(static_cast<scTestEvent*>((*iter).get()));
	//		scAnEvent* e = static_cast<scAnEvent*>((*iter).get());
	//		e->getI32("x");
	//		//e->getString("des");
	//		scErrMsg(e->getString("des")+ scToString(e->getI32("x")) + "," + scToString(e->getI32("y")));
	//	}
	//	else
	//		scErrMsg((*iter)->getName());
	//}

	return true;
}

void scGameWorld::iniScene( string const& fileName, string const& entry /*= "createScene"*/ )
{
	try
	{
		using namespace luabind;
		lua_State* L = lua_open();
		luaL_openlibs(L);
		luabind::open(L);

		// 导出Ogre向量和四元数
		exportOgreMath(L);
		// 导出Ogre Camera 
		exportOgreCamera(L);

		// 导出类
		module(L)
			[
				class_<scGameWorld>("World")
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
				.def("getName", (string const& (scGameWorld::*)())&scGameWorld::getName)
				.def("getEventQueueName", (string const& (scGameWorld::*)())&scGameWorld::getEventQueueName)
			];

		// 加载地图文件
		int i = luaL_dofile(L, fileName.c_str());
		if (i)
			throw luabind::error(L);
		// 创建场景
		call_function<void>(L, entry.c_str(), this);

		lua_close(L);
	}
	catch (luabind::error& e)
	{ scPrintLuaError(e); }
}

void scGameWorld::iniGui( string const& callbackScript, string const& registerScript )
{
	scRenderer::getSingleton().initializeGui(mSceneManager, callbackScript, registerScript);
	scInputManager::getSingleton().registerGuiEvents(MyGUI::InputManager::getInstancePtr());
}

void scGameWorld::iniEvent(string const& callbackScript, string const& callbackEntry,
		string const& registerScript, string const& registerEntry)
{
	try
	{
		using namespace luabind;
		mEventL = lua_open();
		luaL_openlibs(mEventL);
		luabind::open(mEventL);
		// 导出类
		module(mEventL)
			[
				class_<scGameWorld>("World")
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
				.def("getName", (string const& (scGameWorld::*)())&scGameWorld::getName)
				.def("getEventQueueName", (string const& (scGameWorld::*)())&scGameWorld::getEventQueueName)
			];
		// 导出事件系统
		exportScEvent(mEventL);
		// 导出错误
		exportScError(mEventL);

		int i;
		i = luaL_dofile(mEventL, registerScript.c_str());
		if (i) throw luabind::error(mEventL);
		call_function<void>(mEventL, registerEntry.c_str(), this);

		i = luaL_dofile(mEventL, callbackScript.c_str());
		if (i) throw luabind::error(mEventL);
		mEventCallbackEntry = callbackEntry;
	}
	catch (luabind::error& e)
	{ scPrintLuaError(e); }

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
