#ifndef scCore_h__
#define scCore_h__

/**
 * �ļ���scCore
 * ���ڣ�2012/07/06
 * ���ߣ�kid
 */

#include "scTypeDefine.h"
#include <boost/shared_ptr.hpp>
#include <ctime>
#include <Windows.h>

class scTimeLineManager;

/// SaberCore�������
class scCore
{
public:
	/// ���캯��
	/// @param cfgFilePath �����ļ�·��
	scCore(string const& cfgFilePath, bool useConsole = false);
	~scCore(void);

	/// ��������
	void start();

private:
	bool mUseConsole;
	FILE* fpDebugOut; 
	FILE* fpDebugIn;
	FILE* fpDebugErr;

	clock_t mLastTime;
	scTimeLineManager* mTimeLineManager;
};

#endif // scCore_h__

