#include "scLuaWrapper.h"
#include "scAnimation.h"
#include "scAnimationManager.h"
#include "scUiAlphaAnimation.h"
#include "scUiTranslateAnimation.h"
#include "scUiRotateAnimation.h"
#include "scUiScaleAnimation.h"
#include "scUiAnimationGroup.h"

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
			.def("createUiAlphaAnimation", (scUiAlphaAnimationPtr (scAnimationManager::*)(bool))&scAnimationManager::createUiAlphaAnimation)
			.def("createUiTranslateAnimation", (scUiTranslateAnimationPtr (scAnimationManager::*)(bool))&scAnimationManager::createUiTranslateAnimation)
			.def("createUiScaleAnimation", (scUiScaleAnimationPtr (scAnimationManager::*)(bool))&scAnimationManager::createUiScaleAnimation)
			.def("createUiRotateAnimation", (scUiRotateAnimationPtr (scAnimationManager::*)(bool))&scAnimationManager::createUiRotateAnimation)
			.def("createUiAnimationGroup", (scUiAnimationGroupPtr (scAnimationManager::*)(bool))&scAnimationManager::createUiAnimationGroup)
		];
	//<<----../scAnimationManager.h

	exportGuiAnimation(L);
}
void exportGuiAnimation(lua_State* L)
{
	using namespace luabind;
	//---->>../scUiAnimation.h 
	module(L)
		[
			//--scUiAnimation
			class_<scUiAnimation>("scUiAnimation")
		];
	//<<----../scUiAnimation.h
	//---->>../scUiAlphaAnimation.h 
	module(L)
		[
			//--scUiAlphaAnimation
			class_<scUiAlphaAnimation>("scUiAlphaAnimation")
			.def("createKeyFrame", (void (scUiAlphaAnimation::*)(u32,  f32,  scKeyFrame::InterpolationType))&scUiAlphaAnimation::createKeyFrame)
		];
	//<<----../scUiAlphaAnimation.h
	//---->>../scUiTranslateAnimation.h 
	module(L)
		[
			//--scUiTranslateAnimation
			class_<scUiTranslateAnimation>("scUiTranslateAnimation")
			.def("createKeyFrame", (void (scUiTranslateAnimation::*)(u32,  i32,  i32,  scKeyFrame::InterpolationType))&scUiTranslateAnimation::createKeyFrame)
		];
	//<<----../scUiTranslateAnimation.h
	//---->>../scUiScaleAnimation.h 
	module(L)
		[
			//--scUiScaleAnimation
			class_<scUiScaleAnimation>("scUiScaleAnimation")
			.def("createKeyFrame", (void (scUiScaleAnimation::*)(u32,  f32,  f32,  scKeyFrame::InterpolationType))&scUiScaleAnimation::createKeyFrame)
		];
	//<<----../scUiScaleAnimation.h
	//---->>../scUiRotateAnimation.h 
	module(L)
		[
			//--scUiRotateAnimation
			class_<scUiRotateAnimation>("scUiRotateAnimation")
			.def("createKeyFrame", (void (scUiRotateAnimation::*)(u32,  f32,  scKeyFrame::InterpolationType))&scUiRotateAnimation::createKeyFrame)
		];
	//<<----../scUiRotateAnimation.h
	//---->>../scUiAnimationGroup.h 
	module(L)
		[
			//--scUiAnimationGroup
			class_<scUiAnimationGroup>("scUiAnimationGroup")
			.def("addAnimation", (void (scUiAnimationGroup::*)(int))&scUiAnimationGroup::addAnimation)
		];
	//<<----../scUiAnimationGroup.h
}