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
#include "scUtils.h"

/// Ogre渲染引擎子系统
/// 单例
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
	/// @param scriptName 处理UI事件的lua脚本
	/// @param entry 入口函数名称
	/// 入口函数签名：void(scRender*)
	void initializeGui(Ogre::SceneManager* mgr, string const& scriptName, string const& entry);

	/// 关闭GUI
	void shutdownGui();

	//void loadGuiEventConfig(string const& fileName);

	/// 为UI元件注册事件
	/// @param widgetName UI元件名称
	/// @param eventType 事件类型
	/// @param callbackName lua中的回调函数名称
	void registerGuiEvent(string const& widgetName, GuiEventType eventType, string const& callbackName);

	/// 将UI元件与某个UI动画绑定
	/// @param widgetName UI元件的名称
	/// @param ani UI动画
	void bindGuiAnimation(string const& widgetName, scUiAnimationPtr const& ani);

	/// 辅助方法，导入某个lua模块(文件)
	/// 不需要带.lua后缀名
	/// @param moduleName lua模块名
	void luaImport(string const& moduleName);

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
	/// 辅助方法，获取指定名称ui元件的回调函数名
	/// @param widgetName ui元件名称
	/// @param type 事件类型
	/// @return 回调函数名称
	string const& findWidgetCallback(string const& widgetName, GuiEventType type)
	{
		string name = widgetName + scToString(type);
		auto iter = mUIEventCallbackMap.find(name);
		scAssert(iter != mUIEventCallbackMap.end(), "UI widget " + widgetName + "did not register event " + scToString(type));
		scAssert(mGuiL != 0, "Gui lua state not initialized!");
		return iter->second;
	}

	/// 辅助方法，导出自身类
	void exportSelf(lua_State* L);

	/// 事件：Gui键盘按下
	/// @param sender 调用该事件的ui元件
	/// @param key 按键码
	/// @param ch 按键字符
	void onGuiKeyPressed(MyGUI::Widget* sender, MyGUI::KeyCode key, MyGUI::Char ch);

	/// 事件：Gui键盘弹起
	/// @param sender 调用该事件的ui元件
	/// @param key 按键码
	void onGuiKeyReleased(MyGUI::Widget* sender, MyGUI::KeyCode key);

	/// 事件：Gui鼠标移动
	/// @param sender 调用该事件的ui元件
	/// @param left 鼠标x坐标位置
	/// @param top 鼠标y坐标位置
	void onGuiMouseMove(MyGUI::Widget* sender, int left, int top);

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

	/// 事件：Gui获得键盘焦点
	/// @param sender 调用该事件的ui元件
	/// @param old 旧的拥有键盘焦点的ui元件，或者是空指针
	void onGuiKeyGetFocus(MyGUI::Widget* sender, MyGUI::Widget* old);

	/// 事件：Gui失去键盘焦点
	/// @param sender 调用该事件的ui元件
	/// @param new 新的拥有键盘焦点的ui元件，或者是空指针
	void onGuiKeyLoseFocus(MyGUI::Widget* sender, MyGUI::Widget* _new);

	/// 事件：Gui获得鼠标焦点
	/// @param sender 调用该事件的ui元件
	/// @param old 旧的拥有鼠标焦点的ui元件，或者是空指针
	void onGuiMouseGetFocus(MyGUI::Widget* sender, MyGUI::Widget* old);

	/// 事件：Gui失去鼠标焦点
	/// @param sender 调用该事件的ui元件
	/// @param new 新的拥有鼠标焦点的ui元件，或者是空指针
	void onGuiMouseLoseFocus(MyGUI::Widget* sender, MyGUI::Widget* _new);

	/// 事件：Gui鼠标滚轮移动
	/// @param sender 调用该事件的ui元件
	/// @param rel 鼠标滚轮移动量
	void onGuiMouseWheel(MyGUI::Widget* sender, int rel);

	/// 事件：Gui鼠标拖拽
	/// @param sender 调用该事件的ui元件
	/// @param left 鼠标x坐标位置
	/// @param top 鼠标y坐标位置
	/// @param id 鼠标按键id
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
