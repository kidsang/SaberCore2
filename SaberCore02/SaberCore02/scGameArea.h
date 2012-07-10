#ifndef scGameArea_h__
#define scGameArea_h__

/**
 * �ļ���scGameArea
 * ���ڣ�2012/07/09
 * ���ߣ�kid
 */

#include "scTypeDefine.h"
//#include "Ogre.h"

/// ��Ϸ����
/// ��Ϸ���������������Ϸ������ɣ�����Ϸ����ʮ�־޴�ʱ�������
/// ��Ϸ������һ����������Ϸ�����Լ��¼��ļ���
/// ��Ϸ����Ӧ��֧�ֱ�������(���߳�)
class scGameArea
{
public:
	enum Status
	{
		SLEEP, LOADING, ACTIVE, UNLOADING
	};

	scGameArea(void);
	~scGameArea(void);

	/// �첽������
	/// ��ͨ��getStatus()������ѯ��ǰ״̬
	void loadAsync();

	// get/set
public:
	Status getStatus()
	{
		// ֻ��getû��set�Ļ�����Ӧ�ò���Ҫ�����ɣ�
		return mCurrentStatus;
	}

private:
	Status mCurrentStatus;
};

#endif // scGameArea_h__

