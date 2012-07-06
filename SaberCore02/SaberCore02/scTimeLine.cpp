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
	// ʱ�����
	mCurrentTime += dtms;
	if (mCurrentTime < mInterval)
		return true;

	// ����ʱ��
	u32 time = (u32)(mCurrentTime * mScaleFactor);

	// TODO: �������

	// ʱ�����
	mCurrentTime = 0;

	return true;
}