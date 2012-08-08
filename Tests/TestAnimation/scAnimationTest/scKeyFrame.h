#ifndef scKeyFrame_h__
#define scKeyFrame_h__

/**
 * �ļ���scKeyFrame
 * ���ڣ�2012/07/03
 * ���ߣ�kid
 */

#include "scTypeDefine.h"

/// �����ؼ�֡����
/// ͨ���ڶ����м���ؼ�֡�����ǿ��Կ��ƶ����ڹؼ�ʱ������Ϊ
/// ������ɢ�Ͷ�����˵���ؼ�֮֡�����ֵΪ��ǰһ���ؼ�֡��ֵ
/// ���������Ͷ�����˵���ؼ�֮֡�����ֵ���ɲ�ֵ��ʵ��
/// ��Ȼ������Щ���ɶ����������(��ɢ/����)��������
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


	/// ���캯��
	/// @param time �ؼ�֡ʱ��
	scKeyFrame(u32 time)
		: mTime(time), mInterpolationType(IT_NONE)
	{

	}
	virtual ~scKeyFrame(void)
	{

	}

	// get/set
public:
	/// ���ص�ǰ�ؼ�֡��ʱ��
	u32 getTime()
	{ return mTime; }
	/// ��ȡ�ؼ�֡��ֵ����
	InterpolationType getInterpolationType()
	{return mInterpolationType;}
	/// ���ùؼ�֡��ֵ����
	virtual void setInterpolationType(InterpolationType type) = 0;

private:
	u32 mTime;
	InterpolationType mInterpolationType;
};

//////////////////////////////////////////////////////////////////////////
#include <cmath>

/// ��Ծ��ֵ(����ֵ)
/// @param t0 ��ʼ�ؼ�֡ʱ��
/// @param t ��ǰʱ��
/// @param t1 ��ֹ�ؼ�֡ʱ��
/// @param v0 ��ʼֵ
/// @param v1 ��ֵֹ
/// @return ���ز�ֵ���
template <typename T>
T scInterpolationNone(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t < t1)
		return v0;
	return v1;
}

/// ���Բ�ֵ
/// @param t0 ��ʼ�ؼ�֡ʱ��
/// @param t ��ǰʱ��
/// @param t1 ��ֹ�ؼ�֡ʱ��
/// @param v0 ��ʼֵ
/// @param v1 ��ֵֹ
/// @return ���ز�ֵ���
template <typename T>
T scInterpolationLinear(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * ((float)(t - t0) / (float)(t1 - t0)) );
}

/// ���β�ֵ�����룩
/// @param t0 ��ʼ�ؼ�֡ʱ��
/// @param t ��ǰʱ��
/// @param t1 ��ֹ�ؼ�֡ʱ��
/// @param v0 ��ʼֵ
/// @param v1 ��ֵֹ
/// @return ���ز�ֵ���
template <typename T>
T scInterpolationSquareIn(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * pow((float)(t - t0) / (float)(t1 - t0), 2.f) );
}

/// ���β�ֵ��������
/// @param t0 ��ʼ�ؼ�֡ʱ��
/// @param t ��ǰʱ��
/// @param t1 ��ֹ�ؼ�֡ʱ��
/// @param v0 ��ʼֵ
/// @param v1 ��ֵֹ
/// @return ���ز�ֵ���
template <typename T>
T scInterpolationSquareOut(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * sqrt((float)(t - t0) / (float)(t1 - t0)) );
}

/// ���β�ֵ�����룩
/// @param t0 ��ʼ�ؼ�֡ʱ��
/// @param t ��ǰʱ��
/// @param t1 ��ֹ�ؼ�֡ʱ��
/// @param v0 ��ʼֵ
/// @param v1 ��ֵֹ
/// @return ���ز�ֵ���
template <typename T>
T scInterpolationCubicIn(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * pow((float)(t - t0) / (float)(t1 - t0), 3.f) );
}

/// ���β�ֵ��������
/// @param t0 ��ʼ�ؼ�֡ʱ��
/// @param t ��ǰʱ��
/// @param t1 ��ֹ�ؼ�֡ʱ��
/// @param v0 ��ʼֵ
/// @param v1 ��ֵֹ
/// @return ���ز�ֵ���
template <typename T>
T scInterpolationCubicOut(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * pow((float)(t - t0) / (float)(t1 - t0), 1 / 3.f) );
}

/// ָ����ֵ�����룩
/// @param t0 ��ʼ�ؼ�֡ʱ��
/// @param t ��ǰʱ��
/// @param t1 ��ֹ�ؼ�֡ʱ��
/// @param v0 ��ʼֵ
/// @param v1 ��ֵֹ
/// @return ���ز�ֵ���
template <typename T>
T scInterpolationExpIn(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) * ( pow(10.f, (float)(t - t0) / (float)(t1 - t0)) * .1f ) );
}

/// ָ����ֵ��������
/// @param t0 ��ʼ�ؼ�֡ʱ��
/// @param t ��ǰʱ��
/// @param t1 ��ֹ�ؼ�֡ʱ��
/// @param v0 ��ʼֵ
/// @param v1 ��ֵֹ
/// @return ���ز�ֵ���
template <typename T>
T scInterpolationExpOut(u32 t0, u32 t, u32 t1, const T& v0, const T& v1)
{
	if (t1 == t0)
		return v0;
	return ( v0 + (v1 - v0) *  log10((float)(t - t0) / (float)(t1 - t0) * 10.f) );
}

#endif // scKeyFrame_h__

