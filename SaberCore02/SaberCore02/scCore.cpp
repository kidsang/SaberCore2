#include <Windows.h>
#include <iostream>
#include "scCore.h"
#include "scRenderer.h"
#include "scTimeLineManager.h"
#include "scTimeLine.h"

scCore::scCore(string const& cfgFilePath, bool useConsole/*= false*/)
	: mUseConsole(useConsole), mRenderer(0), mTimeLineManager(0)
{
	if (mUseConsole)
	{
		// ��������̨����,������׼����������׼������ͱ�׼�������ض���������̨
		if( !AllocConsole() )
			MessageBoxA(NULL, "����̨����ʧ�ܡ�", NULL, 0); 
		SetConsoleTitleA("Debug Window"); 
		freopen_s(&fpDebugOut, "CONOUT$","w", stdout); 
		freopen_s(&fpDebugIn, "CONIN$", "r", stdin); 
		freopen_s(&fpDebugErr, "CONOUT$","w", stderr); 
		setlocale(LC_ALL, "chs");
		std::cout << "����̨�Ѵ�����" << std::endl;
	}

	// ��ʼ����Ⱦ��ϵͳ
	mRenderer = new scRenderer("resources_d.cfg", "plugins_d.cfg");

	// ����ʱ���������
	mTimeLineManager = new scTimeLineManager();
	// ������Ⱦʱ���ᣬ60hz
	scTimeLinePtr tl = mTimeLineManager->createTimeLine("Render", 60);
	tl->addRunCallBack("Render", [&](u32 dtms)->bool{return mRenderer->_run(dtms);});

}

scCore::~scCore(void)
{
	if (mTimeLineManager)
	{ delete mTimeLineManager; mTimeLineManager = 0; }

	if (mRenderer)
	{ delete mRenderer; mRenderer = 0; }

	if (mUseConsole)
	{
		// ���ٿ���̨����
		fclose(fpDebugOut); 
		fclose(fpDebugIn); 
		fclose(fpDebugErr);
		FreeConsole();
	}
}

void scCore::start()
{
	// ��ʼ��ʱ��
	mLastTime = clock();
	clock_t currentTime = clock();
	u32 dtms;

	// ����ѭ��
	while (true)
	{
		currentTime = clock();
		dtms = currentTime - mLastTime;

		mTimeLineManager->run(dtms);
		//std::cout<<dtms<<std::endl;

		mLastTime = currentTime;
	}

}
