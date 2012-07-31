#ifndef scEventRouter_h__
#define scEventRouter_h__

/**
 * �ļ���scEventRouter
 * ���ڣ�2012/07/16
 * ���ߣ�kid
 */

#include <boost/thread.hpp>
#include <queue>
#include "OgreSingleton.h"
#include "scTypeDefine.h"
class scEventQueue;
struct scEvent;

typedef shared_ptr<scEvent> scEventPtr;
typedef shared_ptr<scEventQueue> scEventQueuePtr;

/// �¼�·����
/// �û����¼��������������
/// �¼��ᱻ·����ָ�����������
/// �û�������Դ�ָ���������������ȡ��Ϣ
class scEventRouter : public Ogre::Singleton<scEventRouter>
{
	typedef std::map<string, scEventQueuePtr> QueueNameMap;
	/// ����ָʾ�����¼�Ӧ��ȥ���ĸ�outputQueue
	typedef std::map<string, string> EventMap;

public:
	/// �����������
	/// @param name ������е�����
	/// @return �����õ��¼��������
	scEventQueuePtr createEventQueue(string const& name);

	/// ע���¼�
	/// @param evtName �¼������ƣ�Ҳ�����¼�������
	/// @param queName �¼���Ŀ�ĵ����ƣ�Ҳ���ǽ�Ҫ��·�ɵ���������е�����
	void registerEvent(string const& evtName, string const& queName);

	/// ���¼�put���������
	/// @param evt Ҫ��������е��¼�
	void putEvent(scEventPtr const& evt);

	/// �����������һ�ι�fetch�����е��¼�,��ȡ�����¼��������eventsOut��
	/// @param queName ������е�����
	/// @param eventsOut ��ȡ�����¼��б�
	//void fetchEvents(string const& queName, std::vector<scEventPtr> & eventsOut);

	/// ��ȡһ���������
	/// @param queName ������е�����
	/// @return �¼��������
	scEventQueuePtr getEventQueue(string const& queName);
	
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
	shared_ptr<scEventQueue> mInputQueue;
	std::vector<scEventPtr> mEvents;
	QueueNameMap mOutputQueues;
	EventMap mEventMap;
	boost::mutex mQueueMutex;

};

#endif // scEventRouter_h__

