#include "scEventQueue.h"
#include "scEvent.h"


scEventQueue::scEventQueue(string const& name)
	: mName(name)
{
}

scEventQueue::scEventQueue()
{

}


scEventQueue::~scEventQueue(void)
{
}

void scEventQueue::putEvent( scEventPtr const& evt )
{
	boost::mutex::scoped_lock lock(mMutex);
	mEvents.push_back(evt);
}

//bool const scEventQueue::fetchEvent( scEventPtr & evtOut )
//{
//	boost::mutex::scoped_lock lock(mMutex);
//
//	if (mEvents.empty())
//		return false;
//
//	evtOut = mEvents.at(0);
//	mEvents.pop_front();
//	return true;
//}

void scEventQueue::fetchEvents( std::vector<scEventPtr> & eventsOut )
{
	boost::mutex::scoped_lock lock(mMutex);
	eventsOut.resize(mEvents.size());
	std::copy(mEvents.begin(), mEvents.end(), eventsOut.begin());
	//for (auto iter = mEvents.begin(); iter != mEvents.end(); ++iter)
	//	eventsOut.push_back(*iter);
	mEvents.clear();
}
