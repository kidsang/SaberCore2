#ifndef scAnEvent_h__
#define scAnEvent_h__

/*
 * time: 2012/07/31
 * author: kid
 */

#include <boost/any.hpp>
#include <map>
#include "scTypeDefine.h"
#include "scEvent.h"
#include "scError.h"

/// 如其名称“一个事件”，这只是一个事件类罢了
/// 你可以在一个事件里放入各种类型的数据
/// 常用的有数字、布尔和字符串
class scAnEvent : public scEvent
{
	typedef std::map<string, boost::any> ItemMap;

public:
	/// 构造函数
	/// @param name 名字相当于是事件的类型
	explicit scAnEvent(string const& name)
		: scEvent(name)
	{}

	// 之所以写这么多不同名称是为了方便导出到lua
	/// 在事件中放入布尔型内容
	void putBool(string const& key, bool value)
	{
		scAssert(mItems.find(key) == mItems.end(), "Event key \"" + key + "\" already exist.");
		mItems.insert(std::make_pair(key, boost::any(value)));
	}

	/// 在事件中放入i32(int)型内容
	void putI32(string const& key, i32 value)
	{
		scAssert(mItems.find(key) == mItems.end(), "Event key \"" + key + "\" already exist.");
		mItems.insert(std::make_pair(key, boost::any(value)));
	}

	/// 在事件中放入f32(float)型内容
	void putF32(string const& key, f32 value)
	{
		scAssert(mItems.find(key) == mItems.end(), "Event key \"" + key + "\" already exist.");
		mItems.insert(std::make_pair(key, boost::any(value)));
	}

	/// 在事件中放入字符串型(string)内容
	void putString(string const& key, string const& value)
	{
		scAssert(mItems.find(key) == mItems.end(), "Event key \"" + key + "\" already exist.");
		mItems.insert(std::make_pair(key, boost::any(value)));
	}

	/// 从事件中取出bool型内容
	bool getBool(string const& key)
	{
		scAssert(mItems.find(key) != mItems.end(), "Event key \"" + key + "\" do not exist.");
		return boost::any_cast<bool>(mItems[key]);
	}

	/// 从事件中取出i32(int)型内容
	i32 getI32(string const& key)
	{
		scAssert(mItems.find(key) != mItems.end(), "Event key \"" + key + "\" do not exist.");
		return boost::any_cast<i32>(mItems[key]);
	}

	/// 从事件中取出f32(float)型内容
	f32 getF32(string const& key)
	{
		scAssert(mItems.find(key) != mItems.end(), "Event key \"" + key + "\" do not exist.");
		return boost::any_cast<f32>(mItems[key]);
	}

	/// 从事件中取出字符串(string)型内容
	const string getString(string const& key)
	{
		scAssert(mItems.find(key) != mItems.end(), "Event key \"" + key + "\" do not exist.");
		return boost::any_cast<string>(mItems[key]);
	}

private:
	ItemMap mItems;

};

#endif // scAnEvent_h__

