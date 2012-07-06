#ifndef scError_h__
#define scError_h__

/**
 * 文件：scError
 * 日期：2012/05/20
 * 作者：kid
 */

#include <iostream>
#include <string>
#include <cassert>
#include "scTypeDefine.h"

/// 关闭关于fopen的警告
#pragma warning(disable: 4996)

/// 断言和错误信息的输出等级
enum scDebugLevel
{
	DL_ALL = 0,
	DL_TRIVIAL = 100,
	DL_NORMAL = 200,
	DL_DEADLY = 300
};

#ifndef SC_DEBUG_LEVEL
#define SC_DEBUG_LEVEL DL_ALL
#endif



#ifdef _DEBUG

/// 输出错误信息
/// @param _msg 错误信息
/// @param _level 错误等级
template <typename T>
inline void scErrMsg(T const& _msg, scDebugLevel _level = DL_NORMAL)
{
	if (_level >= SC_DEBUG_LEVEL)
		std::cerr << _msg << std::endl;
};

#else

template <typename T>
inline void scErrMsg(T const& _msg, scDebugLevel _level = DL_NORMAL)
{
}

#endif

#ifdef _DEBUG

/// saber core断言
/// @param _exp 断言表达式
/// @param _msg 附带信息
/// @param _level 错误等级
template <typename T>
inline void scAssert(bool _exp, T _msg, scDebugLevel _level = DL_NORMAL)
{
	if (_level >= SC_DEBUG_LEVEL)
	{
		if (!_exp)
			scErrMsg(string("Assertion Failed: ") + _msg, _level);
		assert(_exp);
	}
};

#else

template <typename T>
inline void scAssert(bool _exp, T _msg = "", scDebugLevel _level = DL_NORMAL)
{
}

#endif

#endif // scError_h__
