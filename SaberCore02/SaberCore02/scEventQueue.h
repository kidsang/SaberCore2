#ifndef scEventQueue_h__
#define scEventQueue_h__

/*
 * time: 2012/07/30
 * author: kid
 */

#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <deque>
#include <vector>
#include "scTypeDefine.h"
class scEvent;

typedef shared_ptr<scEvent> scEventPtr;

/// 消息队列
/// 该类是线程安全的
class scEventQueue : boost::noncopyable
{
	typedef std::deque<scEventPtr> EventQueue;

public:
	/// 构造函数
	/// @param name 该队列的名称
	scEventQueue(string const& name);
	scEventQueue();
	~scEventQueue(void);

	/// 将事件put到输入队列
	/// @param evt 要被放入队列的事件
	void putEvent(scEventPtr const& evt);

	/// 从输出队列中fetch,被取出的事件将会放在evtOut中
	/// @param evtOut 被取出的事件
	/// @return 如果取出事件成功(即输出队列中有事件)则返回true
	//bool const fetchEvent(scEventPtr & evtOut);

	/// 从输出队列中一次过fetch出所有的事件,被取出的事件将会放在eventsOut中
	/// @param eventsOut 被取出的事件列表
	void fetchEvents(std::vector<scEventPtr> & eventsOut);

	// get/set
public:
	/// 返回该队列的名称
	string const& getName()
	{ return mName; }

private:
	string mName;
	EventQueue mEvents;
	boost::mutex mMutex;
};

#endif // scEventQueue_h__

