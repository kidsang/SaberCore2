#include "scEventRouter.h"
#include "scError.h"
#include "scEvent.h"
#include "scEventQueue.h"

scEventQueuePtr scEventRouter::createEventQueue( string const& name )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// ȷ����Ϣ���в��������ֳ�ͻ
	scAssert(mOutputQueues.find(name) == mOutputQueues.end(), "Output queue name \"" + name + "\" already exist.");
	auto iter = mOutputQueues.insert(std::make_pair(name, scEventQueuePtr(new scEventQueue(name))));
	return iter.first->second;
}

void scEventRouter::registerEvent( string const& evtName, string const& queName )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// ȷ����Ϣ���Ͳ��������ֳ�ͻ
	scAssert(mEventMap.find(evtName) == mEventMap.end(), "Event name \""+ evtName +"\" already exist.");
	// ȷ����Ϣ���д���
	auto iter = mOutputQueues.find(queName);
	scAssert(iter != mOutputQueues.end(), "Output queue named \"" + queName + "\" do not exist.");

	mEventMap.insert(std::make_pair(evtName, queName));
}

void scEventRouter::putEvent( scEventPtr const& evt )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// ȷ����Ϣ���ʹ���
	scAssert(mEventMap.find(evt->name) != mEventMap.end(), "Event name \""+ evt->name +"\" do not exist.");

	mInputQueue->putEvent(evt);
}

//void scEventRouter::fetchEvents(string const& queName, std::vector<scEventPtr> & eventsOut)
//{
//	boost::mutex::scoped_lock lock(mQueueMutex);
//	// ȷ����Ϣ���д���
//	auto iter = mOutputQueues.find(queName);
//	scAssert(iter != mOutputQueues.end(), "Output queue named \"" + queName + "\" do not exist.");
//	iter->second->fetchEvents(eventsOut);
//}

scEventQueuePtr scEventRouter::getEventQueue( string const& queName )
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// ȷ����Ϣ���д���
	auto iter = mOutputQueues.find(queName);
	scAssert(iter != mOutputQueues.end(), "Output queue named \"" + queName + "\" do not exist.");
	return iter->second;
}

void scEventRouter::_run()
{
	boost::mutex::scoped_lock lock(mQueueMutex);
	// �����������fetch
	mInputQueue->fetchEvents(mEvents);
	for (auto iter = mEvents.begin(); iter != mEvents.end(); ++iter)
	{
		// put����Ӧ�������
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
