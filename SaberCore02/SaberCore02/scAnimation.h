#ifndef scAnimation_h__
#define scAnimation_h__

/**
 * �ļ���scAnimation
 * ���ڣ�2012/07/03
 * ���ߣ�kid
 */

#include "scTypeDefine.h"
#include <map>

class scKeyFrame;

/// ��������
/// sc�еĶ���ͨ���ı������������ʵ��
///	��ϣ���ܹ��õ�WPF���������Զ������������Ҫ��������������һ��
///	1. �ض��������͵Ķ�������vector3Animation
///	2. ��Ҫ���������õ����ʵ������SceneNode* node
///	3. ��Ҫ���������ı�����ԣ�����node��λ��position����
/// ͬʱ��������ͨ������Flash�еĹؼ�֡ʵ��
/// �û�ָ�����ɹؼ�֡������������Щ֮֡���ֵ
class scAnimation
{
public:
	typedef std::map<u32, scKeyFrame*> KeyFrameList;

	enum AnimationState
	{
		AS_RUNNING, AS_PAUSED, AS_FINISHED
	};

	/// ���캯��
	/// @param isLoop �����Ƿ�ѭ������
	explicit scAnimation(bool isLoop);
	virtual ~scAnimation();

	/// ���ж���
	/// �����ڲ�ʹ�ã��ú���Ӧ����scTimeLine����
	/// @param dtms ��һ�ε��õ���ε�����������ʱ�������Ժ������
	void _run(u32 dtms);

	/// ɾ���ؼ�֡
	/// ���ؼ�֡���б����Ƴ���������
	/// @param keyFrame Ҫ���ٵĹؼ�֡
	void destoryKeyFrame(scKeyFrame* keyFrame);

	/// ɾ���ؼ�֡
	/// ���ؼ�֡���б����Ƴ���������
	/// @param time �ؼ�֡����ʱ��
	void destoryKeyFrame(u32 time);

	// get/set
public:
	/// ��ȡ��ǰ�����Ƿ�ѭ��
	bool isLoop()
	{ return mIsLoop; }
	/// ���õ�ǰ�����Ƿ�ѭ��
	void setLoop(bool isloop)
	{ mIsLoop = isloop; }

	/// ���ص�ǰʱ��
	u32 getTime()
	{ return mCurrentTime; }

	/// ���ض����ظ�����
	u32 getRepeatTimes()
	{return mRepeatTimes;}
	/// ���ö����ظ�����
	void setRepeatTimes(u32 repeatTimes)
	{mRepeatTimes = repeatTimes;}

	/// ���ض�����ǰ״̬
	AnimationState getCurrentState()
	{return mCurrentState;}
	/// ��ͣ����
	void pause()
	{mCurrentState = AS_PAUSED;}
	/// ���Ŷ���
	void play()
	{mCurrentState = AS_RUNNING;}
	/// ��������
	void stop()
	{mCurrentState = AS_FINISHED;}


protected:
	/// ���ж�����ʵ��
	/// @param k0 ��ǰ����ʱ��ε�ǰһ���ؼ�֡
	/// @param k1 ��ǰ����ʱ��εĺ�һ���ؼ�֡
	virtual void runImpl(scKeyFrame* k0, scKeyFrame* k1) = 0;

	/// ��ӹؼ�֡
	/// �÷���Ӧ�ý������ڲ�
	/// �ض�������ͨ����д�Լ���createKeyFrame��ʵ�ֹ���
	/// �÷�����Ϊ��������
	void addKeyFrame(scKeyFrame* keyFrame);

private:
	bool mIsLoop;
	KeyFrameList mKeyFrameList;
	u32 mCurrentTime;
	u32 mRepeatTimes;
	AnimationState mCurrentState;
};

#endif // scAnimation_h__
