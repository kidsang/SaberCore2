#ifndef scInputManager_h__
#define scInputManager_h__

/*
 * time: 2012/07/26
 * author: kid
 */

#include "scTypeDefine.h"
#include "ois/OIS.h"
#include "OgreSingleton.h"
#include "lua.hpp"

namespace MyGUI {
	class InputManager;
}

/// ���������
/// ��������꼰������Ӧ�¼�
/// ʵ����������¼�ת������Ӧ��lua�ű�����
class scInputManager : public Ogre::Singleton<scInputManager>, public OIS::KeyListener, public OIS::MouseListener
{
public:
	/// ���캯��
	/// @param handle windows�Ĵ��ھ��
	/// @param width ��Ļ���
	/// @param height ��Ļ�߶�
	/// @param isExclusive �Ƿ��Զ�ռģʽ����
	/// ��ռģʽ�����ͼ��̶�����������Ϸ������
	scInputManager(u32 handle, u32 width, u32 height, bool isExclusive = false);
	~scInputManager(void);
	static scInputManager& getSingleton(void);
	static scInputManager* getSingletonPtr(void);

	/// �������Ͱ�����Ϣ
	/// �����ڲ�ʹ�ã�Ӧ������Ӧ��timeline����
	void _run()
	{
		mMouse->capture();
		mKeyboard->capture();
	}

	/// 
	void registerGuiEvents(MyGUI::InputManager* guiInput);

	/// Ϊ���̰����¼�ע�ᴦ��ű�
	/// �����¼�ȫ��ת�Ƹ�lua�ű�����
	/// ͬһʱ�̽�����һ���ű���ע�ᣬ��ע��ĻḲ����ע���
	/// @param fileName lua�ű�����
	void registerKeyPressed(string const& fileName, string const& entry);

	/// Ϊ���̵����¼�ע�ᴦ��ű�
	/// �����¼�ȫ��ת�Ƹ�lua�ű�����
	/// ͬһʱ�̽�����һ���ű���ע�ᣬ��ע��ĻḲ����ע���
	/// @param fileName lua�ű�����
	void registerKeyReleased(string const& fileName, string const& entry);

	/// Ϊ����ƶ��¼�ע�ᴦ��ű�
	/// �����¼�ȫ��ת�Ƹ�lua�ű�����
	/// ͬһʱ�̽�����һ���ű���ע�ᣬ��ע��ĻḲ����ע���
	/// @param fileName lua�ű�����
	void registerMouseMoved(string const& fileName, string const& entry);

	/// Ϊ��갴���¼�ע�ᴦ��ű�
	/// �����¼�ȫ��ת�Ƹ�lua�ű�����
	/// ͬһʱ�̽�����һ���ű���ע�ᣬ��ע��ĻḲ����ע���
	/// @param fileName lua�ű�����
	void registerMousePressed(string const& fileName, string const& entry);

	/// Ϊ��굯���¼�ע�ᴦ��ű�
	/// �����¼�ȫ��ת�Ƹ�lua�ű�����
	/// ͬһʱ�̽�����һ���ű���ע�ᣬ��ע��ĻḲ����ע���
	/// @param fileName lua�ű�����
	void registerMouseReleased(string const& fileName, string const& entry);

	/// �⿪�Լ��̰����¼�����ű���ע��
	void unregisterKeyPressed();

	/// �⿪�Լ��̵����¼�����ű���ע��
	void unregisterKeyReleased();

	/// �⿪������ƶ��¼�����ű���ע��
	void unregisterMouseMoved();

	/// �⿪����갴���¼�����ű���ע��
	void unregisterMousePressed();

	/// �⿪����굯���¼�����ű���ע��
	void unregisterMouseReleased();

	/// �⿪�������¼�����ű���ע��
	void unregisterAll();

	// ������
private:
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );		
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

private:
	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;
	MyGUI::InputManager* mGuiInput;

	string mKeyPressedEntry;
	string mKeyReleasedEntry;
	string mMouseMovedEntry;
	string mMousePressedEntry;
	string mMouseReleasedEntry;

	lua_State* mKeyPressedLuaState;
	lua_State* mKeyReleasedLuaState;
	lua_State* mMouseMovedLuaState;
	lua_State* mMousePressedLuaState;
	lua_State* mMouseReleasedLuaState;
};

/// ��װ��OIS������¼�
/// ��ʵ��Ϊ�˽��luabind�����޷���const��Ա������
struct scMouseEventWrapper
{
	scMouseEventWrapper(OIS::MouseState const& ms)
		: state(ms)
	{
	}

	OIS::MouseState state;
};

#endif // scInputManager_h__

