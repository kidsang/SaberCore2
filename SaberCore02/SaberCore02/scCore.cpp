#include <Windows.h>
#include <iostream>
#include "scCore.h"
#include "scRenderer.h"
#include "scGameWorldManager.h"
#include "scGameWorld.h"
#include "scTimeLineManager.h"
#include "scTimeLine.h"

scCore::scCore(string const& cfgFilePath, bool useConsole/*= false*/)
	: mUseConsole(useConsole), mRenderer(0), mGameWorldManager(0), mTimeLineManager(0)
{
	if (mUseConsole)
	{
		// 创建控制台窗口,并将标准输入流，标准输出流和标准错误流重定向至控制台
		if( !AllocConsole() )
			MessageBoxA(NULL, "控制台生成失败。", NULL, 0); 
		SetConsoleTitleA("Debug Window"); 
		freopen_s(&fpDebugOut, "CONOUT$","w", stdout); 
		freopen_s(&fpDebugIn, "CONIN$", "r", stdin); 
		freopen_s(&fpDebugErr, "CONOUT$","w", stderr); 
		setlocale(LC_ALL, "chs");
		std::cout << "控制台已创建！" << std::endl;
	}

	// 初始化渲染子系统
	mRenderer = new scRenderer("resources_d.cfg", "plugins_d.cfg");
	// 初始化游戏世界管理类
	mGameWorldManager = new scGameWorldManager();
	// 创建时间轴管理类
	mTimeLineManager = new scTimeLineManager();

	// 创建渲染时间轴，60hz
	scTimeLinePtr tl = mTimeLineManager->createTimeLine("Render", 60);
	tl->addRunCallBack("Render", [&](u32 dtms)->bool{return mRenderer->_run(dtms);});
	// 创建游戏世界时间轴, 60Hz
	tl = mTimeLineManager->createTimeLine("GameWorld", 60);
	tl->addRunCallBack("GameWorld", [&](u32 dtms)->bool{return mGameWorldManager->_run(dtms);});
	// 测试一下
	scGameWorldPtr gw(new scGameWorld("test"));
	mGameWorldManager->addGameWorld(gw->getName(), gw);
	mGameWorldManager->initializeGameWorld("test");
	
}

scCore::~scCore(void)
{
	if (mTimeLineManager)
	{ delete mTimeLineManager; mTimeLineManager = 0; }

	if (mGameWorldManager)
	{ delete mGameWorldManager; mGameWorldManager = 0; }

	if (mRenderer)
	{ delete mRenderer; mRenderer = 0; }

	if (mUseConsole)
	{
		// 销毁控制台窗口
		fclose(fpDebugOut); 
		fclose(fpDebugIn); 
		fclose(fpDebugErr);
		FreeConsole();
	}
}

void scCore::start()
{
	// 启动循环
	mTimeLineManager->startMain();
	mTimeLineManager->startThreads();
}
