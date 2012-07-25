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
	typedef std::map<string, Ogre::Viewport*> ViewportMap;
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
	/// @param position ����λ��
	/// @param orientation ���峯��
	/// @param scale ��������
	void addStatic(string const& meshName, Ogre::Vector3 const& position, Ogre::Quaternion const& orientation, Ogre::Vector3 const& scale);

	/// ���������
	/// @param camName���������
	/// @return �����õ������
	Ogre::Camera* addCamera(string const& camName);

	/// ����ָ�����Ƶ������
	/// @param camName���������
	/// @return �����
	Ogre::Camera* getCamera(string const& camName);

	/// ����ָ�����Ƶ������
	void removeCamera(string const& camName);

	/// �����ӿ�,��Ϊ��ָ�������
	/// �󴴽����ӿ���Զ����֮ǰ�������ӿ�
	/// Ĭ��ռ��������Ļ
	/// @param vpName �ӿ�����
	/// @param camName ���������
	void addViewport(string const& vpName, string const& camName);

	/// �����ӿ�,��Ϊ��ָ�������
	/// �󴴽����ӿ���Զ����֮ǰ�������ӿ�
	/// �Զ����Сλ��
	/// @param vpName �ӿ�����
	/// @param camName ���������
	/// @param left �ӿ����Ͻ�x����(0.0 - 1.0)
	/// @param top �ӿ����Ͻ�y����(0.0 - 1.0)
	/// @param width �ӿڿ�(0.0 - 1.0)
	/// @param height �ӿڸ�(0.0 - 1.0)
	void addViewport(string const& vpName, string const& camName, float left, float top, float width, float height);

	/// �Ƴ�ָ�����Ƶ��ӿ�
	/// @param vpName �ӿ�����
	void removeViewport(string const& vpName);

public:
	string const& getName()
	{return mName;}

protected:
	string mName;
	Ogre::SceneManager* mSceneManager;
	ViewportMap mViewports;
	static u32 sNextViewportZOder;
	// TODO:GUI
};

#endif // scGameWorld_h__

