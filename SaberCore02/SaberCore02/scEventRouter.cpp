#include "scEventRouter.h"
#include "scError.h"
#include "scEventQueue.h"

scEventQueuePtr scEventRouter::createEventQueue( string const& name )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 确保消息队列不存在名字冲突
	scAssert(mOutputQueues.find(name) == mOutputQueues.end(), "Output queue name \"" + name + "\" already exist.");
	auto iter = mOutputQueues.insert(std::make_pair(name, scEventQueuePtr(new scEventQueue(name))));
	return iter.first->second;
}

void scEventRouter::destroyEventQueue( string const& name )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 确保消息队列存在
	auto iter = mOutputQueues.find(name);
	scAssert(iter != mOutputQueues.end(), "Output queue named \"" + name + "\" do not exist.");
	mOutputQueues.erase(iter);
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
	scErrMsg("Register event " + evtName + " into queue " + queName);
}

void scEventRouter::unregisterEvent( string const& evtName )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 确保消息类型存在
	auto iter = mEventMap.find(evtName);
	scAssert(iter != mEventMap.end(), "Event name \""+ evtName +"\" do not exist.");
	scErrMsg("Unregister event " + evtName);
	mEventMap.erase(iter);
}

void scEventRouter::unregisterEvents( string const& queName )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	auto evtIter = mEventMap.begin();
	while (evtIter != mEventMap.end())
	{
		if (evtIter->second == queName)
		{
			scErrMsg("Unregister event " + evtIter->first);
			evtIter = mEventMap.erase(evtIter);
		}
		else
			++evtIter;
	}
}

void scEventRouter::putEvent( scEvent const& evt )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 确保消息类型存在
	//scAssert(mEventMap.find(evt.getName()) != mEventMap.end(), "Event name \""+ evt.getName()+"\" do not exist.");

	mInputQueue->putEvent(evt);
}

scEventQueuePtr scEventRouter::getEventQueue( string const& queName )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 确保消息队列存在
	auto iter = mOutputQueues.find(queName);
	scAssert(iter != mOutputQueues.end(), "Output queue named \"" + queName + "\" do not exist.");
	return iter->second;
}

void scEventRouter::_run()
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// 从输入队列中fetch
	mInputQueue->fetchEvents(mEvents);
	for (auto iter = mEvents.begin(); iter != mEvents.end(); ++iter)
	{
		// put到相应输出队列
		auto outNameIter = mEventMap.find((*iter).getName());
		if (outNameIter == mEventMap.end()) // 防止注销事件后事件队列中有残留事件
			continue;
		string outname = outNameIter->second;
		auto output = mOutputQueues.find(outname);
		if (output != mOutputQueues.end()) // 防止注销输出队列后输入队列中有残留事件
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
