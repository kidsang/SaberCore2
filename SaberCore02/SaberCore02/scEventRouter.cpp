#include "scEventRouter.h"
#include "scError.h"
#include "scEvent.h"
#include "scEventQueue.h"

void scEventRouter::createOutputQueue( string const& name )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 确保消息队列不存在名字冲突
	scAssert(mOutputQueues.find(name) == mOutputQueues.end(), "Output queue name \"" + name + "\" already exist.");
	mOutputQueues.insert(std::make_pair(name, EventQueuePtr(new scEventQueue(name))));
}

void scEventRouter::registerEvent( string const& evtName, string const& queName )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 确保消息类型不存在名字冲突
	scAssert(mEventMap.find(evtName) == mEventMap.end(), "Event name \""+ evtName +"\" already exist.");
	// 确保消息队列存在
	auto iter = mOutputQueues.find(queName);
	scAssert(iter != mOutputQueues.end(), "Output queue named \"" + queName + "\" do not exist.");

	mEventMap.insert(std::make_pair(evtName, queName));
}

void scEventRouter::putEvent( scEventPtr const& evt )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 确保消息类型存在
	scAssert(mEventMap.find(evt->name) != mEventMap.end(), "Event name \""+ evt->name +"\" do not exist.");

	mInputQueue->putEvent(evt);
}

void scEventRouter::fetchEvents(string const& queName, std::vector<scEventPtr> & eventsOut)
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 确保消息队列存在
	auto iter = mOutputQueues.find(queName);
	scAssert(iter != mOutputQueues.end(), "Output queue named \"" + queName + "\" do not exist.");
	iter->second->fetchEvents(eventsOut);
}

void scEventRouter::_run()
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 从输入队列中fetch
	mInputQueue->fetchEvents(mEvents);
	for (auto iter = mEvents.begin(); iter != mEvents.end(); ++iter)
	{
		// put到相应输出队列
		string outname = mEventMap.find((*iter)->name)->second;
		auto output = mOutputQueues.find(outname);
		output->second->putEvent(*iter);
	}
	mEvents.clear();
}

template<> scEventRouter* Ogre::Singleton<scEventRouter>::ms_Singleton = 0;
scEventRouter& scEventRouter::getSingleton( void )
{
	assert( ms_Singleton );  return ( *ms_Singleton ); 
}

scEventRouter* scEventRouter::getSingletonPtr( void )
{
	return ms_Singleton;
}

scEventRouter::scEventRouter()
	: mInputQueue(shared_ptr<scEventQueue>(new scEventQueue()))
{
}

scEventRouter::~scEventRouter()
{

}
