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
	explicit scUiScaleAnimation(bool isLoop);
	~scUiScaleAnimation(void);

	/// 为动画注册宿主(作用对象)
	/// 仅供内部使用，由scRenderer调用
	/// @param widget 动画作用的对象，一个UI元件
	virtual void _registerWidget(MyGUI::Widget* widget);

	/// 创建一个关键帧，并将其加入关键帧列表
	/// @param time 关键帧时间, 单位为毫秒
	/// @param scaleX UI元件在X轴方向上的伸缩量
	/// @param scaleY UI元件在Y轴方向上的伸缩量
	/// @param itype 插值方法类型
	void createKeyFrame(u32 time, f32 scaleX, f32 scaleY, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFramePtr k0, scKeyFramePtr k1 );

private:
	int mOriginWidth;
	int mOriginHeight;

	//struct ScaleParams
	//{
	//	f32 scaleX;
	//	f32 scaleY;

	//	ScaleParams(f32 sX, f32 sY)
	//		: scaleX(sX), scaleY(sY)
	//	{}

	//	ScaleParams operator + (ScaleParams const& s)
	//	{ return ScaleParams(scaleX + s.scaleX, scaleY + s.scaleY);	}

	//	ScaleParams operator - (ScaleParams const& s)
	//	{ return ScaleParams(scaleX - s.scaleX, scaleY - s.scaleY);	}

	//	ScaleParams operator * (ScaleParams const& s)
	//	{ return ScaleParams(scaleX * s.scaleX, scaleY * s.scaleY);	}

	//	ScaleParams operator / (ScaleParams const& s)
	//	{ return ScaleParams(scaleX / s.scaleX, scaleY / s.scaleY);	}
	//};
};

#endif // scUiScaleAnimation_h__

