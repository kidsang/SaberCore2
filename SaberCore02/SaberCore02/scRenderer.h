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

/// Ogre��Ⱦ������ϵͳ
/// ����
class scRenderer : public Ogre::Singleton<scRenderer>
{
	typedef std::map<string, string> UIEventCallbackMap;
public:
	enum GuiEventType
	{
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
	/// @param callbackScript ����UI�¼���lua�ű�
	/// @param registerScript ע��UI�¼��ص�������lua�ű�
	void initializeGui(Ogre::SceneManager* mgr, string const& callbackScript, string const& registerScript);

	/// �ر�GUI
	void shutdownGui();

	//void loadGuiEventConfig(string const& fileName);

	/// ΪUIԪ��ע���¼�
	/// @param widgetName UIԪ������
	/// @param eventType �¼�����
	/// @param callbackName lua�еĻص���������
	void registerGuiEvent(string const& widgetName, GuiEventType eventType, string const& callbackName);

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

private:
	Ogre::Root* mRoot;
	MyGUI::OgrePlatform* mPlatform;
	MyGUI::Gui* mGui;
	bool mIsGuiInitialized;
	UIEventCallbackMap mUIEventCallbackMap;
	lua_State* mGuiL;

};

#endif // scRenderer_h__
