#include "scLuaWrapper.h"
#include "scTypeDefine.h"
#include "scEventRouter.h"
#include "scEventQueue.h"
#include "scAnEvent.h"

void exportScEvent(lua_State* L)
{
	using namespace luabind;

	//---->>../scEventQueue.h 
	module(L)
		[
			//--scEventQueue
			class_<scEventQueue>("scEventQueue")
			.def(constructor<const string &>())
			.def(constructor<>())
			.def("putEvent", (void (scEventQueue::*)(int))&scEventQueue::putEvent)
			.def("fetchEvents", (void (scEventQueue::*)(int &))&scEventQueue::fetchEvents)
			.def("getName", (string const& (scEventQueue::*)())&scEventQueue::getName)
		];
	//<<----../scEventQueue.h
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
			.def("putEvent", (void (scEventRouter::*)(int))&scEventRouter::putEvent)
			,
			def("getEventRouter", &scEventRouter::getSingletonPtr)
			//.scope
			//[
			//	def("getSingletonPtr", &scEventRouter::getSingletonPtr)
			//]
			//.def("getEventQueue", (scEventQueuePtr (scEventRouter::*)(const string &))&scEventRouter::getEventQueue)
			//.def("_run", (void (scEventRouter::*)())&scEventRouter::_run)
		];
	//<<----../scEventRouter.h
	//---->>../scAnEvent.h 
	module(L)
		[
			//--scAnEvent
			class_<scAnEvent>("scAnEvent")
			.def(constructor<const string &>())
			.def("putBool", (void (scAnEvent::*)(const string &,  bool))&scAnEvent::putBool)
			.def("putI32", (void (scAnEvent::*)(const string &,  i32))&scAnEvent::putI32)
			.def("putF32", (void (scAnEvent::*)(const string &,  f32))&scAnEvent::putF32)
			.def("putString", (void (scAnEvent::*)(const string &,  const string &))&scAnEvent::putString)
			.def("getBool", (bool (scAnEvent::*)(const string &))&scAnEvent::getBool)
			.def("getI32", (i32 (scAnEvent::*)(const string &))&scAnEvent::getI32)
			.def("getF32", (f32 (scAnEvent::*)(const string &))&scAnEvent::getF32)
			.def("getString", (const string (scAnEvent::*)(const string &))&scAnEvent::getString)
		];
	//<<----../scAnEvent.h
}
