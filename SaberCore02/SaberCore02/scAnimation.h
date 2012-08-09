#ifndef scAnimation_h__
#define scAnimation_h__

/**
 * 文件：scAnimation
 * 日期：2012/07/03
 * 作者：kid
 */

#include "scTypeDefine.h"
#include <map>

class scKeyFrame;

/// 动画基类
/// sc中的动画通过改变物体的属性来实现
///	我希望能够得到WPF那样的属性动画，因此我需要将三件东西绑定在一起
///	1. 特定属性类型的动画，如vector3Animation
///	2. 需要被动画作用的类的实例，如SceneNode* node
///	3. 需要被动画所改变的属性，例如node的位置position属性
/// 同时，动画类通过类似Flash中的关键帧实现
/// 用户指定若干关键帧，动画将在这些帧之间差值
class scAnimation
{
public:
	typedef std::map<u32, scKeyFrame*> KeyFrameList;

	enum AnimationState
	{
		AS_RUNNING, AS_PAUSED, AS_FINISHED
	};

	/// 构造函数
	/// @param isLoop 动画是否循环播放
	explicit scAnimation(bool isLoop);
	virtual ~scAnimation();

	/// 运行动画
	/// 仅供内部使用，该函数应该由scTimeLine调用
	/// @param dtms 上一次调用到这次调用所经过的时间间隔，以毫秒计算
	virtual void _run(u32 dtms);

	/// 删除关键帧
	/// 将关键帧从列表中移除，并销毁
	/// @param keyFrame 要销毁的关键帧
	void destoryKeyFrame(scKeyFrame* keyFrame);

	/// 删除关键帧
	/// 将关键帧从列表中移除，并销毁
	/// @param time 关键帧所在时间
	void destoryKeyFrame(u32 time);

	// get/set
public:
	/// 获取当前动画是否循环
	bool isLoop()
	{ return mIsLoop; }
	/// 设置当前动画是否循环
	void setLoop(bool isloop)
	{ mIsLoop = isloop; }

	/// 返回当前时间
	u32 getTime()
	{ return mCurrentTime; }

	/// 返回动画重复次数
	u32 getRepeatTimes()
	{return mRepeatTimes;}
	/// 设置动画重复次数
	void setRepeatTimes(u32 repeatTimes)
	{mRepeatTimes = repeatTimes;}

	/// 返回动画当前状态
	AnimationState getCurrentState()
	{return mCurrentState;}
	/// 暂停动画
	void pause()
	{mCurrentState = AS_PAUSED;}
	/// 播放动画
	void play()
	{mCurrentState = AS_RUNNING;}
	/// 结束动画
	void stop()
	{mCurrentState = AS_FINISHED;}


protected:
	/// 运行动画的实现
	/// @param k0 当前所处时间段的前一个关键帧
	/// @param k1 当前所处时间段的后一个关键帧
	virtual void runImpl(scKeyFrame* k0, scKeyFrame* k1) = 0;

	/// 添加关键帧
	/// 该方法应该仅用于内部
	/// 特定的子类通过编写自己的createKeyFrame来实现功能
	/// 该方法仅为辅助方法
	void addKeyFrame(scKeyFrame* keyFrame);

private:
	bool mIsLoop;
	KeyFrameList mKeyFrameList;
	u32 mCurrentTime;
	u32 mRepeatTimes;
	AnimationState mCurrentState;
};

#endif // scAnimation_h__
