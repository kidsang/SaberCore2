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
/// 动画组的循环与否取决于其内部的动画
class scUiAnimationGroup : public scUiAnimation
{
	typedef std::vector<scUiAnimationPtr> AnimationList;

public:
	/// 构造函数
	explicit scUiAnimationGroup();
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
	virtual void runImpl( scKeyFramePtr k0, scKeyFramePtr k1 )
	{ 
		// 该类没有runImpl 
	}

private:
	AnimationList mAnimations;
};

class scUiAnimationGroupFactory : public scAnimationFactory
{
public:
	/// 构造函数
	/// @param name 每个工厂都有一个独一无二的名字
	/// 以供AnimationManager类标识
	scUiAnimationGroupFactory(string const& name)
		: scAnimationFactory(name)
	{}

	/// 创建动画的具体实现
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画指针
	virtual scAnimationPtr createAnimation( bool isLoop );
};

#endif // scUiAnimationGroup_h__

