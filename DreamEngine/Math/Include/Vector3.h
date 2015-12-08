#pragma once
#include "MathDefine.h"

namespace Math
{

class CVector3
{
public:

	union 
	{
		struct
		{
			float _x, _y, _z;
		};
		float v[3];
	};

	static const CVector3 ZERO;
	static const CVector3 UNIT_X;
	static const CVector3 UNIT_Y;
	static const CVector3 UNIT_Z;
	static const CVector3 NEGATIVE_UNIT_X;
	static const CVector3 NEGATIVE_UNIT_Y;
	static const CVector3 NEGATIVE_UNIT_Z;

	CVector3(void);
	CVector3(const CVector3& rhs);
	CVector3(float x, float y, float z);
	~CVector3(void);

	CVector3&	operator=(const CVector3& rhs);
	CVector3	operator+(const CVector3& rhs)const;
	CVector3	operator+(float rhs)const;
	CVector3	operator-(const CVector3& rhs)const;
	CVector3	operator-(float)const;
	CVector3	operator*(float rhs)const;
	CVector3	operator*(const CVector3& rhs)const;
	CVector3	operator/(float rhs)const;

	CVector3&	operator/=(float rhs);
	CVector3&	operator+=(const CVector3& rhs);
	CVector3&	operator-=(const CVector3& rhs);

	void			zero(void);
	bool			isZero(void)const;
	float			length(void)const;
	void			normalize(void);

	static  void	normalize(MATH_OUT CVector3* pRes, const CVector3* pLhs);
	static  bool	cross(MATH_OUT CVector3* pRes, const CVector3* pLhs, const CVector3* pRhs);//return is zero
	static  float	dot(const CVector3* pLhs, const CVector3* pRhs);
	static  void	projectVector(MATH_OUT CVector3* pVVec, MATH_OUT CVector3* pHVec, 
								  const CVector3* pLhs, const CVector3* pRhs);
	
};

}


