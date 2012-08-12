#ifndef scAnimationTimeLine_h__
#define scAnimationTimeLine_h__

/**
 * time: 2012/08/10
 * author: kid
 */

#include <deque>
#include "scTypeDefine.h"
#include "scTimeLine.h"
#include "scAnimation.h"
#include "scUiAnimation.h"

class scAnimationTimeLine : public scTimeLine
{
	typedef std::deque<scAnimationPtr> AnimationList;

public:
	/// ���캯��
	/// @param name ��ʱ���������
	/// @param invokeRate ��ʱ����ĵ���Ƶ�ʡ����磺60Hz������ÿ�����60�Ρ�
	scAnimationTimeLine(string const& name, u32 invokeRate);
	~scAnimationTimeLine(void);

	/// �ڶ���ʱ�����Ϲ��ض���
	/// ����ֻ���ڱ�����֮��Ż�ִ��
	/// @param ani ��Ҫ�����صĶ���
	void addAnimation(scAnimationPtr const& ani)
	{ mAnimations.push_back(ani); }

	/// �ڶ���ʱ�����Ϲ��ض���
	/// ����ֻ���ڱ�����֮��Ż�ִ��
	/// @param ani ��Ҫ�����صĶ���
	void addAnimation(scUiAnimationPtr const& ani)
	{ mAnimations.push_back(ani); }

protected:
	/// �����߼���ʵ��
	/// �������ͨ�����ش˺��������������߼�
	virtual bool runImpl(u32 dtms);

private:
	AnimationList mAnimations;
};

#endif // scAnimationTimeLine_h__