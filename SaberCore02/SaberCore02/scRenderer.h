#ifndef scRenderer_h__
#define scRenderer_h__

/**
 * 文件：scRenderer
 * 日期：2012/07/06
 * 作者：kid
 */

//#include "OgreSingleton.h"
#include <iostream>
#include "Ogre.h"
#include "MyGUI/MyGUI.h"
#include "MyGUI/MyGUI_OgrePlatform.h"
#include "scTypeDefine.h"
#include "scError.h"

/// Ogre渲染引擎子系统
/// 单例
class scRenderer : public Ogre::Singleton<scRenderer>
{
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
	void initializeGui(Ogre::SceneManager* mgr);

	/// 关闭GUI
	void shutdownGui();

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
	Ogre::Root* mRoot;
	MyGUI::OgrePlatform* mPlatform;
	MyGUI::Gui* mGui;
	bool mIsGuiInitialized;

};

#endif // scRenderer_h__
