#include "scEventRouter.h"
#include "scError.h"
#include "scEvent.h"

void scEventRouter::createOutputQueue( string const& name )
{
	boost::mutex::scoped_lock lock(mOutputMutex);
	// ȷ����Ϣ���в��������ֳ�ͻ
	scAssert(mOutputQueues.find(name) == mOutputQueues.end(), "Output queue name \"" + name + "\" already exist.");
	mOutputQueues.insert(std::make_pair(name, EventQueuePtr(new EventQueue())));
}

void scEventRouter::registerEvent( string const& evtName, string const& queName )
{
	boost::mutex::scoped_lock lock(mOutputMutex);
	// ȷ����Ϣ���Ͳ��������ֳ�ͻ
	scAssert(mEventMap.find(evtName) == mEventMap.end(), "Event name \""+ evtName +"\" already exist.");
	// ȷ����Ϣ���д���
	auto iter = mOutputQueues.find(queName);
	scAssert(iter != mOutputQueues.end(), "Output queue named \"" + queName + "\" do not exist.");

	mEventMap.insert(std::make_pair(evtName, queName));
}

void scEventRouter::putEvent( scEventPtr const& evt )
{
	boost::mutex::scoped_lock lock(mInputMutex);
	// ȷ����Ϣ���ʹ���
	scAssert(mEventMap.find(evt->name) != mEventMap.end(), "Event name \""+ evt->name +"\" do not exist.");

	mInputQueue.push_back(evt);
}

bool const scEventRouter::fetchEvent( string const& queName, scEventPtr & evtOut )
{
	boost::mutex::scoped_lock lock(mOutputMutex);
	// ȷ����Ϣ���д���
	auto iter = mOutputQueues.find(queName);
	scAssert(iter != mOutputQueues.end(), "Output queue named \"" + queName + "\" do not exist.");

	if (iter->second->empty())
		return false;

	evtOut = iter->second->at(0);
	iter->second->pop_front();
	return true;
}

void scEventRouter::_run()
{
	boost::mutex::scoped_lock inlock(mInputMutex);
	boost::mutex::scoped_lock outlock(mOutputMutex);
	while (!mInputQueue.empty())
	{
		// �����������fetch
		scEventPtr evt = mInputQueue.at(0);
		mInputQueue.pop_front();
		// put����Ӧ�������
		string outname = mEventMap.find(evt->name)->second;
		auto output = mOutputQueues.find(outname);
		output->second->push_back(evt);
	}
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
{

}

scEventRouter::~scEventRouter()
{

}
