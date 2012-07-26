#ifndef scInputManager_h__
#define scInputManager_h__

/*
 * time: 2012/07/26
 * author: kid
 */

#include "scTypeDefine.h"
#include "ois/OIS.h"
#include "OgreSingleton.h"

/// ���������
/// ��������꼰������Ӧ�¼�
/// ʵ����������¼�ת������Ӧ��lua�ű�����
class scInputManager : public Ogre::Singleton<scInputManager>, public OIS::KeyListener, public OIS::MouseListener
{
public:
	/// ���캯��
	/// @param handle windows�Ĵ��ھ��
	/// @param width ��Ļ���
	/// @param height ��Ļ�߶�
	/// @param isExclusive �Ƿ��Զ�ռģʽ����
	/// ��ռģʽ�����ͼ��̶�����������Ϸ������
	scInputManager(u32 handle, u32 width, u32 height, bool isExclusive = false);
	~scInputManager(void);
	static scInputManager& getSingleton(void);
	static scInputManager* getSingletonPtr(void);

	/// �������Ͱ�����Ϣ
	/// �����ڲ�ʹ�ã�Ӧ������Ӧ��timeline����
	void _run()
	{
		mMouse->capture();
		mKeyboard->capture();
	}

	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );		
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

private:
	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;
};

#endif // scInputManager_h__

