#include "scTimeLineManager.h"
#include "scTimeLine.h"
#include "scError.h"


scTimeLinePtr const& scTimeLineManager::createTimeLine( const string& name, u32 invokeRate, i32 priority /*= 0*/, bool threading /*= false*/ )
{
	// ���ȼ����û�����ֳ�ͻ
	auto iter = mTimeLines.begin();
	for (; iter != mTimeLines.end(); ++iter)
		if (iter->second->getName() == name)
			break;
	scAssert(mTimeLines.empty() || iter == mTimeLines.end(), "Time line name \"" + name +"\" already exist.");

	scTimeLinePtr tl = scTimeLinePtr(new scTimeLine(name, invokeRate));
	auto tliter = mTimeLines.insert(std::make_pair(priority, tl));

	// �����Ҫ�ڷ�֧�߳������У����Ȱ����ּ�������
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

scTimeLineManager::scTimeLineManager()
	: mStopRequested(false)
{

}

scTimeLineManager::~scTimeLineManager()
{
	// �����߳�
	for (auto iter = mThreads.begin(); iter != mThreads.end(); ++iter)
		(*iter)->join();
}

void scTimeLineManager::startMain()
{
	// ��ʼ��ʱ��
	u32 lastTime = clock();
	u32 currentTime = clock();
	u32 dtms;

	// ����ѭ��
	while (!mStopRequested)
	{
		currentTime = clock();
		dtms = currentTime - lastTime;

		for (auto iter = mTimeLines.begin(); iter != mTimeLines.end(); ++iter)
		{
			// ֻ���������̵߳�ʱ����
			if (iter->second->getThreadStatus() == scTimeLine::TS_MAIN)
				iter->second->_run(dtms);
		}

		lastTime = currentTime;
	}
}

void scTimeLineManager::startThread( string const& name )
{
	scTimeLinePtr tl = getTimeLine(name);

	// ���¶�Ӧʱ�����߳�״̬
	scAssert(tl->getThreadStatus() == scTimeLine::TS_MAIN, "Time line name \"" + name +"\" already running in a thread.");
	tl->setThreadStatus(scTimeLine::TS_THREAD);

	// �����߳�
	ThreadPtr thread = ThreadPtr(new boost::thread([=](){this->runThread(tl);}));
	mThreads.push_back(thread);
	
}

void scTimeLineManager::runThread( scTimeLinePtr timeLine )
{
	u32 lastTime = clock();
	u32 currentTime = clock();
	// ����ʱ����
	while (!mStopRequested)
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
