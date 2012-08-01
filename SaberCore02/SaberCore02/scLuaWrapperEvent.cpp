#include "scLuaWrapper.h"
#include "scTypeDefine.h"
#include "scEventRouter.h"
#include "scEventQueue.h"
#include "scEvent.h"

void exportScEvent(lua_State* L)
{
	using namespace luabind;

	//---->>../scEventRouter.h 
	module(L)
		[
			//--scEventRouter
			class_<scEventRouter>("scEventRouter")
			.def(constructor<>())
			//.def("createEventQueue", (scEventQueuePtr (scEventRouter::*)(const string &))&scEventRouter::createEventQueue)
			//.def("destroyEventQueue", (void (scEventRouter::*)(const string &))&scEventRouter::destroyEventQueue)
			.def("registerEvent", (void (scEventRouter::*)(const string &,  const string &))&scEventRouter::registerEvent)
			.def("unregisterEvent", (void (scEventRouter::*)(const string &))&scEventRouter::unregisterEvent)
			.def("unregisterEvents", (void (scEventRouter::*)(const string &))&scEventRouter::unregisterEvents)
			.def("putEvent", (void (scEventRouter::*)(scEvent const&))&scEventRouter::putEvent)
			,
			def("getEventRouter", &scEventRouter::getSingletonPtr)
			//.def("getEventQueue", (scEventQueuePtr (scEventRouter::*)(const string &))&scEventRouter::getEventQueue)
			//.def("_run", (void (scEventRouter::*)())&scEventRouter::_run)
		];
	//<<----../scEventRouter.h
	//---->>../scAnEvent.h 
	module(L)
		[
			//--scAnEvent
			class_<scEvent>("scEvent")
			.def(constructor<const string &>())
			.def("getName", (const string &(scEvent::*)())&scEvent::getName)
			.def("putBool", (void (scEvent::*)(const string &,  bool))&scEvent::putBool)
			.def("putI32", (void (scEvent::*)(const string &,  i32))&scEvent::putI32)
			.def("putF32", (void (scEvent::*)(const string &,  f32))&scEvent::putF32)
			.def("putString", (void (scEvent::*)(const string &,  const string &))&scEvent::putString)
			.def("getBool", (bool (scEvent::*)(const string &))&scEvent::getBool)
			.def("getI32", (i32 (scEvent::*)(const string &))&scEvent::getI32)
			.def("getF32", (f32 (scEvent::*)(const string &))&scEvent::getF32)
			.def("getString", (const string (scEvent::*)(const string &))&scEvent::getString)
		];
	//<<----../scEvent.h
}
