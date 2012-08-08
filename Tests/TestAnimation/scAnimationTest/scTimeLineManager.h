#ifndef scTimeLineManager_h__
#define scTimeLineManager_h__

/**
 * �ļ���scTimeLineManager
 * ���ڣ�2012/07/01
 * ���ߣ�kid
 */

#include <map>
#include <string>
#include "OgreSingleton.h"
#include "scTypeDefine.h"

class scTimeLine;

/// ʱ���������
/// ����ʱ����Ĵ�������������ٹ���
class scTimeLineManager : public Ogre::Singleton<scTimeLineManager>
{
	typedef std::multimap<i32, scTimeLine*> scTimeLineMap;

public:
	~scTimeLineManager();

	/// ����һ��ʱ����
	/// ��ʱ���Ὣ�Զ�����scTimeLineManager�Ĺ��������
	/// ����ɾ����ʱ���ᣬ�����scTimeLineManager::destroyTimeLine()
	/// @param name ��ʱ���������
	/// @param invokeRate ��ʱ����ĵ���Ƶ�ʡ����磺60Hz������ÿ�����60�Ρ�
	/// @param priority ʱ��������ȼ�������ԽС���ȼ�Խ�ߣ����ȼ��ߵ�ʱ����ᱻ���ȵ���
	/// @return �����õ�ʱ����ʵ��
	scTimeLine* createTimeLine(const std::string& name, u32 invokeRate, i32 priority = 0);

	/// ����һ��ʱ���ᣬ�⽫�ḽ���������渽�ŵ��κ�ʱ�����
	/// @param timeLine ʱ�����ʵ��ָ�롣�����������ᱨ��
	void destoryTimeLine(scTimeLine* timeLine);

	/// ����һ��ʱ���ᣬ�⽫�ḽ���������渽�ŵ��κ�ʱ�����
	/// @param name ʱ��������ơ������������ᱨ��
	void destoryTimeLine(std::string const& name);

	/// ����һ��ʱ��������ȼ�
	/// @param timeLine ʱ�����ʵ��ָ�롣�����������ᱨ��
	/// @param priority ʱ��������ȼ�������ԽС���ȼ�Խ�ߣ����ȼ��ߵ�ʱ����ᱻ���ȵ���
	void setPriority(scTimeLine* timeLine, i32 priority);

	/// ����һ��ʱ��������ȼ�
	/// @param name ʱ��������ơ������������ᱨ��
	/// @param priority ʱ��������ȼ�������ԽС���ȼ�Խ�ߣ����ȼ��ߵ�ʱ����ᱻ���ȵ���
	void setPriority(std::string const& name, i32 priority);

	/// ��ȡָ�����Ƶ�ʱ����
	/// @param name ʱ��������ơ������������ᱨ��
	/// @return ʱ����ʵ��ָ��
	scTimeLine* getTimeLine(std::string const& name);

	/// ��������ʱ����
	/// �ú���Ӧ����ÿ��ѭ����ʱ�����
	/// �ú��������ÿ��ʱ�����run()��������Ϊ��������ʱ��
	/// @param dtms ��һ�ε��õ���ε�����������ʱ�������Ժ������
	/// @return TODO: �ҵ��÷���ֵ������
	bool run(u32 dtms);

	/** Override standard Singleton retrieval.
	@remarks
	Why do we do this? Well, it's because the Singleton
	implementation is in a .h file, which means it gets compiled
	i32o anybody who includes it. This is needed for the
	Singleton template to work, but we actually only want it
	compiled i32o the implementation of the class based on the
	Singleton, not all of them. If we don't change this, we get
	link errors when trying to use the Singleton-based class from
	an outside dll.
	@par
	This method just delegates to the template version anyway,
	but the implementation stays in this single compilation unit,
	preventing link errors.
	*/
	static scTimeLineManager& getSingleton(void);
	/** Override standard Singleton retrieval.
	@remarks
	Why do we do this? Well, it's because the Singleton
	implementation is in a .h file, which means it gets compiled
	i32o anybody who includes it. This is needed for the
	Singleton template to work, but we actually only want it
	compiled i32o the implementation of the class based on the
	Singleton, not all of them. If we don't change this, we get
	link errors when trying to use the Singleton-based class from
	an outside dll.
	@par
	This method just delegates to the template version anyway,
	but the implementation stays in this single compilation unit,
	preventing link errors.
	*/
	static scTimeLineManager* getSingletonPtr(void);

private:
	scTimeLineMap mTimeLines;
};

#endif // scTimeLineManager_h__