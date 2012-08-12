#ifndef scAnimationTimeLine_h__
#define scAnimationTimeLine_h__

/**
 * time: 2012/08/10
 * author: kid
 */

#include <deque>
#include "scTypeDefine.h"
#include "scTimeLine.h"
#include "scAnimation.h"
#include "scUiAnimation.h"

class scAnimationTimeLine : public scTimeLine
{
	typedef std::deque<scAnimationPtr> AnimationList;

public:
	/// 构造函数
	/// @param name 该时间轴的名称
	/// @param invokeRate 该时间轴的调用频率。例如：60Hz，就是每秒调用60次。
	scAnimationTimeLine(string const& name, u32 invokeRate);
	~scAnimationTimeLine(void);

	/// 在动画时间轴上挂载动画
	/// 动画只有在被挂载之后才会执行
	/// @param ani 需要被挂载的动画
	void addAnimation(scAnimationPtr const& ani)
	{ mAnimations.push_back(ani); }

	/// 在动画时间轴上挂载动画
	/// 动画只有在被挂载之后才会执行
	/// @param ani 需要被挂载的动画
	void addAnimation(scUiAnimationPtr const& ani)
	{ mAnimations.push_back(ani); }

protected:
	/// 运行逻辑的实现
	/// 子类可以通过重载此函数以增加运行逻辑
	virtual bool runImpl(u32 dtms);

private:
	AnimationList mAnimations;
};

#endif // scAnimationTimeLine_h__