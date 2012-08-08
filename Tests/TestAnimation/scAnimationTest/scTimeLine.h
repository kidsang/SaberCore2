#ifndef scTimeLine_h__
#define scTimeLine_h__

/**
 * 文件：scTimeLine
 * 日期：2012/07/01
 * 作者：kid
 */

#include "scTypeDefine.h"
#include <list>
#include <string>
#include "scGenericAnimation.h"

class scAnimation;

/// 时间轴
class scTimeLine
{
	typedef std::list<scAnimation*> AnimationList;

public:
	/// 构造函数
	/// @param name 该时间轴的名称
	/// @param invokeRate 该时间轴的调用频率。例如：60Hz，就是每秒调用60次。
	scTimeLine(const std::string& name, u32 invokeRate);
	~scTimeLine();

	/// 销毁一段动画，这将会附带销毁上面附着的任何动画
	/// @param timeLine 动画的实例指针。
	void destoryAnimation(scAnimation* animation);

	/// 销毁一段动画，这将会附带销毁上面附着的任何动画
	/// @param index 动画在列表中的下标索引。
	void destoryAnimation(u32 index);

	/// 运行时间轴
	/// 仅供内部使用，该函数应该由scTimeLineManager调用
	/// 为时间轴增加时间。增加的时间将被乘以时间缩放因子，因而可以变为负数
	/// 当时间轴累计时间大于调用间隔(或者是小于负调用间隔)，将会触发所有动画的调用
	/// @param dtms 上一次调用到这次调用所经过的时间间隔，以毫秒计算
	/// @return TODO: 找到该返回值的意义
	bool _run(u32 dtms);

	/// 创建一段Ogre::Vector2属性动画
	/// @param setter 包含有Ogre::Vector2类型属性的仿函数
	/// @param isLoop 是否循环播放
	/// @return 创建好的动画实例
	scVector2Animation* createVector2Animation(Vector2Setter setter, bool isLoop = false);

	/// 创建一段Ogre::Vector3属性动画
	/// @param setter 包含有Ogre::Vector3类型属性的仿函数
	/// @param isLoop 是否循环播放
	/// @return 创建好的动画实例
	scVector3Animation* createVector3Animation(Vector3Setter setter, bool isLoop = false);

	/// 创建一段Ogre::Vector4属性动画
	/// @param setter 包含有Ogre::Vector4类型属性的仿函数
	/// @param isLoop 是否循环播放
	/// @return 创建好的动画实例
	scVector4Animation* createVector4Animation(Vector4Setter setter, bool isLoop = false);

	/// 创建一段f32属性动画
	/// @param setter 包含有f32类型属性的仿函数
	/// @param isLoop 是否循环播放
	/// @return 创建好的动画实例
	scF32Animation* createF32Animation(F32Setter setter, bool isLoop = false);


public:
	/// 返回该时间轴的名字
	const std::string& getName()
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


private:
	AnimationList mAnimations;

	std::string mName;
	f32 mScaleFactor;
	u32 mInterval;
	u32 mCurrentTime;

};

#endif // scTimeLine_h__

