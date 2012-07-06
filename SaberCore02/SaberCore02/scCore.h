#ifndef scCore_h__
#define scCore_h__

/**
 * 文件：scCore
 * 日期：2012/07/06
 * 作者：kid
 */

#include "scTypeDefine.h"
#include <boost/shared_ptr.hpp>
#include <ctime>
#include <Windows.h>

class scRenderer;
class scTimeLineManager;

/// SaberCore引擎入口
class scCore
{
public:
	/// 构造函数
	/// @param cfgFilePath 配置文件路径
	scCore(string const& cfgFilePath, bool useConsole = false);
	~scCore(void);

	/// 运行引擎
	void start();

private:
	bool mUseConsole;
	FILE* fpDebugOut; 
	FILE* fpDebugIn;
	FILE* fpDebugErr;

	scRenderer* mRenderer;

	clock_t mLastTime;
	scTimeLineManager* mTimeLineManager;
};

#endif // scCore_h__

