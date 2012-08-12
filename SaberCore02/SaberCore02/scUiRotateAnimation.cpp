#include "scUiRotateAnimation.h"
#include "MyGUI/MyGUI_Widget.h"
#include "MyGUI/MyGUI_ISubWidgetRect.h"
#include "MyGUI/MyGUI_RotatingSkin.h"
#include "scGenericKeyFrame.h"
#include "OgreVector3.h"


scUiRotateAnimation::scUiRotateAnimation(bool isLoop)
	: scUiAnimation(isLoop)
{
}


scUiRotateAnimation::~scUiRotateAnimation(void)
{
}

void scUiRotateAnimation::runImpl( scKeyFramePtr k0, scKeyFramePtr k1 )
{
	scContinuousKeyFrame<Ogre::Vector3> *tk0, *tk1;
	tk0 = static_cast<scContinuousKeyFrame<Ogre::Vector3>*>(k0.get());
	tk1 = static_cast<scContinuousKeyFrame<Ogre::Vector3>*>(k1.get());

	Ogre::Vector3 value = tk0->getInterpolationFunc()(tk0->getTime(), getTime(), tk1->getTime(), tk0->getValue(), tk1->getValue());

	MyGUI::ISubWidgetRect* m = getHost()->getSubWidgetMain();
	MyGUI::RotatingSkin* r = m->castType<MyGUI::RotatingSkin>();
	r->setCenter(MyGUI::IntPoint((i32)(value.y * getHost()->getWidth()), (i32)(value.z * getHost()->getHeight())));
	r->setAngle(value.x);
}

void scUiRotateAnimation::createKeyFrame( u32 time, f32 radian, f32 centerX /*= 0.5f*/, f32 centerY /*= 0.5f*/, scKeyFrame::InterpolationType itype /*= scKeyFrame::IT_LINEAR*/ )
{
	scContinuousKeyFrame<Ogre::Vector3>* keyFrame = new scContinuousKeyFrame<Ogre::Vector3>(time, Ogre::Vector3(radian, centerX, centerY));
	keyFrame->setInterpolationType(itype);
	addKeyFrame(scKeyFramePtr(keyFrame));
}

scAnimationPtr scUiRotateAnimationFactory::createAnimation( bool isLoop )
{
	return scAnimationPtr(new scUiRotateAnimation(isLoop));
}
