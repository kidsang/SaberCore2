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
/// ֧���б�ImageBox
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
	/// @param itype ��ֵ��������
	void createKeyFrame(u32 time, f32 radian, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFrame* k0, scKeyFrame* k1 );

};

#endif // scUiRotateAnimation_h__

