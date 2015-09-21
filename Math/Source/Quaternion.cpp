#include "Quaternion.h"
#include "MathFunction.h"
#include <memory>

namespace Math
{
CQuaternion::CQuaternion(void)
{
	identity();
}

CQuaternion::CQuaternion(float w, const CVector3& vec):
_w(w),
_x(vec._x),
_y(vec._y),
_z(vec._z)
{

}

CQuaternion::CQuaternion(float w, float x, float y, float z):
_w(w),_x(x),_y(y),_z(z)
{

}

CQuaternion::CQuaternion(const CQuaternion& rhs)
{
	*this = rhs;
}

CQuaternion::~CQuaternion(void)
{
}

CQuaternion& CQuaternion::operator=(const CQuaternion& rhs)
{
	if (this != &rhs)
	{
		memcpy(q, rhs.q, sizeof(float)*4);
	}
	return *this;
}

CQuaternion CQuaternion::operator-()
{
	return CQuaternion(_w, -_x, -_y, -_z);
}

CQuaternion CQuaternion::operator-(const CQuaternion& rhs)
{
	CQuaternion res;
	CQuaternion::sub(&res, this, &rhs);

	return res;
}

CQuaternion CQuaternion::operator*(const CQuaternion& rhs)
{
	CQuaternion quaternion;
	CQuaternion::multiply(&quaternion, this, &rhs);

	return quaternion;
}

CQuaternion& CQuaternion::operator*=(const CQuaternion& rhs)
{
	CQuaternion::multiply(this, this, &rhs);

	return *this;
}

CQuaternion& CQuaternion::operator-=(const CQuaternion& rhs)
{
	CQuaternion::sub(this, this, &rhs);

	return *this;
}

bool CQuaternion::isZore()const
{
	return (CMathFunction::isZore(_w) && CMathFunction::isZore(_x) 
			&& CMathFunction::isZore(_y) && CMathFunction::isZore(_z));
}

float CQuaternion::module()
{
	return std::sqrt(_w*_w+_x*_x+_y*_y+_z*_z);
}

void CQuaternion::identity()
{
	_w = 1.0f;
	_x = _y = _z = 0.0f;
}

void CQuaternion::normalize()
{
	float md = module();
	if (md > 0.0f)
	{
		_w  /= md;
		_x  /= md;
		_y	/= md;
		_z	/= md;
	}
	else
	{
		identity();
	}
}

void CQuaternion::inverse()
{
	CQuaternion::inverse(this, this);
}

void CQuaternion::opposite()
{
	_w  = -_w;
	_x  = -_x;
	_y	= -_y;
	_z	= -_z;
}

float CQuaternion::getRotateAngle()const
{
	return CMathFunction::safeAcos(_w)*2;
}

CVector3 CQuaternion::getRotationAxis()const
{
	CVector3 axis(_x, _y, _z);
	float sinHalfTha = sqrt(1-_w*_w);

	if (sinHalfTha > 0.0f)
	{
		axis._x = _x/sinHalfTha;
		axis._y = _y/sinHalfTha;
		axis._z = _z/sinHalfTha;
	}
	axis.normalize();

	return axis;
}

void CQuaternion::yaw(float angle)
{
	_w = cos(angle/2);
	_x = 0.0f;
	_y = sin(angle/2);
	_z = 0.0f;

	normalize();
}

void CQuaternion::pitch(float angle)
{
	_w = cos(angle/2);
	_x = sin(angle/2);
	_y = 0.0f;
	_z = 0.0f;

	normalize();
}

void CQuaternion::roll(float angle)
{
	_w = cos(angle/2);
	_x = 0.0f;
	_y = 0.0f;
	_z = sin(angle/2);

	normalize();
}

void CQuaternion::rotate(const CVector3& n, float angle)
{
	CVector3 tempn = n;
	tempn.normalize();

	_w = cos(angle/2);
	_x = tempn._x*sin(angle/2);
	_y = tempn._y*sin(angle/2);
	_z = tempn._z*sin(angle/2);

	normalize();
}

void CQuaternion::rotateYawPitchRoll(float yaw, float pitch, float roll)
{
	_w	=	cos(yaw/2)*cos(pitch/2)*cos(roll/2)+sin(yaw/2)*sin(pitch/2)*sin(roll/2);
	_x	=	cos(yaw/2)*sin(pitch/2)*cos(roll/2)+sin(yaw/2)*cos(pitch/2)*sin(roll/2);
	_y	=	sin(yaw/2)*cos(pitch/2)*cos(roll/2)-cos(yaw/2)*sin(pitch/2)*sin(roll/2);
	_z	=	cos(yaw/2)*cos(pitch/2)*sin(roll/2)-sin(yaw/2)*sin(pitch/2)*cos(roll/2);

	normalize();

}

void CQuaternion::multiply(MATH_OUT CQuaternion* pRes, const CQuaternion* pLhs, const CQuaternion* pRhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL || pRhs==MATH_NULL)	return;

	pRes->_w = (pLhs->_w*pRhs->_w)-(pLhs->_x*pRhs->_x)-(pLhs->_y*pRhs->_y)-(pLhs->_z*pRhs->_z);
	pRes->_x = (pLhs->_w*pRhs->_x)+(pLhs->_x*pRhs->_w)+(pLhs->_z*pRhs->_y)-(pLhs->_y*pRhs->_z);
	pRes->_y = (pLhs->_w*pRhs->_y)+(pLhs->_y*pRhs->_w)+(pLhs->_x*pRhs->_z)-(pLhs->_z*pRhs->_x);
	pRes->_z = (pLhs->_w*pRhs->_z)+(pLhs->_z*pRhs->_w)+(pLhs->_y*pRhs->_x)-(pLhs->_x*pRhs->_y);

	pRes->normalize();

}

float CQuaternion::dot(const CQuaternion* pLhs, const CQuaternion* pRhs)
{
	if (pLhs==MATH_NULL || pRhs==MATH_NULL)return 0.0f;

	return (pLhs->_w*pRhs->_w+pLhs->_x*pRhs->_x+pLhs->_y*pRhs->_y+pLhs->_z*pRhs->_z);
}

void CQuaternion::inverse(MATH_OUT CQuaternion* pRes, const CQuaternion* pLhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL)return;

	pRes->_x=-pLhs->_x; 
	pRes->_y=-pLhs->_y; 
	pRes->_z=-pLhs->_z;
	pRes->_w=pLhs->_w;

	pRes->normalize();
}

void CQuaternion::sub(MATH_OUT CQuaternion* pRes, const CQuaternion* pLhs, const CQuaternion* pRhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL || pRhs==MATH_NULL)return;

	CQuaternion InverLhs;
	CQuaternion::inverse(&InverLhs, pLhs);
	*pRes = InverLhs*(*pRhs);

	pRes->normalize();
}
void CQuaternion::pow(MATH_OUT CQuaternion* pRes, const CQuaternion* pLhs, float pow)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL)return;

	float halfTheta = fabs(CMathFunction::safeAcos(pRes->_w));
	if (halfTheta < 0.99999f)
	{
		float newTheta = pow*halfTheta;
		pRes->_w = cos(newTheta);
		
		float module = sin(newTheta)/sin(halfTheta);

		pRes->_x  = pLhs->_x*module;
		pRes->_y  = pLhs->_y*module;
		pRes->_z  = pLhs->_z*module;
	}
	
	pRes->normalize();
}

void CQuaternion::slerp(MATH_OUT CQuaternion* pRes, const CQuaternion* pLhs, const CQuaternion* pRhs, float t)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL || pRhs==MATH_NULL) return;
	
	if (t <= 0.0f) *pRes=*pLhs;
	if (t >= 1.0f) *pRes=*pRhs;

	float cosOmega = CQuaternion::dot(pLhs, pRhs);
	CQuaternion tempRhs = *pRhs;

	if (cosOmega < MATH_FZORE)
	{
		tempRhs.opposite();
		cosOmega = -cosOmega;
	} 

	float k0, k1;
	//CMathFunction::Limit(t, 0, 1);
	if (cosOmega > 0.9999f)
	{
		k0 = 1-t;
		k1 = t;
	}
	else
	{
		float Omega = CMathFunction::safeAcos(cosOmega);

		k0 = sin((1-t)*Omega)/sin(Omega);
		k1 = sin(t*Omega)/sin(Omega);
	}

	pRes->_w = pLhs->_w*k0+tempRhs._w*k1;
	pRes->_x = pLhs->_x*k0+tempRhs._x*k1;
	pRes->_y = pLhs->_y*k0+tempRhs._y*k1;
	pRes->_z = pLhs->_z*k0+tempRhs._z*k1;

	pRes->normalize();
}


}
