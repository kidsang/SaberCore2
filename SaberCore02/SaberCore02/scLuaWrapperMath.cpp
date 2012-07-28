#include "scLuaWrapper.h"


/*void exportVectorAndQuaternion( lua_State* L )
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
}*/
#include "Ogre.h"
#include "scError.h"

void exportOgreMath( lua_State* L )
{
	using namespace luabind;
	using namespace Ogre;

	//---->>include/OgreMath.h 
	module(L)
		[
			//--Radian
			class_<Radian>("Radian")
			.def(constructor<Real>())
			.def(constructor<const Ogre::Degree &>())
			.def("valueDegrees", (Real (Radian::*)())&Radian::valueDegrees)
			.def("valueRadians", (Real (Radian::*)())&Radian::valueRadians)
			.def("valueAngleUnits", (Real (Radian::*)())&Radian::valueAngleUnits)
			.def(self + other<const Ogre::Radian &>())
			.def(self + other<const Ogre::Degree &>())
			.def(self - other<const Ogre::Radian &>())
			.def(self - other<const Ogre::Degree &>())
			.def(self * other<Real>())
			.def(self * other<const Ogre::Radian &>())
			.def(self / other<Real>())
			.def(self < other<const Ogre::Radian &>())
			.def(self <= other<const Ogre::Radian &>())
			.def(self == other<const Ogre::Radian &>())
			,
			//--Degree
			class_<Degree>("Degree")
			.def(constructor<Real>())
			.def(constructor<const Ogre::Radian &>())
			.def("valueDegrees", (Real (Degree::*)())&Degree::valueDegrees)
			.def("valueRadians", (Real (Degree::*)())&Degree::valueRadians)
			.def("valueAngleUnits", (Real (Degree::*)())&Degree::valueAngleUnits)
			.def(self + other<const Ogre::Degree &>())
			.def(self + other<const Ogre::Radian &>())
			.def(self - other<const Ogre::Degree &>())
			.def(self - other<const Ogre::Radian &>())
			.def(self * other<Real>())
			.def(self * other<const Ogre::Degree &>())
			.def(self / other<Real>())
			.def(self < other<const Ogre::Degree &>())
			.def(self <= other<const Ogre::Degree &>())
			.def(self == other<const Ogre::Degree &>())
			,
			//--Angle
			class_<Angle>("Angle")
			.def(constructor<Real>())
			,
			//--Math
			class_<Math>("Math")
			.def(constructor<unsigned int>())
			//.def("buildTrigTables", (void (Math::*)())&Math::buildTrigTables)
		];
	//<<----include/OgreMath.h
	//---->>include/OgreVector2.h 
	module(L)
		[
			//--Vector2
			class_<Vector2>("Vector2")
			.def(constructor<>())
			.def(constructor<const Real,  const Real>())
			.def(constructor<const Real>())
			.def(constructor<const Real *>())
			.def(constructor<const int *>())
			//.def(constructor<Real *const>())
			.def("swap", (void (Vector2::*)(Ogre::Vector2 &))&Vector2::swap)
			.def("ptr", (Real* (Vector2::*)())&Vector2::ptr)
			//.def("ptr", (const Real* (Vector2::*)())&Vector2::ptr)
			.def("length", (Real (Vector2::*)())&Vector2::length)
			.def("squaredLength", (Real (Vector2::*)())&Vector2::squaredLength)
			.def("distance", (Real (Vector2::*)(const Ogre::Vector2 &))&Vector2::distance)
			.def("squaredDistance", (Real (Vector2::*)(const Ogre::Vector2 &))&Vector2::squaredDistance)
			.def("dotProduct", (Real (Vector2::*)(const Ogre::Vector2 &))&Vector2::dotProduct)
			.def("normalise", (Real (Vector2::*)())&Vector2::normalise)
			.def("midPoint", (Vector2 (Vector2::*)(const Ogre::Vector2 &))&Vector2::midPoint)
			.def("makeFloor", (void (Vector2::*)(const Ogre::Vector2 &))&Vector2::makeFloor)
			.def("makeCeil", (void (Vector2::*)(const Ogre::Vector2 &))&Vector2::makeCeil)
			.def("perpendicular", (Vector2 (Vector2::*)())&Vector2::perpendicular)
			.def("crossProduct", (Real (Vector2::*)(const Ogre::Vector2 &))&Vector2::crossProduct)
			.def("randomDeviant", (Vector2 (Vector2::*)(Real))&Vector2::randomDeviant)
			.def("isZeroLength", (bool (Vector2::*)())&Vector2::isZeroLength)
			.def("normalisedCopy", (Vector2 (Vector2::*)())&Vector2::normalisedCopy)
			.def("reflect", (Vector2 (Vector2::*)(const Ogre::Vector2 &))&Vector2::reflect)
			.def("isNaN", (bool (Vector2::*)())&Vector2::isNaN)
			//高版本才支持.def("angleBetween", (Ogre::Radian (Vector2::*)(const Ogre::Vector2 &))&Vector2::angleBetween)
			//高版本才支持.def("angleTo", (Ogre::Radian (Vector2::*)(const Ogre::Vector2 &))&Vector2::angleTo)
			.def(self == other<const Ogre::Vector2 &>())
			.def(self + other<const Ogre::Vector2 &>())
			.def(self - other<const Ogre::Vector2 &>())
			.def(self * other<const Real>())
			.def(self * other<const Ogre::Vector2 &>())
			.def(self / other<const Real>())
			.def(self / other<const Ogre::Vector2 &>())
			.def(self < other<const Ogre::Vector2 &>())
		];
	//<<----include/OgreVector2.h
	//---->>include/OgreVector3.h 
	module(L)
		[
			//--Vector3
			class_<Vector3>("Vector3")
			.def(constructor<>())
			.def(constructor<const Real,  const Real,  const Real>())
			.def(constructor<const Real *>())
			.def(constructor<const int *>())
			//.def(constructor<Real *const>())
			.def(constructor<const Real>())
			.def("swap", (void (Vector3::*)(Ogre::Vector3 &))&Vector3::swap)
			.def("ptr", (Real* (Vector3::*)())&Vector3::ptr)
			//.def("ptr", (const Real* (Vector3::*)())&Vector3::ptr)
			.def("length", (Real (Vector3::*)())&Vector3::length)
			.def("squaredLength", (Real (Vector3::*)())&Vector3::squaredLength)
			.def("distance", (Real (Vector3::*)(const Ogre::Vector3 &))&Vector3::distance)
			.def("squaredDistance", (Real (Vector3::*)(const Ogre::Vector3 &))&Vector3::squaredDistance)
			.def("dotProduct", (Real (Vector3::*)(const Ogre::Vector3 &))&Vector3::dotProduct)
			.def("absDotProduct", (Real (Vector3::*)(const Ogre::Vector3 &))&Vector3::absDotProduct)
			.def("normalise", (Real (Vector3::*)())&Vector3::normalise)
			.def("crossProduct", (Vector3 (Vector3::*)(const Ogre::Vector3 &))&Vector3::crossProduct)
			.def("midPoint", (Vector3 (Vector3::*)(const Ogre::Vector3 &))&Vector3::midPoint)
			.def("makeFloor", (void (Vector3::*)(const Ogre::Vector3 &))&Vector3::makeFloor)
			.def("makeCeil", (void (Vector3::*)(const Ogre::Vector3 &))&Vector3::makeCeil)
			.def("perpendicular", (Vector3 (Vector3::*)())&Vector3::perpendicular)
			.def("randomDeviant", (Vector3 (Vector3::*)(const Ogre::Radian &,  const Ogre::Vector3 &))&Vector3::randomDeviant)
			.def("angleBetween", (Radian (Vector3::*)(const Ogre::Vector3 &))&Vector3::angleBetween)
			.def("getRotationTo", (Quaternion (Vector3::*)(const Ogre::Vector3 &,  const Ogre::Vector3 &))&Vector3::getRotationTo)
			.def("isZeroLength", (bool (Vector3::*)())&Vector3::isZeroLength)
			.def("normalisedCopy", (Vector3 (Vector3::*)())&Vector3::normalisedCopy)
			.def("reflect", (Vector3 (Vector3::*)(const Ogre::Vector3 &))&Vector3::reflect)
			.def("positionEquals", (bool (Vector3::*)(const Ogre::Vector3 &,  Real))&Vector3::positionEquals)
			.def("positionCloses", (bool (Vector3::*)(const Ogre::Vector3 &,  Real))&Vector3::positionCloses)
			.def("directionEquals", (bool (Vector3::*)(const Ogre::Vector3 &,  const Ogre::Radian &))&Vector3::directionEquals)
			.def("isNaN", (bool (Vector3::*)())&Vector3::isNaN)
			//高版本才支持.def("primaryAxis", (Vector3 (Vector3::*)())&Vector3::primaryAxis)
			.def(self == other<const Ogre::Vector3 &>())
			.def(self + other<const Ogre::Vector3 &>())
			.def(self - other<const Ogre::Vector3 &>())
			.def(self * other<const Real>())
			.def(self * other<const Ogre::Vector3 &>())
			.def(self / other<const Real>())
			.def(self / other<const Ogre::Vector3 &>())
			.def(self < other<const Ogre::Vector3 &>())
		];
	//<<----include/OgreVector3.h
	//---->>include/OgreVector4.h 
	module(L)
		[
			//--Vector4
			class_<Vector4>("Vector4")
			.def(constructor<>())
			.def(constructor<const Real,  const Real,  const Real,  const Real>())
			.def(constructor<const Real *>())
			.def(constructor<const int *>())
			//.def(constructor<Real *const>())
			.def(constructor<const Real>())
			.def(constructor<const Ogre::Vector3 &>())
			.def("swap", (void (Vector4::*)(Ogre::Vector4 &))&Vector4::swap)
			.def("ptr", (Real* (Vector4::*)())&Vector4::ptr)
			//.def("ptr", (const Real* (Vector4::*)())&Vector4::ptr)
			.def("dotProduct", (Real (Vector4::*)(const Ogre::Vector4 &))&Vector4::dotProduct)
			.def("isNaN", (bool (Vector4::*)())&Vector4::isNaN)
			.def(self == other<const Ogre::Vector4 &>())
			.def(self + other<const Ogre::Vector4 &>())
			.def(self - other<const Ogre::Vector4 &>())
			.def(self * other<const Real>())
			.def(self * other<const Ogre::Vector4 &>())
			.def(self / other<const Real>())
			.def(self / other<const Ogre::Vector4 &>())
		];
	//<<----include/OgreVector4.h
	//---->>include/OgreMatrix3.h 
	module(L)
		[
			//--Matrix3
			class_<Matrix3>("Matrix3")
			.def(constructor<>())
			.def(constructor<const Real (*)[3]>())
			.def(constructor<const Ogre::Matrix3 &>())
			.def(constructor<Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real>())
			.def("swap", (void (Matrix3::*)(Ogre::Matrix3 &))&Matrix3::swap)
			.def("GetColumn", (Vector3 (Matrix3::*)(size_t))&Matrix3::GetColumn)
			.def("SetColumn", (void (Matrix3::*)(size_t,  const Ogre::Vector3 &))&Matrix3::SetColumn)
			.def("FromAxes", (void (Matrix3::*)(const Ogre::Vector3 &,  const Ogre::Vector3 &,  const Ogre::Vector3 &))&Matrix3::FromAxes)
			.def("Transpose", (Matrix3 (Matrix3::*)())&Matrix3::Transpose)
			//.def("Inverse", (bool (Matrix3::*)(Ogre::Matrix3 &,  Real))&Matrix3::Inverse)
			//.def("Inverse", (Matrix3 (Matrix3::*)(Real))&Matrix3::Inverse)
			.def("Determinant", (Real (Matrix3::*)())&Matrix3::Determinant)
			.def("SingularValueDecomposition", (void (Matrix3::*)(Ogre::Matrix3 &,  Ogre::Vector3 &,  Ogre::Matrix3 &))&Matrix3::SingularValueDecomposition)
			.def("SingularValueComposition", (void (Matrix3::*)(const Ogre::Matrix3 &,  const Ogre::Vector3 &,  const Ogre::Matrix3 &))&Matrix3::SingularValueComposition)
			.def("Orthonormalize", (void (Matrix3::*)())&Matrix3::Orthonormalize)
			.def("QDUDecomposition", (void (Matrix3::*)(Ogre::Matrix3 &,  Ogre::Vector3 &,  Ogre::Vector3 &))&Matrix3::QDUDecomposition)
			.def("SpectralNorm", (Real (Matrix3::*)())&Matrix3::SpectralNorm)
			//.def("ToAngleAxis", (void (Matrix3::*)(Ogre::Vector3 &,  Ogre::Radian &))&Matrix3::ToAngleAxis)
			//.def("ToAngleAxis", (void (Matrix3::*)(Ogre::Vector3 &,  Ogre::Degree &))&Matrix3::ToAngleAxis)
			//高版本才支持.def("FromAngleAxis", (void (Matrix3::*)(const Ogre::Vector3 &,  const Ogre::Radian &))&Matrix3::FromAngleAxis)
			.def("ToEulerAnglesXYZ", (bool (Matrix3::*)(Ogre::Radian &,  Ogre::Radian &,  Ogre::Radian &))&Matrix3::ToEulerAnglesXYZ)
			.def("ToEulerAnglesXZY", (bool (Matrix3::*)(Ogre::Radian &,  Ogre::Radian &,  Ogre::Radian &))&Matrix3::ToEulerAnglesXZY)
			.def("ToEulerAnglesYXZ", (bool (Matrix3::*)(Ogre::Radian &,  Ogre::Radian &,  Ogre::Radian &))&Matrix3::ToEulerAnglesYXZ)
			.def("ToEulerAnglesYZX", (bool (Matrix3::*)(Ogre::Radian &,  Ogre::Radian &,  Ogre::Radian &))&Matrix3::ToEulerAnglesYZX)
			.def("ToEulerAnglesZXY", (bool (Matrix3::*)(Ogre::Radian &,  Ogre::Radian &,  Ogre::Radian &))&Matrix3::ToEulerAnglesZXY)
			.def("ToEulerAnglesZYX", (bool (Matrix3::*)(Ogre::Radian &,  Ogre::Radian &,  Ogre::Radian &))&Matrix3::ToEulerAnglesZYX)
			.def("FromEulerAnglesXYZ", (void (Matrix3::*)(const Ogre::Radian &,  const Ogre::Radian &,  const Ogre::Radian &))&Matrix3::FromEulerAnglesXYZ)
			.def("FromEulerAnglesXZY", (void (Matrix3::*)(const Ogre::Radian &,  const Ogre::Radian &,  const Ogre::Radian &))&Matrix3::FromEulerAnglesXZY)
			.def("FromEulerAnglesYXZ", (void (Matrix3::*)(const Ogre::Radian &,  const Ogre::Radian &,  const Ogre::Radian &))&Matrix3::FromEulerAnglesYXZ)
			.def("FromEulerAnglesYZX", (void (Matrix3::*)(const Ogre::Radian &,  const Ogre::Radian &,  const Ogre::Radian &))&Matrix3::FromEulerAnglesYZX)
			.def("FromEulerAnglesZXY", (void (Matrix3::*)(const Ogre::Radian &,  const Ogre::Radian &,  const Ogre::Radian &))&Matrix3::FromEulerAnglesZXY)
			.def("FromEulerAnglesZYX", (void (Matrix3::*)(const Ogre::Radian &,  const Ogre::Radian &,  const Ogre::Radian &))&Matrix3::FromEulerAnglesZYX)
			.def("EigenSolveSymmetric", (void (Matrix3::*)(Real *,  Ogre::Vector3 *))&Matrix3::EigenSolveSymmetric)
			.def("hasScale", (bool (Matrix3::*)())&Matrix3::hasScale)
			//.def("Tridiagonal", (void (Matrix3::*)(Real *,  Real *))&Matrix3::Tridiagonal)
			//.def("QLAlgorithm", (bool (Matrix3::*)(Real *,  Real *))&Matrix3::QLAlgorithm)
			.def(self == other<const Ogre::Matrix3 &>())
			.def(self + other<const Ogre::Matrix3 &>())
			.def(self - other<const Ogre::Matrix3 &>())
			.def(self * other<const Ogre::Matrix3 &>())
			.def(self * other<const Ogre::Vector3 &>())
			.def(self * other<Real>())
		];
	//<<----include/OgreMatrix3.h
	//---->>include/OgreMatrix4.h 
	module(L)
		[
			//--Matrix4
			class_<Matrix4>("Matrix4")
			.def(constructor<>())
			//.def(constructor<Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real,  Real>())
			.def(constructor<const Ogre::Matrix3 &>())
			.def(constructor<const Ogre::Quaternion &>())
			.def("swap", (void (Matrix4::*)(Ogre::Matrix4 &))&Matrix4::swap)
			.def("concatenate", (Matrix4 (Matrix4::*)(const Ogre::Matrix4 &))&Matrix4::concatenate)
			.def("transpose", (Matrix4 (Matrix4::*)())&Matrix4::transpose)
			.def("setTrans", (void (Matrix4::*)(const Ogre::Vector3 &))&Matrix4::setTrans)
			// .def("getTrans", (Vector3 (Matrix4::*)())&Matrix4::getTrans)
			.def("makeTrans", (void (Matrix4::*)(const Ogre::Vector3 &))&Matrix4::makeTrans)
			.def("makeTrans", (void (Matrix4::*)(Real,  Real,  Real))&Matrix4::makeTrans)
			.def("setScale", (void (Matrix4::*)(const Ogre::Vector3 &))&Matrix4::setScale)
			.def("extract3x3Matrix", (void (Matrix4::*)(Ogre::Matrix3 &))&Matrix4::extract3x3Matrix)
			.def("hasScale", (bool (Matrix4::*)())&Matrix4::hasScale)
			.def("hasNegativeScale", (bool (Matrix4::*)())&Matrix4::hasNegativeScale)
			.def("extractQuaternion", (Quaternion (Matrix4::*)())&Matrix4::extractQuaternion)
			.def("adjoint", (Matrix4 (Matrix4::*)())&Matrix4::adjoint)
			.def("determinant", (Real (Matrix4::*)())&Matrix4::determinant)
			.def("inverse", (Matrix4 (Matrix4::*)())&Matrix4::inverse)
			.def("makeTransform", (void (Matrix4::*)(const Ogre::Vector3 &,  const Ogre::Vector3 &,  const Ogre::Quaternion &))&Matrix4::makeTransform)
			.def("makeInverseTransform", (void (Matrix4::*)(const Ogre::Vector3 &,  const Ogre::Vector3 &,  const Ogre::Quaternion &))&Matrix4::makeInverseTransform)
			.def("decomposition", (void (Matrix4::*)(Ogre::Vector3 &,  Ogre::Vector3 &,  Ogre::Quaternion &))&Matrix4::decomposition)
			.def("isAffine", (bool (Matrix4::*)())&Matrix4::isAffine)
			.def("inverseAffine", (Matrix4 (Matrix4::*)())&Matrix4::inverseAffine)
			.def("concatenateAffine", (Matrix4 (Matrix4::*)(const Ogre::Matrix4 &))&Matrix4::concatenateAffine)
			//.def("transformAffine", (Vector3 (Matrix4::*)(const Ogre::Vector3 &))&Matrix4::transformAffine)
			//.def("transformAffine", (Vector4 (Matrix4::*)(const Ogre::Vector4 &))&Matrix4::transformAffine)
			.def(self * other<const Ogre::Matrix4 &>())
			.def(self * other<const Ogre::Vector3 &>())
			.def(self * other<const Ogre::Vector4 &>())
			.def(self * other<const Ogre::Plane &>())
			.def(self + other<const Ogre::Matrix4 &>())
			.def(self - other<const Ogre::Matrix4 &>())
			.def(self == other<const Ogre::Matrix4 &>())
			.def(self * other<Real>())
		];
	//<<----include/OgreMatrix4.h
	//---->>include/OgreQuaternion.h 
	module(L)
		[
			//--Quaternion
			class_<Quaternion>("Quaternion")
			.def(constructor<>())
			.def(constructor<Real,  Real,  Real,  Real>())
			.def(constructor<const Ogre::Matrix3 &>())
			.def(constructor<const Ogre::Radian &,  const Ogre::Vector3 &>())
			.def(constructor<const Ogre::Vector3 &,  const Ogre::Vector3 &,  const Ogre::Vector3 &>())
			.def(constructor<const Ogre::Vector3 *>())
			.def(constructor<Real *>())
			.def("swap", (void (Quaternion::*)(Ogre::Quaternion &))&Quaternion::swap)
			.def("ptr", (Real* (Quaternion::*)())&Quaternion::ptr)
			//.def("ptr", (const Real* (Quaternion::*)())&Quaternion::ptr)
			.def("FromRotationMatrix", (void (Quaternion::*)(const Ogre::Matrix3 &))&Quaternion::FromRotationMatrix)
			.def("ToRotationMatrix", (void (Quaternion::*)(Ogre::Matrix3 &))&Quaternion::ToRotationMatrix)
			.def("FromAngleAxis", (void (Quaternion::*)(const Ogre::Radian &,  const Ogre::Vector3 &))&Quaternion::FromAngleAxis)
			//.def("ToAngleAxis", (void (Quaternion::*)(Ogre::Radian &,  Ogre::Vector3 &))&Quaternion::ToAngleAxis)
			//.def("ToAngleAxis", (void (Quaternion::*)(Ogre::Degree &,  Ogre::Vector3 &))&Quaternion::ToAngleAxis)
			.def("FromAxes", (void (Quaternion::*)(const Ogre::Vector3 *))&Quaternion::FromAxes)
			.def("FromAxes", (void (Quaternion::*)(const Ogre::Vector3 &,  const Ogre::Vector3 &,  const Ogre::Vector3 &))&Quaternion::FromAxes)
			//.def("ToAxes", (void (Quaternion::*)(Ogre::Vector3 *))&Quaternion::ToAxes)
			//.def("ToAxes", (void (Quaternion::*)(Ogre::Vector3 &,  Ogre::Vector3 &,  Ogre::Vector3 &))&Quaternion::ToAxes)
			.def("xAxis", (Vector3 (Quaternion::*)())&Quaternion::xAxis)
			.def("yAxis", (Vector3 (Quaternion::*)())&Quaternion::yAxis)
			.def("zAxis", (Vector3 (Quaternion::*)())&Quaternion::zAxis)
			.def("Dot", (Real (Quaternion::*)(const Ogre::Quaternion &))&Quaternion::Dot)
			.def("Norm", (Real (Quaternion::*)())&Quaternion::Norm)
			.def("normalise", (Real (Quaternion::*)())&Quaternion::normalise)
			.def("Inverse", (Quaternion (Quaternion::*)())&Quaternion::Inverse)
			.def("UnitInverse", (Quaternion (Quaternion::*)())&Quaternion::UnitInverse)
			.def("Exp", (Quaternion (Quaternion::*)())&Quaternion::Exp)
			.def("Log", (Quaternion (Quaternion::*)())&Quaternion::Log)
			.def("getRoll", (Radian (Quaternion::*)(bool))&Quaternion::getRoll)
			.def("getPitch", (Radian (Quaternion::*)(bool))&Quaternion::getPitch)
			.def("getYaw", (Radian (Quaternion::*)(bool))&Quaternion::getYaw)
			.def("equals", (bool (Quaternion::*)(const Ogre::Quaternion &,  const Ogre::Radian &))&Quaternion::equals)
			.def("isNaN", (bool (Quaternion::*)())&Quaternion::isNaN)
			.def(self + other<const Ogre::Quaternion &>())
			.def(self - other<const Ogre::Quaternion &>())
			.def(self * other<const Ogre::Quaternion &>())
			.def(self * other<Real>())
			.def(self == other<const Ogre::Quaternion &>())
			.def(self * other<const Ogre::Vector3 &>())
		];
	//<<----include/OgreQuaternion.h
}
