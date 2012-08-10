#include "scAnimationTimeLine.h"


scAnimationTimeLine::scAnimationTimeLine(string const& name, u32 invokeRate)
	: scTimeLine(name, invokeRate)
{
}


scAnimationTimeLine::~scAnimationTimeLine(void)
{
}

bool scAnimationTimeLine::runImpl( u32 dtms )
{
	// 先调用父类的
	scTimeLine::runImpl(dtms);
	// 执行动画
	for (auto iter = mAnimations.begin(); iter != mAnimations.end(); ++iter)
	{
		(*iter)->_run(dtms);
		// 清除结束的动画
		if ((*iter)->getCurrentState() == scAnimation::AS_FINISHED)
		{
			iter = mAnimations.erase(iter);
			if (iter == mAnimations.end())
				break;
		}
	}
	return true;
}
