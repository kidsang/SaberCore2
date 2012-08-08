#ifndef scUiAlphaAnimation_h__
#define scUiAlphaAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include "scKeyFrame.h"

/// UI透明度动画
class scUiAlphaAnimation : public scUiAnimation
{
public:
	/// 构造函数
	/// @param isLoop 动画是否循环播放
	explicit scUiAlphaAnimation(bool isLoop);
	~scUiAlphaAnimation(void);

	/// 创建一个关键帧，并将其加入关键帧列表
	/// @param time 关键帧时间, 单位为毫秒
	/// @param alpha UI元件的alpha值，必须在0.f-1.f之间
	/// @param itype 插值方法类型
	void createKeyFrame(u32 time, f32 alpha, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFrame* k0, scKeyFrame* k1 );


};

#endif // scUiAlphaAnimation_h__

