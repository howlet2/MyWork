#pragma once
#include "Vector3.h"

namespace Math
{

class CRect3D
{
public:

	CRect3D();
	CRect3D(const CVector3& vMin, const CVector3& vMax);
	CRect3D(float x1, float y1, float z1, float x2, float y2, float z2);
	~CRect3D();


protected:

	float _x1, _y1, _z1;
	float _x2, _y2, _z2;
};

}