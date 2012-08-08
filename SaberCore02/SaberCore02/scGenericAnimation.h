#ifndef scGenericAnimation_h__
#define scGenericAnimation_h__

/**
 * �ļ���scGenericAnimation
 * ���ڣ�2012/07/05
 * ���ߣ�kid
 */

#include "scAnimation.h"
#include "scGenericKeyFrame.h"
#include <functional>

//////////////////////////////////////////////////////////////////////////

/// �����Ͷ���
/// ������ζ��������֮֡�����ֵ�ǿɲ�ֵ��
template <typename T>
class scContinuousAnimation : public scAnimation
{
public:
	/// ���캯��
	/// @param setter �����пɲ�ֵ��������(��i32��)�ķº���
	/// @param isLoop �Ƿ�ѭ������
	scContinuousAnimation(std::function<void (T const&)> setter, bool isLoop)
		: scAnimation(isLoop), mSetter(setter)
	{

	}

	/// ����һ���ؼ�֡�����������ؼ�֡�б�
	/// @param time �ؼ�֡ʱ��, ��λΪ����
	/// @param val �ɲ�ֵ�ͱ���
	/// @param itype ��ֵ��������
	/// @return �����õĹؼ�ָ֡��
	scContinuousKeyFrame<T>* createKeyFrame(u32 time, T const& value, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR)
	{
		scContinuousKeyFrame<T>* keyFrame = new scContinuousKeyFrame<T>(time, value);
		keyFrame->setInterpolationType(itype);
		addKeyFrame(keyFrame);
		return keyFrame;
	}

private:
	/// @see scAnimation::runImpl
	virtual void runImpl( scKeyFrame* k0, scKeyFrame* k1 );

private:
	std::function<void (T const&)> mSetter;

};

template <typename T>
void scContinuousAnimation<T>::runImpl( scKeyFrame* k0, scKeyFrame* k1 )
{
	scContinuousKeyFrame<T> *mk0, *mk1;
	mk0 = static_cast<scContinuousKeyFrame<T>*>(k0);
	mk1 = static_cast<scContinuousKeyFrame<T>*>(k1);

	T value = mk0->getInterpolationFunc()(mk0->getTime(), getTime(), mk1->getTime(), mk0->getValue(), mk1->getValue());
	mSetter(value);
}

//////////////////////////////////////////////////////////////////////////

/// ��ɢ�Ͷ���
/// ��ɢ��ζ��������֮֡�����ֵ�ǲ��ɲ�ֵ��
template <typename T>
class scDiscreteAnimation : public scAnimation
{
public:
	/// ���캯��
	/// @param setter ��������ɢ��������(��bool��)�ķº���
	/// @param isLoop �Ƿ�ѭ������
	scDiscreteAnimation(std::function<void (T const&)> setter, bool isLoop)
		: scAnimation(isLoop), mSetter(setter)
	{

	}

	/// ����һ���ؼ�֡�����������ؼ�֡�б�
	/// @param time �ؼ�֡ʱ��, ��λΪ����
	/// @param val �ɲ�ֵ�ͱ���
	/// @param itype ��ֵ��������
	/// @return �����õĹؼ�ָ֡��
	scDiscreteKeyFrame<T>* createKeyFrame(u32 time, T const& value)
	{
		scDiscreteKeyFrame<T>* keyFrame = new scDiscreteKeyFrame<T>(time, value);
		addKeyFrame(keyFrame);
		return keyFrame;
	}

private:
	/// @see scAnimation::runImpl
	virtual void runImpl( scKeyFrame* k0, scKeyFrame* k1 );

private:
	std::function<void (T const&)> mSetter;

};

template <typename T>
void scDiscreteAnimation<T>::runImpl( scKeyFrame* k0, scKeyFrame* k1 )
{
	scDiscreteKeyFrame<T> *mk0, *mk1;
	mk0 = static_cast<scDiscreteKeyFrame<T>*>(k0);
	mk1 = static_cast<scDiscreteKeyFrame<T>*>(k1);

	T value = mk0->getInterpolationFunc()(mk0->getTime(), getTime(), mk1->getTime(), mk0->getValue(), mk1->getValue());
	mSetter(value);
}

//////////////////////////////////////////////////////////////////////////

#include <string>
#include "OgreVector2.h"
#include "OgreVector3.h"
#include "OgreVector4.h"

// ���Զ���
typedef std::function<void (Ogre::Vector2 const&)> Vector2Setter;
typedef std::function<void (Ogre::Vector3 const&)> Vector3Setter;
typedef std::function<void (Ogre::Vector4 const&)> Vector4Setter;
typedef std::function<void (i32)> I32Setter;
typedef std::function<void (u32)> U32Setter;
typedef std::function<void (f32)> F32Setter;
typedef std::function<void (bool)> BoolSetter;
typedef std::function<void (std::string const&)> StringSetter;

// ����ģ�嶨��
typedef scContinuousAnimation<Ogre::Vector2> scVector2Animation;
typedef scContinuousAnimation<Ogre::Vector3> scVector3Animation;
typedef scContinuousAnimation<Ogre::Vector4> scVector4Animation;
typedef scContinuousAnimation<i32> scI32Animation;
typedef scContinuousAnimation<u32> scU32Animation;
typedef scContinuousAnimation<f32> scF32Animation;
typedef scDiscreteAnimation<bool> scBoolAnimation;
typedef scDiscreteAnimation<std::string> scStringAnimation;

// �ؼ�֡ģ�嶨��
typedef scContinuousKeyFrame<Ogre::Vector2> scVector2KeyFrame;
typedef scContinuousKeyFrame<Ogre::Vector3> scVector3KeyFrame;
typedef scContinuousKeyFrame<Ogre::Vector4> scVector4KeyFrame;
typedef scContinuousKeyFrame<i32> scI32KeyFrame;
typedef scContinuousKeyFrame<u32> scU32KeyFrame;
typedef scContinuousKeyFrame<f32> scF32KeyFrame;
typedef scDiscreteKeyFrame<bool> scBoolKeyFrame;
typedef scDiscreteKeyFrame<std::string> scStringKeyFrame;

#endif // scGenericAnimation_h__
