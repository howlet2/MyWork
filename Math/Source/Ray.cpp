#include "Ray.h"

namespace Math
{

CRay::CRay(void):
_p(0.0f, 0.0f, 0.0f),
_d(0.0f, 0.0f, 0.0f),
_t(0.0f)
{
}

CRay::CRay(const CVector3& p, const CVector3& n, float t)
{
	_p = p;
	_t = t;
	CVector3::Normalize(&_d, &n);
}

CRay::~CRay(void)
{
}

bool CRay::Intersect(MATH_OUT float* pt1, MATH_OUT float* pt2, 
					 const CRay* pLhs, const CRay* pRhs,
					 float error/*=0.0f*/)
{
	if (pt1==MATH_NULL_PTR || pt2==MATH_NULL_PTR 
		|| pLhs==MATH_NULL_PTR || pRhs==MATH_NULL_PTR)
			return false;
	
	CVector3 d		= pRhs->_d*pLhs->_d;			if (d.IsZero())return false;
	CVector3 p		= (pRhs->_p-pLhs->_p);
	CVector3 pdv1	= p*pRhs->_d;
	CVector3 pdv2	= p*pLhs->_d;
	float  nLength	= d.Length();

	*pt1			= CVector3::Dot(&pdv1, &d)/nLength*nLength;
	*pt2			= CVector3::Dot(&pdv2, &d)/nLength*nLength;
	
	//if not in the same plane distance must be less than error
	CVector3 ip1		= pLhs->_p+pLhs->_d*(*pt1);
	CVector3 ip2		= pRhs->_p+pRhs->_d*(*pt2);
	
	return ((ip1-ip2).Length()<error);
}

bool CRay::Intersect(MATH_OUT CVector3* pRes, const CRay* pLhs, const CPlane* pRhs)
{
	if (pRes==MATH_NULL_PTR || pLhs==MATH_NULL_PTR)			return false;

	float dn  = CVector3::Dot(&pLhs->_d, &pRhs->_normal);	if (dn==MATH_FZORE) return false;
	float pn  = CVector3::Dot(&pLhs->_p, &pRhs->_normal);
	
	float t   = (pRhs->_d-pn)/dn;

	*pRes = (pLhs->_p + pLhs->_d*t);

	return true;
}

}