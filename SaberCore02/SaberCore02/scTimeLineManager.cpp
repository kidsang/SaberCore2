#include "scTimeLineManager.h"
#include "scTimeLine.h"
#include "scError.h"


scTimeLinePtr const& scTimeLineManager::createTimeLine( const string& name, u32 invokeRate, i32 priority /*= 0*/, bool threading /*= false*/ )
{
	// 首先检查有没有名字冲突
	auto iter = mTimeLines.begin();
	for (; iter != mTimeLines.end(); ++iter)
		if (iter->second->getName() == name)
			break;
	scAssert(mTimeLines.empty() || iter == mTimeLines.end(), "Time line name \"" + name +"\" already exist.");

	scTimeLinePtr tl = scTimeLinePtr(new scTimeLine(name, invokeRate));
	auto tliter = mTimeLines.insert(std::make_pair(priority, tl));

	// 如果需要在分支线程中运行，则先把名字加入名单
	if (threading)
		mThreadingTimeLines.push_back(name);

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

void scTimeLineManager::startMain()
{
	// 初始化时间
	u32 lastTime = clock();
	u32 currentTime = clock();
	u32 dtms;

	// 启动循环
	while (true)
	{
		currentTime = clock();
		dtms = currentTime - lastTime;

		for (auto iter = mTimeLines.begin(); iter != mTimeLines.end(); ++iter)
		{
			// 只运行在主线程的时间轴
			if (iter->second->getThreadStatus() == scTimeLine::TS_MAIN)
				iter->second->_run(dtms);
		}

		lastTime = currentTime;
	}
}

void scTimeLineManager::startThread( string const& name )
{
	scTimeLinePtr tl = getTimeLine(name);

	// 更新对应时间轴线程状态
	scAssert(tl->getThreadStatus() == scTimeLine::TS_MAIN, "Time line name \"" + name +"\" already running in a thread.");
	tl->setThreadStatus(scTimeLine::TS_THREAD);

	// 启动线程
	ThreadPtr thread = ThreadPtr(new boost::thread([=](){this->runThread(tl);}));
	mThreads.push_back(thread);
	
}

void scTimeLineManager::runThread( scTimeLinePtr timeLine )
{
	u32 lastTime = clock();
	u32 currentTime = clock();
	// 运行时间轴
	while (true)
	{
		currentTime = clock();

		timeLine->_run(currentTime - lastTime);

		lastTime = currentTime;
	}
}

void scTimeLineManager::startThreads()
{
	for (auto iter = mThreadingTimeLines.begin(); iter != mThreadingTimeLines.end(); ++iter)
		startThread((*iter));
}
