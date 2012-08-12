#ifndef scAnimationManager_h__
#define scAnimationManager_h__

/**
 * �ļ���scAnimationManager
 * ���ڣ�2012/08/11
 * ���ߣ�kid
 */

#include <map>
#include "OgreSingleton.h"
#include "scTypeDefine.h"

/// ����������
/// ����Ҫְ���ǵ��ò�ͬ�Ĺ�����������ͬ�Ķ���
/// �����������಻ͬ�����ಢû��_run()����
/// �������Ϊһ����������ݴ���
/// ����������������Ҫ����ӵ�AnimationTimeLine��ʹ�乤��
/// ����
class scAnimationManager : public Ogre::Singleton<scAnimationManager>
{
	typedef std::map<string, scAnimationFactoryPtr> FactoryMap;

public:
	scAnimationManager(void);
	~scAnimationManager(void);
	static scAnimationManager& getSingleton(void);
	static scAnimationManager* getSingletonPtr(void);

	/// ���һ���¹���
	/// @param factory ����ʵ��
	void addFactory(scAnimationFactoryPtr factory);

	/// ʹ���ض�������������
	/// @param factoryName ����������
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scAnimationPtr createAnimation(string const& factoryName, bool isLoop);

	/// ����GUI͸���ȶ���
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scUiAlphaAnimationPtr createUiAlphaAnimation(bool isLoop);

	/// ����GUIƽ�ƶ���
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scUiTranslateAnimationPtr createUiTranslateAnimation(bool isLoop);

	/// ����GUI���Ŷ���
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scUiScaleAnimationPtr createUiScaleAnimation(bool isLoop);

	/// ����GUI��ת����
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scUiRotateAnimationPtr createUiRotateAnimation(bool isLoop);

	/// ����GUI������
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scUiAnimationGroupPtr createUiAnimationGroup();

	/// ����GUI͸���ȶ���
	/// �����ڲ�ʹ�ã�����lua��װ
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scUiAnimationPtr _createUiAlphaAnimation(bool isLoop);

	/// ����GUIƽ�ƶ���
	/// �����ڲ�ʹ�ã�����lua��װ
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scUiAnimationPtr _createUiTranslateAnimation(bool isLoop);

	/// ����GUI���Ŷ���
	/// �����ڲ�ʹ�ã�����lua��װ
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scUiAnimationPtr _createUiScaleAnimation(bool isLoop);

	/// ����GUI��ת����
	/// �����ڲ�ʹ�ã�����lua��װ
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scUiAnimationPtr _createUiRotateAnimation(bool isLoop);

	/// ����GUI������
	/// �����ڲ�ʹ�ã�����lua��װ
	/// @param isLoop �����Ƿ�ѭ������
	/// @return �����õĶ���ʵ��
	scUiAnimationPtr _createUiAnimationGroup();

private:
	/// �������������Դ����ڽ��Ķ�������
	void createBuildInFactories();
private:
	FactoryMap mFactories;
};

#endif // scAnimationManager_h__

