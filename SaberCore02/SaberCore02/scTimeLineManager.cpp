#include "scTimeLineManager.h"
#include "scTimeLine.h"
#include "scError.h"


scTimeLinePtr const& scTimeLineManager::createTimeLine( const string& name, u32 invokeRate, int priority /*= 0*/ )
{
	// 首先检查有没有名字冲突
	auto iter = mTimeLines.begin();
	for (; iter != mTimeLines.end(); ++iter)
		if (iter->second->getName() == name)
			break;
	scAssert(mTimeLines.empty() || iter == mTimeLines.end(), "Time line name \"" + name +"\" already exist.");

	scTimeLinePtr tl = scTimeLinePtr(new scTimeLine(name, invokeRate));
	auto tliter = mTimeLines.insert(std::make_pair(priority, tl));

	return tliter->second;
}

void scTimeLineManager::destoryTimeLine( scTimeLinePtr const& timeLine )
{
	for (auto iter = mTimeLines.begin(); iter != mTimeLines.end(); ++iter)
	{
		if (iter->second == timeLine)
		{
			mTimeLines.erase(iter);
			break;
		}
	}
}

void scTimeLineManager::destoryTimeLine( string const& name )
{
	for (auto iter = mTimeLines.begin(); iter != mTimeLines.end(); ++iter)
	{
		if (iter->second->getName() == name)
		{
			mTimeLines.erase(iter);
			break;
		}
	}
}

void scTimeLineManager::setPriority( scTimeLinePtr const& timeLine, int priority )
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

void scTimeLineManager::setPriority( string const& name, int priority )
{
	auto iter = mTimeLines.begin();
	for (; iter != mTimeLines.end(); ++iter)
		if (iter->second->getName() == name)
			break;

	if (iter != mTimeLines.end())
	{
		scTimeLinePtr timeLine = iter->second;
		mTimeLines.erase(iter);
		mTimeLines.insert(std::make_pair(priority, timeLine));
	} 
}

scTimeLinePtr const& scTimeLineManager::getTimeLine( string const& name )
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

template<> scTimeLineManager* Ogre::Singleton<scTimeLineManager>::ms_Singleton = 0;
scTimeLineManager& scTimeLineManager::getSingleton( void )
{
	assert( ms_Singleton );  return ( *ms_Singleton ); 
}
scTimeLineManager* scTimeLineManager::getSingletonPtr( void )
{
	return ms_Singleton;
}

scTimeLineManager::~scTimeLineManager()
{
}

bool scTimeLineManager::run( u32 dtms )
{
	for (auto iter = mTimeLines.begin(); iter != mTimeLines.end(); ++iter)
		iter->second->_run(dtms);
	return true;
}
