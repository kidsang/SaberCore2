#include "scAnimationManager.h"
#include "scError.h"
#include "scAnimation.h"
#include "scUiAlphaAnimation.h"
#include "scUiTranslateAnimation.h"
#include "scUiRotateAnimation.h"
#include "scUiScaleAnimation.h"
#include "scUiAnimationGroup.h"

scAnimationManager::scAnimationManager(void)
{
	createBuildInFactories();
}


scAnimationManager::~scAnimationManager(void)
{
}

template<> scAnimationManager* Ogre::Singleton<scAnimationManager>::ms_Singleton = 0;
scAnimationManager& scAnimationManager::getSingleton( void )
{
	assert(ms_Singleton); return (*ms_Singleton);
}
scAnimationManager* scAnimationManager::getSingletonPtr( void )
{
	return ms_Singleton;
}

void scAnimationManager::addFactory( scAnimationFactoryPtr factory )
{
	scAssert(mFactories.find(factory->getName()) == mFactories.end(), "Animation factory named \"" + factory->getName() + "\" already exist.");
	mFactories.insert(std::make_pair(factory->getName(), factory));
}

scAnimationPtr scAnimationManager::createAnimation( string const& name, bool isLoop )
{
	auto iter = mFactories.find(name);
	scAssert(iter != mFactories.end(), "Could not find animation factory named \"" + name + "\".");
	return iter->second->createAnimation(isLoop);
}

void scAnimationManager::createBuildInFactories()
{
	addFactory(shared_ptr<scUiAlphaAnimationFactory>(new scUiAlphaAnimationFactory("UiAlpha")));
	addFactory(shared_ptr<scUiTranslateAnimationFactory>(new scUiTranslateAnimationFactory("UiTranslate")));
	addFactory(shared_ptr<scUiRotateAnimationFactory>(new scUiRotateAnimationFactory("UiRotate")));
	addFactory(shared_ptr<scUiScaleAnimationFactory>(new scUiScaleAnimationFactory("UiScale")));
	addFactory(shared_ptr<scUiAnimationGroupFactory>(new scUiAnimationGroupFactory("UiGroup")));
}

scUiAlphaAnimationPtr scAnimationManager::createUiAlphaAnimation( bool isLoop )
{
	return boost::dynamic_pointer_cast<scUiAlphaAnimation>(createAnimation("UiAlpha", isLoop));
}

scUiTranslateAnimationPtr scAnimationManager::createUiTranslateAnimation( bool isLoop )
{
	return boost::dynamic_pointer_cast<scUiTranslateAnimation>(createAnimation("UiTranslate", isLoop));
}

scUiScaleAnimationPtr scAnimationManager::createUiScaleAnimation( bool isLoop )
{
	return boost::dynamic_pointer_cast<scUiScaleAnimation>(createAnimation("UiScale", isLoop));
}

scUiRotateAnimationPtr scAnimationManager::createUiRotateAnimation( bool isLoop )
{
	return boost::dynamic_pointer_cast<scUiRotateAnimation>(createAnimation("UiRotate", isLoop));
}

scUiAnimationGroupPtr scAnimationManager::createUiAnimationGroup( bool isLoop )
{
	return boost::dynamic_pointer_cast<scUiAnimationGroup>(createAnimation("UiGroup", isLoop));
}
