#ifndef scEvent_h__
#define scEvent_h__

/*
 * time: 2012/07/31
 * author: kid
 */

#include <boost/any.hpp>
#include <map>
#include "scTypeDefine.h"
#include "scError.h"

/// �������ơ�һ���¼�������ֻ��һ���¼������
/// �������һ���¼������������͵�����
/// ���õ������֡��������ַ���
class scEvent
{
	typedef std::map<string, boost::any> ItemMap;

public:
	/// ���캯��
	/// @param name �����൱�����¼�������
	explicit scEvent(string const& name)
		: mName(name)
	{}
	scEvent()
		: mName("")
	{}

	string const& getName()
	{ return mName; }

	// ֮����д��ô�಻ͬ������Ϊ�˷��㵼����lua
	/// ���¼��з��벼��������
	void putBool(string const& key, bool value)
	{
		scAssert(mItems.find(key) == mItems.end(), "Event key \"" + key + "\" already exist.");
		mItems.insert(std::make_pair(key, boost::any(value)));
	}

	/// ���¼��з���i32(int)������
	void putI32(string const& key, i32 value)
	{
		scAssert(mItems.find(key) == mItems.end(), "Event key \"" + key + "\" already exist.");
		mItems.insert(std::make_pair(key, boost::any(value)));
	}

	/// ���¼��з���f32(float)������
	void putF32(string const& key, f32 value)
	{
		scAssert(mItems.find(key) == mItems.end(), "Event key \"" + key + "\" already exist.");
		mItems.insert(std::make_pair(key, boost::any(value)));
	}

	/// ���¼��з����ַ�����(string)����
	void putString(string const& key, string const& value)
	{
		scAssert(mItems.find(key) == mItems.end(), "Event key \"" + key + "\" already exist.");
		mItems.insert(std::make_pair(key, boost::any(value)));
	}

	/// ���¼���ȡ��bool������
	bool getBool(string const& key)
	{
		scAssert(mItems.find(key) != mItems.end(), "Event key \"" + key + "\" do not exist.");
		return boost::any_cast<bool>(mItems[key]);
	}

	/// ���¼���ȡ��i32(int)������
	i32 getI32(string const& key)
	{
		scAssert(mItems.find(key) != mItems.end(), "Event key \"" + key + "\" do not exist.");
		return boost::any_cast<i32>(mItems[key]);
	}

	/// ���¼���ȡ��f32(float)������
	f32 getF32(string const& key)
	{
		scAssert(mItems.find(key) != mItems.end(), "Event key \"" + key + "\" do not exist.");
		return boost::any_cast<f32>(mItems[key]);
	}

	/// ���¼���ȡ���ַ���(string)������
	const string getString(string const& key)
	{
		scAssert(mItems.find(key) != mItems.end(), "Event key \"" + key + "\" do not exist.");
		return boost::any_cast<string>(mItems[key]);
	}

private:
	string mName;
	ItemMap mItems;

};

#endif // scEvent_h__
