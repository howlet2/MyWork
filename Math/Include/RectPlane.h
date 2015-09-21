#pragma once
#include "Vector3.h"
#include "Plane.h"

namespace Math
{
class CRectPlane
{
public:
	CVector3	_pt1, _pt2, _pt3, _pt4;

public:
	//CRectPlane(const CVector3& max, const CVector3& min, const CPlane& plane);
	CRectPlane(const CVector3& pt1, const CVector3& pt2,\
		const CVector3& pt3, const CVector3& pt4);
	CRectPlane(void);
	~CRectPlane(void);

protected:

	//bool _DefineRect(const CVector3& max, CVector3& min, CPlane& plane) ;
};

}

