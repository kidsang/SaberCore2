#ifndef scUiScaleAnimation_h__
#define scUiScaleAnimation_h__

/**
 * time: 2012/08/08
 * author: kid
 */

#include "scUiAnimation.h"
#include "scKeyFrame.h"
namespace MyGUI {
	class Widget;
}

/// UI ���Ŷ���
class scUiScaleAnimation : public scUiAnimation
{
public:
	explicit scUiScaleAnimation(bool isLoop);
	~scUiScaleAnimation(void);

	/// Ϊ����ע������(���ö���)
	/// �����ڲ�ʹ�ã���scRenderer����
	/// @param widget �������õĶ���һ��UIԪ��
	virtual void _registerWidget(MyGUI::Widget* widget);

	/// ����һ���ؼ�֡�����������ؼ�֡�б�
	/// @param time �ؼ�֡ʱ��, ��λΪ����
	/// @param scaleX UIԪ����X�᷽���ϵ�������
	/// @param scaleY UIԪ����Y�᷽���ϵ�������
	/// @param itype ��ֵ��������
	void createKeyFrame(u32 time, f32 scaleX, f32 scaleY, scKeyFrame::InterpolationType itype = scKeyFrame::IT_LINEAR);

protected:
	virtual void runImpl( scKeyFramePtr k0, scKeyFramePtr k1 );

private:
	int mOriginWidth;
	int mOriginHeight;

	//struct ScaleParams
	//{
	//	f32 scaleX;
	//	f32 scaleY;

	//	ScaleParams(f32 sX, f32 sY)
	//		: scaleX(sX), scaleY(sY)
	//	{}

	//	ScaleParams operator + (ScaleParams const& s)
	//	{ return ScaleParams(scaleX + s.scaleX, scaleY + s.scaleY);	}

	//	ScaleParams operator - (ScaleParams const& s)
	//	{ return ScaleParams(scaleX - s.scaleX, scaleY - s.scaleY);	}

	//	ScaleParams operator * (ScaleParams const& s)
	//	{ return ScaleParams(scaleX * s.scaleX, scaleY * s.scaleY);	}

	//	ScaleParams operator / (ScaleParams const& s)
	//	{ return ScaleParams(scaleX / s.scaleX, scaleY / s.scaleY);	}
	//};
};

#endif // scUiScaleAnimation_h__

