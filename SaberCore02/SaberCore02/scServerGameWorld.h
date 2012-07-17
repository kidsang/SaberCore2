#ifndef scServerGameWorld_h__
#define scServerGameWorld_h__

/*
 * time: 2012/07/17
 * author: kid
 */

#include "scTypeDefine.h"
#include "scGameWorld.h"

class scServerGameWorld : public scGameWorld
{
public:
	/// ���캯��
	/// @param worlName ��Ϸ���������
	/// @param mapName ��ͼ����
	scServerGameWorld(string const& worldName, string const& mapName);
	~scServerGameWorld(void);

	/// ��ʼ����Ϸ����
	virtual void initialize();

	/// �ͷ���Դ
	virtual void release();

	/// ���г������߼�
	/// �����ڲ�ʹ�ã��ú���Ӧ������Ϸ������������
	/// @param dtms ��һ֡����һ֡��������ʱ�䣬��λ����
	virtual bool _run(u32 dtms);

private:
	string mMapName;
};

#endif // scServerGameWorld_h__

