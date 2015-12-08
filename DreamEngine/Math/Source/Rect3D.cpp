#include "Rect3D.h"

namespace Math
{

CRect3D::CRect3D()
{
	_x1 = _y1 = _z1 = _x2 = _y2 = _z2 = 0;
}

CRect3D::CRect3D(const CVector3& vMin, const CVector3& vMax)
{
	_x1 = vMin.x; _y1 = vMin.y; _z1 = vMin.z;
	_x2 = vMax.x; _y2 = vMax.y; _z2 = vMax.z;
}

CRect3D::CRect3D(float x1, float y1, float z1, float x2, float y2, float z2):
_x1(x1), _y1(y1), _z1(z1),
_x2(x2), _y2(y2), _z2(z2)
{

}

CRect3D::~CRect3D()
{

}

}