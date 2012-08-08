#ifndef scGenericAnimation_h__
#define scGenericAnimation_h__

/**
 * 文件：scGenericAnimation
 * 日期：2012/07/05
 * 作者：kid
 */

#include "scAnimation.h"
#include "scGenericKeyFrame.h"
#include <functional>

//////////////////////////////////////////////////////////////////////////

/// 连续型动画
/// 连续意味着任意两帧之间的数值是可插值的
template <typename T>
class scContinuousAnimation : public scAnimation
{
public:
	/// 构造函数
	/// @param setter 包含有可插值类型属性(如i32型)的仿函数
	/// @param isLoop 是否循环播放
	scContinuousAnimation(std::function<void (T const&)> setter, bool isLoop)
		: scAnimation(isLoop), mSetter(setter)
	{

	}

	/// 创建一个关键帧，并将其加入关键帧列表
	/// @param time 关键帧时间, 单位为毫秒
	/// @param val 可插值型变量
	/// @param itype 插值方法类型
	/// @return 创建好的关键帧指针
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

/// 离散型动画
/// 离散意味着任意两帧之间的数值是不可插值的
template <typename T>
class scDiscreteAnimation : public scAnimation
{
public:
	/// 构造函数
	/// @param setter 包含有离散类型属性(如bool型)的仿函数
	/// @param isLoop 是否循环播放
	scDiscreteAnimation(std::function<void (T const&)> setter, bool isLoop)
		: scAnimation(isLoop), mSetter(setter)
	{

	}

	/// 创建一个关键帧，并将其加入关键帧列表
	/// @param time 关键帧时间, 单位为毫秒
	/// @param val 可插值型变量
	/// @param itype 插值方法类型
	/// @return 创建好的关键帧指针
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

// 属性定义
typedef std::function<void (Ogre::Vector2 const&)> Vector2Setter;
typedef std::function<void (Ogre::Vector3 const&)> Vector3Setter;
typedef std::function<void (Ogre::Vector4 const&)> Vector4Setter;
typedef std::function<void (i32)> I32Setter;
typedef std::function<void (u32)> U32Setter;
typedef std::function<void (f32)> F32Setter;
typedef std::function<void (bool)> BoolSetter;
typedef std::function<void (std::string const&)> StringSetter;

// 动画模板定义
typedef scContinuousAnimation<Ogre::Vector2> scVector2Animation;
typedef scContinuousAnimation<Ogre::Vector3> scVector3Animation;
typedef scContinuousAnimation<Ogre::Vector4> scVector4Animation;
typedef scContinuousAnimation<i32> scI32Animation;
typedef scContinuousAnimation<u32> scU32Animation;
typedef scContinuousAnimation<f32> scF32Animation;
typedef scDiscreteAnimation<bool> scBoolAnimation;
typedef scDiscreteAnimation<std::string> scStringAnimation;

// 关键帧模板定义
typedef scContinuousKeyFrame<Ogre::Vector2> scVector2KeyFrame;
typedef scContinuousKeyFrame<Ogre::Vector3> scVector3KeyFrame;
typedef scContinuousKeyFrame<Ogre::Vector4> scVector4KeyFrame;
typedef scContinuousKeyFrame<i32> scI32KeyFrame;
typedef scContinuousKeyFrame<u32> scU32KeyFrame;
typedef scContinuousKeyFrame<f32> scF32KeyFrame;
typedef scDiscreteKeyFrame<bool> scBoolKeyFrame;
typedef scDiscreteKeyFrame<std::string> scStringKeyFrame;

#endif // scGenericAnimation_h__
