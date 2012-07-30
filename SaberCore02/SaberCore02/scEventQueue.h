#ifndef scEventQueue_h__
#define scEventQueue_h__

/*
 * time: 2012/07/30
 * author: kid
 */

#include <deque>
#include <vector>
#include <boost/thread.hpp>
#include "scTypeDefine.h"
struct scEvent;

typedef shared_ptr<scEvent> scEventPtr;

/// ��Ϣ����
/// �������̰߳�ȫ��
class scEventQueue
{
	typedef std::deque<scEventPtr> EventQueue;

public:
	/// ���캯��
	/// @param name �ö��е�����
	scEventQueue(string const& name);
	~scEventQueue(void);

	/// ���¼�put���������
	/// @param evt Ҫ��������е��¼�
	void putEvent(scEventPtr const& evt);

	/// �����������fetch,��ȡ�����¼��������evtOut��
	/// @param evtOut ��ȡ�����¼�
	/// @return ���ȡ���¼��ɹ�(��������������¼�)�򷵻�true
	bool const fetchEvent(scEventPtr & evtOut);

	/// �����������һ�ι�fetch�����е��¼�,��ȡ�����¼��������eventsOut��
	/// @param eventsOut ��ȡ�����¼��б�
	void fetchEvents(std::vector<scEventPtr> & eventsOut);

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

