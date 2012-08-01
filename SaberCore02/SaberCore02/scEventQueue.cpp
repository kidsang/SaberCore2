#include "scEventQueue.h"
//#include "scEvent.h"


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

void scEventQueue::putEvent( scEvent const& evt )
{
	boost::mutex::scoped_lock lock(mMutex);
	mEvents.push_back(evt);
}

void scEventQueue::fetchEvents( std::vector<scEvent> & eventsOut )
{
	boost::mutex::scoped_lock lock(mMutex);
	eventsOut.resize(mEvents.size());
	std::copy(mEvents.begin(), mEvents.end(), eventsOut.begin());
	//for (auto iter = mEvents.begin(); iter != mEvents.end(); ++iter)
	//	eventsOut.push_back(*iter);
	mEvents.clear();
}
