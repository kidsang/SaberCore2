#ifndef scTimeLineManager_h__
#define scTimeLineManager_h__

/**
 * �ļ���scTimeLineManager
 * ���ڣ�2012/07/01
 * ���ߣ�kid
 */

#include <map>
#include <ctime>
#include <vector>
#include "OgreSingleton.h"
#include "scTypeDefine.h"

class scTimeLine;
typedef shared_ptr<scTimeLine> scTimeLinePtr;

/// ʱ���������
/// ����ʱ����Ĵ�������������ٹ���
/// ����
class scTimeLineManager : public Ogre::Singleton<scTimeLineManager>
{
	typedef std::multimap<i32, scTimeLinePtr> TimeLineMap;
	typedef boost::shared_ptr<boost::thread> ThreadPtr;
	typedef std::vector<ThreadPtr> ThreadList;
	typedef std::vector<string> ThreadingTimeLines;

public:
	~scTimeLineManager();

	/// ����һ��ʱ����
	/// ��ʱ���Ὣ�Զ�����scTimeLineManager�Ĺ��������
	/// ����ɾ����ʱ���ᣬ�����scTimeLineManager::destroyTimeLine()
	/// @param name ��ʱ���������
	/// @param invokeRate ��ʱ����ĵ���Ƶ�ʡ����磺60Hz������ÿ�����60�Ρ�
	/// @param priority ʱ��������ȼ�������ԽС���ȼ�Խ�ߣ����ȼ��ߵ�ʱ����ᱻ���ȵ���
	/// @param threading ʱ�����Ƿ�Ҫ�����ڵ������̣߳�Ĭ�����������߳�
	/// @return �����õ�ʱ����ʵ��
	scTimeLinePtr const& createTimeLine(const string& name, u32 invokeRate, i32 priority = 0, bool threading = false);

	/// ����һ��ʱ���ᣬ�⽫�ḽ���������渽�ŵ��κ�ʱ�����
	/// @param timeLine ʱ�����ʵ��ָ�롣�����������ᱨ��
	void destoryTimeLine(scTimeLinePtr const& timeLine);

	/// ����һ��ʱ���ᣬ�⽫�ḽ���������渽�ŵ��κ�ʱ�����
	/// @param name ʱ��������ơ������������ᱨ��
	void destoryTimeLine(string const& name);

	/// ����һ��ʱ��������ȼ�
	/// @param timeLine ʱ�����ʵ��ָ�롣�����������ᱨ��
	/// @param priority ʱ��������ȼ�������ԽС���ȼ�Խ�ߣ����ȼ��ߵ�ʱ����ᱻ���ȵ���
	void setPriority(scTimeLinePtr const& timeLine, i32 priority);

	/// ����һ��ʱ��������ȼ�
	/// @param name ʱ��������ơ������������ᱨ��
	/// @param priority ʱ��������ȼ�������ԽС���ȼ�Խ�ߣ����ȼ��ߵ�ʱ����ᱻ���ȵ���
	void setPriority(string const& name, i32 priority);

	/// ��ȡָ�����Ƶ�ʱ����
	/// @param name ʱ��������ơ������������ᱨ��
	/// @return ʱ����ʵ��ָ��
	scTimeLinePtr const& getTimeLine(string const& name);

	/// �����������߳�ʱ����
	/// �ú��������ÿ��ʱ�����run()��������Ϊ��������ʱ��
	void startMain();

	/// �������з�֧�߳�ʱ����
	/// ע��ͬһ��ʱ����Ҫ���������̣߳�Ҫ�����ڷ�֧�̣߳�����ͬʱ�ڶ����߳�
	void startThreads();


	/// Override standard Singleton retrieval.
	static scTimeLineManager& getSingleton(void);
	/// Override standard Singleton retrieval.
	static scTimeLineManager* getSingletonPtr(void);

private:
	/// ����ָ�����Ƶķ�֧�߳�ʱ����
	/// @param ʱ��������ơ�
	/// ע��ͬһ��ʱ����Ҫ���������̣߳�Ҫ�����ڷ�֧�̣߳�����ͬʱ�ڶ����߳�
	void startThread(string const& name);

	/// �����߳�������ָ����ʱ����
	void runThread(scTimeLinePtr timeLine);

private:
	TimeLineMap mTimeLines;
	ThreadList mThreads;
	ThreadingTimeLines mThreadingTimeLines;

};

#endif // scTimeLineManager_h__