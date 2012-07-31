#ifndef scEvent_h__
#define scEvent_h__

/**
 * 文件：scEvent
 * 日期：2012/07/16
 * 作者：kid
 */

#include "scTypeDefine.h"

/// 事件基类
class scEvent
{
public:

	/// 构造函数
	/// @param name 名字相当于是事件的类型
	scEvent(string const& name)
		: mName(name)
	{}
	virtual ~scEvent()
	{
	}

	string const& getName()
	{ return mName; }

private:
	string mName;
};

#endif // scEvent_h__
