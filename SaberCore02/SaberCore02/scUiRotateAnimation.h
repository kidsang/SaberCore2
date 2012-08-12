#ifndef scUiRotateAnimation_h__
#define scUiRotateAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include "scKeyFrame.h"

/// UI ��ת����
/// ע�⣬����������UIԪ����֧����ת
/// ֧���б�ImageBox(skinΪRotatingSkin)
class scUiRotateAnimation : public scUiAnimation
{
public:
	/// ���캯��
	/// @param isLoop �����Ƿ�ѭ������
	scUiRotateAnimation(bool isLoop);
	~scUiRotateAnimation(void);

	/// ����һ���ؼ�֡�����������ؼ�֡�б�
	/// @param time �ؼ�֡ʱ��, ��λΪ����
	/// @param radian UIԪ������ת�Ƕȣ��Ի�����Ϊ��λ������Ϊ����
	/// @param centerX ��ת����x���꣬0.5��ΪԪ������
	/// @param centerY ��ת����y���꣬0.5��ΪԪ������
	/// @param itype ��ֵ��������
	void createKeyFrame(u32 time, f32 radian, f32 centerX = 0.5f, f32 centerY = 0.5f, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFramePtr k0, scKeyFramePtr k1 );

};

class scUiRotateAnimationFactory : public scAnimationFactory
{
public:
	/// ���캯��
	/// @param name ÿ����������һ����һ�޶�������
	/// �Թ�AnimationManager���ʶ
	scUiRotateAnimationFactory(string const& name)
		: scAnimationFactory(name)
	{}

	/// ���������ľ���ʵ��
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ָ��
	virtual scAnimationPtr createAnimation( bool isLoop );

};
#endif // scUiRotateAnimation_h__

