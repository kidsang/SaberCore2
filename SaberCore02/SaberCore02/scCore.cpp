#include "scCore.h"
#include "scTimeLineManager.h"
#include <Windows.h>
#include <iostream>

scCore::scCore(string const& cfgFilePath, bool useConsole/*= false*/)
	: mUseConsole(useConsole), mTimeLineManager(0)
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


	// ����ʱ���������
	mTimeLineManager = new scTimeLineManager();
	scTimeLinePtr tl = mTimeLineManager->createTimeLine("Render", 60);

}

scCore::~scCore(void)
{

	if (mTimeLineManager)
	{
		delete mTimeLineManager;
		mTimeLineManager = 0;
	}

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
		std::cout<<dtms<<std::endl;

		mLastTime = currentTime;
	}

}
