#ifndef scTypeDefine_h__
#define scTypeDefine_h__

/**
 * 文件：scTypeDefine
 * 日期：2012/07/01
 * 作者：kid
 */

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef float f32;
typedef double f64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#include <string>
typedef std::string string;

#include <boost/shared_ptr.hpp>
//#define shared_ptr boost::shared_ptr
using boost::shared_ptr;

#endif // scTypeDefine_h__
