#ifndef scGameArea_h__
#define scGameArea_h__

/**
 * 文件：scGameArea
 * 日期：2012/07/09
 * 作者：kid
 */

#include "scTypeDefine.h"
//#include "Ogre.h"

/// 游戏区域
/// 游戏世界可能由许多个游戏区域组成，当游戏场景十分巨大时更是如此
/// 游戏区域是一块区域中游戏对象以及事件的集合
/// 游戏区域应该支持背景加载(多线程)
class scGameArea
{
public:
	enum Status
	{
		SLEEP, LOADING, ACTIVE, UNLOADING
	};

	scGameArea(void);
	~scGameArea(void);

	/// 异步加载资
	/// 可通过getStatus()函数查询当前状态
	void loadAsync();

	// get/set
public:
	Status getStatus()
	{
		// 只有get没有set的话。。应该不需要加锁吧？
		return mCurrentStatus;
	}

private:
	Status mCurrentStatus;
};

#endif // scGameArea_h__

