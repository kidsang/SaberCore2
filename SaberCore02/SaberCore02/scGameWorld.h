#ifndef scGameWorld_h__
#define scGameWorld_h__

/**
 * �ļ���scGameWorld
 * ���ڣ�2012/07/07
 * ���ߣ�kid
 */

#include "scTypeDefine.h"
#include <map>
#include "lua.hpp"
namespace Ogre
{
	class Viewport;
	class SceneManager;
}
class scEventQueue;
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

public:
	/// ���캯��
	/// @param name ��Ϸ���������
	/// @param scriptName ������Ϸ�����lua�ű���
	/// @param scriptEntry �ű�����ں�����
	scGameWorld(string const& name, string const& scriptName, string const& scriptEntry);
	virtual ~scGameWorld(void);

	/// ��ʼ����Ϸ����
	virtual void initialize();

	/// �ͷ���Դ
	virtual void release();

	/// ���г������߼�
	/// �����ڲ�ʹ�ã��ú���Ӧ������Ϸ������������
	/// @param dtms ��һ֡����һ֡��������ʱ�䣬��λ����
	virtual bool _run(u32 dtms);

	/// ��lua�ļ��г�ʼ������
	/// @param fileName lua�ļ���
	/// @param entry lua��ں�����
	/// ��ں���ǩ��void (scServerGameWorld* )
	void iniScene(string const& scriptName, string const& entry);

	/// ��lua�ļ��г�ʼ��UIϵͳ,��Ҫ��ΪUIע���¼���Ӧ�����ʹ�����
	/// @param scriptName ����UI�¼���lua�ű�
	/// @param entry ��ں�������
	/// ��ں���ǩ����void(scRender*)
	void iniGui(string const& scriptName, string const& entry);

	// TODO: ����ط��������⣬callback�޷���ɢ�������ű���д
	/// ��lua�ļ��г�ʼ���¼�ϵͳ
	/// @param callbackScript �����¼���lua�ű�
	/// @param callbackEntry �����¼��ĺ������
	/// ����ǩ����void(*func)(scAnEvent*)
	/// @param registerScript ע���¼����͵�lua�ű�
	/// @param registerEntry ע���¼��ĺ������
	/// ����ǩ����void(*func)(scGameWorld*)
	void iniEvent(string const& callbackScript, string const& callbackEntry,
		string const& registerScript, string const& registerEntry);

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

	/// ��������������ĳ��luaģ��(�ļ�)
	/// ����Ҫ��.lua��׺��
	/// @param moduleName luaģ����
	void luaImport(string const& moduleName);

	/// Ϊ���̰����¼�ע�ᴦ��ű�
	/// ͬһʱ�̽�����һ���ű���ע�ᣬ��ע��ĻḲ����ע���
	/// @param moduleName luaģ������
	/// @param entry ��ں�������
	void registerKeyPressed(string const& moduleName, string const& entry);

	/// Ϊ���̵����¼�ע�ᴦ��ű�
	/// ͬһʱ�̽�����һ���ű���ע�ᣬ��ע��ĻḲ����ע���
	/// @param moduleName luaģ������
	/// @param entry ��ں�������
	void registerKeyReleased(string const& moduleName, string const& entry);

	/// Ϊ����ƶ��¼�ע�ᴦ��ű�
	/// ͬһʱ�̽�����һ���ű���ע�ᣬ��ע��ĻḲ����ע���
	/// @param moduleName luaģ������
	/// @param entry ��ں�������
	void registerMouseMoved(string const& moduleName, string const& entry);

	/// Ϊ��갴���¼�ע�ᴦ��ű�
	/// ͬһʱ�̽�����һ���ű���ע�ᣬ��ע��ĻḲ����ע���
	/// @param moduleName luaģ������
	/// @param entry ��ں�������
	void registerMousePressed(string const& moduleName, string const& entry);

	/// Ϊ��굯���¼�ע�ᴦ��ű�
	/// ͬһʱ�̽�����һ���ű���ע�ᣬ��ע��ĻḲ����ע���
	/// @param moduleName luaģ������
	/// @param entry ��ں�������
	void registerMouseReleased(string const& moduleName, string const& entry);

	/// ��UIԪ����ĳ��UI������
	/// @param widgetName UIԪ��������
	/// @param ani UI����
	void bindGuiAnimation(string const& widgetName, scUiAnimationPtr const& ani);

public:
	/// ������Ϸ���������
	string const& getName()
	{return mName;}

	/// ������Ϸ������ӵ�е��¼����е�����
	string const& getEventQueueName();

private:
	/// ��������������������
	void exportSelf(lua_State* L);

	/// �������������Ҷ�Ӧ���ƽű���·��
	//string const getScriptPath(string const& name);

protected:
	string mName;
	Ogre::SceneManager* mSceneManager;
	ViewportMap mViewports;
	static u32 sNextViewportZOder; // ��һ���ӿڵĸ߶�
	shared_ptr<scEventQueue> mEventQueue; // �¼�����
	lua_State* mL; // �����¼������lua�����
	string mScriptName;
	string mScriptEntry;
	string mEventCallbackEntry; // lua���¼�������ں�����
};

#endif // scGameWorld_h__

