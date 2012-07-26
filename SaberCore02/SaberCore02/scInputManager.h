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

/// 输入管理类
/// 负责处理鼠标及键盘响应事件
/// 实际上它会把事件转交给对应的lua脚本处理
class scInputManager : public Ogre::Singleton<scInputManager>, public OIS::KeyListener, public OIS::MouseListener
{
public:
	/// 构造函数
	/// @param handle windows的窗口句柄
	/// @param width 屏幕宽度
	/// @param height 屏幕高度
	/// @param isExclusive 是否以独占模式运行
	/// 独占模式下鼠标和键盘都被局限在游戏窗口内
	scInputManager(u32 handle, u32 width, u32 height, bool isExclusive = false);
	~scInputManager(void);
	static scInputManager& getSingleton(void);
	static scInputManager* getSingletonPtr(void);

	/// 捕获鼠标和按键消息
	/// 仅供内部使用，应该由响应的timeline调用
	void _run()
	{
		mMouse->capture();
		mKeyboard->capture();
	}

	/// 为键盘按下事件注册处理脚本
	/// 输入事件全部转移给lua脚本处理
	/// 同一时刻仅能有一个脚本被注册，后注册的会覆盖新注册的
	/// @param fileName lua脚本名称
	void registerKeyPressed(string const& fileName, string const& entry);

	/// 为键盘弹起事件注册处理脚本
	/// 输入事件全部转移给lua脚本处理
	/// 同一时刻仅能有一个脚本被注册，后注册的会覆盖新注册的
	/// @param fileName lua脚本名称
	void registerKeyReleased(string const& fileName, string const& entry);

	/// 为鼠标移动事件注册处理脚本
	/// 输入事件全部转移给lua脚本处理
	/// 同一时刻仅能有一个脚本被注册，后注册的会覆盖新注册的
	/// @param fileName lua脚本名称
	void registerMouseMoved(string const& fileName, string const& entry);

	/// 为鼠标按下事件注册处理脚本
	/// 输入事件全部转移给lua脚本处理
	/// 同一时刻仅能有一个脚本被注册，后注册的会覆盖新注册的
	/// @param fileName lua脚本名称
	void registerMousePressed(string const& fileName, string const& entry);

	/// 为鼠标弹起事件注册处理脚本
	/// 输入事件全部转移给lua脚本处理
	/// 同一时刻仅能有一个脚本被注册，后注册的会覆盖新注册的
	/// @param fileName lua脚本名称
	void registerMouseReleased(string const& fileName, string const& entry);

	/// 解开对键盘按下事件处理脚本的注册
	void unregisterKeyPressed();

	/// 解开对键盘弹起事件处理脚本的注册
	void unregisterKeyReleased();

	/// 解开对鼠标移动事件处理脚本的注册
	void unregisterMouseMoved();

	/// 解开对鼠标按下事件处理脚本的注册
	void unregisterMousePressed();

	/// 解开对鼠标弹起事件处理脚本的注册
	void unregisterMouseReleased();

	/// 解开对所有事件处理脚本的注册
	void unregisterAll();

	// 监听器
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

/// 包装了OIS的鼠标事件
/// 其实是为了解决luabind里面无法绑定const成员的问题
struct scMouseEventWrapper
{
	scMouseEventWrapper(OIS::MouseState ms)
		: state(ms)
	{
	}

	OIS::MouseState state;
};

#endif // scInputManager_h__

