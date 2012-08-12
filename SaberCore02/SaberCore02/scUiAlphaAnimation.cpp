#include "scUiAlphaAnimation.h"
#include "MyGUI/MyGUI_Widget.h"
#include "scGenericKeyFrame.h"
#include "scError.h"
#include "scUtils.h"

scUiAlphaAnimation::scUiAlphaAnimation( bool isLoop )
	: scUiAnimation(isLoop)
{

}


scUiAlphaAnimation::~scUiAlphaAnimation(void)
{
}

void scUiAlphaAnimation::runImpl( scKeyFramePtr k0, scKeyFramePtr k1 )
{
	scContinuousKeyFrame<f32> *tk0, *tk1;
	tk0 = static_cast<scContinuousKeyFrame<f32>*>(k0.get());
	tk1 = static_cast<scContinuousKeyFrame<f32>*>(k1.get());

	f32 value = tk0->getInterpolationFunc()(tk0->getTime(), getTime(), tk1->getTime(), tk0->getValue(), tk1->getValue());
	getHost()->setAlpha(value);
}

void scUiAlphaAnimation::createKeyFrame( u32 time, f32 alpha, scKeyFrame::InterpolationType itype /*= scKeyFrame::IT_LINEAR*/ )
{
	scAssert(alpha >= 0.f && alpha <= 1.f, "Widget alpha must in range 0 to 1! Current: " + scToString(alpha));
	scContinuousKeyFrame<f32>* keyFrame = new scContinuousKeyFrame<f32>(time, alpha);
	keyFrame->setInterpolationType(itype);
	addKeyFrame(scKeyFramePtr(keyFrame));
}

scAnimationPtr scUiAlphaAnimationFactory::createAnimation( bool isLoop )
{
	return scAnimationPtr(new scUiAlphaAnimation(isLoop));
}
