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

// 版本问题，1.80为msSingleton，而之前的为ms_Singleton
#include "OgrePrerequisites.h"
#if (OGRE_VERSION == ((1 << 16) | (8 << 8) | 0) )
#define ms_Singleton msSingleton 
#endif

// 动画
class scAnimation;
typedef shared_ptr<scAnimation> scAnimationPtr;
class scAnimationFactory;
typedef shared_ptr<scAnimationFactory> scAnimationFactoryPtr;
class scUiAnimation;
typedef shared_ptr<scUiAnimation> scUiAnimationPtr;
class scUiTranslateAnimation;
typedef shared_ptr<scUiTranslateAnimation> scUiTranslateAnimationPtr;
class scUiScaleAnimation;
typedef shared_ptr<scUiScaleAnimation> scUiScaleAnimationPtr;
class scUiRotateAnimation;
typedef shared_ptr<scUiRotateAnimation> scUiRotateAnimationPtr;
class scUiAlphaAnimation;
typedef shared_ptr<scUiAlphaAnimation> scUiAlphaAnimationPtr;
class scUiAnimationGroup;
typedef shared_ptr<scUiAnimationGroup> scUiAnimationGroupPtr;

#endif // scTypeDefine_h__
