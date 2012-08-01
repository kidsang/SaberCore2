#ifndef scEventQueue_h__
#define scEventQueue_h__

/*
 * time: 2012/07/30
 * author: kid
 */

#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <deque>
#include <vector>
#include "scTypeDefine.h"
//class scEvent;
#include "scEvent.h"

/// ��Ϣ����
/// �������̰߳�ȫ��
class scEventQueue : boost::noncopyable
{
	typedef std::deque<scEvent> EventQueue;

public:
	/// ���캯��
	/// @param name �ö��е�����
	explicit scEventQueue(string const& name);
	scEventQueue();
	~scEventQueue(void);

	/// ���¼�put���������
	/// @param evt Ҫ��������е��¼�
	void putEvent(scEvent const& evt);

	/// �����������һ�ι�fetch�����е��¼�,��ȡ�����¼��������eventsOut��
	/// @param eventsOut ��ȡ�����¼��б�
	void fetchEvents(std::vector<scEvent> & eventsOut);

	// get/set
public:
	/// ���ظö��е�����
	string const& getName()
	{ return mName; }

private:
	string mName;
	EventQueue mEvents;
	boost::mutex mMutex;
};

#endif // scEventQueue_h__

