#pragma once
#include "Vector3.h"
#include "Plane.h"
//////////////////////////////////////////////////////////////////////////this class not test yet

namespace Math
{

class CRay
{
public:

	CVector3	_p;
	CVector3	_d;
	float		_t;

public:

	CRay(void);
	CRay(const CVector3& p, const CVector3& n, float t);
	~CRay(void);



	//intersect with ray
	static	bool	Intersect(MATH_OUT float* pt1, MATH_OUT float* pt2,
							  const CRay* pLhs, const CRay* pRhs,
							  float error=0.0f);

	//intersect with plane
	static  bool	Intersect(MATH_OUT CVector3* pRes, const CRay* pLhs, const CPlane* pRhs);
};

}
