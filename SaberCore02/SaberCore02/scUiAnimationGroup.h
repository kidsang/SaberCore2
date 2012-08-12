#ifndef scUiAnimationGroup_h__
#define scUiAnimationGroup_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include <vector>

/// UI������
/// ��������Խ�������������һ��Ӧ����UIԪ��
/// �������ѭ�����ȡ�������ڲ��Ķ���
class scUiAnimationGroup : public scUiAnimation
{
	typedef std::vector<scUiAnimationPtr> AnimationList;

public:
	/// ���캯��
	explicit scUiAnimationGroup();
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
	/// �ر�أ����������Ƕ�����
	/// @param ani ��Ҫ����Ķ���
	void addAnimation(scUiAnimationPtr ani);


private:
	virtual void runImpl( scKeyFramePtr k0, scKeyFramePtr k1 )
	{ 
		// ����û��runImpl 
	}

private:
	AnimationList mAnimations;
};

class scUiAnimationGroupFactory : public scAnimationFactory
{
public:
	/// ���캯��
	/// @param name ÿ����������һ����һ�޶�������
	/// �Թ�AnimationManager���ʶ
	scUiAnimationGroupFactory(string const& name)
		: scAnimationFactory(name)
	{}

	/// ���������ľ���ʵ��
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ָ��
	virtual scAnimationPtr createAnimation( bool isLoop );
};

#endif // scUiAnimationGroup_h__

