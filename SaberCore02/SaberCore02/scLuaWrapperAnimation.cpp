#include "scLuaWrapper.h"
#include "scAnimation.h"
#include "scAnimationManager.h"
#include "scUiAlphaAnimation.h"
#include "scUiTranslateAnimation.h"
#include "scUiRotateAnimation.h"
#include "scUiScaleAnimation.h"
#include "scUiAnimationGroup.h"
#include "scKeyFrame.h"

// 辅助方法，返回动画管理类实例
scAnimationManager* getAnimationManager()
{ return scAnimationManager::getSingletonPtr(); }

void exportKeyFrame(lua_State* L);
void exportGuiAnimation(lua_State* L);

void exportScAnimation(lua_State* L)
{
	using namespace luabind;

	//---->>../scAnimation.h 
	module(L)
		[
			//--scAnimation
			class_<scAnimation>("scAnimation")
			.def("isLoop", (bool (scAnimation::*)())&scAnimation::isLoop)
			.def("setLoop", (void (scAnimation::*)(bool))&scAnimation::setLoop)
			.def("getTime", (u32 (scAnimation::*)())&scAnimation::getTime)
			.def("getRepeatTimes", (u32 (scAnimation::*)())&scAnimation::getRepeatTimes)
			.def("setRepeatTimes", (void (scAnimation::*)(u32))&scAnimation::setRepeatTimes)
			.def("getCurrentState", (scAnimation::AnimationState (scAnimation::*)())&scAnimation::getCurrentState)
			.def("pause", (void (scAnimation::*)())&scAnimation::pause)
			.def("play", (void (scAnimation::*)())&scAnimation::play)
			.def("stop", (void (scAnimation::*)())&scAnimation::stop)
			//----> AnimationState
			.enum_("constants")
			[
				value("AS_RUNNING", 0),
				value("AS_PAUSED", 1),
				value("AS_FINISHED", 2)
			]
			//<---- AnimationState
		];
	//<<----../scAnimation.h
	//---->>../scAnimationManager.h 
	module(L)
		[
			//--scAnimationManager
			class_<scAnimationManager>("scAnimationManager")
			.def("addFactory", (void (scAnimationManager::*)(int))&scAnimationManager::addFactory)
			.def("createAnimation", (scAnimationPtr (scAnimationManager::*)(const string &,  bool))&scAnimationManager::createAnimation)
			.def("createUiAlphaAnimation", (scUiAnimationPtr (scAnimationManager::*)(bool))&scAnimationManager::_createUiAlphaAnimation)
			.def("createUiTranslateAnimation", (scUiAnimationPtr (scAnimationManager::*)(bool))&scAnimationManager::_createUiTranslateAnimation)
			.def("createUiScaleAnimation", (scUiAnimationPtr (scAnimationManager::*)(bool))&scAnimationManager::_createUiScaleAnimation)
			.def("createUiRotateAnimation", (scUiAnimationPtr (scAnimationManager::*)(bool))&scAnimationManager::_createUiRotateAnimation)
			.def("createUiAnimationGroup", (scUiAnimationPtr (scAnimationManager::*)())&scAnimationManager::_createUiAnimationGroup)
		];
	//<<----../scAnimationManager.h
	//---->>helper funcs
	module(L)
		[
			def("getAnimationManager", getAnimationManager)
		];
	//<<----helper funcs

	exportKeyFrame(L);
	exportGuiAnimation(L);
}
void exportKeyFrame(lua_State* L)
{
	using namespace luabind;

	//---->>../scKeyFrame.h 
	module(L)
		[
			//--scKeyFrame
			class_<scKeyFrame>("scKeyFrame")
			.def("getTime", (u32 (scKeyFrame::*)())&scKeyFrame::getTime)
			.def("getInterpolationType", (scKeyFrame::InterpolationType (scKeyFrame::*)())&scKeyFrame::getInterpolationType)
			.def("setInterpolationType", (void (scKeyFrame::*)(scKeyFrame::InterpolationType))&scKeyFrame::setInterpolationType)
			//----> InterpolationType
			.enum_("constants")
			[
				value("IT_NONE", 0),
				value("IT_LINEAR", 1),
				value("IT_SQUARE_IN", 2),
				value("IT_SQUARE_OUT", 3),
				value("IT_CUBIC_IN", 4),
				value("IT_CUBIC_OUT", 5),
				value("IT_EXP_IN", 6),
				value("IT_EXP_OUT", 7)
			]
			//<---- InterpolationType
		];
	//<<----../scKeyFrame.h
}

void exportGuiAnimation(lua_State* L)
{
	using namespace luabind;
	//---->>../scUiAnimation.h 
	module(L)
		[
			//--scUiAnimation
			class_<scUiAnimation, scAnimation>("scUiAnimation")
		];
	//<<----../scUiAnimation.h
	//---->>../scUiAlphaAnimation.h 
	module(L)
		[
			//--scUiAlphaAnimation
			class_<scUiAlphaAnimation, scUiAnimation>("scUiAlphaAnimation")
			.def("createKeyFrame", (void (scUiAlphaAnimation::*)(u32,  f32,  scKeyFrame::InterpolationType))&scUiAlphaAnimation::createKeyFrame)
		];
	//<<----../scUiAlphaAnimation.h
	//---->>../scUiTranslateAnimation.h 
	module(L)
		[
			//--scUiTranslateAnimation
			class_<scUiTranslateAnimation, scUiAnimation>("scUiTranslateAnimation")
			.def("createKeyFrame", (void (scUiTranslateAnimation::*)(u32,  i32,  i32,  scKeyFrame::InterpolationType))&scUiTranslateAnimation::createKeyFrame)
		];
	//<<----../scUiTranslateAnimation.h
	//---->>../scUiScaleAnimation.h 
	module(L)
		[
			//--scUiScaleAnimation
			class_<scUiScaleAnimation, scUiAnimation>("scUiScaleAnimation")
			.def("createKeyFrame", (void (scUiScaleAnimation::*)(u32,  f32,  f32,  scKeyFrame::InterpolationType))&scUiScaleAnimation::createKeyFrame)
		];
	//<<----../scUiScaleAnimation.h
	//---->>../scUiRotateAnimation.h 
	module(L)
		[
			//--scUiRotateAnimation
			class_<scUiRotateAnimation, scUiAnimation>("scUiRotateAnimation")
			.def("createKeyFrame", (void (scUiRotateAnimation::*)(u32, f32, f32, f32, scKeyFrame::InterpolationType))&scUiRotateAnimation::createKeyFrame)
		];
	//<<----../scUiRotateAnimation.h
	//---->>../scUiAnimationGroup.h 
	module(L)
		[
			//--scUiAnimationGroup
			class_<scUiAnimationGroup, scUiAnimation>("scUiAnimationGroup")
			.def("addAnimation", (void (scUiAnimationGroup::*)(scUiAnimationPtr))&scUiAnimationGroup::addAnimation)
		];
	//<<----../scUiAnimationGroup.h
}