#ifndef scError_h__
#define scError_h__

/**
 * �ļ���scError
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include <iostream>
#include <string>
#include <cassert>
#include "scTypeDefine.h"

/// �رչ���fopen�ľ���
#pragma warning(disable: 4996)

/// ���Ժʹ�����Ϣ������ȼ�
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

/// ���������Ϣ
/// @param _msg ������Ϣ
/// @param _level ����ȼ�
template <typename T>
inline void scErrMsg(T const& _msg, u32 _level = DL_NORMAL)
{
	if (_level >= SC_DEBUG_LEVEL)
		std::cerr << _msg << std::endl;
};

#else

template <typename T>
inline void scErrMsg(T const& _msg, u32 _level = DL_NORMAL)
{
}

#endif

#ifdef _DEBUG

/// saber core����
/// @param _exp ���Ա��ʽ
/// @param _msg ������Ϣ
/// @param _level ����ȼ�
template <typename T>
inline void scAssert(bool _exp, T _msg, u32 _level = DL_NORMAL)
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
inline void scAssert(bool _exp, T _msg = "", u32 _level = DL_NORMAL)
{
}

#endif

#endif // scError_h__
