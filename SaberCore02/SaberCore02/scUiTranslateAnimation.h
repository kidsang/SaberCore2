#ifndef scUiTranslateAnimation_h__
#define scUiTranslateAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include "scKeyFrame.h"

/// UI 位移动画
class scUiTranslateAnimation : public scUiAnimation
{
public:
	explicit scUiTranslateAnimation(bool isLoop);
	~scUiTranslateAnimation(void);

	/// 为动画注册宿主(作用对象)
	/// 仅供内部使用，由scRenderer调用
	/// @param widget 动画作用的对象，一个UI元件
	virtual void _registerWidget(MyGUI::Widget* widget);

	/// 创建一个关键帧，并将其加入关键帧列表
	/// @param time 关键帧时间, 单位为毫秒
	/// @param offsetX UI元件在X轴方向上的偏移量
	/// @param offsetY UI元件在Y轴方向上的偏移量
	/// @param itype 插值方法类型
	void createKeyFrame(u32 time, i32 offsetX, i32 offsetY, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFramePtr k0, scKeyFramePtr k1 );

private:
	int mOriginX;
	int mOriginY;
};

class scUiTranslateAnimationFactory : public scAnimationFactory
{
public:
	/// 构造函数
	/// @param name 每个工厂都有一个独一无二的名字
	/// 以供AnimationManager类标识
	scUiTranslateAnimationFactory(string const& name)
		: scAnimationFactory(name)
	{}

	/// 创建动画的具体实现
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画指针
	virtual scAnimationPtr createAnimation( bool isLoop );
};

#endif // scUiTranslateAnimation_h__

