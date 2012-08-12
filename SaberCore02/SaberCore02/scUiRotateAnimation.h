#ifndef scUiRotateAnimation_h__
#define scUiRotateAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include "scKeyFrame.h"

/// UI 旋转动画
/// 注意，并不是所有UI元件都支持旋转
/// 支持列表：ImageBox(skin为RotatingSkin)
class scUiRotateAnimation : public scUiAnimation
{
public:
	/// 构造函数
	/// @param isLoop 动画是否循环播放
	scUiRotateAnimation(bool isLoop);
	~scUiRotateAnimation(void);

	/// 创建一个关键帧，并将其加入关键帧列表
	/// @param time 关键帧时间, 单位为毫秒
	/// @param radian UI元件的旋转角度，以弧度制为单位，可以为负数
	/// @param centerX 旋转中心x坐标，0.5即为元件中心
	/// @param centerY 旋转中心y坐标，0.5即为元件中心
	/// @param itype 插值方法类型
	void createKeyFrame(u32 time, f32 radian, f32 centerX = 0.5f, f32 centerY = 0.5f, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFramePtr k0, scKeyFramePtr k1 );

};

class scUiRotateAnimationFactory : public scAnimationFactory
{
public:
	/// 构造函数
	/// @param name 每个工厂都有一个独一无二的名字
	/// 以供AnimationManager类标识
	scUiRotateAnimationFactory(string const& name)
		: scAnimationFactory(name)
	{}

	/// 创建动画的具体实现
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画指针
	virtual scAnimationPtr createAnimation( bool isLoop );

};
#endif // scUiRotateAnimation_h__

