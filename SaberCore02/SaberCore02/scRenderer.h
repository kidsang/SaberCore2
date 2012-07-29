#ifndef scRenderer_h__
#define scRenderer_h__

/**
 * 文件：scRenderer
 * 日期：2012/07/06
 * 作者：kid
 */

#include <map>
#include "Ogre.h"
#include "MyGUI/MyGUI.h"
#include "MyGUI/MyGUI_OgrePlatform.h"
#include "lua.hpp"
#include "scTypeDefine.h"
#include "scError.h"

/// Ogre渲染引擎子系统
/// 单例
class scRenderer : public Ogre::Singleton<scRenderer>
{
	typedef std::map<string, string> UIEventCallbackMap;
public:
	enum GuiEventType
	{
		UI_MOUSE_PRESSED, UI_MOUSE_RELEASED, UI_MOUSE_CLICK, UI_MOUSE_DOUBLE_CLICK
	};

public:
	/// 构造函数
	/// @param resourceCfgPath 资源配置文件路径
	/// @param pluginCfgPath 插件配置文件路径
	scRenderer(string const& resourceCfgPath, string const& pluginCfgPath);
	~scRenderer(void);
	static scRenderer& getSingleton(void);
	static scRenderer* getSingletonPtr(void);

	/// 调用Ogre进行渲染
	/// 仅供内部使用，该函数应该由某个时间轴调用
	bool _run(u32 dtms);

	/// 初始化GUI
	/// @param mgr 场景管理器
	/// @param callbackScript 处理UI事件的lua脚本
	/// @param registerScript 注册UI事件回调函数的lua脚本
	void initializeGui(Ogre::SceneManager* mgr, string const& callbackScript, string const& registerScript);

	/// 关闭GUI
	void shutdownGui();

	//void loadGuiEventConfig(string const& fileName);

	/// 为UI元件注册事件
	/// @param widgetName UI元件名称
	/// @param eventType 事件类型
	/// @param callbackName lua中的回调函数名称
	void registerGuiEvent(string const& widgetName, GuiEventType eventType, string const& callbackName);

	// get/set
public:
	/// 返回OgreRoot
	Ogre::Root* getOgreRoot()
	{ return mRoot; }

	/// 返回MyGUI
	MyGUI::Gui* getGui()
	{ 
		scAssert(mIsGuiInitialized, "GUI not initialized! You must first call initializeGui()");
		return mGui; 
	}

private:
	/// 事件：Gui鼠标按下
	/// @param sender 调用该事件的ui元件
	/// @param left 鼠标x坐标位置
	/// @param top 鼠标y坐标位置
	/// @param id 鼠标按键id
	void onGuiMousePressed(MyGUI::Widget* sender, int left, int top, MyGUI::MouseButton id);

	/// 事件：Gui鼠标弹起
	/// @param sender 调用该事件的ui元件
	/// @param left 鼠标x坐标位置
	/// @param top 鼠标y坐标位置
	/// @param id 鼠标按键id
	void onGuiMouseReleased(MyGUI::Widget* sender, int left, int top, MyGUI::MouseButton id);

	/// 事件：Gui鼠标单击
	/// @param sender 调用该事件的ui元件
	void onGuiMouseClick(MyGUI::Widget* sender);

	/// 事件：Gui鼠标双击
	/// @param sender 调用该事件的ui元件
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
