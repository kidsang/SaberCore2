#ifndef scGameWorld_h__
#define scGameWorld_h__

/**
 * �ļ���scGameWorld
 * ���ڣ�2012/07/07
 * ���ߣ�kid
 */

#include "scTypeDefine.h"
#include <map>
#include "Ogre.h"
class scGameArea;
typedef shared_ptr<scGameArea> scGameAreaPtr;

/// ��Ϸ����GameWorld
/// һ����Ϸ�������������������Լ����кͽ������߼�
/// ��Ϸ�����ڴ���ʱ���������������ݣ��ڽ���ʱ������������
/// һ����Ϸ����ͨ�������У�
/// 1. һ�鳡����������һ�龵ͷ��һ���ӿ�
/// 2. һ��GUI
/// 3. �����Ϊ��Ϸ����(GameArea)�����ݿ�
/// ��Ϸ��������Ϸ�����һ���Ӽ�
/// �������ǳ���ʱ�����ǿ��Խ����ص�ǰ��Ҫ����Ϸ����
/// ����������ʣ���
class scGameWorld
{
	typedef std::map<string, Ogre::SceneManager*> SceneManagerMap; 
	typedef std::map<string, Ogre::Camera*> CameraMap;
	typedef std::map<i32, Ogre::Viewport*> ViewportMap;
	// TODO:GUI
	typedef std::map<string, scGameAreaPtr> GameAreaMap;

public:
	scGameWorld(string const& name);
	~scGameWorld(void);

	/// ��ʼ����Ϸ����
	void initialize();

	/// �ͷ���Դ
	void release();

	/// ���г������߼�
	/// �����ڲ�ʹ�ã��ú���Ӧ������Ϸ������������
	/// @param dtms ��һ֡����һ֡��������ʱ�䣬��λ����
	bool _run(u32 dtms);

public:
	string const& getName()
	{return mName;}

private:
	string mName;
	SceneManagerMap mSceneManagers;
	CameraMap mCameras;
	ViewportMap mViewports;
	// TODO:GUI
	GameAreaMap mGameAreas;
};

#endif // scGameWorld_h__

