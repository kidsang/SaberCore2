#include "scInputManager.h"
#include "scError.h"
#include "scLuaWrapper.h"

/// �������������lua������Ϣ
void printLuaError(luabind::error& e)
{
	scErrMsg("---------------------------------------------");
	scErrMsg(e.what());
	scErrMsg(lua_tostring(e.state(), -1));
	scErrMsg("---------------------------------------------");
}
	
void testPrint(string const& str)
{
	scErrMsg(str);
}

typedef void(*ExportFunc)(lua_State*);
/// �����������������¼����Ӧ�ű���
/// @param L ��Ӧ��lua�����
/// @param fileName Ҫ�󶨵Ľű�����
/// @param exportFunc ��Ҫ�����ģ��
void registerScript(lua_State*& L, string const& fileName, ExportFunc exportFunc)
{
	try
	{
		using namespace luabind;
		L = lua_open();
		luaL_openlibs(L);
		luabind::open(L);

		// TODO: �ö�Ϊ���Դ��룬��Ҫ��ɾ��
		module(L)
			[
				def("testPrint", &testPrint)
			];

		exportFunc(L);
		int i = luaL_dofile(L, fileName.c_str());
		if (i)
			throw luabind::error(L);
	}
	catch (luabind::error& e)
	{
		printLuaError(e);
	}
}

/// ������������������¼���ű��İ�
/// @param L ��Ӧ��lua�����
void unregisterScript(lua_State*& L)
{
	if (L)
	{ lua_close(L); L= 0; }
}


scInputManager::scInputManager( u32 handle, u32 width, u32 height, bool isExclusive /*= false*/ )
	: mInputMgr(0), mKeyboard(0), mMouse(0),
	mKeyPressedLuaState(0), mKeyReleasedLuaState(0),
	mMouseMovedLuaState(0), mMousePressedLuaState(0), mMouseReleasedLuaState(0)
{
	OIS::ParamList pl;
    std::ostringstream windowHndStr;
    windowHndStr << handle;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	if (!isExclusive)
	{
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
	}

	mInputMgr = OIS::InputManager::createInputSystem(pl);
	mKeyboard = static_cast<OIS::Keyboard*>(mInputMgr->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputMgr->createInputObject(OIS::OISMouse, true));

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

scInputManager::~scInputManager(void)
{
	unregisterAll();

	if( mInputMgr )
	{
		if (mMouse)
			mInputMgr->destroyInputObject( mMouse );
		if (mKeyboard)
			mInputMgr->destroyInputObject( mKeyboard );
		OIS::InputManager::destroyInputSystem(mInputMgr);
		mMouse = 0;
		mKeyboard = 0;
		mInputMgr = 0;
	}
}

template<> scInputManager* Ogre::Singleton<scInputManager>::ms_Singleton = 0;
scInputManager& scInputManager::getSingleton( void )
{
	assert(ms_Singleton); return (*ms_Singleton);
}
scInputManager* scInputManager::getSingletonPtr( void )
{
	return ms_Singleton;
}

bool scInputManager::keyPressed( const OIS::KeyEvent &arg )
{
	if (mKeyPressedLuaState)
	{
		try
		{
			using namespace luabind;
			call_function<void>(mKeyPressedLuaState, mKeyPressedEntry.c_str(), arg);
		}
		catch (luabind::error& e)
		{
			printLuaError(e);
		}
	}
	return true;
}

bool scInputManager::keyReleased( const OIS::KeyEvent &arg )
{
	if (mKeyReleasedLuaState)
	{
		try
		{
			using namespace luabind;
			call_function<void>(mKeyReleasedLuaState, mKeyReleasedEntry.c_str(), arg);
		}
		catch (luabind::error& e)
		{
			printLuaError(e);
		}
	}
	return true;
}

bool scInputManager::mouseMoved( const OIS::MouseEvent &arg )
{
	if (mMouseMovedLuaState)
	{
		try
		{
			using namespace luabind;
			call_function<void>(mMouseMovedLuaState, mMouseMovedEntry.c_str(), scMouseEventWrapper(arg.state));
		}
		catch (luabind::error& e)
		{
			printLuaError(e);
		}
	}
	return true;
}

bool scInputManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (mMousePressedLuaState)
	{
		try
		{
			using namespace luabind;
			call_function<void>(mMousePressedLuaState, mMousePressedEntry.c_str(), scMouseEventWrapper(arg.state));
		}
		catch (luabind::error& e)
		{
			printLuaError(e);
		}
	}
	return true;
}

bool scInputManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (mMouseReleasedLuaState)
	{
		try
		{
			using namespace luabind;
			call_function<void>(mMouseReleasedLuaState, mMouseReleasedEntry.c_str(), scMouseEventWrapper(arg.state));
		}
		catch (luabind::error& e)
		{
			printLuaError(e);
		}
	}
	return true;
}

void scInputManager::registerKeyPressed(string const& fileName, string const& entry)
{
	unregisterKeyPressed();
	registerScript(mKeyReleasedLuaState, fileName, exportOISKeyboardEvent);
	mKeyReleasedEntry = entry;
}

void scInputManager::registerKeyReleased(string const& fileName, string const& entry)
{
	unregisterKeyReleased();
	registerScript(mKeyPressedLuaState, fileName, exportOISKeyboardEvent);
	mKeyPressedEntry = entry;
}

void scInputManager::registerMouseMoved(string const& fileName, string const& entry)
{
	unregisterMouseMoved();
	registerScript(mMouseMovedLuaState, fileName, exportOISMouseEvent);
	mMouseMovedEntry = entry;
}

void scInputManager::registerMousePressed(string const& fileName, string const& entry)
{
	unregisterMousePressed();
	registerScript(mMousePressedLuaState , fileName, exportOISMouseEvent);
	mMousePressedEntry = entry;
}

void scInputManager::registerMouseReleased(string const& fileName, string const& entry)
{
	unregisterMouseReleased();
	registerScript(mMouseReleasedLuaState, fileName, exportOISMouseEvent);
	mMouseReleasedEntry = entry;
}

void scInputManager::unregisterKeyPressed()
{
	unregisterScript(mKeyPressedLuaState);
}

void scInputManager::unregisterKeyReleased()
{
	unregisterScript(mKeyReleasedLuaState);
}

void scInputManager::unregisterMouseMoved()
{
	unregisterScript(mMouseMovedLuaState);
}

void scInputManager::unregisterMousePressed()
{
	unregisterScript(mMousePressedLuaState);
}

void scInputManager::unregisterMouseReleased()
{
	unregisterScript(mMouseReleasedLuaState);
}

void scInputManager::unregisterAll()
{
	unregisterKeyPressed();
	unregisterKeyReleased();
	unregisterMouseMoved();
	unregisterMousePressed();
	unregisterMouseReleased();
}
