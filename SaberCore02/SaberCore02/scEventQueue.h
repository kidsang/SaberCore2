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
//class scEvent;
#include "scEvent.h"

/// 消息队列
/// 该类是线程安全的
class scEventQueue : boost::noncopyable
{
	typedef std::deque<scEvent> EventQueue;

public:
	/// 构造函数
	/// @param name 该队列的名称
	explicit scEventQueue(string const& name);
	scEventQueue();
	~scEventQueue(void);

	/// 将事件put到输入队列
	/// @param evt 要被放入队列的事件
	void putEvent(scEvent const& evt);

	/// 从输出队列中一次过fetch出所有的事件,被取出的事件将会放在eventsOut中
	/// @param eventsOut 被取出的事件列表
	void fetchEvents(std::vector<scEvent> & eventsOut);

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

