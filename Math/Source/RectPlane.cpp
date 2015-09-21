#include "RectPlane.h"

namespace Math
{

//CRectPlane::CRectPlane(const CVector3& max, const CVector3& min, const CPlane& plane)
//{
//
//}

CRectPlane::CRectPlane()
{

}

CRectPlane::CRectPlane(const CVector3& pt1, const CVector3& pt2, \
	const CVector3& pt3, const CVector3& pt4):
_pt1(pt1), _pt2(pt2), _pt3(pt3), _pt4(pt4)
{

}



CRectPlane::~CRectPlane(void)
{
}

//bool CRectPlane::_DefineRect(const CVector3& max, CVector3& min, CPlane& plane)
//{
//	if (plane.GetSide(max)!=CPlane::Side::NO_SIDE ||
//		plane.GetSide(min)!=CPlane::Side::NO_SIDE )
//	{
//		return false;
//	}
//
//	
//}

}

