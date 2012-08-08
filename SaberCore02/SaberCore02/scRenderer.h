#ifndef scRenderer_h__
#define scRenderer_h__

/**
 * �ļ���scRenderer
 * ���ڣ�2012/07/06
 * ���ߣ�kid
 */

#include <map>
#include "Ogre.h"
#include "MyGUI/MyGUI.h"
#include "MyGUI/MyGUI_OgrePlatform.h"
#include "lua.hpp"
#include "scTypeDefine.h"
#include "scError.h"
#include "scUtils.h"

/// Ogre��Ⱦ������ϵͳ
/// ����
class scRenderer : public Ogre::Singleton<scRenderer>
{
	typedef std::map<string, string> UIEventCallbackMap;
public:
	enum GuiEventType
	{
		UI_KEY_GET_FOCUS, UI_KEY_LOSE_FOCUS,
		UI_KEY_PRESSED, UI_KEY_RELEASED,
		UI_MOUSE_GET_FOCUS, UI_MOUSE_LOSE_FOCUS,
		UI_MOUSE_MOVE, UI_MOUSE_WHEEL,UI_MOUSE_DRAG,
		UI_MOUSE_PRESSED, UI_MOUSE_RELEASED, UI_MOUSE_CLICK, UI_MOUSE_DOUBLE_CLICK
	};

public:
	/// ���캯��
	/// @param resourceCfgPath ��Դ�����ļ�·��
	/// @param pluginCfgPath ��������ļ�·��
	scRenderer(string const& resourceCfgPath, string const& pluginCfgPath);
	~scRenderer(void);
	static scRenderer& getSingleton(void);
	static scRenderer* getSingletonPtr(void);

	/// ����Ogre������Ⱦ
	/// �����ڲ�ʹ�ã��ú���Ӧ����ĳ��ʱ�������
	bool _run(u32 dtms);

	/// ��ʼ��GUI
	/// @param mgr ����������
	/// @param scriptName ����UI�¼���lua�ű�
	/// @param entry ��ں�������
	/// ��ں���ǩ����void(scRender*)
	void initializeGui(Ogre::SceneManager* mgr, string const& scriptName, string const& entry);

	/// �ر�GUI
	void shutdownGui();

	//void loadGuiEventConfig(string const& fileName);

	/// ΪUIԪ��ע���¼�
	/// @param widgetName UIԪ������
	/// @param eventType �¼�����
	/// @param callbackName lua�еĻص���������
	void registerGuiEvent(string const& widgetName, GuiEventType eventType, string const& callbackName);

	/// ��������������ĳ��luaģ��(�ļ�)
	/// ����Ҫ��.lua��׺��
	/// @param moduleName luaģ����
	void luaImport(string const& moduleName);

	// get/set
public:
	/// ����OgreRoot
	Ogre::Root* getOgreRoot()
	{ return mRoot; }

	/// ����MyGUI
	MyGUI::Gui* getGui()
	{ 
		scAssert(mIsGuiInitialized, "GUI not initialized! You must first call initializeGui()");
		return mGui; 
	}

private:
	/// ������������ȡָ������uiԪ���Ļص�������
	/// @param widgetName uiԪ������
	/// @param type �¼�����
	/// @return �ص���������
	string const& findWidgetCallback(string const& widgetName, GuiEventType type)
	{
		string name = widgetName + scToString(type);
		auto iter = mUIEventCallbackMap.find(name);
		scAssert(iter != mUIEventCallbackMap.end(), "UI widget " + widgetName + "did not register event " + scToString(type));
		scAssert(mGuiL != 0, "Gui lua state not initialized!");
		return iter->second;
	}

	/// ��������������������
	void exportSelf(lua_State* L);

	/// �¼���Gui���̰���
	/// @param sender ���ø��¼���uiԪ��
	/// @param key ������
	/// @param ch �����ַ�
	void onGuiKeyPressed(MyGUI::Widget* sender, MyGUI::KeyCode key, MyGUI::Char ch);

	/// �¼���Gui���̵���
	/// @param sender ���ø��¼���uiԪ��
	/// @param key ������
	void onGuiKeyReleased(MyGUI::Widget* sender, MyGUI::KeyCode key);

	/// �¼���Gui����ƶ�
	/// @param sender ���ø��¼���uiԪ��
	/// @param left ���x����λ��
	/// @param top ���y����λ��
	void onGuiMouseMove(MyGUI::Widget* sender, int left, int top);

	/// �¼���Gui��갴��
	/// @param sender ���ø��¼���uiԪ��
	/// @param left ���x����λ��
	/// @param top ���y����λ��
	/// @param id ��갴��id
	void onGuiMousePressed(MyGUI::Widget* sender, int left, int top, MyGUI::MouseButton id);

	/// �¼���Gui��굯��
	/// @param sender ���ø��¼���uiԪ��
	/// @param left ���x����λ��
	/// @param top ���y����λ��
	/// @param id ��갴��id
	void onGuiMouseReleased(MyGUI::Widget* sender, int left, int top, MyGUI::MouseButton id);

	/// �¼���Gui��굥��
	/// @param sender ���ø��¼���uiԪ��
	void onGuiMouseClick(MyGUI::Widget* sender);

	/// �¼���Gui���˫��
	/// @param sender ���ø��¼���uiԪ��
	void onGuiMouseDoubleClick(MyGUI::Widget* sender);

	/// �¼���Gui��ü��̽���
	/// @param sender ���ø��¼���uiԪ��
	/// @param old �ɵ�ӵ�м��̽����uiԪ���������ǿ�ָ��
	void onGuiKeyGetFocus(MyGUI::Widget* sender, MyGUI::Widget* old);

	/// �¼���Guiʧȥ���̽���
	/// @param sender ���ø��¼���uiԪ��
	/// @param new �µ�ӵ�м��̽����uiԪ���������ǿ�ָ��
	void onGuiKeyLoseFocus(MyGUI::Widget* sender, MyGUI::Widget* _new);

	/// �¼���Gui�����꽹��
	/// @param sender ���ø��¼���uiԪ��
	/// @param old �ɵ�ӵ����꽹���uiԪ���������ǿ�ָ��
	void onGuiMouseGetFocus(MyGUI::Widget* sender, MyGUI::Widget* old);

	/// �¼���Guiʧȥ��꽹��
	/// @param sender ���ø��¼���uiԪ��
	/// @param new �µ�ӵ����꽹���uiԪ���������ǿ�ָ��
	void onGuiMouseLoseFocus(MyGUI::Widget* sender, MyGUI::Widget* _new);

	/// �¼���Gui�������ƶ�
	/// @param sender ���ø��¼���uiԪ��
	/// @param rel �������ƶ���
	void onGuiMouseWheel(MyGUI::Widget* sender, int rel);

	/// �¼���Gui�����ק
	/// @param sender ���ø��¼���uiԪ��
	/// @param left ���x����λ��
	/// @param top ���y����λ��
	/// @param id ��갴��id
	void onGuiMouseDrag(MyGUI::Widget* sender, int left, int top, MyGUI::MouseButton id);

private:
	Ogre::Root* mRoot;
	MyGUI::OgrePlatform* mPlatform;
	MyGUI::Gui* mGui;
	bool mIsGuiInitialized;
	UIEventCallbackMap mUIEventCallbackMap;
	lua_State* mGuiL;

};

#endif // scRenderer_h__
