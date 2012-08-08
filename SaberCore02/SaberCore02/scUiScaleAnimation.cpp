#include "scUiScaleAnimation.h"
#include "MyGUI/MyGUI_Widget.h"
#include "scGenericKeyFrame.h"


scUiScaleAnimation::scUiScaleAnimation(bool isLoop)
	: scUiAnimation(isLoop),
	mOriginWidth(0), mOriginHeight(0)
{
}


scUiScaleAnimation::~scUiScaleAnimation(void)
{
}

void scUiScaleAnimation::runImpl( scKeyFrame* k0, scKeyFrame* k1 )
{
	throw std::exception("The method or operation is not implemented.");
}

void scUiScaleAnimation::_registerWidget( MyGUI::Widget* widget )
{
	scUiAnimation::_registerWidget(widget);
	mOriginWidth = widget->getWidth();
	mOriginHeight = widget->getHeight();
}
