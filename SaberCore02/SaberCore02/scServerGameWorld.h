#ifndef scServerGameWorld_h__
#define scServerGameWorld_h__

/*
 * time: 2012/07/17
 * author: kid
 */

//#include "scTypeDefine.h"
//#include "scGameWorld.h"
//
//class scServerGameWorld : public scGameWorld
//{
//public:
//	/// 构造函数
//	/// @param worlName 游戏世界的名称
//	/// @param mapName 地图名称
//	scServerGameWorld(string const& worldName, string const& mapName);
//	~scServerGameWorld(void);
//
//	/// 初始化游戏世界
//	virtual void initialize();
//
//	/// 释放资源
//	virtual void release();
//
//	/// 运行场景的逻辑
//	/// 仅供内部使用，该函数应该由游戏世界管理类调用
//	/// @param dtms 上一帧到这一帧所经历的时间，单位毫秒
//	virtual bool _run(u32 dtms);
//
//	/// 从lua文件中加载场景
//	/// @param fileName lua文件名
//	/// @param entry lua入口函数名，形如void (scServerGameWorld* )
//	void loadScene(string const& fileName, string const& entry = "createScene");
//
//	/// 放置静态物体
//	/// @param meshName 模型名称
//	void addStatic(string const& meshName, Ogre::Vector3 const& position, Ogre::Quaternion const& orientation, Ogre::Vector3 const& scale);
//
//private:
//	string mMapName;
//};

#endif // scServerGameWorld_h__

