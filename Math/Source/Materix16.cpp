#include "Materix16.h"
#include <cmath>
#include <memory>

namespace Math
{

CMatrix16::CMatrix16(void)
{
	identity();
}

CMatrix16::CMatrix16(const CMatrix16& rhs)
{
	*this = rhs;
}

CMatrix16::~CMatrix16(void)
{
}

CMatrix16& CMatrix16::operator=(const CMatrix16& rhs)
{
	if (this != &rhs)
		memcpy(m, rhs.m, sizeof(float)*16);

	return *this;
}

CMatrix16& CMatrix16::operator*=(const CMatrix16& rhs)
{
	CMatrix16::multiply(this, this, &rhs);

	return *this;
}

CMatrix16 CMatrix16::operator*(const CMatrix16& rhs)const
{
	CMatrix16 res;
	CMatrix16::multiply(&res, this, &rhs);
	return res;
}

CMatrix16& CMatrix16::operator+=(const CMatrix16& rhs)
{
	CMatrix16::add(this, this, &rhs);

	return *this;
}

CMatrix16& CMatrix16::operator-=(const CMatrix16& rhs)
{
	CMatrix16::sub(this, this, &rhs);

	return *this;
}

void CMatrix16::zero()
{
	for (int i=0; i<4; ++i)
		for (int j=0; j<4; ++j)
			m[i][j]	= 0.0f;
}

void CMatrix16::identity()
{
	CMatrix16::identity(this, this);
}

float CMatrix16::cofactor(m_uint8 r0, m_uint8 r1, m_uint8 r2, 
						 m_uint8 c0, m_uint8 c1, m_uint8 c2)const
{
	return CMatrix16::cofactor(this, r0, r1, r2, c0, c1, c2);
}

float CMatrix16::determinant(void)const
{
	return CMatrix16::determinant(this);
}

bool CMatrix16::inverse(void)
{
	return CMatrix16::inverse(this, this);
}

float CMatrix16::cofactor(const CMatrix16* pLhs, 
						 m_uint8 r0, m_uint8 r1, m_uint8 r2,
						 m_uint8 c0, m_uint8 c1, m_uint8 c2)
{
	if (pLhs==MATH_NULL) return 0.0f;

return  pLhs->m[r0][c0]*(pLhs->m[r1][c1]*pLhs->m[r2][c2] - pLhs->m[r2][c1]*pLhs->m[r1][c2]) -
		pLhs->m[r0][c1]*(pLhs->m[r1][c0]*pLhs->m[r2][c2] - pLhs->m[r2][c0]*pLhs->m[r1][c2]) +
		pLhs->m[r0][c2]*(pLhs->m[r1][c0]*pLhs->m[r2][c1] - pLhs->m[r2][c0]*pLhs->m[r1][c1]);

}

float CMatrix16::determinant(const CMatrix16* pLhs)
{
	if (pLhs==MATH_NULL) return 0.0f;

	return	pLhs->m[0][0] * cofactor(pLhs, 1, 2, 3, 1, 2, 3) -
			pLhs->m[0][1] * cofactor(pLhs, 1, 2, 3, 0, 2, 3) +
			pLhs->m[0][2] * cofactor(pLhs, 1, 2, 3, 0, 1, 3) -
			pLhs->m[0][3] * cofactor(pLhs, 1, 2, 3, 0, 1, 2);
}

//copy form ogre
bool  CMatrix16::inverse(MATH_OUT CMatrix16* pRes, const CMatrix16* pLhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL) return false;

	float m00 = pLhs->m[0][0], m01 = pLhs->m[0][1], m02 = pLhs->m[0][2], m03 = pLhs->m[0][3];
	float m10 = pLhs->m[1][0], m11 = pLhs->m[1][1], m12 = pLhs->m[1][2], m13 = pLhs->m[1][3];
	float m20 = pLhs->m[2][0], m21 = pLhs->m[2][1], m22 = pLhs->m[2][2], m23 = pLhs->m[2][3];
	float m30 = pLhs->m[3][0], m31 = pLhs->m[3][1], m32 = pLhs->m[3][2], m33 = pLhs->m[3][3];

	float v0 = m20*m31-m21*m30;
	float v1 = m20*m32-m22*m30;
	float v2 = m20*m33-m23*m30;
	float v3 = m21*m32-m22*m31;
	float v4 = m21*m33-m23*m31;
	float v5 = m22*m33-m23*m32;

	float t00 = +(v5*m11-v4*m12+v3*m13);
	float t10 = -(v5*m10-v2*m12+v1*m13);
	float t20 = +(v4*m10-v2*m11+v0*m13);
	float t30 = -(v3*m10-v1*m11+v0*m12);

	float determinant = (t00*m00+t10*m01+t20*m02+t30*m03);
	if (determinant<MATH_FZORE) return false;
	float invDet = 1/determinant;
	
	float d00 = t00*invDet;
	float d10 = t10*invDet;
	float d20 = t20*invDet;
	float d30 = t30*invDet;

	float d01 = -(v5*m01-v4*m02+v3*m03)*invDet;
	float d11 = +(v5*m00-v2*m02+v1*m03)*invDet;
	float d21 = -(v4*m00-v2*m01+v0*m03)*invDet;
	float d31 = +(v3*m00-v1*m01+v0*m02)*invDet;

	v0 = m10*m31-m11*m30;
	v1 = m10*m32-m12*m30;
	v2 = m10*m33-m13*m30;
	v3 = m11*m32-m12*m31;
	v4 = m11*m33-m13*m31;
	v5 = m12*m33-m13*m32;

	float d02 = +(v5*m01-v4*m02+v3*m03)*invDet;
	float d12 = -(v5*m00-v2*m02+v1*m03)*invDet;
	float d22 = +(v4*m00-v2*m01+v0*m03)*invDet;
	float d32 = -(v3*m00-v1*m01+v0*m02)*invDet;

	v0 = m21*m10-m20*m11;
	v1 = m22*m10-m20*m12;
	v2 = m23*m10-m20*m13;
	v3 = m22*m11-m21*m12;
	v4 = m23*m11-m21*m13;
	v5 = m23*m12-m22*m13;

	float d03 = -(v5*m01-v4*m02+v3*m03)*invDet;
	float d13 = +(v5*m00-v2*m02+v1*m03)*invDet;
	float d23 = -(v4*m00-v2*m01+v0*m03)*invDet;
	float d33 = +(v3*m00-v1*m01+v0*m02)*invDet;

	pRes->m[0][0]=d00; pRes->m[0][1]=d01; pRes->m[0][2]=d02; pRes->m[0][3]=d03;
	pRes->m[1][0]=d10; pRes->m[1][1]=d11; pRes->m[1][2]=d12; pRes->m[1][3]=d13;
	pRes->m[2][0]=d20; pRes->m[2][1]=d21; pRes->m[2][2]=d22; pRes->m[2][3]=d23;
	pRes->m[3][0]=d30; pRes->m[3][1]=d31; pRes->m[3][2]=d32; pRes->m[3][3]=d33;

	return true;
}

void CMatrix16::identity(MATH_OUT CMatrix16* pRes, const CMatrix16* pLhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL) return;

	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			i==j?pRes->m[i][j]=1.0f:pRes->m[i][j]=0.0f;
		}
	}
}

void CMatrix16::multiply(MATH_OUT CMatrix16* pRes, const CMatrix16* pLhs, const CMatrix16* pRhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL || pRhs==MATH_NULL) return;

	pRes->zero();
	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			for (int k=0; k<4; ++k)
			{
				pRes->m[i][j] += pLhs->m[i][k]*pRhs->m[k][j];
			}
		}
	}
}

void CMatrix16::add(MATH_OUT CMatrix16* pRes, const CMatrix16* pLhs, const CMatrix16* pRhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL || pRhs==MATH_NULL) return;

	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			pRes->m[i][j] = pLhs->m[i][j]+pRhs->m[i][j];
		}
	}
}

void CMatrix16::sub(MATH_OUT CMatrix16* pRes, const CMatrix16* pLhs, const CMatrix16* pRhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL || pRhs==MATH_NULL) return;

	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			pRes->m[i][j] = pLhs->m[i][j]-pRhs->m[i][j];
		}
	}
}

void CMatrix16::translate(MATH_OUT CMatrix16* pRes, float x, float y, float z)
{
	if (pRes==MATH_NULL) return;

	CMatrix16::identity(pRes, pRes);

	pRes->_41 = x; pRes->_42 = y; pRes->_43 = z;
}

//Transform (x, y, z, 1) by matrix, project result back into w=1
void CMatrix16::transformCoord(MATH_OUT CVector3 *pRes, const CVector3 *pV, const CMatrix16 *pM)
{
	if (pRes==MATH_NULL || pV==MATH_NULL || pM==MATH_NULL)return;

	float w = 1.0f;
	w = pV->_x*pM->_41+pV->_y*pM->_42+pV->_z*pM->_43+w*pM->_44;

	pRes->_x = (pV->_x*pM->_11+pV->_y*pM->_12+pV->_z*pM->_13+w*pM->_14)/w;
	pRes->_y = (pV->_x*pM->_21+pV->_y*pM->_22+pV->_z*pM->_23+w*pM->_24)/w;
	pRes->_z = (pV->_x*pM->_31+pV->_y*pM->_32+pV->_z*pM->_33+w*pM->_34)/w;
}

void CMatrix16::makeTranslate(MATH_OUT CMatrix16* pRes, 
							  const CVector3& position, 
							  const CVector3& sacle, 
							  const CQuaternion& rotate)
{
	if (pRes==MATH_NULL) return;

	pRes->identity();

	CMatrix16 rotMat;
	CMatrix16::quaternionTo(&rotMat, &rotate);
	pRes->_11=rotMat._11*sacle._x; pRes->_12=rotMat._12*sacle._y; pRes->_13=rotMat._13*sacle._z;
	pRes->_21=rotMat._21*sacle._x; pRes->_22=rotMat._22*sacle._y; pRes->_23=rotMat._23*sacle._z;
	pRes->_31=rotMat._31*sacle._x; pRes->_32=rotMat._32*sacle._y; pRes->_33=rotMat._33*sacle._z;

	pRes->_41=position._x; pRes->_42=position._y; pRes->_43=position._z;
}

void CMatrix16::scale(MATH_OUT CMatrix16* pRes, float x, float y, float z)
{
	if (pRes==MATH_NULL) return;

	CMatrix16::identity(pRes, pRes);

	pRes->_11 = x; pRes->_22 = y; pRes->_33 = z;
}

void CMatrix16::getTransition(MATH_OUT CVector3* pRes, const CMatrix16* pLhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL)return;

	pRes->_x = pLhs->_41;
	pRes->_y = pLhs->_42;
	pRes->_z = pLhs->_43;
}

void CMatrix16::rotateX(MATH_OUT CMatrix16* pRes, float angle)
{
	if (pRes==MATH_NULL) return;

	CMatrix16::identity(pRes, pRes);

	float fsin = std::sin(angle);
	float fcos = std::cos(angle);
	pRes->_22 = fcos; pRes->_23=fsin; pRes->_32=-fsin; pRes->_33=fcos;

}

void CMatrix16::rotateY(MATH_OUT CMatrix16* pRes, float angle)
{
	if (pRes==MATH_NULL) return;

	CMatrix16::identity(pRes, pRes);

	float fsin = std::sin(angle);
	float fcos = std::cos(angle);
	pRes->_11 = fcos; pRes->_13=-fsin; pRes->_31=fsin; pRes->_33=fcos;

}

void CMatrix16::rotateZ(MATH_OUT CMatrix16* pRes, float angle)
{
	if (pRes==MATH_NULL) return;

	CMatrix16::identity(pRes, pRes);

	float fsin = std::sin(angle);
	float fcos = std::cos(angle);
	pRes->_11 = fcos; pRes->_12=fsin; pRes->_21=-fsin; pRes->_22=fcos;
}

void CMatrix16::rotationAxis(MATH_OUT CMatrix16* pRes, CVector3* pVec, float angle)
{
	if (pRes==MATH_NULL || pVec==MATH_NULL)return;

	/*
		nx*nx(1-cos@)+cos@, nx*ny(1-cos@)+nz(sin@), nx*nz(1-cos@)-ny(sin@)
		nx*ny(1-cos@)-nz(sin@), ny*ny(1-cos@)+cos@, ny*nz(1-cos@)+nx(sin@)
		nx*nz(1-cos@)-ny(sin@), ny*nz(1-cos@)-nx(sin@), nz*nz(1-cos@)+cos@
	*/
	pRes->identity();
	pVec->normalize();

	float fsin = std::sin(angle);
	float fcos = std::cos(angle);

	pRes->_11=pVec->_x*pVec->_x*(1-fcos)+fcos; 
	pRes->_12=pVec->_x*pVec->_y*(1-fcos)+pVec->_z*fsin;
	pRes->_13=pVec->_x*pVec->_z*(1-fcos)-pVec->_y*fsin;

	pRes->_21=pVec->_x*pVec->_y*(1-fcos)-pVec->_z*fsin; 
	pRes->_22=pVec->_y*pVec->_y*(1-fcos)+fcos;
	pRes->_23=pVec->_y*pVec->_z*(1-fcos)+pVec->_x*fsin;

	pRes->_31=pVec->_x*pVec->_z*(1-fcos)-pVec->_y*fsin; 
	pRes->_32=pVec->_y*pVec->_z*(1-fcos)-pVec->_x*fsin;
	pRes->_33=pVec->_z*pVec->_z*(1-fcos)+fcos;
}

void CMatrix16::rotationYawPicthRoll(MATH_OUT CMatrix16* pRes,
									float yaw, float pitch, float roll)
{
	if (pRes == MATH_NULL)
		return;

	pRes->identity();

	pRes->_11	=	cos(yaw)*cos(roll)+sin(yaw)*sin(pitch)*sin(roll);
	pRes->_12	=	sin(roll)*cos(pitch);
	pRes->_13	=	-sin(yaw)*cos(roll)+cos(yaw)*sin(pitch)*sin(roll);
	pRes->_21	=	-cos(yaw)*sin(roll)+sin(yaw)*sin(pitch)*cos(roll);
	pRes->_22	=	cos(roll)*cos(pitch);
	pRes->_23	=	sin(roll)*sin(yaw)+cos(yaw)*sin(pitch)*cos(roll);
	pRes->_31	=	sin(yaw)*cos(pitch);
	pRes->_32	=	-sin(pitch);
	pRes->_33	=	cos(yaw)*cos(pitch);
}

void CMatrix16::matrixLookAtLH(MATH_OUT CMatrix16* pRes, \
	const CVector3* pEye, const CVector3* pAt, const CVector3* pUp)
{
	if (pRes==MATH_NULL || pEye==MATH_NULL || pAt==MATH_NULL || pUp==MATH_NULL) return;

	CVector3 direction = *pAt-*pEye;
	CVector3 right;
	CVector3 up = *pUp;

	CVector3::normalize(&direction, &direction);
	CVector3::cross(&right, &up, &direction);
	CVector3::normalize(&right,&right);
	CVector3::cross(&up, &direction, &right);
	CVector3::normalize(&up,&up);


	// Build the view matrix:
	float x = -CVector3::dot(&right,pEye);
	float y = -CVector3::dot(&up, pEye);
	float z = -CVector3::dot(&direction, pEye);

	pRes->_11=right._x; pRes->_12=up._x; pRes->_13=direction._x; pRes->_14=0.0f;
	pRes->_21=right._y; pRes->_22=up._y; pRes->_23=direction._y; pRes->_24=0.0f;
	pRes->_31=right._z; pRes->_32=up._z; pRes->_33=direction._z; pRes->_34=0.0f;
	pRes->_41=x; pRes->_42=y; pRes->_43=z; pRes->_44=1.0f; 

}

void CMatrix16::matrixPerspectiveFovLH(MATH_OUT CMatrix16* pRes,\
	float fovy, float Aspect, float zn, float zf)
{
	if (pRes==MATH_NULL) return;

	pRes->identity();

	float fovVert = fovy;
	float h = 1/tan(fovVert/2);
	float w = h/Aspect;
	float Q = zf/(zf-zn);

	pRes->_11 = w;
	pRes->_22 = h;
	pRes->_33 = Q;
	pRes->_43 = -Q*zn;
	pRes->_34 = 1;
	pRes->_44 = 0;
}

void CMatrix16::matrixViewport(MATH_OUT CMatrix16* pRes, \
	m_dwrd xStrat, m_dwrd yStrat, m_dwrd width, m_dwrd height, m_dwrd zMin, m_dwrd zMax)
{
	if (pRes==MATH_NULL) return;
	
	pRes->identity();
	pRes->_11 = float (width/2);
	pRes->_14 = float (xStrat+width/2);
	pRes->_22 = -float(height/2);
	pRes->_24 = float (yStrat+height/2);
	pRes->_33 = float (zMax-zMin);
	pRes->_34 = float (zMin);

}

void CMatrix16::quaternionTo(MATH_OUT CMatrix16* pRes, const CQuaternion* pLhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL) return;

	pRes->identity();

	pRes->_11  =  1-2*pLhs->_y*pLhs->_y-2*pLhs->_z*pLhs->_z;
	pRes->_12  =  2*pLhs->_x*pLhs->_y+2*pLhs->_w*pLhs->_z;
	pRes->_13  =  2*pLhs->_x*pLhs->_z-2*pLhs->_w*pLhs->_y;
	pRes->_21  =  2*pLhs->_x*pLhs->_y-2*pLhs->_w*pLhs->_z;
	pRes->_22  =  1-2*pLhs->_x*pLhs->_x-2*pLhs->_z*pLhs->_z;
	pRes->_23  =  2*pLhs->_y*pLhs->_z+2*pLhs->_w*pLhs->_x;
	pRes->_31  =  2*pLhs->_x*pLhs->_z+2*pLhs->_w*pLhs->_y;
	pRes->_32  =  2*pLhs->_y*pLhs->_z-2*pLhs->_w*pLhs->_x;
	pRes->_33  =  1-2*pLhs->_x*pLhs->_x-2*pLhs->_y*pLhs->_y; 

}

void CMatrix16::toQuaternion(MATH_OUT CQuaternion* pRes, const CMatrix16* pLhs)
{
	if (pRes==MATH_NULL || pLhs==MATH_NULL) return;

	float vww = (pLhs->_11+pLhs->_22+pLhs->_33);
	float vxx = (pLhs->_11-pLhs->_22-pLhs->_33);
	float vyy = (-pLhs->_11+pLhs->_22-pLhs->_33);
	float vzz = (-pLhs->_11-pLhs->_22+pLhs->_33);

	int   bigIndex = 1; 
	float bigVaule = vww;

	if (vxx>bigVaule) {bigIndex=2; bigVaule=vxx;}
	if (vyy>bigVaule) {bigIndex=3; bigVaule=vyy;}
	if (vzz>bigVaule) {bigIndex=4; bigVaule=vzz;}

	bigVaule   = float(sqrt(bigVaule+1)*0.5);
	float mult = 0.25f/bigVaule;

	switch (bigIndex)
	{
	case 1:
		{
			pRes->_w = bigVaule;
			pRes->_x = (pLhs->_23-pLhs->_32)*mult;
			pRes->_y = (pLhs->_31-pLhs->_13)*mult;
			pRes->_z = (pLhs->_12-pLhs->_21)*mult;
		}break;

	case 2:
		{
			pRes->_x = bigVaule;
			pRes->_w = (pLhs->_23-pLhs->_32)*mult;
			pRes->_y = (pLhs->_12+pLhs->_21)*mult;
			pRes->_z = (pLhs->_31+pLhs->_13)*mult;
		}break;

	case 3:
		{
			pRes->_y = bigVaule;
			pRes->_w = pLhs->_31-pLhs->_13;
			pRes->_x = pLhs->_12+pLhs->_21;
			pRes->_z = pLhs->_23+pLhs->_32;
		}break;

	case 4:
		{
			pRes->_z = bigVaule;
			pRes->_w = pLhs->_12-pLhs->_21;
			pRes->_x = pLhs->_31+pLhs->_13;
			pRes->_y = pLhs->_23+pLhs->_32;
		}break;

	default: break;
	}
}


}
