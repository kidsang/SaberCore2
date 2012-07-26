#include "scInputManager.h"
#include "scError.h"
#include "scLuaWrapper.h"

/// 辅助方法，输出lua错误信息
void printLuaError(luabind::error& e)
{
	scErrMsg("---------------------------------------------");
	scErrMsg(e.what());
	scErrMsg(lua_tostring(e.state(), -1));
	scErrMsg("---------------------------------------------");
}

scInputManager::scInputManager( u32 handle, u32 width, u32 height, bool isExclusive /*= false*/ )
	: mInputMgr(0), mKeyboard(0), mMouse(0),
	//mKeyPressedScriptName(""), mKeyReleasedScriptName(""),
	//mMouseMovedScriptName(""), mMousePressedScriptName(""), mMouseReleasedScriptName(""),
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
	return true;
}

bool scInputManager::keyReleased( const OIS::KeyEvent &arg )
{
	return true;
}

bool scInputManager::mouseMoved( const OIS::MouseEvent &arg )
{
	//std::ostringstream ostr;
	//ostr << arg.state.X.abs << ", " << arg.state.Y.abs;
	//scErrMsg(ostr.str());

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
	return true;
}

bool scInputManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}

void scInputManager::registerKeyPressed(string const& fileName, string const& entry)
{
	unregisterKeyPressed();

}

void scInputManager::registerKeyReleased(string const& fileName, string const& entry)
{
	unregisterKeyReleased();
}

void testPrint(string const& str)
{
	scErrMsg(str);
}

void scInputManager::registerMouseMoved(string const& fileName, string const& entry)
{
	unregisterMouseMoved();

	try
	{
		using namespace luabind;
		mMouseMovedLuaState = lua_open();
		luaL_openlibs(mMouseMovedLuaState );
		luabind::open(mMouseMovedLuaState );

		module(mMouseMovedLuaState)
			[
				def("testPrint", &testPrint)
			];

		exportOISMouseEvent(mMouseMovedLuaState);
		int i = luaL_dofile(mMouseMovedLuaState, fileName.c_str());
		if (i)
			throw luabind::error(mMouseMovedLuaState);
		mMouseMovedEntry = entry;
	}
	catch (luabind::error& e)
	{
		printLuaError(e);
	}
}

void scInputManager::registerMousePressed(string const& fileName, string const& entry)
{
	unregisterMousePressed();
}

void scInputManager::registerMouseReleased(string const& fileName, string const& entry)
{
	unregisterMouseReleased();
}

void scInputManager::unregisterKeyPressed()
{
	if (mKeyPressedLuaState)
	{ lua_close(mKeyPressedLuaState); mKeyPressedLuaState= 0; }
}

void scInputManager::unregisterKeyReleased()
{
	if (mKeyReleasedLuaState)
	{ lua_close(mKeyReleasedLuaState); mKeyReleasedLuaState= 0; }
}

void scInputManager::unregisterMouseMoved()
{
	if (mMouseMovedLuaState)
	{ lua_close(mMouseMovedLuaState); mMouseMovedLuaState= 0; }
}

void scInputManager::unregisterMousePressed()
{
	if (mMousePressedLuaState)
	{ lua_close(mMousePressedLuaState); mMousePressedLuaState= 0; }
}

void scInputManager::unregisterMouseReleased()
{
	if (mMouseReleasedLuaState)
	{ lua_close(mMouseReleasedLuaState); mMouseReleasedLuaState= 0; }
}

void scInputManager::unregisterAll()
{
	unregisterKeyPressed();
	unregisterKeyReleased();
	unregisterMouseMoved();
	unregisterMousePressed();
	unregisterMouseReleased();
}
