#ifndef scGameWorld_h__
#define scGameWorld_h__

/**
 * �ļ���scGameWorld
 * ���ڣ�2012/07/07
 * ���ߣ�kid
 */

#include "scTypeDefine.h"
#include <map>
//#include "Ogre.h"
namespace Ogre
{
	class Viewport;
	class SceneManager;
}
//class scGameArea;
//typedef shared_ptr<scGameArea> scGameAreaPtr;

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
protected:
	typedef std::map<i32, Ogre::Viewport*> ViewportMap;
	// TODO:GUI

public:
	/// ���캯��
	/// @param name ��Ϸ���������
	scGameWorld(string const& name);
	virtual ~scGameWorld(void);

	/// ��ʼ����Ϸ����
	virtual void initialize();

	/// �ͷ���Դ
	virtual void release();

	/// ���г������߼�
	/// �����ڲ�ʹ�ã��ú���Ӧ������Ϸ������������
	/// @param dtms ��һ֡����һ֡��������ʱ�䣬��λ����
	virtual bool _run(u32 dtms);

	/// ��lua�ļ��м��س���
	/// @param fileName lua�ļ���
	/// @param entry lua��ں�����������void (scServerGameWorld* )
	void loadScene(string const& fileName, string const& entry = "createScene");

	// helper functions
public:
	/// ���Ӿ�̬����
	/// @param meshName ģ������
	void addStatic(string const& meshName, Ogre::Vector3 const& position, Ogre::Quaternion const& orientation, Ogre::Vector3 const& scale);

	/// ���������
	void addCamera(string const& camName);

public:
	string const& getName()
	{return mName;}

protected:
	string mName;
	Ogre::SceneManager* mSceneManager;
	ViewportMap mViewports;
	// TODO:GUI
};

#endif // scGameWorld_h__

