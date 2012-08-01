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
#include "scEvent.h"
class scEventQueue;

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
	/// �����¼�����
	/// @param name ������е�����
	/// @return �����õ��¼��������
	scEventQueuePtr createEventQueue(string const& name);

	/// �����¼�����
	/// @param name ������е�����
	void destroyEventQueue(string const& name);

	/// ע���¼�
	/// @param evtName �¼������ƣ�Ҳ�����¼�������
	/// @param queName �¼���Ŀ�ĵ����ƣ�Ҳ���ǽ�Ҫ��·�ɵ���������е�����
	void registerEvent(string const& evtName, string const& queName);

	/// ȡ��ע���¼�
	/// @param evtName �¼������ƣ�Ҳ�����¼�������
	void unregisterEvent(string const& evtName);

	/// ȡ��ע��ĳ�����ж�Ӧ�������¼�
	/// @param queName �¼���Ŀ�ĵ����ƣ�Ҳ���ǽ�Ҫ��·�ɵ���������е�����
	void unregisterEvents(string const& queName);

	/// ���¼�put���������
	/// @param evt Ҫ��������е��¼�
	void putEvent(scEvent const& evt);


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
	std::vector<scEvent> mEvents;
	QueueNameMap mOutputQueues;
	EventMap mEventMap;
	boost::mutex mQueueMutex;

};

#endif // scEventRouter_h__

