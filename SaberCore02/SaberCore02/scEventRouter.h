#ifndef scEventRouter_h__
#define scEventRouter_h__

/**
 * �ļ���scEventRouter
 * ���ڣ�2012/07/16
 * ���ߣ�kid
 */

#include "scTypeDefine.h"
#include "OgreSingleton.h"
#include <boost/thread.hpp>
#include <queue>
struct scEvent;

typedef shared_ptr<scEvent> scEventPtr;

/// �¼�·����
/// �û����¼��������������
/// �¼��ᱻ·����ָ�����������
/// �û�������Դ�ָ���������������ȡ��Ϣ
class scEventRouter : public Ogre::Singleton<scEventRouter>
{
	typedef std::deque<scEventPtr> EventQueue;
	typedef shared_ptr<EventQueue> EventQueuePtr;
	typedef std::map<string, EventQueuePtr> QueueNameMap;
	/// ����ָʾ�����¼�Ӧ��ȥ���ĸ�outputQueue
	typedef std::map<string, string> EventMap;

public:
	/// �����������
	/// @param name ������е�����
	void createOutputQueue(string const& name);

	/// ע���¼�
	/// @param evtName �¼������ƣ�Ҳ�����¼�������
	/// @param queName �¼���Ŀ�ĵ����ƣ�Ҳ���ǽ�Ҫ��·�ɵ���������е�����
	void registerEvent(string const& evtName, string const& queName);

	/// ���¼�put���������
	/// @param evt Ҫ��������е��¼�
	void putEvent(scEventPtr const& evt);

	/// �����������fetch,��ȡ�����¼��������evtOut��
	/// @param queName ������е�����
	/// @param evtOut ��ȡ�����¼�
	/// @return ���ȡ���¼��ɹ�(��������������¼�)�򷵻�true
	bool const fetchEvent(string const& queName, scEventPtr & evtOut);
	
	// ִ��·�ɹ���
	// ��ͣ�ش�input queue��fetch����put��output queue��
	// �����ڲ�ʹ�ã���TimeLine����
	void _run();

	/// Override standard Singleton retrieval.
	static scEventRouter& getSingleton(void);
	/// Override standard Singleton retrieval.
	static scEventRouter* getSingletonPtr(void);
	scEventRouter();
	~scEventRouter();

private:
	EventQueue mInputQueue;
	QueueNameMap mOutputQueues;
	EventMap mEventMap;

	boost::mutex mInputMutex;
	boost::mutex mOutputMutex;

};

#endif // scEventRouter_h__

