#include "scServerGameWorld.h"


scServerGameWorld::scServerGameWorld(string const& worldName, string const& mapName)
	: scGameWorld(worldName), mMapName(mapName)
{
}


scServerGameWorld::~scServerGameWorld(void)
{
}

void scServerGameWorld::initialize()
{
	scGameWorld::initialize();

	// test static geometry
	Ogre::SceneManager* sceneMgr = mSceneManagers["test"];
	Ogre::Entity* ogreHead = sceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::StaticGeometry* sg = sceneMgr->createStaticGeometry("Heads");
	for (int i = 0; i < 10; ++i)
	{
		sg->addEntity(ogreHead, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY, Ogre::Vector3(0.1f));
	}
	sg->build();
}

void scServerGameWorld::release()
{
	scGameWorld::release();
}

bool scServerGameWorld::_run( u32 dtms )
{
	return true;
}
