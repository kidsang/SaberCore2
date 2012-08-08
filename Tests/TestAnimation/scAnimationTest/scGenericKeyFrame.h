#ifndef scGenericKeyFrame_h__
#define scGenericKeyFrame_h__

/**
 * �ļ���scGenericKeyFrame
 * ���ڣ�2012/07/05
 * ���ߣ�kid
 */

#include "scKeyFrame.h"
//////////////////////////////////////////////////////////////////////////

/// ���������Է��͹ؼ�֡
/// �ؼ�֡�ں�ĳ�����͵�value��Ȼ��value�����Ͳ���֪��������ɷ���
/// ����scKeyFrameҪ����ͳһ�ĸ���ָ�룬��˲��ɽ�scKeyFrameģ�廯
/// ��������˼�ǣ���֮֡�����ֵ����ͨ����ֵ�õ�
template <typename T>
class scContinuousKeyFrame : public scKeyFrame
{
public:
	typedef T(*FuncType)(u32 t0, u32 t, u32 t1, T const& v0, T const& v1);

	/// ���캯��
	/// @param time �ؼ�֡ʱ��
	/// @param val ������ֵ
	scContinuousKeyFrame(u32 time, T const& val)
		: scKeyFrame(time), mValue(val), mInterpolationFunc(scInterpolationNone)
	{

	}

	/// ���ظ��ຯ��
	/// Ϊ�����͹ؼ�ָ֡����ֵ����
	virtual void setInterpolationType( InterpolationType type );

	/// ���ر���ֵ
	T const& getValue()
	{return mValue;}
	/// ���ñ���ֵ
	void setValue(T const& val)
	{mValue = val;}
	/// ���ص�ǰ��ֵ����
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

/// ��ɢ�����Է��͹ؼ�֡
/// �ؼ�֡�ں�ĳ�����͵�value��Ȼ��value�����Ͳ���֪��������ɷ���
/// ����scKeyFrameҪ����ͳһ�ĸ���ָ�룬��˲��ɽ�scKeyFrameģ�廯
/// ��ɢ����˼�ǣ���֮֡�䲻�ɲ�ֵ
template <typename T>
class scDiscreteKeyFrame : public scKeyFrame
{
public:
	typedef T(*FuncType)(u32 t0, u32 t, u32 t1, T const& v0, T const& v1);

	/// ���캯��
	/// @param time �ؼ�֡ʱ��
	/// @param val ������ֵ
	scDiscreteKeyFrame(u32 time, T const& val)
		: scKeyFrame(time), mValue(val), mInterpolationFunc(scInterpolationNone)
	{

	}

	/// ���ظ��ຯ��
	/// Ϊ��ɢ�͹ؼ�ָ֡����ֵ����
	/// ע����ɢ�Ͳ��ɲ�ֵ������ָ��ΪIT_NONE
	virtual void setInterpolationType( InterpolationType type );

	/// ���ر���ֵ
	T const& getValue()
	{return mValue;}
	/// ���ñ���ֵ
	void setValue(T const& val)
	{mValue = val;}
	/// ���ص�ǰ��ֵ����
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
