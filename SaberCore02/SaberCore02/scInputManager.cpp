#include "scInputManager.h"
#include "scError.h"

scInputManager::scInputManager( u32 handle, u32 width, u32 height, bool isExclusive /*= false*/ )
	: mInputMgr(0), mKeyboard(0), mMouse(0)
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
	std::ostringstream ostr;
	ostr << arg.state.X.abs << ", " << arg.state.Y.abs;
	scErrMsg(ostr.str());
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
