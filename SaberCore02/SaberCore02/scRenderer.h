#ifndef scRenderer_h__
#define scRenderer_h__

/**
 * �ļ���scRenderer
 * ���ڣ�2012/07/06
 * ���ߣ�kid
 */

//#include "OgreSingleton.h"
#include <iostream>
#include "Ogre.h"
#include "MyGUI/MyGUI.h"
#include "MyGUI/MyGUI_OgrePlatform.h"
#include "scTypeDefine.h"
#include "scError.h"

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
	bool _run(u32 dtms);

	/// ��ʼ��GUI
	/// @param mgr ����������
	void initializeGui(Ogre::SceneManager* mgr);

	/// �ر�GUI
	void shutdownGui();

	// get/set
public:
	/// ����OgreRoot
	Ogre::Root* getOgreRoot()
	{ return mRoot; }

	/// ����MyGUI
	MyGUI::Gui* getGui()
	{ 
		scAssert(mIsGuiInitialized, "GUI not initialized! You must first call initializeGui()");
		return mGui; 
	}

private:
	Ogre::Root* mRoot;
	MyGUI::OgrePlatform* mPlatform;
	MyGUI::Gui* mGui;
	bool mIsGuiInitialized;

};

#endif // scRenderer_h__
