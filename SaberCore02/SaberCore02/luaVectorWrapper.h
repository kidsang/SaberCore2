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

	{
		using namespace Ogre;
	}
}

void exportOgreMath(lua_State* L)
{
	using namespace luabind;
	using namespace Ogre;

	//---- file: OgreMath.h----

	module(L)
		[

			//---- class: Radian----
			class_<Radian>("Radian")
			.def(constructor<Real >())
			.def(constructor<const Degree & >())
			.def("valueAngleUnits", (Real (Radian::*)())&Radian::valueAngleUnits)
			,

			//---- class: Degree----
			class_<Degree>("Degree")
			.def(constructor<Real >())
			.def(constructor<const Radian & >())
			.def("valueDegrees", (Real (Degree::*)())&Degree::valueDegrees)
			.def("valueRadians", (Real (Degree::*)())&Degree::valueRadians)
			,

			//---- class: Angle----
			class_<Angle>("Angle")
			.def(constructor<Real >())
			,

			//---- class: Math----
			class_<Math>("Math")
			.def(constructor<int >())
			.def(constructor<>())

		];

	//---- file: OgreVector2.h----

	module(L)
		[

			//---- class: Vector2----
			class_<Vector2>("Vector2")
			.def(constructor<>())
			.def(constructor<const Real , const Real >())
			.def(constructor<const Real >())
			//.def(constructor<const Real >())
			//.def(constructor<const int >())
			.def(constructor<const Real * >())
			.def("swap", (void (Vector2::*)(Vector2 & ))&Vector2::swap)
			.def("ptr", (Real * (Vector2::*)())&Vector2::ptr)
			//.def("ptr", (const Real * (Vector2::*)())&Vector2::ptr)
			.def("length", (Real (Vector2::*)())&Vector2::length)
			.def("squaredLength", (Real (Vector2::*)())&Vector2::squaredLength)
			.def("distance", (Real (Vector2::*)(const  Vector2 & ))&Vector2::distance)
			.def("squaredDistance", (Real (Vector2::*)(const  Vector2 & ))&Vector2::squaredDistance)
			.def("dotProduct", (Real (Vector2::*)(const  Vector2 & ))&Vector2::dotProduct)
			.def("normalise", (Real (Vector2::*)())&Vector2::normalise)
			.def("midPoint", (Vector2 (Vector2::*)(const  Vector2 & ))&Vector2::midPoint)
			.def("makeFloor", (void (Vector2::*)(const  Vector2 & ))&Vector2::makeFloor)
			.def("makeCeil", (void (Vector2::*)(const  Vector2 & ))&Vector2::makeCeil)
			.def("perpendicular", (Vector2 (Vector2::*)(void  ))&Vector2::perpendicular)
			.def("crossProduct", (Real (Vector2::*)(const  Vector2 & ))&Vector2::crossProduct)
			.def("randomDeviant", (Vector2 (Vector2::*)(Real  ))&Vector2::randomDeviant)
			.def("isZeroLength", (bool (Vector2::*)(void  ))&Vector2::isZeroLength)
			.def("normalisedCopy", (Vector2 (Vector2::*)(void  ))&Vector2::normalisedCopy)
			.def("reflect", (Vector2 (Vector2::*)(const  Vector2 & ))&Vector2::reflect)
			.def("isNaN", (bool (Vector2::*)())&Vector2::isNaN)

		];

	//---- file: OgreVector3.h----

	module(L)
		[

			//---- class: Vector3----
			class_<Vector3>("Vector3")
			.def(constructor<>())
			.def(constructor<const Real , const Real , const Real >())
			//.def(constructor<const Real >())
			//.def(constructor<const int >())
			.def(constructor<const Real * >())
			.def(constructor<const Real >())
			.def("swap", (void (Vector3::*)(Vector3 & ))&Vector3::swap)
			.def("ptr", (Real * (Vector3::*)())&Vector3::ptr)
			//.def("ptr", (const Real * (Vector3::*)())&Vector3::ptr)
			.def("length", (Real (Vector3::*)())&Vector3::length)
			.def("squaredLength", (Real (Vector3::*)())&Vector3::squaredLength)
			.def("distance", (Real (Vector3::*)(const  Vector3 & ))&Vector3::distance)
			.def("squaredDistance", (Real (Vector3::*)(const  Vector3 & ))&Vector3::squaredDistance)
			.def("dotProduct", (Real (Vector3::*)(const  Vector3 & ))&Vector3::dotProduct)
			.def("absDotProduct", (Real (Vector3::*)(const  Vector3 & ))&Vector3::absDotProduct)
			.def("normalise", (Real (Vector3::*)())&Vector3::normalise)
			.def("crossProduct", (Vector3 (Vector3::*)(const  Vector3 & ))&Vector3::crossProduct)
			.def("midPoint", (Vector3 (Vector3::*)(const  Vector3 & ))&Vector3::midPoint)
			.def("makeFloor", (void (Vector3::*)(const  Vector3 & ))&Vector3::makeFloor)
			.def("makeCeil", (void (Vector3::*)(const  Vector3 & ))&Vector3::makeCeil)
			.def("perpendicular", (Vector3 (Vector3::*)(void  ))&Vector3::perpendicular)
			.def("randomDeviant", (Vector3 (Vector3::*)(const  Radian & , const  Vector3 & ))&Vector3::randomDeviant)
			//.def("Radian", (Angle (Vector3::*)())&Vector3::Radian)
			.def("angleBetween", (Radian (Vector3::*)(const  Vector3 & ))&Vector3::angleBetween)
			.def("getRotationTo", (Quaternion (Vector3::*)(const  Vector3 & , const  Vector3 & ))&Vector3::getRotationTo)
			.def("isZeroLength", (bool (Vector3::*)(void  ))&Vector3::isZeroLength)
			.def("normalisedCopy", (Vector3 (Vector3::*)(void  ))&Vector3::normalisedCopy)
			.def("reflect", (Vector3 (Vector3::*)(const  Vector3 & ))&Vector3::reflect)
			.def("positionEquals", (bool (Vector3::*)(const  Vector3 & , Real  ))&Vector3::positionEquals)
			.def("positionCloses", (bool (Vector3::*)(const  Vector3 & , Real  ))&Vector3::positionCloses)
			.def("directionEquals", (bool (Vector3::*)(const  Vector3 & , const  Radian & ))&Vector3::directionEquals)
			.def("isNaN", (bool (Vector3::*)())&Vector3::isNaN)

		];

	//---- file: OgreVector4.h----

	module(L)
		[

			//---- class: Vector4----
			class_<Vector4>("Vector4")
			.def(constructor<>())
			.def(constructor<const Real , const Real , const Real , const Real >())
			//.def(constructor<const Real >())
			//.def(constructor<const int >())
			.def(constructor<const Real * >())
			.def(constructor<const Real >())
			.def(constructor<const Vector3 & >())
			.def("swap", (void (Vector4::*)(Vector4 & ))&Vector4::swap)
			.def("ptr", (Real * (Vector4::*)())&Vector4::ptr)
			//.def("ptr", (const Real * (Vector4::*)())&Vector4::ptr)
			.def("dotProduct", (Real (Vector4::*)(const  Vector4 & ))&Vector4::dotProduct)
			.def("isNaN", (bool (Vector4::*)())&Vector4::isNaN)

		];

	//---- file: OgreMatrix3.h----

	module(L)
		[

			//---- class: Matrix3----
			class_<Matrix3>("Matrix3")
			.def(constructor<>())
			//.def(constructor<const Real >())
			.def(constructor<const Matrix3 & >())
			.def("swap", (void (Matrix3::*)(Matrix3 & ))&Matrix3::swap)
			.def("GetColumn", (Vector3 (Matrix3::*)(size_t  ))&Matrix3::GetColumn)
			.def("SetColumn", (void (Matrix3::*)(size_t  , const  Vector3 & ))&Matrix3::SetColumn)
			.def("FromAxes", (void (Matrix3::*)(const  Vector3 & , const  Vector3 & , const  Vector3 & ))&Matrix3::FromAxes)
			.def("FromAxisAngle", (void (Matrix3::*)(const  Vector3 & , const  Radian & ))&Matrix3::FromAxisAngle)
			.def("ToEulerAnglesXYZ", (bool (Matrix3::*)(Radian & , Radian & , Radian & ))&Matrix3::ToEulerAnglesXYZ)
			.def("ToEulerAnglesXZY", (bool (Matrix3::*)(Radian & , Radian & , Radian & ))&Matrix3::ToEulerAnglesXZY)
			.def("ToEulerAnglesYXZ", (bool (Matrix3::*)(Radian & , Radian & , Radian & ))&Matrix3::ToEulerAnglesYXZ)
			.def("ToEulerAnglesYZX", (bool (Matrix3::*)(Radian & , Radian & , Radian & ))&Matrix3::ToEulerAnglesYZX)
			.def("ToEulerAnglesZXY", (bool (Matrix3::*)(Radian & , Radian & , Radian & ))&Matrix3::ToEulerAnglesZXY)
			.def("ToEulerAnglesZYX", (bool (Matrix3::*)(Radian & , Radian & , Radian & ))&Matrix3::ToEulerAnglesZYX)
			.def("FromEulerAnglesXYZ", (void (Matrix3::*)(const  Radian & , const  Radian & , const  Radian & ))&Matrix3::FromEulerAnglesXYZ)
			.def("FromEulerAnglesXZY", (void (Matrix3::*)(const  Radian & , const  Radian & , const  Radian & ))&Matrix3::FromEulerAnglesXZY)
			.def("FromEulerAnglesYXZ", (void (Matrix3::*)(const  Radian & , const  Radian & , const  Radian & ))&Matrix3::FromEulerAnglesYXZ)
			.def("FromEulerAnglesYZX", (void (Matrix3::*)(const  Radian & , const  Radian & , const  Radian & ))&Matrix3::FromEulerAnglesYZX)
			.def("FromEulerAnglesZXY", (void (Matrix3::*)(const  Radian & , const  Radian & , const  Radian & ))&Matrix3::FromEulerAnglesZXY)
			.def("FromEulerAnglesZYX", (void (Matrix3::*)(const  Radian & , const  Radian & , const  Radian & ))&Matrix3::FromEulerAnglesZYX)
			.def("EigenSolveSymmetric", (void (Matrix3::*)(Real  , Vector3  ))&Matrix3::EigenSolveSymmetric)
			.def("hasScale", (bool (Matrix3::*)())&Matrix3::hasScale)

		];

	//---- file: OgreMatrix4.h----

	module(L)
		[

			//---- class: Matrix4----
			class_<Matrix4>("Matrix4")

		];

	//---- file: OgreQuaternion.h----

	module(L)
		[

			//---- class: Quaternion----
			class_<Quaternion>("Quaternion")
			.def(constructor<const Matrix3 & >())
			.def(constructor<const Radian & , const Vector3 & >())
			.def(constructor<const Vector3 & , const Vector3 & , const Vector3 & >())
			.def(constructor<const Vector3 * >())
			.def(constructor<Real * >())
			.def(constructor<Real  , Real  , Real  , Real  >())
			//.def("Quaternion", ((Quaternion::*)(Real  , Real  , Real  , Real  ))&Quaternion::Quaternion)
			.def("swap", (void (Quaternion::*)(Quaternion & ))&Quaternion::swap)
			.def("ptr", (Real * (Quaternion::*)())&Quaternion::ptr)
			//.def("ptr", (const Real * (Quaternion::*)())&Quaternion::ptr)
			.def("FromRotationMatrix", (void (Quaternion::*)(const  Matrix3 & ))&Quaternion::FromRotationMatrix)
			.def("ToRotationMatrix", (void (Quaternion::*)(Matrix3 & ))&Quaternion::ToRotationMatrix)
			.def("FromAngleAxis", (void (Quaternion::*)(const  Radian & , const  Vector3 & ))&Quaternion::FromAngleAxis)
			//.def("ToAngleAxis", (void (Quaternion::*)(Radian & , Vector3 & ))&Quaternion::ToAngleAxis)
			//.def("ToAngleAxis", (void (Quaternion::*)(Degree & , Vector3 & ))&Quaternion::ToAngleAxis)
			.def("FromAxes", (void (Quaternion::*)(const  Vector3 * ))&Quaternion::FromAxes)
			.def("FromAxes", (void (Quaternion::*)(const  Vector3 & , const  Vector3 & , const  Vector3 & ))&Quaternion::FromAxes)
			//.def("ToAxes", (void (Quaternion::*)(Vector3 * ))&Quaternion::ToAxes)
			//.def("ToAxes", (void (Quaternion::*)(Vector3 & , Vector3 & , Vector3 & ))&Quaternion::ToAxes)
			.def("xAxis", (Vector3 (Quaternion::*)(void  ))&Quaternion::xAxis)
			.def("yAxis", (Vector3 (Quaternion::*)(void  ))&Quaternion::yAxis)
			.def("zAxis", (Vector3 (Quaternion::*)(void  ))&Quaternion::zAxis)
			.def("Dot", (Real (Quaternion::*)(const  Quaternion & ))&Quaternion::Dot)
			.def("Inverse", (Quaternion (Quaternion::*)())&Quaternion::Inverse)
			.def("Log", (Quaternion (Quaternion::*)())&Quaternion::Log)

		];
}


#endif // luaVectorWrapper_h__