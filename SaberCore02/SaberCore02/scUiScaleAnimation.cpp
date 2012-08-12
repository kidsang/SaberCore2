#include "scUiScaleAnimation.h"
#include "MyGUI/MyGUI_Widget.h"
#include "OgreVector4.h"
#include "scGenericKeyFrame.h"


scUiScaleAnimation::scUiScaleAnimation(bool isLoop)
	: scUiAnimation(isLoop),
	mOriginWidth(0), mOriginHeight(0), mOriginX(0), mOriginY(0)
{
}


scUiScaleAnimation::~scUiScaleAnimation(void)
{
}

void scUiScaleAnimation::runImpl( scKeyFramePtr k0, scKeyFramePtr k1 )
{
	scContinuousKeyFrame<Ogre::Vector4> *tk0, *tk1;
	tk0 = static_cast<scContinuousKeyFrame<Ogre::Vector4>*>(k0.get());
	tk1 = static_cast<scContinuousKeyFrame<Ogre::Vector4>*>(k1.get());

	Ogre::Vector4 value = tk0->getInterpolationFunc()(tk0->getTime(), getTime(), tk1->getTime(), tk0->getValue(), tk1->getValue());
	getHost()->setPosition(mOriginX - (i32)((value.x - 1) * mOriginWidth * value.z),
		mOriginY - (i32)((value.y - 1) * mOriginHeight * value.w));
	getHost()->setSize((i32)(mOriginWidth * value.x), (i32)(mOriginHeight * value.y));
}

void scUiScaleAnimation::_registerWidget( MyGUI::Widget* widget )
{
	scUiAnimation::_registerWidget(widget);
	mOriginWidth = widget->getWidth();
	mOriginHeight = widget->getHeight();
	mOriginX = widget->getLeft();
	mOriginY = widget->getTop();
}

void scUiScaleAnimation::createKeyFrame( u32 time, f32 scaleX, f32 scaleY, f32 centerX /*= 0.5f*/, f32 centerY /*= 0.5f*/, scKeyFrame::InterpolationType itype /*= scKeyFrame::IT_LINEAR*/ )
{
	scContinuousKeyFrame<Ogre::Vector4>* keyFrame = new scContinuousKeyFrame<Ogre::Vector4>(time, Ogre::Vector4(scaleX, scaleY, centerX, centerY));
	keyFrame->setInterpolationType(itype);
	addKeyFrame(scKeyFramePtr(keyFrame));
}

scAnimationPtr scUiScaleAnimationFactory::createAnimation( bool isLoop )
{
	return scAnimationPtr(new scUiScaleAnimation(isLoop));
}
