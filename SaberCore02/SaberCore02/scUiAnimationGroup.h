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
	scUiAnimationGroup(bool isLoop);
	~scUiAnimationGroup(void);

	/// �򶯻����м��붯��
	/// �ر�أ����������Ƕ�����
	/// @param ani ��Ҫ����Ķ���
	void addAnimation(scUiAnimation const& ani);
};

#endif // scUiAnimationGroup_h__

