#include "scGameWorld.h"
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

	// ��������������
	mSceneManager = renderer->getOgreRoot()->createSceneManager(Ogre::ST_GENERIC);

	// ��ʼ���¼�����
	mEventQueue = scEventRouter::getSingleton().createEventQueue(mName);
	// ����һ���¼�·��
	iniEvent("../../Media/lua/testevent.lua", "callbackEntry", "../../Media/lua/testevent.lua", "registerEntry");
	
	// ������갴���¼�
	inputMgr->registerMouseMoved("../../Media/lua/testinput.lua", "onMouseMoved");

	// ����װ�س���
	iniScene("../../Media/lua/testscene.lua");

	// ���Գ�ʼ��GUI
	iniGui("../../Media/lua/testguievent.lua", "../../Media/lua/testguievent.lua");

	// ����GUI
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
	// ����GUI
	scInputManager::getSingleton().unregisterGuiEvents();
	scRenderer::getSingleton().shutdownGui();

	// �����¼�ϵͳ
	if (mEventL)
	{ lua_close(mEventL); mEventL = 0; }
	scEventRouter::getSingleton().unregisterEvents(mEventQueue->getName());
	scEventRouter::getSingleton().destroyEventQueue(mEventQueue->getName());

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
	//scEvent evt("test2");
	//evt.putI32("time", dtms);
	//scEventRouter::getSingleton().putEvent(evt);

	std::vector<scEvent> evts;
	mEventQueue->fetchEvents(evts);
	if (mEventL)
	{
		try
		{
			for (auto iter = evts.begin(); iter != evts.end(); ++iter)
			{
				luabind::call_function<void>(mEventL, mEventCallbackEntry.c_str(), (*iter));
			}
		}
		catch (luabind::error& e)
		{ scPrintLuaError(e); }
	}
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

		// ����Ogre��������Ԫ��
		exportOgreMath(L);
		// ����Ogre Camera 
		exportOgreCamera(L);

		// ������
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

		// ���ص�ͼ�ļ�
		int i = luaL_dofile(L, fileName.c_str());
		if (i)
			throw luabind::error(L);
		// ��������
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
		// ������
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
		// �����¼�ϵͳ
		exportScEvent(mEventL);
		// ��������
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
