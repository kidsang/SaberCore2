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
/// 支持列表：ImageBox
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
	/// @param itype 插值方法类型
	void createKeyFrame(u32 time, f32 radian, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFrame* k0, scKeyFrame* k1 );

};

#endif // scUiRotateAnimation_h__

