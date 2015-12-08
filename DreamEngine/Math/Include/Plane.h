#pragma once

#include "Vector3.h"

namespace Math
{

class CPlane
{
public:

enum Side
{	
	NO_SIDE,
	POSITIVE_SIDE,
	NEGATIVE_SIDE,
	BOTH_SIDE
};

public:

	float	 _d;
	CVector3 _normal;

public:

	CPlane (void);
	CPlane (const CVector3& normal, float p);
	
	CPlane (float xa, float xb, float xc, float d);
	CPlane (const CVector3& normal, const CVector3& rkPoint);
	CPlane (const CVector3& rkPoint0, const CVector3& rkPoint1,
		const CVector3& rkPoint2);

	Side  getSide(const CVector3& pt)const;
	float distance(const CVector3& pt)const;
};

}
