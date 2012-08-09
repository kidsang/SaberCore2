#include "scUiTranslateAnimation.h"
#include "MyGUI/MyGUI_Widget.h"
#include "OgreVector2.h"
#include "scGenericKeyFrame.h"


scUiTranslateAnimation::scUiTranslateAnimation(bool isLoop)
	: scUiAnimation(isLoop)
{
}


scUiTranslateAnimation::~scUiTranslateAnimation(void)
{
}

void scUiTranslateAnimation::runImpl( scKeyFrame* k0, scKeyFrame* k1 ) {
	scContinuousKeyFrame<Ogre::Vector2> *tk0, *tk1;
	tk0 = static_cast<scContinuousKeyFrame<Ogre::Vector2>*>(k0);
	tk1 = static_cast<scContinuousKeyFrame<Ogre::Vector2>*>(k1);

	Ogre::Vector2 value = tk0->getInterpolationFunc()(tk0->getTime(), getTime(), tk1->getTime(), tk0->getValue(), tk1->getValue());
	getHost()->setPosition(mOriginX + (i32)value.x, mOriginY + (i32)value.y);
}

void scUiTranslateAnimation::_registerWidget( MyGUI::Widget* widget )
{
	scUiAnimation::_registerWidget(widget);
	mOriginX = widget->getPosition().left;
	mOriginY = widget->getPosition().top;
}

void scUiTranslateAnimation::createKeyFrame( u32 time, i32 scaleX, i32 scaleY, scKeyFrame::InterpolationType itype /*= scKeyFrame::IT_LINEAR*/ )
{
	scContinuousKeyFrame<Ogre::Vector2>* keyFrame = new scContinuousKeyFrame<Ogre::Vector2>(time, Ogre::Vector2((f32)scaleX, (f32)scaleY));
	keyFrame->setInterpolationType(itype);
	addKeyFrame(keyFrame);
}
