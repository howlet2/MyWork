#pragma once
#include <cmath>
#include "Vector3.h"

namespace Math
{

class CQuaternion
{
public:

	union 
	{
		struct
		{
			float _w, _x, _y, _z;
		};
		float q[4];
	};
	
	CQuaternion();
	CQuaternion(float w, float x, float y, float z);
	CQuaternion(float w, const CVector3& vec);
	CQuaternion(const CQuaternion& rhs);
	~CQuaternion(void);

	CQuaternion& operator=(const CQuaternion& rhs);

	CQuaternion  operator-(void);					//Inverse
	CQuaternion  operator-(const CQuaternion& rhs);	//Sub
	CQuaternion  operator*(const CQuaternion& rhs);	//Multiply
	
	CQuaternion& operator*=(const CQuaternion& rhs);
	CQuaternion& operator-=(const CQuaternion& rhs);

	bool		 isZore(void)const;

	float		 module(void);
	void		 normalize(void);
	void		 identity(void);
	void		 inverse(void);
	void         opposite(void);
	float		 getRotateAngle(void)const;
	CVector3     getRotationAxis(void)const;

	void		 yaw(float angle);
	void		 pitch(float angle);
	void         roll(float angle);
	void		 rotate(const CVector3& n, float angle);
	void		 rotateYawPitchRoll(float yaw, float pitch, float roll);

	static  void  multiply(MATH_OUT CQuaternion* pRes, const CQuaternion* pLhs, const CQuaternion* pRhs);
	static  float dot(const CQuaternion* pLhs, const CQuaternion* pRhs);
	static  void  inverse(MATH_OUT CQuaternion* pRes, const CQuaternion* pLhs);
	static  void  sub(MATH_OUT CQuaternion* pRes, const CQuaternion* pLhs, const CQuaternion* pRhs);
	static  void  pow(MATH_OUT CQuaternion* pRes, const CQuaternion* pLhs, float pow);
	static  void  slerp(MATH_OUT CQuaternion* pRes, const CQuaternion* pLhs, const CQuaternion* pRhs, float t);
	
};

}