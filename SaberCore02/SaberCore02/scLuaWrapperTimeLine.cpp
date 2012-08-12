#include "scLuaWrapper.h"
#include "scTimeLine.h"
#include "scAnimationTimeLine.h"
#include "scTimeLineManager.h"

// 辅助方法，获取时间轴管理类
scTimeLineManager* getTimeLineManager()
{ return scTimeLineManager::getSingletonPtr(); }

void exportScTimeLine(lua_State* L)
{
	using namespace luabind;
	//---->>../scTimeLineManager.h 
	module(L)
		[
			//--scTimeLineManager
			class_<scTimeLineManager>("scTimeLineManager")
			.def("getTimeLine", &scTimeLineManager::_getTimeLine) 
			//.def("destoryTimeLine", (void (scTimeLineManager::*)(int))&scTimeLineManager::destoryTimeLine)
			//.def("destoryTimeLine", (void (scTimeLineManager::*)(const string &))&scTimeLineManager::destoryTimeLine)
			//.def("setPriority", (void (scTimeLineManager::*)(int))&scTimeLineManager::setPriority)
			//.def("setPriority", (void (scTimeLineManager::*)(const string &,  i32))&scTimeLineManager::setPriority)
			//.def("startMain", (void (scTimeLineManager::*)())&scTimeLineManager::startMain)
			//.def("startThreads", (void (scTimeLineManager::*)())&scTimeLineManager::startThreads)
		];
	//<<----../scTimeLineManager.h
	//---->>../scTimeLine.h 
	module(L)
		[
			//--scTimeLine
			class_<scTimeLine>("scTimeLine")
			//.def("addRunCallBack", (void (scTimeLine::*)(const string &,  const FrameCallBack &))&scTimeLine::addRunCallBack)
			//.def("removeRunCallBack", (void (scTimeLine::*)(const string &))&scTimeLine::removeRunCallBack)
			//.def("getName", (const string& (scTimeLine::*)())&scTimeLine::getName)
			//.def("getScaleFactor", (f32 (scTimeLine::*)())&scTimeLine::getScaleFactor)
			//.def("setScaleFactor", (void (scTimeLine::*)(f32))&scTimeLine::setScaleFactor)
			//.def("getInvokeInterval", (u32 (scTimeLine::*)())&scTimeLine::getInvokeInterval)
			//.def("setInvokeInterval", (void (scTimeLine::*)(u32))&scTimeLine::setInvokeInterval)
			//.def("getInvokeRate", (u32 (scTimeLine::*)())&scTimeLine::getInvokeRate)
			//.def("setInvokeRate", (void (scTimeLine::*)(u32))&scTimeLine::setInvokeRate)
			//.def("getThreadStatus", (ThreadStatus (scTimeLine::*)())&scTimeLine::getThreadStatus)
			//.def("setThreadStatus", (void (scTimeLine::*)(scTimeLine::ThreadStatus))&scTimeLine::setThreadStatus)
			////----> ThreadStatus
			//.enum_("constants")
			//[
			//	value("TS_MAIN", 0),
			//	value("TS_THREAD", 1)
			//]
			//<---- ThreadStatus
		];
	//<<----../scTimeLine.h
	//---->>../scAnimationTimeLine.h 
	module(L)
		[
			//--scAnimationTimeLine
			class_<scAnimationTimeLine, scTimeLine>("scAnimationTimeLine")
			.def("addAnimation", (void (scAnimationTimeLine::*)(scAnimationPtr const&))&scAnimationTimeLine::addAnimation)
			.def("addAnimation", (void (scAnimationTimeLine::*)(scUiAnimationPtr const&))&scAnimationTimeLine::addAnimation)
		];
	//<<----../scAnimationTimeLine.h
	//---->>helper funcs
	module(L)
		[
			def("getTimeLineManager", getTimeLineManager)
		];
	//<<----helper funcs
}