#ifndef luaVectorWrapper_h__
#define luaVectorWrapper_h__

/*
 * time: 2012/07/18
 * author: kid
 */

/// vector lua 包装

#include "scTypeDefine.h"
#include "OgreVector2.h"
#include "OgreVector3.h"
#include "OgreVector4.h"
#include "OgreQuaternion.h"

//////////////////////////////////////////////////////////////////////////
// Vector2

Ogre::Vector2 makeVector2(f32 x, f32 y)
{
	return Ogre::Vector2(x, y);
}

Ogre::Vector2 makeVector2(f32 scale)
{
	return Ogre::Vector2(scale);
}

Ogre::Vector2 makeVector2()
{
	return Ogre::Vector2(0.f);
}

//////////////////////////////////////////////////////////////////////////
// Vector3

Ogre::Vector3 makeVector3(f32 x, f32 y, f32 z)
{
	return Ogre::Vector3(x, y, z);
}

Ogre::Vector3 makeVector3(f32 scale)
{
	return Ogre::Vector3(scale);
}

Ogre::Vector3 makeVector3()
{
	return Ogre::Vector3(0.f);
}

//////////////////////////////////////////////////////////////////////////
// Vector 4

Ogre::Vector4 makeVector4(f32 x, f32 y, f32 z, f32 w)
{
	return Ogre::Vector4(x, y, z, w);
}

Ogre::Vector4 makeVector4(f32 scale)
{
	return Ogre::Vector4(scale);
}

Ogre::Vector4 makeVector4()
{
	return Ogre::Vector4(0.f);
}


//////////////////////////////////////////////////////////////////////////
// Quaternion

Ogre::Quaternion makeQuaternion(f32 w, f32 y, f32 z, f32 x)
{
	return Ogre::Quaternion(w, y, z, x);
}

Ogre::Quaternion makeQuaternion(f32 angle, Ogre::Vector3 const& axis)
{
	return Ogre::Quaternion(Ogre::Radian(angle), axis);
}

Ogre::Quaternion makeQuaternion()
{
	return Ogre::Quaternion();
}

//////////////////////////////////////////////////////////////////////////

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "scError.h"

void exportVectorAndQuaternion(lua_State* L)
{
	using namespace luabind;
	// 导出
	module(L)
		[
			def("Vector2", (Ogre::Vector2(*)())&makeVector2),
			def("Vector2", (Ogre::Vector2(*)(f32))&makeVector2),
			def("Vector2", (Ogre::Vector2(*)(f32, f32))&makeVector2),
			def("Vector3", (Ogre::Vector3(*)())&makeVector3),
			def("Vector3", (Ogre::Vector3(*)(f32))&makeVector3),
			def("Vector3", (Ogre::Vector3(*)(f32, f32, f32))&makeVector3),
			def("Vector4", (Ogre::Vector4(*)())&makeVector4),
			def("Vector4", (Ogre::Vector4(*)(f32))&makeVector4),
			def("Vector4", (Ogre::Vector4(*)(f32, f32, f32, f32))&makeVector4),
			def("Quaternion", (Ogre::Quaternion(*)())&makeQuaternion),
			def("Quaternion", (Ogre::Quaternion(*)(f32, f32, f32, f32))&makeQuaternion),
			def("Quaternion", (Ogre::Quaternion(*)(f32, Ogre::Vector3 const&))&makeQuaternion),
			class_<Ogre::Vector2>("DummyVector2"),
			class_<Ogre::Vector3>("DummyVector3"),
			class_<Ogre::Vector4>("DummyVector4"),
			class_<Ogre::Quaternion>("DummyQuaternion")
		];
}


#endif // luaVectorWrapper_h__