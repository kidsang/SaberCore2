#ifndef scGenericKeyFrame_h__
#define scGenericKeyFrame_h__

/**
 * 文件：scGenericKeyFrame
 * 日期：2012/07/05
 * 作者：kid
 */

#include "scKeyFrame.h"
//////////////////////////////////////////////////////////////////////////

/// 连续型属性泛型关键帧
/// 关键帧内含某种类型的value，然而value的类型不可知，因此做成泛型
/// 由于scKeyFrame要用作统一的父类指针，因此不可将scKeyFrame模板化
/// 连续的意思是，两帧之间的数值可以通过插值得到
template <typename T>
class scContinuousKeyFrame : public scKeyFrame
{
public:
	typedef T(*FuncType)(u32 t0, u32 t, u32 t1, T const& v0, T const& v1);

	/// 构造函数
	/// @param time 关键帧时间
	/// @param val 变量的值
	scContinuousKeyFrame(u32 time, T const& val)
		: scKeyFrame(time), mValue(val), mInterpolationFunc(scInterpolationNone)
	{

	}

	/// 重载父类函数
	/// 为连续型关键帧指定插值函数
	virtual void setInterpolationType( InterpolationType type );

	/// 返回变量值
	T const& getValue()
	{return mValue;}
	/// 设置变量值
	void setValue(T const& val)
	{mValue = val;}
	/// 返回当前插值寒素
	const FuncType getInterpolationFunc()
	{return mInterpolationFunc;}

private:
	T mValue;
	FuncType mInterpolationFunc;
};

template <typename T>
void scContinuousKeyFrame<T>::setInterpolationType( InterpolationType type )
	{
		switch (type)
		{
		case IT_NONE:
			mInterpolationFunc = scInterpolationNone;
			break;
		case scKeyFrame::IT_LINEAR:
			mInterpolationFunc = scInterpolationLinear;
			break;
		case scKeyFrame::IT_SQUARE_IN:
			mInterpolationFunc = scInterpolationSquareIn;
			break;
		case scKeyFrame::IT_SQUARE_OUT:
			mInterpolationFunc = scInterpolationSquareOut;
			break;
		case scKeyFrame::IT_CUBIC_IN:
			mInterpolationFunc = scInterpolationCubicIn;
			break;
		case scKeyFrame::IT_CUBIC_OUT:
			mInterpolationFunc = scInterpolationCubicOut;
			break;
		case scKeyFrame::IT_EXP_IN:
			mInterpolationFunc = scInterpolationExpIn;
			break;
		case scKeyFrame::IT_EXP_OUT:
			mInterpolationFunc = scInterpolationExpOut;
			break;
		default:
			mInterpolationFunc = scInterpolationNone;
		}
	}

//////////////////////////////////////////////////////////////////////////

/// 离散型属性泛型关键帧
/// 关键帧内含某种类型的value，然而value的类型不可知，因此做成泛型
/// 由于scKeyFrame要用作统一的父类指针，因此不可将scKeyFrame模板化
/// 离散的意思是，两帧之间不可差值
template <typename T>
class scDiscreteKeyFrame : public scKeyFrame
{
public:
	typedef T(*FuncType)(u32 t0, u32 t, u32 t1, T const& v0, T const& v1);

	/// 构造函数
	/// @param time 关键帧时间
	/// @param val 变量的值
	scDiscreteKeyFrame(u32 time, T const& val)
		: scKeyFrame(time), mValue(val), mInterpolationFunc(scInterpolationNone)
	{

	}

	/// 重载父类函数
	/// 为离散型关键帧指定插值函数
	/// 注意离散型不可插值，必须指定为IT_NONE
	virtual void setInterpolationType( InterpolationType type );

	/// 返回变量值
	T const& getValue()
	{return mValue;}
	/// 设置变量值
	void setValue(T const& val)
	{mValue = val;}
	/// 返回当前插值寒素
	const FuncType getInterpolationFunc()
	{return mInterpolationFunc;}

private:
	T mValue;
	FuncType mInterpolationFunc;
};

template <typename T>
void scDiscreteKeyFrame<T>::setInterpolationType( InterpolationType type )
{
	scAssert(type == IT_NONE, "Discrete key frame must have interpolation function type \"IT_NONE\".");
	mInterpolationFunc = scInterpolationNone;
}

//////////////////////////////////////////////////////////////////////////

#endif // scGenericKeyFrame_h__
