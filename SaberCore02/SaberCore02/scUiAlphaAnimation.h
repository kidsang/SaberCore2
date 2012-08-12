#ifndef scUiAlphaAnimation_h__
#define scUiAlphaAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include "scKeyFrame.h"

/// UI͸���ȶ���
class scUiAlphaAnimation : public scUiAnimation
{
public:
	/// ���캯��
	/// @param isLoop �����Ƿ�ѭ������
	explicit scUiAlphaAnimation(bool isLoop);
	~scUiAlphaAnimation(void);

	/// ����һ���ؼ�֡�����������ؼ�֡�б�
	/// @param time �ؼ�֡ʱ��, ��λΪ����
	/// @param alpha UIԪ����alphaֵ��������0.f-1.f֮��
	/// @param itype ��ֵ��������
	void createKeyFrame(u32 time, f32 alpha, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFramePtr k0, scKeyFramePtr k1 );
};

class scUiAlphaAnimationFactory : public scAnimationFactory
{
public:
	/// ���캯��
	/// @param name ÿ����������һ����һ�޶�������
	/// �Թ�AnimationManager���ʶ
	scUiAlphaAnimationFactory(string const& name)
		: scAnimationFactory(name)
	{}

	/// ���������ľ���ʵ��
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ָ��
	virtual scAnimationPtr createAnimation( bool isLoop );

};

#endif // scUiAlphaAnimation_h__

