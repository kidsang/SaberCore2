#ifndef scTimeLine_h__
#define scTimeLine_h__

/**
 * �ļ���scTimeLine
 * ���ڣ�2012/07/01
 * ���ߣ�kid
 */

#include "scTypeDefine.h"
#include <list>
#include <map>
#include <functional>

/// ʱ����
/// ʱ��������˹�������������ĵ���Ƶ��
/// ʱ���ỹ����ʱ�������
class scTimeLine
{
	typedef std::function<bool (u32)> FrameCallBack;
	typedef std::map<string, FrameCallBack> FrameCallBackMap;
public:
	/// ���캯��
	/// @param name ��ʱ���������
	/// @param invokeRate ��ʱ����ĵ���Ƶ�ʡ����磺60Hz������ÿ�����60�Ρ�
	scTimeLine(string const& name, u32 invokeRate);
	virtual ~scTimeLine();

	/// ����ʱ����
	/// �����ڲ�ʹ�ã��ú���Ӧ����scTimeLineManager����
	/// Ϊʱ��������ʱ�䡣���ӵ�ʱ�佫������ʱ���������ӣ�������Ա�Ϊ����
	/// ��ʱ�����ۼ�ʱ����ڵ��ü��(������С�ڸ����ü��)�����ᴥ�����й��صĻص�����
	/// @param dtms ��һ�ε��õ���ε�����������ʱ�������Ժ������
	/// @return TODO: �ҵ��÷���ֵ������
	bool _run(u32 dtms);

	/// ���һ��֡�ص��������ú������ᰴ��ʱ����ĵ���Ƶ��ÿ֡����
	/// @param name �ص�����������
	/// @param callback �ص���������ʵ�Ƿº���������ʹ��lambda���ʽ����
	///	���磺[&mRenderer](u32 dtms)->bool{return mRenderer->run(dtms);}
	void addRunCallBack(string const& name, FrameCallBack const& callback);

	/// �Ƴ�һ��֡�ص�����
	/// @param name �ص�����������
	void removeRunCallBack(string const& name);

public:
	/// ���ظ�ʱ���������
	const string& getName()
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

protected:
	/// �����߼���ʵ��
	/// �������ͨ�����ش˺��������������߼�
	virtual bool runImpl(u32 dtms);

private:
	string mName;
	f32 mScaleFactor;
	u32 mInterval;
	u32 mCurrentTime;
	FrameCallBackMap mCallBackMap;
};

#endif // scTimeLine_h__

