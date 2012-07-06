#ifndef scTimeLine_h__
#define scTimeLine_h__

/**
 * 文件：scTimeLine
 * 日期：2012/07/01
 * 作者：kid
 */

#include "scTypeDefine.h"
#include <list>
#include <map>
#include <functional>

/// 时间轴
/// 时间轴控制了挂载在其上物体的调用频率
/// 时间轴还控制时间的缩放
class scTimeLine
{
	typedef std::function<bool (u32)> FrameCallBack;
	typedef std::map<string, FrameCallBack> FrameCallBackMap;
public:
	/// 构造函数
	/// @param name 该时间轴的名称
	/// @param invokeRate 该时间轴的调用频率。例如：60Hz，就是每秒调用60次。
	scTimeLine(string const& name, u32 invokeRate);
	virtual ~scTimeLine();

	/// 运行时间轴
	/// 仅供内部使用，该函数应该由scTimeLineManager调用
	/// 为时间轴增加时间。增加的时间将被乘以时间缩放因子，因而可以变为负数
	/// 当时间轴累计时间大于调用间隔(或者是小于负调用间隔)，将会触发所有挂载的回调函数
	/// @param dtms 上一次调用到这次调用所经过的时间间隔，以毫秒计算
	/// @return TODO: 找到该返回值的意义
	bool _run(u32 dtms);

	/// 添加一条帧回调函数，该函数将会按照时间轴的调用频率每帧调用
	/// @param name 回调函数的名称
	/// @param callback 回调函数，其实是仿函数，可以使用lambda表达式生成
	///	例如：[&mRenderer](u32 dtms)->bool{return mRenderer->run(dtms);}
	void addRunCallBack(string const& name, FrameCallBack const& callback);

	/// 移除一条帧回调函数
	/// @param name 回调函数的名称
	void removeRunCallBack(string const& name);

public:
	/// 返回该时间轴的名字
	const string& getName()
	{
		return mName;
	}

	/// 返回时间缩放系数
	/// 时间被累加到时间轴之前会乘以时间缩放系数
	/// 改变时间缩放系数将影响时间轴和其上动画的动画速度
	f32 getScaleFactor()
	{
		return mScaleFactor;
	}
	/// 设置时间缩放系数
	/// 时间被累加到时间轴之前会乘以时间缩放系数
	/// 改变时间缩放系数将影响时间轴和其上动画的动画速度
	void setScaleFactor(f32 scaleFactor)
	{
		if (scaleFactor < 0)
			mScaleFactor = 0;
		else
			mScaleFactor = scaleFactor;
	}

	/// 返回时间轴两次调用之间的时间间隔
	/// 以毫秒为单位
	u32 getInvokeInterval()
	{
		return mInterval;
	}
	/// 设置时间轴两次调用之间的时间间隔
	/// 以毫秒为单位
	void setInvokeInterval(u32 interval)
	{
		mInterval = interval;
	}

	/// 返回时间轴的调用频率
	/// 以赫兹为单位(即每秒多少次)
	u32 getInvokeRate()
	{
		return 1000 / mInterval;
	}
	/// 设置时间轴的调用频率
	/// 以赫兹为单位(即每秒多少次)
	void setInvokeRate(u32 rate)
	{
		mInterval = (1000 / rate);
	}

protected:
	/// 运行逻辑的实现
	/// 子类可以通过重载此函数以增加运行逻辑
	virtual bool runImpl(u32 dtms);

private:
	string mName;
	f32 mScaleFactor;
	u32 mInterval;
	u32 mCurrentTime;
	FrameCallBackMap mCallBackMap;
};

#endif // scTimeLine_h__

