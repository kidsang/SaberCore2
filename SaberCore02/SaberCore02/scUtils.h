#ifndef scUtils_h__
#define scUtils_h__

/**
 * 文件：scUtils
 * 日期：2012/07/29
 * 作者：kid
 */

#include <iostream>
#include "scTypeDefine.h"

/// 将任意对象转化为string
/// 注意必须重载运算符<<
/// @param any 任意类型的对象
template <typename T>
const string scToString(T const& any)
{
	std::ostringstream out;
	out << any;
	return out.str();
}

#endif // scUtils_h__
