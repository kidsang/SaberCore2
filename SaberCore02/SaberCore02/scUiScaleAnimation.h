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
	explicit scUiScaleAnimation(bool isLoop);
	~scUiScaleAnimation(void);

	/// Ϊ����ע������(���ö���)
	/// �����ڲ�ʹ�ã���scRenderer����
	/// @param widget �������õĶ���һ��UIԪ��
	virtual void _registerWidget(MyGUI::Widget* widget);

	/// ����һ���ؼ�֡�����������ؼ�֡�б�
	/// @param time �ؼ�֡ʱ��, ��λΪ����
	/// @param scaleX UIԪ����X�᷽���ϵ�������
	/// @param scaleY UIԪ����Y�᷽���ϵ�������
	/// @param itype ��ֵ��������
	void createKeyFrame(u32 time, f32 scaleX, f32 scaleY, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFramePtr k0, scKeyFramePtr k1 );

private:
	int mOriginWidth;
	int mOriginHeight;
};

class scUiScaleAnimationFactory : public scAnimationFactory
{
public:
	/// ���캯��
	/// @param name ÿ����������һ����һ�޶�������
	/// �Թ�AnimationManager���ʶ
	scUiScaleAnimationFactory(string const& name)
		: scAnimationFactory(name)
	{}

	/// ���������ľ���ʵ��
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ָ��
	virtual scAnimationPtr createAnimation( bool isLoop );
};

#endif // scUiScaleAnimation_h__

