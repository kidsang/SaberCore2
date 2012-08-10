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
	// �ȵ��ø����
	scTimeLine::runImpl(dtms);
	// ִ�ж���
	for (auto iter = mAnimations.begin(); iter != mAnimations.end(); ++iter)
	{
		(*iter)->_run(dtms);
		// ��������Ķ���
		if ((*iter)->getCurrentState() == scAnimation::AS_FINISHED)
		{
			iter = mAnimations.erase(iter);
			if (iter == mAnimations.end())
				break;
		}
	}
	return true;
}
