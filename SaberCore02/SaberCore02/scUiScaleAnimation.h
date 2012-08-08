#ifndef scUiScaleAnimation_h__
#define scUiScaleAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include "scKeyFrame.h"
namespace MyGUI {
	class Widget;
}

/// UI ���Ŷ���
class scUiScaleAnimation : public scUiAnimation
{
public:
	scUiScaleAnimation(bool isLoop);
	~scUiScaleAnimation(void);

	/// Ϊ����ע������(���ö���)
	/// �����ڲ�ʹ�ã���scRenderer����
	/// @param widget �������õĶ���һ��UIԪ��
	virtual void _registerWidget(MyGUI::Widget* widget);

	void createKeyFrame(u32 time, f32 alpha, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFrame* k0, scKeyFrame* k1 );

private:
	int mOriginWidth;
	int mOriginHeight;
};

#endif // scUiScaleAnimation_h__

