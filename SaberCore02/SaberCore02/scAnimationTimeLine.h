#ifndef scAnimationTimeLine_h__
#define scAnimationTimeLine_h__

/**
 * time: 2012/08/10
 * author: kid
 */

#include "scTimeLine.h"
#include "scAnimation.h"

typedef shared_ptr<scAnimation> scAnimationPtr;

class scAnimationTimeLine : public scTimeLine
{
	typedef std::list<scAnimationPtr> AnimationList;

public:
	/// ���캯��
	/// @param name ��ʱ���������
	/// @param invokeRate ��ʱ����ĵ���Ƶ�ʡ����磺60Hz������ÿ�����60�Ρ�
	scAnimationTimeLine(string const& name, u32 invokeRate);
	~scAnimationTimeLine(void);

	/// �ڶ���ʱ�����Ϲ��ض���
	/// ����ֻ���ڱ�����֮��Ż�ִ��
	/// @param ani ��Ҫ�����صĶ���
	void addAnimation(scAnimationPtr ani)
	{ mAnimations.push_back(ani); }

protected:
	/// �����߼���ʵ��
	/// �������ͨ�����ش˺��������������߼�
	virtual bool runImpl(u32 dtms);

private:
	AnimationList mAnimations;
};

#endif // scAnimationTimeLine_h__


#ifndef scTimeLine_h__
#define scTimeLine_h__

/**
 * �ļ���scTimeLine
 * ���ڣ�2012/07/01
 * ���ߣ�kid
 */

#include "scTypeDefine.h"
#include <list>
#include <string>
#include "scGenericAnimation.h"

class scAnimation;

/// ʱ����
class scTimeLine
{
	typedef std::list<scAnimation*> AnimationList;

public:
	/// ���캯��
	/// @param name ��ʱ���������
	/// @param invokeRate ��ʱ����ĵ���Ƶ�ʡ����磺60Hz������ÿ�����60�Ρ�
	scTimeLine(const std::string& name, u32 invokeRate);
	~scTimeLine();

	/// ����һ�ζ������⽫�ḽ���������渽�ŵ��κζ���
	/// @param timeLine ������ʵ��ָ�롣
	void destoryAnimation(scAnimation* animation);

	/// ����һ�ζ������⽫�ḽ���������渽�ŵ��κζ���
	/// @param index �������б��е��±�������
	void destoryAnimation(u32 index);

	/// ����ʱ����
	/// �����ڲ�ʹ�ã��ú���Ӧ����scTimeLineManager����
	/// Ϊʱ��������ʱ�䡣���ӵ�ʱ�佫������ʱ���������ӣ�������Ա�Ϊ����
	/// ��ʱ�����ۼ�ʱ����ڵ��ü��(������С�ڸ����ü��)�����ᴥ�����ж����ĵ���
	/// @param dtms ��һ�ε��õ���ε�����������ʱ�������Ժ������
	/// @return TODO: �ҵ��÷���ֵ������
	bool _run(u32 dtms);

	/// ����һ��Ogre::Vector2���Զ���
	/// @param setter ������Ogre::Vector2�������Եķº���
	/// @param isLoop �Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scVector2Animation* createVector2Animation(Vector2Setter setter, bool isLoop = false);

	/// ����һ��Ogre::Vector3���Զ���
	/// @param setter ������Ogre::Vector3�������Եķº���
	/// @param isLoop �Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scVector3Animation* createVector3Animation(Vector3Setter setter, bool isLoop = false);

	/// ����һ��Ogre::Vector4���Զ���
	/// @param setter ������Ogre::Vector4�������Եķº���
	/// @param isLoop �Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scVector4Animation* createVector4Animation(Vector4Setter setter, bool isLoop = false);

	/// ����һ��f32���Զ���
	/// @param setter ������f32�������Եķº���
	/// @param isLoop �Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scF32Animation* createF32Animation(F32Setter setter, bool isLoop = false);


public:
	/// ���ظ�ʱ���������
	const std::string& getName()
	{
		return mName;
	}

	/// ����ʱ������ϵ��
	/// ʱ�䱻�ۼӵ�ʱ����֮ǰ�����ʱ������ϵ��
	/// �ı�ʱ������ϵ����Ӱ��ʱ��������϶����Ķ����ٶ�
	f32 getScaleFactor()
	{
		return mScaleFactor;
	}
	/// ����ʱ������ϵ��
	/// ʱ�䱻�ۼӵ�ʱ����֮ǰ�����ʱ������ϵ��
	/// �ı�ʱ������ϵ����Ӱ��ʱ��������϶����Ķ����ٶ�
	void setScaleFactor(f32 scaleFactor)
	{
		if (scaleFactor < 0)
			mScaleFactor = 0;
		else
			mScaleFactor = scaleFactor;
	}

	/// ����ʱ�������ε���֮���ʱ����
	/// �Ժ���Ϊ��λ
	u32 getInvokeInterval()
	{
		return mInterval;
	}
	/// ����ʱ�������ε���֮���ʱ����
	/// �Ժ���Ϊ��λ
	void setInvokeInterval(u32 interval)
	{
		mInterval = interval;
	}

	/// ����ʱ����ĵ���Ƶ��
	/// �Ժ���Ϊ��λ(��ÿ����ٴ�)
	u32 getInvokeRate()
	{
		return 1000 / mInterval;
	}
	/// ����ʱ����ĵ���Ƶ��
	/// �Ժ���Ϊ��λ(��ÿ����ٴ�)
	void setInvokeRate(u32 rate)
	{
		mInterval = (1000 / rate);
	}


private:
	AnimationList mAnimations;

	std::string mName;
	f32 mScaleFactor;
	u32 mInterval;
	u32 mCurrentTime;

};

#endif // scTimeLine_h__