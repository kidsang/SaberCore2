#include "scTimeLine.h"

scTimeLine::scTimeLine( const string& name, u32 invokeRate )
	: mName(name), mInterval(1000 / invokeRate), mCurrentTime(0),
	mScaleFactor(1.0f)
{

}

scTimeLine::~scTimeLine()
{
}

bool scTimeLine::_run( u32 dtms )
{
	// 时间控制
	mCurrentTime += dtms;
	if (mCurrentTime < mInterval)
		return true;

	// 缩放时间
	u32 time = (u32)(mCurrentTime * mScaleFactor);

	// TODO: 加入代码

	// 时间控制
	mCurrentTime = 0;

	return true;
}