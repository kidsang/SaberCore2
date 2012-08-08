#ifndef scUiScaleAnimation_h__
#define scUiScaleAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include "scKeyFrame.h"
namespace MyGUI {
	class Widget;
}

/// UI 缩放动画
class scUiScaleAnimation : public scUiAnimation
{
public:
	scUiScaleAnimation(bool isLoop);
	~scUiScaleAnimation(void);

	/// 为动画注册宿主(作用对象)
	/// 仅供内部使用，由scRenderer调用
	/// @param widget 动画作用的对象，一个UI元件
	virtual void _registerWidget(MyGUI::Widget* widget);

	void createKeyFrame(u32 time, f32 alpha, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFrame* k0, scKeyFrame* k1 );

private:
	int mOriginWidth;
	int mOriginHeight;
};

#endif // scUiScaleAnimation_h__

