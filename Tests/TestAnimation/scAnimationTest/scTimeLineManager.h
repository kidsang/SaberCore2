#ifndef scTimeLineManager_h__
#define scTimeLineManager_h__

/**
 * 文件：scTimeLineManager
 * 日期：2012/07/01
 * 作者：kid
 */

#include <map>
#include <string>
#include "OgreSingleton.h"
#include "scTypeDefine.h"

class scTimeLine;

/// 时间轴管理类
/// 负责时间轴的创建、管理和销毁工作
class scTimeLineManager : public Ogre::Singleton<scTimeLineManager>
{
	typedef std::multimap<i32, scTimeLine*> scTimeLineMap;

public:
	~scTimeLineManager();

	/// 创建一条时间轴
	/// 该时间轴将自动加入scTimeLineManager的管理队列中
	/// 如需删除该时间轴，请调用scTimeLineManager::destroyTimeLine()
	/// @param name 该时间轴的名称
	/// @param invokeRate 该时间轴的调用频率。例如：60Hz，就是每秒调用60次。
	/// @param priority 时间轴的优先级，数字越小优先级越高，优先级高的时间轴会被优先调用
	/// @return 创建好的时间轴实例
	scTimeLine* createTimeLine(const std::string& name, u32 invokeRate, i32 priority = 0);

	/// 销毁一条时间轴，这将会附带销毁上面附着的任何时间剪辑
	/// @param timeLine 时间轴的实例指针。如果不存在则会报错
	void destoryTimeLine(scTimeLine* timeLine);

	/// 销毁一条时间轴，这将会附带销毁上面附着的任何时间剪辑
	/// @param name 时间轴的名称。如果不存在则会报错
	void destoryTimeLine(std::string const& name);

	/// 设置一条时间轴的优先级
	/// @param timeLine 时间轴的实例指针。如果不存在则会报错
	/// @param priority 时间轴的优先级，数字越小优先级越高，优先级高的时间轴会被优先调用
	void setPriority(scTimeLine* timeLine, i32 priority);

	/// 设置一条时间轴的优先级
	/// @param name 时间轴的名称。如果不存在则会报错
	/// @param priority 时间轴的优先级，数字越小优先级越高，优先级高的时间轴会被优先调用
	void setPriority(std::string const& name, i32 priority);

	/// 获取指定名称的时间轴
	/// @param name 时间轴的名称。如果不存在则会报错
	/// @return 时间轴实例指针
	scTimeLine* getTimeLine(std::string const& name);

	/// 运行所有时间轴
	/// 该函数应该在每次循环的时候调用
	/// 该函数会调用每个时间轴的run()函数，并为它们增加时间
	/// @param dtms 上一次调用到这次调用所经过的时间间隔，以毫秒计算
	/// @return TODO: 找到该返回值的意义
	bool run(u32 dtms);

	/** Override standard Singleton retrieval.
	@remarks
	Why do we do this? Well, it's because the Singleton
	implementation is in a .h file, which means it gets compiled
	i32o anybody who includes it. This is needed for the
	Singleton template to work, but we actually only want it
	compiled i32o the implementation of the class based on the
	Singleton, not all of them. If we don't change this, we get
	link errors when trying to use the Singleton-based class from
	an outside dll.
	@par
	This method just delegates to the template version anyway,
	but the implementation stays in this single compilation unit,
	preventing link errors.
	*/
	static scTimeLineManager& getSingleton(void);
	/** Override standard Singleton retrieval.
	@remarks
	Why do we do this? Well, it's because the Singleton
	implementation is in a .h file, which means it gets compiled
	i32o anybody who includes it. This is needed for the
	Singleton template to work, but we actually only want it
	compiled i32o the implementation of the class based on the
	Singleton, not all of them. If we don't change this, we get
	link errors when trying to use the Singleton-based class from
	an outside dll.
	@par
	This method just delegates to the template version anyway,
	but the implementation stays in this single compilation unit,
	preventing link errors.
	*/
	static scTimeLineManager* getSingletonPtr(void);

private:
	scTimeLineMap mTimeLines;
};

#endif // scTimeLineManager_h__