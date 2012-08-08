#include "scAnimation.h"
#include "scKeyFrame.h"

void scAnimation::_run( u32 dtms )
{
	if (mCurrentState != AS_RUNNING)
		return;
	if (mKeyFrameList.empty())
	{
		mCurrentState = AS_FINISHED;
		return;
	}

	mCurrentTime += dtms;

	// 单帧
	if (mKeyFrameList.size() == 1)
	{
		if (mIsLoop && mCurrentTime >= mKeyFrameList.begin()->first) // 单帧且循环
		{
			runImpl(mKeyFrameList.begin()->second, mKeyFrameList.begin()->second);
			mCurrentTime -= mKeyFrameList.begin()->first;
		}
		else
		{
			mCurrentState = AS_FINISHED;
			return;
		}
	}
	else
	{
		auto endIter = mKeyFrameList.rbegin();

		// 时间超过动画长度
		if (mCurrentTime > endIter->first)
		{
			if (mIsLoop || mRepeatTimes > 0)
			{
				if (mRepeatTimes > 0)
					mRepeatTimes--;
				mCurrentTime %= endIter->first;
			}
			else
			{
				mCurrentState = AS_FINISHED;
				mCurrentTime = endIter->first; // 播放最后一帧
			}
		}

		// 找到对应的两帧
		auto k0iter = mKeyFrameList.begin();
		auto k1iter = mKeyFrameList.begin();
		++k1iter;
		while (k1iter != mKeyFrameList.end())
		{
			if (mCurrentTime >= k0iter->first && mCurrentTime <= k1iter->first)
				break;
			++k0iter;
			++k1iter;
		}
		runImpl(k0iter->second, k1iter->second);
	}
}

scAnimation::scAnimation( bool isLoop ) 
	: mIsLoop(isLoop), mCurrentTime(0), mRepeatTimes(0), mCurrentState(AS_RUNNING)
{

}

scAnimation::~scAnimation()
{
	for (auto iter = mKeyFrameList.begin(); iter != mKeyFrameList.end(); ++iter)
		delete iter->second;
}

void scAnimation::addKeyFrame( scKeyFrame* keyFrame )
{
	auto iter = mKeyFrameList.find(keyFrame->getTime());
	if (iter != mKeyFrameList.end())
		mKeyFrameList.erase(iter); // 先移除之前的

	mKeyFrameList.insert(std::make_pair(keyFrame->getTime(), keyFrame));
}

void scAnimation::destoryKeyFrame( u32 time )
{
	auto iter = mKeyFrameList.find(time);
	if (iter != mKeyFrameList.end())
	{
		delete iter->second;
		mKeyFrameList.erase(iter);
	}
}

void scAnimation::destoryKeyFrame( scKeyFrame* keyFrame )
{
	auto iter = mKeyFrameList.begin();
	for (; iter != mKeyFrameList.end(); ++iter)
		if (iter->second == keyFrame)
			break;
	if (iter != mKeyFrameList.end())
	{
		delete iter->second;
		mKeyFrameList.erase(iter);
	}
}
