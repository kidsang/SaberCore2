#ifndef scGameWorldManager_h__
#define scGameWorldManager_h__

/**
 * 文件：scGameWorldManager
 * 日期：2012/07/07
 * 作者：kid
 */

#include <map>
#include "scTypeDefine.h"
#include "OgreSingleton.h"
#include "scError.h"

class scGameWorld;
typedef shared_ptr<scGameWorld> scGameWorldPtr;

/// 游戏世界管理类
/// 负责游戏世界的创建、管理、跳转和销毁
/// 管理类内部维护一个游戏世界名称与所需创建世界的参数的键值对表
/// 发生场景跳转时，首先从当前世界获取下一个世界的名称，
/// 销毁当前世界，创建下一个世界，并将其变为当前世界
/// 单例
class scGameWorldManager : public Ogre::Singleton<scGameWorldManager>
{
	typedef std::map<string, scGameWorldPtr> GameWorldMap;

public:
	scGameWorldManager();

	/// 向管理类中添加一个游戏世界
	/// @param name 游戏世界的名字
	/// @param world 游戏世界的实例
	void addGameWorld(string const& name, scGameWorldPtr const& world);

	/// 移除一个游戏世界
	/// 一般来说应该不会用到这个功能…好吧，我还是加了
	/// @param name 游戏世界的名字
	void removeGameWorld(string const& name);

	/// 创建游戏的初始游戏世界
	/// 这是整个游戏中的第一个游戏世界
	/// 其它世界只能跳转而不能像初始世界一样直接创建
	/// @param name 需要被创建的世界的名称
	void initializeGameWorld(string const& name);

	/// 跳转到下一个游戏世界
	/// @param name 下一个游戏世界的名称
	void jumpTo(string const& name);

	/// 运行当前的游戏世界
	/// 仅供内部使用，该函数应该由相应的时间轴调用
	/// @param dtms 上一帧到这一帧所经历的时间，单位毫秒
	bool _run(u32 dtms);

	// get/set
public:
	/// 获取当前游戏世界
	scGameWorldPtr const& getCurrentGameWorld()
	{
		scAssert(isInitialized, "No game world initialized, call \"initializeGameWorld()\" first.");
		return mCurrentGameWorld;
	}

	/// Override standard Singleton retrieval.
	static scGameWorldManager& getSingleton(void);
	/// Override standard Singleton retrieval.
	static scGameWorldManager* getSingletonPtr(void);

private:
	bool isInitialized;
	scGameWorldPtr mCurrentGameWorld;
	GameWorldMap mGameWorldMap;
};

#endif // scGameWorldManager_h__

