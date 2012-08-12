#include "scUiAnimationGroup.h"


scUiAnimationGroup::scUiAnimationGroup(bool isLoop)
	: scUiAnimation(isLoop)
{
}


scUiAnimationGroup::~scUiAnimationGroup(void)
{
}

void scUiAnimationGroup::_run( u32 dtms )
{
	if (getCurrentState() != AS_RUNNING)
		return;
	if (mAnimations.empty())
		setCurrentState(AS_FINISHED);

	auto iter = mAnimations.begin();
	while (iter != mAnimations.end())
	{
		(*iter)->_run(dtms);
		if ((*iter)->getCurrentState() == scAnimation::AS_FINISHED)
			iter = mAnimations.erase(iter);
		else
			++iter;
	}
}

void scUiAnimationGroup::_registerWidget( MyGUI::Widget* widget )
{
	for (auto iter = mAnimations.begin(); iter != mAnimations.end(); ++iter)
		(*iter)->_registerWidget(widget);
}

void scUiAnimationGroup::addAnimation( scUiAnimationPtr ani )
{
	mAnimations.push_back(ani);
}

scAnimationPtr scUiAnimationGroupFactory::createAnimation( bool isLoop )
{
	return scAnimationPtr(new scUiAnimationGroup(isLoop));
}
