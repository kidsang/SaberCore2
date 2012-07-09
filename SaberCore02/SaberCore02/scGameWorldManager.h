#ifndef scGameWorldManager_h__
#define scGameWorldManager_h__

/**
 * �ļ���scGameWorldManager
 * ���ڣ�2012/07/07
 * ���ߣ�kid
 */

#include <map>
#include "scTypeDefine.h"
#include "OgreSingleton.h"
#include "scError.h"

class scGameWorld;
typedef shared_ptr<scGameWorld> scGameWorldPtr;

/// ��Ϸ���������
/// ������Ϸ����Ĵ�����������ת������
/// �������ڲ�ά��һ����Ϸ�������������贴������Ĳ����ļ�ֵ�Ա�
/// ����������תʱ�����ȴӵ�ǰ�����ȡ��һ����������ƣ�
/// ���ٵ�ǰ���磬������һ�����磬�������Ϊ��ǰ����
/// ����
class scGameWorldManager : public Ogre::Singleton<scGameWorldManager>
{
	typedef std::map<string, scGameWorldPtr> GameWorldMap;

public:
	scGameWorldManager();

	/// ������������һ����Ϸ����
	/// @param name ��Ϸ���������
	/// @param world ��Ϸ�����ʵ��
	void addGameWorld(string const& name, scGameWorldPtr const& world);

	/// �Ƴ�һ����Ϸ����
	/// һ����˵Ӧ�ò����õ�������ܡ��ðɣ��һ��Ǽ���
	/// @param name ��Ϸ���������
	void removeGameWorld(string const& name);

	/// ������Ϸ�ĳ�ʼ��Ϸ����
	/// ����������Ϸ�еĵ�һ����Ϸ����
	/// ��������ֻ����ת���������ʼ����һ��ֱ�Ӵ���
	/// @param name ��Ҫ�����������������
	void initializeGameWorld(string const& name);

	/// ��ת����һ����Ϸ����
	/// @param name ��һ����Ϸ���������
	void jumpTo(string const& name);

	/// ���е�ǰ����Ϸ����
	/// �����ڲ�ʹ�ã��ú���Ӧ������Ӧ��ʱ�������
	/// @param dtms ��һ֡����һ֡��������ʱ�䣬��λ����
	bool _run(u32 dtms);

	// get/set
public:
	/// ��ȡ��ǰ��Ϸ����
	scGameWorldPtr const& getCurrentGameWorld()
	{
		scAssert(isInitialized, "No game world initialized, call \"initializeGameWorld()\" first.");
		return mCurrentGameWorld;
	}

	/// Override standard Singleton retrieval.
	static scGameWorldManager& getSingleton(void);
	/// Override standard Singleton retrieval.
	static scGameWorldManager* getSingletonPtr(void);

private:
	bool isInitialized;
	scGameWorldPtr mCurrentGameWorld;
	GameWorldMap mGameWorldMap;
};

#endif // scGameWorldManager_h__

