#include "scGameWorldManager.h"
#include "scGameWorld.h"


scGameWorldManager::scGameWorldManager()
	: isInitialized(false)
{
}

template<> scGameWorldManager* Ogre::Singleton<scGameWorldManager>::ms_Singleton = 0;
scGameWorldManager& scGameWorldManager::getSingleton( void )
{
	assert( ms_Singleton );  return ( *ms_Singleton ); 
}
scGameWorldManager* scGameWorldManager::getSingletonPtr( void )
{
	return ms_Singleton;
}

void scGameWorldManager::addGameWorld( string const& name, scGameWorldPtr const& world )
{
	scAssert(mGameWorldMap.find(name) == mGameWorldMap.end(), "Game world named \""+ name + "\" already exist.");
	mGameWorldMap.insert(std::make_pair(name, world));
}

void scGameWorldManager::removeGameWorld( string const& name )
{
	auto iter = mGameWorldMap.find(name);
	scAssert(iter != mGameWorldMap.end(), "Game world named \"" + name + "\" do not exist.");
	mGameWorldMap.erase(iter);
}

void scGameWorldManager::initializeGameWorld( string const& name )
{
	scAssert(!isInitialized, "You can only initialize game world once. You should use \"jumpTo()\"");
	auto iter = mGameWorldMap.find(name);
	scAssert(iter != mGameWorldMap.end(), "Can not find game world named \""+ name + "\"");
	iter->second->initialize();

	mCurrentGameWorld = iter->second;
	isInitialized = true;
}

bool scGameWorldManager::_run( u32 dtms )
{
	if (!isInitialized)
		return true;

	return mCurrentGameWorld->_run(dtms);
}

void scGameWorldManager::jumpTo( string const& name )
{
	auto iter = mGameWorldMap.find(name);
	scAssert(iter != mGameWorldMap.end(), "Game world named \"" + name + "\" do not exist.");
	
	// 卸载旧世界
	mCurrentGameWorld->release();
	// 指向新世界
	mCurrentGameWorld = iter->second;
	// 加载新世界
	mCurrentGameWorld->initialize();

}
