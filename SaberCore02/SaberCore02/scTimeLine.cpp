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
	// ʱ�����
	mCurrentTime += dtms;
	if (mCurrentTime < mInterval)
		return true;

	// ����ʱ��
	u32 time = (u32)(mCurrentTime * mScaleFactor);
	runImpl(time);

	// ʱ�����
	mCurrentTime = 0;

	return true;
}

bool scTimeLine::runImpl( u32 dtms )
{
	// ������ûص�����
	for (auto iter = mCallBackMap.begin(); iter != mCallBackMap.end(); ++iter)
		iter->second(dtms);
	return true;
}

void scTimeLine::addRunCallBack( string const& name, FrameCallBack const& callback )
{
	// ����ȷ��û�����ֳ�ͻ
	scAssert(mCallBackMap.find(name) == mCallBackMap.end(), "Timeline call back name \"" + name + "\" already exist.");
	mCallBackMap.insert(std::make_pair(name, callback));
}

void scTimeLine::removeRunCallBack( string const& name )
{
	auto iter = mCallBackMap.find(name);
	// ȷ������
	scAssert(iter != mCallBackMap.end(), "Timeline call back named \"" + name + "\" do not exist.");
	mCallBackMap.erase(iter);
}
