#ifndef scGameWorld_h__
#define scGameWorld_h__

/**
 * 文件：scGameWorld
 * 日期：2012/07/07
 * 作者：kid
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

/// 游戏世界GameWorld
/// 一个游戏世界包含有自身的数据以及运行和交互的逻辑
/// 游戏世界在创建时加载自身所需数据，在结束时负责销毁数据
/// 一个游戏世界通常包含有：
/// 1. 一组场景管理器，一组镜头和一组视口
/// 2. 一套GUI
/// 3. 多个名为游戏区域(GameArea)的数据块
/// 游戏区域是游戏世界的一个子集
/// 当场景非常大时，我们可以仅加载当前需要的游戏区域
/// 并在随后加载剩余的
class scGameWorld
{
protected:
	typedef std::map<string, Ogre::Viewport*> ViewportMap;

public:
	/// 构造函数
	/// @param name 游戏世界的名称
	/// @param scriptName 创建游戏世界的lua脚本名
	/// @param scriptEntry 脚本的入口函数名
	scGameWorld(string const& name, string const& scriptName, string const& scriptEntry);
	virtual ~scGameWorld(void);

	/// 初始化游戏世界
	virtual void initialize();

	/// 释放资源
	virtual void release();

	/// 运行场景的逻辑
	/// 仅供内部使用，该函数应该由游戏世界管理类调用
	/// @param dtms 上一帧到这一帧所经历的时间，单位毫秒
	virtual bool _run(u32 dtms);

	/// 从lua文件中初始化场景
	/// @param fileName lua文件名
	/// @param entry lua入口函数名，形如void (scServerGameWorld* )
	void iniScene(string const& fileName, string const& entry = "createScene");

	/// 从lua文件中初始化UI系统,主要是为UI注册事件响应函数
	/// @param callbackScript 处理UI事件的lua脚本
	/// @param registerScript 注册UI事件回调函数的lua脚本
	void iniGui(string const& callbackScript, string const& registerScript);

	/// 从lua文件中初始化事件系统
	/// @param callbackScript 处理事件的lua脚本
	/// @param callbackEntry 处理事件的函数入口
	/// 函数签名：void(*func)(scAnEvent*)
	/// @param registerScript 注册事件类型的lua脚本
	/// @param registerEntry 注册事件的函数入口
	/// 函数签名：void(*func)(scGameWorld*)
	void iniEvent(string const& callbackScript, string const& callbackEntry,
		string const& registerScript, string const& registerEntry);

	// helper functions
public:
	/// 增加静态物体
	/// @param meshName 模型名称
	/// @param position 物体位置
	/// @param orientation 物体朝向
	/// @param scale 物体缩放
	void addStatic(string const& meshName, Ogre::Vector3 const& position, Ogre::Quaternion const& orientation, Ogre::Vector3 const& scale);

	/// 增加摄像机
	/// @param camName摄像机名称
	/// @return 创建好的摄像机
	Ogre::Camera* addCamera(string const& camName);

	/// 返回指定名称的摄像机
	/// @param camName摄像机名称
	/// @return 摄像机
	Ogre::Camera* getCamera(string const& camName);

	/// 销毁指定名称的摄像机
	void removeCamera(string const& camName);

	/// 增加视口,并为其指定摄像机
	/// 后创建的视口永远覆盖之前创建的视口
	/// 默认占据整个屏幕
	/// @param vpName 视口名称
	/// @param camName 摄像机名称
	void addViewport(string const& vpName, string const& camName);

	/// 增加视口,并为其指定摄像机
	/// 后创建的视口永远覆盖之前创建的视口
	/// 自定义大小位置
	/// @param vpName 视口名称
	/// @param camName 摄像机名称
	/// @param left 视口左上角x坐标(0.0 - 1.0)
	/// @param top 视口左上角y坐标(0.0 - 1.0)
	/// @param width 视口宽(0.0 - 1.0)
	/// @param height 视口高(0.0 - 1.0)
	void addViewport(string const& vpName, string const& camName, float left, float top, float width, float height);

	/// 移除指定名称的视口
	/// @param vpName 视口名称
	void removeViewport(string const& vpName);

	/// 辅助方法，导入某个lua模块(文件)
	/// 不需要带.lua后缀名
	void luaImport(string const& moduleName);

public:
	/// 返回游戏世界的名称
	string const& getName()
	{return mName;}

	/// 返回游戏世界所拥有的事件队列的名称
	string const& getEventQueueName();

private:
	/// 辅助方法，导出自身类
	void exportSelf(lua_State* L);

	/// 辅助方法，查找对应名称脚本的路径
	string const getScriptPath(string const& name);

protected:
	string mName;
	Ogre::SceneManager* mSceneManager;
	ViewportMap mViewports;
	static u32 sNextViewportZOder; // 下一个视口的高度
	shared_ptr<scEventQueue> mEventQueue; // 事件队列
	lua_State* mL; // 负责事件处理的lua虚拟机
	string mScriptName;
	string mScriptEntry;
	string mEventCallbackEntry; // lua中事件处理入口函数名
};

#endif // scGameWorld_h__

