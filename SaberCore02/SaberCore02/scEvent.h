#ifndef scEvent_h__
#define scEvent_h__

/**
 * �ļ���scEvent
 * ���ڣ�2012/07/16
 * ���ߣ�kid
 */

#include "scTypeDefine.h"

/// �¼�����
class scEvent
{
public:

	/// ���캯��
	/// @param name �����൱�����¼�������
	explicit scEvent(string const& name)
		: mName(name)
	{}
	virtual ~scEvent()
	{
	}

	string const& getName()
	{ return mName; }

private:
	string mName;
};

#endif // scEvent_h__
