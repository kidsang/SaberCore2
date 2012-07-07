#ifndef scRenderer_h__
#define scRenderer_h__

/**
 * �ļ���scRenderer
 * ���ڣ�2012/07/06
 * ���ߣ�kid
 */

//#include "OgreSingleton.h"
#include "Ogre.h"
#include "scTypeDefine.h"
#include <iostream>

/// Ogre��Ⱦ������ϵͳ
/// ����
class scRenderer : public Ogre::Singleton<scRenderer>
{
public:
	/// ���캯��
	/// @param resourceCfgPath ��Դ�����ļ�·��
	/// @param pluginCfgPath ��������ļ�·��
	scRenderer(string const& resourceCfgPath, string const& pluginCfgPath);
	~scRenderer(void);
	static scRenderer& getSingleton(void);
	static scRenderer* getSingletonPtr(void);

	/// ����Ogre������Ⱦ
	/// �����ڲ�ʹ�ã��ú���Ӧ����ĳ��ʱ�������
	bool _run(u32 dtms)
	{
		Ogre::WindowEventUtilities::messagePump();
		return mRoot->renderOneFrame((float)dtms / 1000.f);
	}

private:
	Ogre::Root* mRoot;
};

#endif // scRenderer_h__
