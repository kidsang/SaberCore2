#ifndef scUtils_h__
#define scUtils_h__

/**
 * �ļ���scUtils
 * ���ڣ�2012/07/29
 * ���ߣ�kid
 */

#include <iostream>
#include "scTypeDefine.h"

/// ���������ת��Ϊstring
/// ע��������������<<
/// @param any �������͵Ķ���
template <typename T>
const string scToString(T const& any)
{
	std::ostringstream out;
	out << any;
	return out.str();
}

#endif // scUtils_h__
