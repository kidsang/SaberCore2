#ifndef scEventRouter_h__
#define scEventRouter_h__

/**
 * 文件：scEventRouter
 * 日期：2012/07/16
 * 作者：kid
 */

#include <boost/thread.hpp>
#include <queue>
#include "OgreSingleton.h"
#include "scTypeDefine.h"
class scEventQueue;
struct scEvent;

typedef shared_ptr<scEvent> scEventPtr;

/// 事件路由器
/// 用户将事件放入输入队列中
/// 事件会被路由至指定的输出队列
/// 用户而后可以从指定的输出队列中提取消息
class scEventRouter : public Ogre::Singleton<scEventRouter>
{
	typedef shared_ptr<scEventQueue> EventQueuePtr;
	typedef std::map<string, EventQueuePtr> QueueNameMap;
	/// 用以指示哪种事件应该去到哪个outputQueue
	typedef std::map<string, string> EventMap;

public:
	/// 创建输出队列
	/// @param name 输出队列的名称
	void createOutputQueue(string const& name);

	/// 注册事件
	/// @param evtName 事件的名称，也就是事件的类型
	/// @param queName 事件的目的地名称，也就是将要被路由到的输出队列的名称
	void registerEvent(string const& evtName, string const& queName);

	/// 将事件put到输入队列
	/// @param evt 要被放入队列的事件
	void putEvent(scEventPtr const& evt);

	/// 从输出队列中一次过fetch出所有的事件,被取出的事件将会放在eventsOut中
	/// @param queName 输出队列的名称
	/// @param eventsOut 被取出的事件列表
	void fetchEvents(string const& queName, std::vector<scEventPtr> & eventsOut);

	
	// 执行路由工作
	// 不停地从input queue中fetch，并put到output queue中
	// 仅供内部使用，由TimeLine调用
	void _run();

	/// Override standard Singleton retrieval.
	static scEventRouter& getSingleton(void);
	/// Override standard Singleton retrieval.
	static scEventRouter* getSingletonPtr(void);
	scEventRouter();
	~scEventRouter();

private:
	shared_ptr<scEventQueue> mInputQueue;
	std::vector<scEventPtr> mEvents;
	QueueNameMap mOutputQueues;
	EventMap mEventMap;
	boost::mutex mQueueMutex;

};

#endif // scEventRouter_h__

