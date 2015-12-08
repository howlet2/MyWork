#include "Vector3.h"
#include <cmath>
#include <memory>

namespace Math
{

const CVector3 CVector3::ZERO(0,0,0);
const CVector3 CVector3::UNIT_X(1,0,0);
const CVector3 CVector3::UNIT_Y(0,1,0);
const CVector3 CVector3::UNIT_Z(0,0,1);
const CVector3 CVector3::NEGATIVE_UNIT_X(-1,0,0);
const CVector3 CVector3::NEGATIVE_UNIT_Y(0,-1,0);
const CVector3 CVector3::NEGATIVE_UNIT_Z(0,0,-1);

CVector3::CVector3(void):
_x(0.0f),
_y(0.0f),
_z(0.0f)
{
}

CVector3::CVector3(float x, float y, float z):
_x(x),
_y(y),
_z(z)
{

}

CVector3::CVector3(const CVector3& rhs)
{
	*this = rhs;
}


CVector3::~CVector3(void)
{
}

CVector3& CVector3::operator=(const CVector3& rhs)
{
	if (this != &rhs)
		memcpy(v, rhs.v, sizeof(float)*3);

	return *this;
}

CVector3 CVector3::operator+(const CVector3& rhs)const
{
	return CVector3(_x+rhs._x, _y+rhs._y, _z+rhs._z);
}

CVector3 CVector3::operator+(float rhs)const
{
	return CVector3(_x+rhs, _y+rhs, _z+rhs);
}

CVector3 CVector3::operator-(const CVector3& rhs)const
{
	return CVector3(_x-rhs._x, _y-rhs._y, _z-rhs._z);
}

CVector3 CVector3::operator-(float rhs)const
{
	return CVector3(_x-rhs, _y-rhs, _z-rhs);
}

CVector3 CVector3::operator*(float rhs)const
{
	return CVector3(_x*rhs, _y*rhs, _z*rhs);
}

CVector3 CVector3::operator*(const CVector3& rhs)const
{
	CVector3 res;
	CVector3::cross(&res, this, &rhs);

	return res;
}

CVector3 CVector3::operator/(float rhs)const
{
	return CVector3(_x/rhs, _y/rhs, _z/rhs);
}

CVector3& CVector3::operator/=(float rhs)
{
	_x/=rhs; _y/=rhs; _z/=rhs;

	return *this;
}

CVector3& CVector3::operator+=(const CVector3& rhs)
{
	_x += rhs._x;
	_y += rhs._y;
	_z += rhs._z;

	return *this;
}
CVector3& CVector3::operator-=(const CVector3& rhs)
{
	_x -= rhs._x;
	_y -= rhs._y;
	_z -= rhs._z;

	return *this;
}

void CVector3::zero(void)
{
	_x = _y = _z = 0.0f;
}

bool CVector3::isZero()const
{
	return (_x==MATH_FZORE && _y==MATH_FZORE && _z==MATH_FZORE);
}

float CVector3::length(void)const
{
	return (std::sqrt(_x*_x+_y*_y+_z*_z));
}

void CVector3::normalize(void)
{
	CVector3::normalize(this, this);
}

void CVector3::normalize(MATH_OUT CVector3* pRes, const CVector3* pLhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL) return;

	float length = pLhs->length();
	if (length > 0.0000001f)
	{
		pRes->_x = pLhs->_x/length;
		pRes->_y = pLhs->_y/length;
		pRes->_z = pLhs->_z/length;
	}
}

bool CVector3::cross(MATH_OUT CVector3* pRes, const CVector3* pLhs, const CVector3* pRhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL || pRhs==MATH_NULL) return false;

	pRes->_x = pLhs->_y*pRhs->_z-pLhs->_z*pRhs->_y;
	pRes->_y = pLhs->_z*pRhs->_x-pLhs->_x*pRhs->_z;
	pRes->_z = pLhs->_x*pRhs->_y-pLhs->_y*pRhs->_x;

	return pRes->isZero();
}

float CVector3::dot(const CVector3* pLhs, const CVector3* pRhs)
{
	if (pLhs==MATH_NULL || pRhs==MATH_NULL) return 0.0f;

	return (pLhs->_x*pRhs->_x+pLhs->_y*pRhs->_y+pLhs->_z*pRhs->_z);
}

void CVector3::projectVector(MATH_OUT CVector3* pVVec, 
							 MATH_OUT CVector3* pHVec, 
							 const CVector3* pLhs, 
							 const CVector3* pRhs)
{
	if (pVVec==MATH_NULL || pVVec==MATH_NULL
	  || pLhs==MATH_NULL || pRhs==MATH_NULL)
			return;

	float dt			 = dot(pLhs, pRhs);
	float leng			 = pRhs->length();

	*pHVec	= *pRhs*dt/(leng*leng);
	*pVVec =  *pLhs-*pHVec;
}

}

