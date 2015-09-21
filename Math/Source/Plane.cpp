#include "Plane.h"

namespace Math
{
CPlane::CPlane()
{
	_d = 0.0f;
	_normal.zero();
}

CPlane::CPlane(const CVector3& normal, const CVector3& rkPoint)
{
	_normal = normal;
	_normal.normalize();
	_d = CVector3::dot(&_normal, &rkPoint);
}

CPlane::CPlane(float xa, float xb, float xc, float d)
{
	_normal._x=xa; _normal._y=xb; _normal._z=xc;
	_normal.normalize();
	_d = d;
}

CPlane::CPlane(const CVector3& rkPoint0, const CVector3& rkPoint1, const CVector3& rkPoint2)
{
	CVector3 vec1 = rkPoint0-rkPoint1;
	CVector3 vec2 = rkPoint0-rkPoint2;
	CVector3::cross(&_normal, &vec1, &vec2);
	_normal.normalize();

	_d = CVector3::dot(&_normal, &rkPoint0);
}


CPlane::Side CPlane::getSide(const CVector3& pt)const
{
	float d = distance(pt);
	if (d>0.0f)
	{
		return POSITIVE_SIDE;
	}
	else if (d<0.0f)
	{
		return NEGATIVE_SIDE;
	}
	else
	{
		return NO_SIDE;
	}
}

float CPlane::distance(const CVector3& pt)const
{
	return (CVector3::dot(&pt, &_normal)-_d);
}
}