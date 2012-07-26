#ifndef scInputManager_h__
#define scInputManager_h__

/*
 * time: 2012/07/26
 * author: kid
 */

#include "scTypeDefine.h"
#include "ois/OIS.h"
#include "OgreSingleton.h"

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

	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );		
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

private:
	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;
};

#endif // scInputManager_h__

