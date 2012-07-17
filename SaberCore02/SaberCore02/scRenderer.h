#ifndef scRenderer_h__
#define scRenderer_h__

/**
 * 文件：scRenderer
 * 日期：2012/07/06
 * 作者：kid
 */

//#include "OgreSingleton.h"
#include "Ogre.h"
#include "scTypeDefine.h"
#include <iostream>

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
	bool _run(u32 dtms)
	{
		Ogre::WindowEventUtilities::messagePump();
		// 显示FPS
		HWND hwnd;
		Ogre::RenderWindow* window = mRoot->getAutoCreatedWindow();
		window->getCustomAttribute("WINDOW", (void*)&hwnd);
		char buff[64];
		sprintf(buff, "FPS: %f", window->getLastFPS());
		SetWindowTextA(hwnd, buff);
		return mRoot->renderOneFrame((float)dtms / 1000.f);
	}

private:
	Ogre::Root* mRoot;
};

#endif // scRenderer_h__
