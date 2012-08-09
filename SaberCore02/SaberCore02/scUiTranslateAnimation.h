#ifndef scUiTranslateAnimation_h__
#define scUiTranslateAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include "scKeyFrame.h"

/// UI λ�ƶ���
class scUiTranslateAnimation : public scUiAnimation
{
public:
	explicit scUiTranslateAnimation(bool isLoop);
	~scUiTranslateAnimation(void);

	/// Ϊ����ע������(���ö���)
	/// �����ڲ�ʹ�ã���scRenderer����
	/// @param widget �������õĶ���һ��UIԪ��
	virtual void _registerWidget(MyGUI::Widget* widget);


	/// ����һ���ؼ�֡�����������ؼ�֡�б�
	/// @param time �ؼ�֡ʱ��, ��λΪ����
	/// @param offsetX UIԪ����X�᷽���ϵ�ƫ����
	/// @param offsetY UIԪ����Y�᷽���ϵ�ƫ����
	/// @param itype ��ֵ��������
	void createKeyFrame(u32 time, i32 offsetX, i32 offsetY, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFrame* k0, scKeyFrame* k1 );

private:
	int mOriginX;
	int mOriginY;

};

#endif // scUiTranslateAnimation_h__

