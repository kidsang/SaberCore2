#include "scTimeLine.h"
#include "scError.h"

scTimeLine::scTimeLine( const string& name, u32 invokeRate )
	: mName(name), mInterval(1000 / invokeRate), mCurrentTime(0),
	mScaleFactor(1.0f), mThreadStatus(TS_MAIN)
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
	runImpl(time);

	// 时间控制
	mCurrentTime = 0;

	return true;
}

bool scTimeLine::runImpl( u32 dtms )
{
	// 逐个调用回调函数
	for (auto iter = mCallBackMap.begin(); iter != mCallBackMap.end(); ++iter)
		iter->second(dtms);
	return true;
}

void scTimeLine::addRunCallBack( string const& name, FrameCallBack const& callback )
{
	// 首先确定没有名字冲突
	scAssert(mCallBackMap.find(name) == mCallBackMap.end(), "Timeline call back name \"" + name + "\" already exist.");
	mCallBackMap.insert(std::make_pair(name, callback));
}

void scTimeLine::removeRunCallBack( string const& name )
{
	auto iter = mCallBackMap.find(name);
	// 确保存在
	scAssert(iter != mCallBackMap.end(), "Timeline call back named \"" + name + "\" do not exist.");
	mCallBackMap.erase(iter);
}
