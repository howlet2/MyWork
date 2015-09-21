#pragma once
#include "MathDefine.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace Math
{

class CMatrix16
{
public:
	CMatrix16(void);
	CMatrix16(const CMatrix16& rhs);
	~CMatrix16(void);

	union 
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};

	CMatrix16&	operator=(const CMatrix16& rhs);
	CMatrix16&  operator*=(const CMatrix16& rhs);
	CMatrix16	operator*(const CMatrix16& rhs)const;
	CMatrix16&  operator+=(const CMatrix16& rhs);
	CMatrix16&  operator-=(const CMatrix16& rhs);
	
	void			zero(void);
	void			identity(void);
	float			cofactor(m_uint8 r0, m_uint8 r1, m_uint8 r2, 
							 m_uint8 c0, m_uint8 c1, m_uint8 c2)const;
	float			determinant(void)const;
	bool			inverse(void);

	static void		identity(MATH_OUT CMatrix16* pRes, const CMatrix16* pLhs);

	static float	cofactor(const CMatrix16* pLhs,  
							 m_uint8 r0, m_uint8 r1, m_uint8 r2, 
							 m_uint8 c0, m_uint8 c1, m_uint8 c2);
	static float    determinant(const CMatrix16* pLhs);
	static bool		inverse(MATH_OUT CMatrix16* pRes, const CMatrix16* pLhs);

	static void		multiply(MATH_OUT CMatrix16* pRes, const CMatrix16* pLhs, const CMatrix16* pRhs);
	static void		add(MATH_OUT CMatrix16* pRes, const CMatrix16* pLhs, const CMatrix16* pRhs);
	static void		sub(MATH_OUT CMatrix16* pRes, const CMatrix16* pLhs, const CMatrix16* pRhs);

	static void		translate(MATH_OUT CMatrix16* pRes, float x, float y, float z);
	static void		transformCoord(MATH_OUT CVector3 *pRes, const CVector3 *pV, const CMatrix16 *pM);
	static void		makeTranslate(MATH_OUT CMatrix16* pRes,
							  const CVector3& position,
							  const CVector3& sacle,
							  const CQuaternion& rotate);

	static void		scale(MATH_OUT CMatrix16* pRes, float x, float y, float z);
	static void		getTransition(MATH_OUT CVector3* pRes, const CMatrix16* pLhs);

	static void		rotateX(MATH_OUT CMatrix16* pRes, float angle);
	static void		rotateY(MATH_OUT CMatrix16* pRes, float angle);
	static void		rotateZ(MATH_OUT CMatrix16* pRes, float angle);
	static void		rotationAxis(MATH_OUT CMatrix16* pRes, CVector3* pVec, float angle);
	static void		rotationYawPicthRoll(MATH_OUT CMatrix16* pRes,
										 float yaw, float pitch, float roll);

	static void		matrixLookAtLH(MATH_OUT CMatrix16* pRes, \
								   const CVector3* pEye, 
								   const CVector3* pAt, 
								   const CVector3* pUp);

	static void matrixPerspectiveFovLH(MATH_OUT CMatrix16* pRes,\
		float fovy, float Aspect, float zn, float zf);
	static void matrixViewport(MATH_OUT CMatrix16* pRes, \
		m_dwrd xStrat, m_dwrd yStrat, m_dwrd width, m_dwrd height, m_dwrd zMin, m_dwrd zMax);
	
	static  void  quaternionTo(MATH_OUT CMatrix16* pRes, const CQuaternion* pLhs);
	static  void  toQuaternion(MATH_OUT CQuaternion* pRes, const CMatrix16* pLhs);

	
};

}

