#include "scGameWorld.h"
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "scGameWorldManager.h"
#include "scError.h"
#include "scRenderer.h"
#include "scInputManager.h"
#include "scLuaWrapper.h"
#include "scEventRouter.h"
#include "scEvent.h"
#include "scEventQueue.h"

u32 scGameWorld::sNextViewportZOder = 0;

scGameWorld::scGameWorld(string const& name)
	: mName(name), mSceneManager(0)
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

	// 测试输入系统绑定
	inputMgr->registerMouseMoved("../../Media/lua/testinput.lua", "onMouseMoved");
	inputMgr->registerMousePressed("../../Media/lua/testinput.lua", "onMousePressed");
	inputMgr->registerKeyReleased("../../Media/lua/testinput.lua", "onKeyPressed");

	// 测试装载场景
	loadScene("../../Media/lua/testscene.lua");

	// 测试初始化GUI
	renderer->initializeGui(mSceneManager, "../../Media/lua/testguievent.lua", "../../Media/lua/testguievent.lua");
	inputMgr->registerGuiEvents(MyGUI::InputManager::getInstancePtr());
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
	// 测试
	std::vector<scEventPtr> evts;
	scEventQueuePtr apple, orange;
	apple = scEventRouter::getSingleton().getEventQueue("apple");
	orange = scEventRouter::getSingleton().getEventQueue("orange");
	apple->fetchEvents(evts);
	for (auto iter = evts.begin(); iter != evts.end(); ++iter)
		scErrMsg((*iter)->name);
	evts.clear();
	orange->fetchEvents(evts);
	for (auto iter = evts.begin(); iter != evts.end(); ++iter)
		scErrMsg((*iter)->name);
	//scEventPtr evt;
	//while (scEventRouter::getSingleton().fetchEvent("apple", evt))
	//	scErrMsg(evt->name);
	//while (scEventRouter::getSingleton().fetchEvent("orange", evt))
	//	scErrMsg(evt->name);

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

		// 导出Ogre向量和四元数
		exportOgreMath(L);
		// 导出Ogre Camera
		exportOgreCamera(L);

		// 导出类
		module(L)
			[
				class_<scGameWorld>("World")
				.def("addStatic", (void (scGameWorld::*)(string const& meshName, Ogre::Vector3 const& position, Ogre::Quaternion const& orientation, Ogre::Vector3 const& scale))&scGameWorld::addStatic)
				.def("addCamera", (Ogre::Camera* (scGameWorld::*)(const string &))&scGameWorld::addCamera)
				.def("getCamera", (Ogre::Camera* (scGameWorld::*)(const string &))&scGameWorld::getCamera)
				.def("removeCamera", (void (scGameWorld::*)(const string &))&scGameWorld::removeCamera)
				.def("addViewport", (void (scGameWorld::*)(const string &,  const string &))&scGameWorld::addViewport)
				.def("addViewport", (void (scGameWorld::*)(const string &,  const string &,  float,  float,  float,  float))&scGameWorld::addViewport)
				.def("removeViewport", (void (scGameWorld::*)(const string &))&scGameWorld::removeViewport)
			];

		// 加载地图文件
		luaL_dofile(L, fileName.c_str());
		// 创建场景
		call_function<void>(L, entry.c_str(), this);

		lua_close(L);
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
