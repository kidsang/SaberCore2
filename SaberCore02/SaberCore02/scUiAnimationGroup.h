#ifndef scUiAnimationGroup_h__
#define scUiAnimationGroup_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"

/// UI������
/// ��������Խ�������������һ��Ӧ����UIԪ��
class scUiAnimationGroup : public scUiAnimation
{
public:
	explicit scUiAnimationGroup(bool isLoop);
	~scUiAnimationGroup(void);

	/// ���ж���
	/// �����ڲ�ʹ�ã��ú���Ӧ����scTimeLine����
	/// ����scAnimation::_run()
	/// @param dtms ��һ�ε��õ���ε�����������ʱ�������Ժ������
	virtual void _run(u32 dtms);

	/// Ϊ����ע������(���ö���)
	/// �����ڲ�ʹ�ã���scRenderer����
	/// ����scUiAnimation::_registerWidget()
	/// @param widget �������õĶ���һ��UIԪ��
	virtual void _registerWidget(MyGUI::Widget* widget);

	/// �򶯻����м��붯��
	/// �ر�أ����������Ƕ������
	/// @param ani ��Ҫ����Ķ���
	void addAnimation(scUiAnimation const& ani);
};

#endif // scUiAnimationGroup_h__
