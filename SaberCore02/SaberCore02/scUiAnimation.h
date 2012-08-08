#ifndef scUiAnimation_h__
#define scUiAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scTypeDefine.h"
#include "scAnimation.h"
namespace MyGUI {
	class Widget;
}

/// ui�����ӿ���
class scUiAnimation : public scAnimation
{
public:
	/// ���캯��
	/// @param isLoop �����Ƿ�ѭ������
	explicit scUiAnimation(bool isLoop)
		: scAnimation(isLoop)
	{ }
	virtual ~scUiAnimation(void)
	{ }

	/// Ϊ����ע������(���ö���)
	/// �����ڲ�ʹ�ã���scRenderer����
	/// @param widget �������õĶ���һ��UIԪ��
	virtual void _registerWidget(MyGUI::Widget* widget)
	{ mHost = widget; }

protected:
	/// ���ж�����ʵ��
	/// @param k0 ��ǰ����ʱ��ε�ǰһ���ؼ�֡
	/// @param k1 ��ǰ����ʱ��εĺ�һ���ؼ�֡
	virtual void runImpl( scKeyFrame* k0, scKeyFrame* k1 ) = 0;

	/// ���ض�����������һ��UIԪ��
	MyGUI::Widget* getHost()
	{ return mHost; }

private:
	MyGUI::Widget* mHost;

};

#endif // scUiAnimation_h__

