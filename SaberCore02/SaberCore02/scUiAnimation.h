#ifndef scUiAnimation_h__
#define scUiAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scTypeDefine.h"
#include "scAnimation.h"
#include "scError.h"
namespace MyGUI {
	class Widget;
}

/// ui动画接口类
class scUiAnimation : public scAnimation
{
public:
	/// 构造函数
	/// @param isLoop 动画是否循环播放
	explicit scUiAnimation(bool isLoop)
		: scAnimation(isLoop), mHost(0)
	{ }
	virtual ~scUiAnimation(void)
	{ }

	/// 为动画注册宿主(作用对象)
	/// 仅供内部使用，由scRenderer调用
	/// @param widget 动画作用的对象，一个UI元件
	virtual void _registerWidget(MyGUI::Widget* widget)
	{ mHost = widget; }

protected:
	/// 运行动画的实现
	/// @param k0 当前所处时间段的前一个关键帧
	/// @param k1 当前所处时间段的后一个关键帧
	virtual void runImpl( scKeyFrame* k0, scKeyFrame* k1 ) = 0;

	/// 返回动画的宿主，一个UI元件
	MyGUI::Widget* getHost()
	{ 
		scAssert(mHost != 0, "Host not exist, do you foget to call \"_registerWidget()\" ?");
		return mHost;
	}

private:
	MyGUI::Widget* mHost;

};

#endif // scUiAnimation_h__

