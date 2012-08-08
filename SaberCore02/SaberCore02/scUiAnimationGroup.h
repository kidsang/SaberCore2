#ifndef scUiAnimationGroup_h__
#define scUiAnimationGroup_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"

/// UI动画组
/// 动画组可以将多个动画组合在一起应用于UI元件
class scUiAnimationGroup : public scUiAnimation
{
public:
	scUiAnimationGroup(void);
	~scUiAnimationGroup(void);

	/// 向动画组中加入动画
	/// 特别地，动画组可以嵌套添加
	/// @param ani 需要加入的动画
	void addAnimation(scUiAnimation const& ani);
};

#endif // scUiAnimationGroup_h__

