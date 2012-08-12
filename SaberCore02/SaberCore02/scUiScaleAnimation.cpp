#include "scUiScaleAnimation.h"
#include "MyGUI/MyGUI_Widget.h"
#include "OgreVector2.h"
#include "scGenericKeyFrame.h"


scUiScaleAnimation::scUiScaleAnimation(bool isLoop)
	: scUiAnimation(isLoop),
	mOriginWidth(0), mOriginHeight(0)
{
}


scUiScaleAnimation::~scUiScaleAnimation(void)
{
}

void scUiScaleAnimation::runImpl( scKeyFramePtr k0, scKeyFramePtr k1 )
{
	scContinuousKeyFrame<Ogre::Vector2> *tk0, *tk1;
	tk0 = static_cast<scContinuousKeyFrame<Ogre::Vector2>*>(k0.get());
	tk1 = static_cast<scContinuousKeyFrame<Ogre::Vector2>*>(k1.get());

	Ogre::Vector2 value = tk0->getInterpolationFunc()(tk0->getTime(), getTime(), tk1->getTime(), tk0->getValue(), tk1->getValue());
	getHost()->setSize((i32)(mOriginWidth * value.x), (i32)(mOriginHeight * value.y));
}

void scUiScaleAnimation::_registerWidget( MyGUI::Widget* widget )
{
	scUiAnimation::_registerWidget(widget);
	mOriginWidth = widget->getWidth();
	mOriginHeight = widget->getHeight();
}

void scUiScaleAnimation::createKeyFrame( u32 time, f32 scaleX, f32 scaleY, scKeyFrame::InterpolationType itype /*= scKeyFrame::IT_LINEAR*/ )
{
	scContinuousKeyFrame<Ogre::Vector2>* keyFrame = new scContinuousKeyFrame<Ogre::Vector2>(time, Ogre::Vector2(scaleX, scaleY));
	keyFrame->setInterpolationType(itype);
	addKeyFrame(scKeyFramePtr(keyFrame));
}

scAnimationPtr scUiScaleAnimationFactory::createAnimation( bool isLoop )
{
	return scAnimationPtr(new scUiScaleAnimation(isLoop));
}
