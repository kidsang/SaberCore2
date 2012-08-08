#ifndef scKeyFrame_h__
#define scKeyFrame_h__

/**
 * 文件：scKeyFrame
 * 日期：2012/07/03
 * 作者：kid
 */

#include "scTypeDefine.h"

/// 动画关键帧基类
/// 通过在动画中加入关键帧，我们可以控制动画在关键时间点的行为
/// 对于离散型动画来说，关键帧之间的数值为其前一个关键帧的值
/// 对于连续型动画来说，关键帧之间的数值将由差值来实现
/// 当然啦，这些是由动画类的类型(离散/连续)来决定的
class scKeyFrame
{
public:
	enum InterpolationType
	{
		IT_NONE, IT_LINEAR,
		IT_SQUARE_IN, IT_SQUARE_OUT,
		IT_CUBIC_IN, IT_CUBIC_OUT,
		IT_EXP_IN, IT_EXP_OUT
	};


	/// 构造函数
	/// @param time 关键帧时间
	scKeyFrame(u32 time)
		: mTime(time), mInterpolationType(IT_NONE)
	{

	}
	virtual ~scKeyFrame(void)
	{

	}

	// get/set
public:
	/// 返回当前关键帧的时间
	u32 getTime()
	{ return mTime; }
	/// 获取关键帧插值方法
	InterpolationType getInterpolationType()
	{return mInterpolationType;}
	/// 设置关键帧插值方法
	virtual void setInterpolationType(InterpolationType type) = 0;

private:
	u32 mTime;
	InterpolationType mInterpolationType;
};

//////////////////////////////////////////////////////////////////////////
#include <cmath>

/// 阶跃插值(不插值)
/// @param t0 起始关键帧时间
/// @param t 当前时间
/// @param t1 终止关键帧时间
/// @param v0 起始值
/// @param v1 终止值
/// @return 返回差值结果
template <typename T>
T scInterpolationNone(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t < t1)
		return v0;
	return v1;
}

/// 线性差值
/// @param t0 起始关键帧时间
/// @param t 当前时间
/// @param t1 终止关键帧时间
/// @param v0 起始值
/// @param v1 终止值
/// @return 返回差值结果
template <typename T>
T scInterpolationLinear(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * ((float)(t - t0) / (float)(t1 - t0)) );
}

/// 二次插值（渐入）
/// @param t0 起始关键帧时间
/// @param t 当前时间
/// @param t1 终止关键帧时间
/// @param v0 起始值
/// @param v1 终止值
/// @return 返回差值结果
template <typename T>
T scInterpolationSquareIn(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * pow((float)(t - t0) / (float)(t1 - t0), 2.f) );
}

/// 二次插值（渐出）
/// @param t0 起始关键帧时间
/// @param t 当前时间
/// @param t1 终止关键帧时间
/// @param v0 起始值
/// @param v1 终止值
/// @return 返回差值结果
template <typename T>
T scInterpolationSquareOut(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * sqrt((float)(t - t0) / (float)(t1 - t0)) );
}

/// 三次插值（渐入）
/// @param t0 起始关键帧时间
/// @param t 当前时间
/// @param t1 终止关键帧时间
/// @param v0 起始值
/// @param v1 终止值
/// @return 返回差值结果
template <typename T>
T scInterpolationCubicIn(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * pow((float)(t - t0) / (float)(t1 - t0), 3.f) );
}

/// 三次插值（渐出）
/// @param t0 起始关键帧时间
/// @param t 当前时间
/// @param t1 终止关键帧时间
/// @param v0 起始值
/// @param v1 终止值
/// @return 返回差值结果
template <typename T>
T scInterpolationCubicOut(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * pow((float)(t - t0) / (float)(t1 - t0), 1 / 3.f) );
}

/// 指数插值（渐入）
/// @param t0 起始关键帧时间
/// @param t 当前时间
/// @param t1 终止关键帧时间
/// @param v0 起始值
/// @param v1 终止值
/// @return 返回差值结果
template <typename T>
T scInterpolationExpIn(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * ( pow(10.f, (float)(t - t0) / (float)(t1 - t0)) * .1f ) );
}

/// 指数插值（渐出）
/// @param t0 起始关键帧时间
/// @param t 当前时间
/// @param t1 终止关键帧时间
/// @param v0 起始值
/// @param v1 终止值
/// @return 返回差值结果
template <typename T>
T scInterpolationExpOut(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) *  log10((float)(t - t0) / (float)(t1 - t0) * 10.f) );
}

#endif // scKeyFrame_h__

