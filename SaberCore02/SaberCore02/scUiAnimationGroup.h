#ifndef scUiAnimationGroup_h__
#define scUiAnimationGroup_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include <vector>

/// UI动画组
/// 动画组可以将多个动画组合在一起应用于UI元件
class scUiAnimationGroup : public scUiAnimation
{
	typedef std::vector<scUiAnimationPtr> AnimationList;

public:
	explicit scUiAnimationGroup(bool isLoop);
	~scUiAnimationGroup(void);

	/// 运行动画
	/// 仅供内部使用，该函数应该由scTimeLine调用
	/// 重载scAnimation::_run()
	/// @param dtms 上一次调用到这次调用所经过的时间间隔，以毫秒计算
	virtual void _run(u32 dtms);

	/// 为动画注册宿主(作用对象)
	/// 仅供内部使用，由scRenderer调用
	/// 重载scUiAnimation::_registerWidget()
	/// @param widget 动画作用的对象，一个UI元件
	virtual void _registerWidget(MyGUI::Widget* widget);

	/// 向动画组中加入动画
	/// 特别地，动画组可以嵌套添加
	/// @param ani 需要加入的动画
	void addAnimation(scUiAnimationPtr ani);

private:
	AnimationList mAnimations;
};

#endif // scUiAnimationGroup_h__

