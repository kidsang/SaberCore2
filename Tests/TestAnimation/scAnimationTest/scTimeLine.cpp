#include "scTimeLine.h"
#include "scAnimation.h"

scTimeLine::scTimeLine( const std::string& name, u32 invokeRate )
	: mName(name), mInterval(1000 / invokeRate), mCurrentTime(0),
	mScaleFactor(1.0f)
{

}

scTimeLine::~scTimeLine()
{
	for (auto iter = mAnimations.begin(); iter != mAnimations.end(); ++iter)
		delete (*iter);
}

bool scTimeLine::_run( u32 dtms )
{
	// 时间控制
	mCurrentTime += dtms;
	if (mCurrentTime < mInterval)
		return true;

	// 缩放时间
	u32 time = (u32)(mCurrentTime * mScaleFactor);
	// 执行动画
	for (auto iter = mAnimations.begin(); iter != mAnimations.end(); ++iter)
	{
		(*iter)->_run(time);
		// 清除结束的动画
		if ((*iter)->getCurrentState() == scAnimation::AS_FINISHED)
		{
			delete (*iter);
			iter = mAnimations.erase(iter);
			if (iter == mAnimations.end())
				break;
		}
	}

	// 时间控制
	mCurrentTime = 0;

	return true;
}

void scTimeLine::destoryAnimation( scAnimation* animation )
{
	auto iter = mAnimations.begin();
	for (; iter != mAnimations.end(); ++iter)
		if ((*iter) == animation)
			break;
	if (iter != mAnimations.end())
	{
		delete (*iter);
		mAnimations.erase(iter);
	}
}

void scTimeLine::destoryAnimation( u32 index )
{
	auto iter = mAnimations.begin();
	int i = 0;
	while (iter != mAnimations.end())
	{
		if (i == index)
		{
			delete (*iter);
			mAnimations.erase(iter);
			break;
		}
		++i;
		++iter;
	}
}

scVector2Animation* scTimeLine::createVector2Animation( Vector2Setter setter, bool isLoop /*= false*/ )
{
	scVector2Animation* ani = new scVector2Animation(setter, isLoop);
	mAnimations.push_back(ani);
	return ani;
}

scVector3Animation* scTimeLine::createVector3Animation( Vector3Setter setter, bool isLoop /*= false*/ )
{
	scVector3Animation* ani = new scVector3Animation(setter, isLoop);
	mAnimations.push_back(ani);
	return ani;
}

scVector4Animation* scTimeLine::createVector4Animation( Vector4Setter setter, bool isLoop /*= false*/ )
{
	scVector4Animation* ani = new scVector4Animation(setter, isLoop);
	mAnimations.push_back(ani);
	return ani;
}

scF32Animation* scTimeLine::createF32Animation( F32Setter setter, bool isLoop /*= false*/ )
{
	scF32Animation* ani = new scF32Animation(setter, isLoop);
	mAnimations.push_back(ani);
	return ani;
}
