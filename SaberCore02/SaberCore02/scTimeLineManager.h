#ifndef scTimeLineManager_h__
#define scTimeLineManager_h__

/**
 * 文件：scTimeLineManager
 * 日期：2012/07/01
 * 作者：kid
 */

#include <map>
#include <ctime>
#include <vector>
#include "OgreSingleton.h"
#include "scTypeDefine.h"

class scTimeLine;
typedef shared_ptr<scTimeLine> scTimeLinePtr;

/// 时间轴管理类
/// 负责时间轴的创建、管理和销毁工作
/// 单例
class scTimeLineManager : public Ogre::Singleton<scTimeLineManager>
{
	typedef std::multimap<i32, scTimeLinePtr> TimeLineMap;
	typedef boost::shared_ptr<boost::thread> ThreadPtr;
	typedef std::vector<ThreadPtr> ThreadList;
	typedef std::vector<string> ThreadingTimeLines;

public:
	~scTimeLineManager();

	/// 创建一条时间轴
	/// 该时间轴将自动加入scTimeLineManager的管理队列中
	/// 如需删除该时间轴，请调用scTimeLineManager::destroyTimeLine()
	/// @param name 该时间轴的名称
	/// @param invokeRate 该时间轴的调用频率。例如：60Hz，就是每秒调用60次。
	/// @param priority 时间轴的优先级，数字越小优先级越高，优先级高的时间轴会被优先调用
	/// @param threading 时间轴是否要运行于单独的线程，默认运行于主线程
	/// @return 创建好的时间轴实例
	scTimeLinePtr const& createTimeLine(const string& name, u32 invokeRate, i32 priority = 0, bool threading = false);

	/// 销毁一条时间轴，这将会附带销毁上面附着的任何时间剪辑
	/// @param timeLine 时间轴的实例指针。如果不存在则会报错
	void destoryTimeLine(scTimeLinePtr const& timeLine);

	/// 销毁一条时间轴，这将会附带销毁上面附着的任何时间剪辑
	/// @param name 时间轴的名称。如果不存在则会报错
	void destoryTimeLine(string const& name);

	/// 设置一条时间轴的优先级
	/// @param timeLine 时间轴的实例指针。如果不存在则会报错
	/// @param priority 时间轴的优先级，数字越小优先级越高，优先级高的时间轴会被优先调用
	void setPriority(scTimeLinePtr const& timeLine, i32 priority);

	/// 设置一条时间轴的优先级
	/// @param name 时间轴的名称。如果不存在则会报错
	/// @param priority 时间轴的优先级，数字越小优先级越高，优先级高的时间轴会被优先调用
	void setPriority(string const& name, i32 priority);

	/// 获取指定名称的时间轴
	/// @param name 时间轴的名称。如果不存在则会报错
	/// @return 时间轴实例指针
	scTimeLinePtr const& getTimeLine(string const& name);

	/// 运行所有主线程时间轴
	/// 该函数会调用每个时间轴的run()函数，并为它们增加时间
	void startMain();

	/// 运行所有分支线程时间轴
	/// 注意同一条时间轴要不就在主线程，要不就在分支线程，不可同时在多条线程
	void startThreads();


	/// Override standard Singleton retrieval.
	static scTimeLineManager& getSingleton(void);
	/// Override standard Singleton retrieval.
	static scTimeLineManager* getSingletonPtr(void);

private:
	/// 运行指定名称的分支线程时间轴
	/// @param 时间轴的名称。
	/// 注意同一条时间轴要不就在主线程，要不就在分支线程，不可同时在多条线程
	void startThread(string const& name);

	/// 在新线程中运行指定的时间轴
	void runThread(scTimeLinePtr timeLine);

private:
	TimeLineMap mTimeLines;
	ThreadList mThreads;
	ThreadingTimeLines mThreadingTimeLines;

};

#endif // scTimeLineManager_h__