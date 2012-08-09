#include "scUiRotateAnimation.h"
#include "MyGUI/MyGUI_Widget.h"
#include "MyGUI/MyGUI_ISubWidgetRect.h"
#include "MyGUI/MyGUI_RotatingSkin.h"
#include "scGenericKeyFrame.h"


scUiRotateAnimation::scUiRotateAnimation(bool isLoop)
	: scUiAnimation(isLoop)
{
}


scUiRotateAnimation::~scUiRotateAnimation(void)
{
}

void scUiRotateAnimation::runImpl( scKeyFramePtr k0, scKeyFramePtr k1 )
{
	scContinuousKeyFrame<f32> *tk0, *tk1;
	tk0 = static_cast<scContinuousKeyFrame<f32>*>(k0.get());
	tk1 = static_cast<scContinuousKeyFrame<f32>*>(k1.get());

	f32 value = tk0->getInterpolationFunc()(tk0->getTime(), getTime(), tk1->getTime(), tk0->getValue(), tk1->getValue());

	MyGUI::ISubWidgetRect* m = getHost()->getSubWidgetMain();
	MyGUI::RotatingSkin* r = m->castType<MyGUI::RotatingSkin>();
	r->setAngle(value);
}

void scUiRotateAnimation::createKeyFrame( u32 time, f32 radian, scKeyFrame::InterpolationType itype /*= scKeyFrame::IT_LINEAR*/ )
{
	scContinuousKeyFrame<f32>* keyFrame = new scContinuousKeyFrame<f32>(time, radian);
	keyFrame->setInterpolationType(itype);
	addKeyFrame(scKeyFramePtr(keyFrame));
}