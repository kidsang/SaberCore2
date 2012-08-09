#include "scTimeLineManager.h"
#include "scTimeLine.h"
#include "scError.h"


scTimeLine* scTimeLineManager::createTimeLine( const std::string& name, u32 invokeRate, int priority /*= 0*/ )
{
	// 首先检查有没有名字冲突
	auto iter = mTimeLines.begin();
	for (; iter != mTimeLines.end(); ++iter)
		if (iter->second->getName() == name)
			break;
	scAssert(mTimeLines.empty() || iter == mTimeLines.end(), "Time line name \"" + name +"\" already exist.");

	scTimeLine* tl = new scTimeLine(name, invokeRate);
	mTimeLines.insert(std::make_pair(priority, tl));
	return tl;
}

void scTimeLineManager::destoryTimeLine( scTimeLine* timeLine )
{
	for (auto iter = mTimeLines.begin(); iter != mTimeLines.end(); ++iter)
	{
		if (iter->second == timeLine)
		{
			delete iter->second;
			mTimeLines.erase(iter);
			break;
		}
	}
}

void scTimeLineManager::destoryTimeLine( std::string const& name )
{
	for (auto iter = mTimeLines.begin(); iter != mTimeLines.end(); ++iter)
	{
		if (iter->second->getName() == name)
		{
			delete iter->second;
			mTimeLines.erase(iter);
			break;
		}
	}
}

void scTimeLineManager::setPriority( scTimeLine* timeLine, int priority )
{
	auto iter = mTimeLines.begin();
	for (; iter != mTimeLines.end(); ++iter)
		if (iter->second == timeLine)
			break;

	if (iter != mTimeLines.end())
	{
		mTimeLines.erase(iter);
		mTimeLines.insert(std::make_pair(priority, timeLine));
	}
}

void scTimeLineManager::setPriority( std::string const& name, int priority )
{
	auto iter = mTimeLines.begin();
	for (; iter != mTimeLines.end(); ++iter)
		if (iter->second->getName() == name)
			break;

	if (iter != mTimeLines.end())
	{
		scTimeLine* timeLine = iter->second;
		mTimeLines.erase(iter);
		mTimeLines.insert(std::make_pair(priority, timeLine));
	} 
}

scTimeLine* scTimeLineManager::getTimeLine( std::string const& name )
{
	auto iter = mTimeLines.begin();
	while (iter != mTimeLines.end())
	{
		if (iter->second->getName() == name)
			break;
		++iter;
	}

	scAssert(iter != mTimeLines.end(), "Time line name \"" + name +"\" do not exist.");
	return iter->second;
}

template<> scTimeLineManager* Ogre::Singleton<scTimeLineManager>::msSingleton = 0;
scTimeLineManager& scTimeLineManager::getSingleton( void )
{
	assert( msSingleton );  return ( *msSingleton ); 
}
scTimeLineManager* scTimeLineManager::getSingletonPtr( void )
{
	return msSingleton;
}

scTimeLineManager::~scTimeLineManager()
{
	for (auto iter = mTimeLines.begin(); iter != mTimeLines.end(); ++iter)
		delete iter->second;
}

bool scTimeLineManager::run( u32 dtms )
{
	for (auto iter = mTimeLines.begin(); iter != mTimeLines.end(); ++iter)
		iter->second->_run(dtms);
	return true;
}
