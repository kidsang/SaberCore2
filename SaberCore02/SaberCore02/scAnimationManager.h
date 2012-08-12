#ifndef scAnimationManager_h__
#define scAnimationManager_h__

/**
 * 文件：scAnimationManager
 * 日期：2012/08/11
 * 作者：kid
 */

#include <map>
#include "OgreSingleton.h"
#include "scTypeDefine.h"

/// 动画管理类
/// 其主要职责是调用不同的工厂来创建不同的动画
/// 与其它管理类不同，该类并没有_run()函数
/// 该类仅作为一个创建者身份存在
/// 动画创建出来后，需要被添加到AnimationTimeLine以使其工作
/// 单例
class scAnimationManager : public Ogre::Singleton<scAnimationManager>
{
	typedef std::map<string, scAnimationFactoryPtr> FactoryMap;

public:
	scAnimationManager(void);
	~scAnimationManager(void);
	static scAnimationManager& getSingleton(void);
	static scAnimationManager* getSingletonPtr(void);

	/// 添加一个新工厂
	/// @param factory 工厂实例
	void addFactory(scAnimationFactoryPtr factory);

	/// 使用特定工厂创建动画
	/// @param factoryName 工厂的名称
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scAnimationPtr createAnimation(string const& factoryName, bool isLoop);

	/// 创建GUI透明度动画
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scUiAlphaAnimationPtr createUiAlphaAnimation(bool isLoop);

	/// 创建GUI平移动画
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scUiTranslateAnimationPtr createUiTranslateAnimation(bool isLoop);

	/// 创建GUI缩放动画
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scUiScaleAnimationPtr createUiScaleAnimation(bool isLoop);

	/// 创建GUI旋转动画
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scUiRotateAnimationPtr createUiRotateAnimation(bool isLoop);

	/// 创建GUI动画组
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scUiAnimationGroupPtr createUiAnimationGroup();

	/// 创建GUI透明度动画
	/// 仅供内部使用，用于lua包装
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scUiAnimationPtr _createUiAlphaAnimation(bool isLoop);

	/// 创建GUI平移动画
	/// 仅供内部使用，用于lua包装
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scUiAnimationPtr _createUiTranslateAnimation(bool isLoop);

	/// 创建GUI缩放动画
	/// 仅供内部使用，用于lua包装
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scUiAnimationPtr _createUiScaleAnimation(bool isLoop);

	/// 创建GUI旋转动画
	/// 仅供内部使用，用于lua包装
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scUiAnimationPtr _createUiRotateAnimation(bool isLoop);

	/// 创建GUI动画组
	/// 仅供内部使用，用于lua包装
	/// @param isLoop 动画是否循环播放
	/// @return 创建好的动画实例
	scUiAnimationPtr _createUiAnimationGroup();

private:
	/// 辅助方法，用以创建内建的动画工厂
	void createBuildInFactories();
private:
	FactoryMap mFactories;
};

#endif // scAnimationManager_h__

