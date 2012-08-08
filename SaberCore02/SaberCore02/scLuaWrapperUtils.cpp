#include "scLuaWrapper.h"
#include "OgreResourceGroupManager.h"
#include "scError.h"

string const getScriptPath(string const& name )
{
	Ogre::ResourceGroupManager* mgr = Ogre::ResourceGroupManager::getSingletonPtr();
	string group;
	try
	{ group = mgr->findGroupContainingResource(name); }
	catch (...)
	{ scAssert(0, "Can not locate lua script \"" + name + "\" in any group.");}
	Ogre::FileInfoListPtr infos = mgr->findResourceFileInfo(group, name);
	return infos->at(0).archive->getName() + "/" + name;
}
