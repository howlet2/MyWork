#include "Vector2.h"

namespace Math
{

CVector2::CVector2(void):
_x(0.0f),
_y(0.0f)
{
}

CVector2::CVector2(float x, float y):
_x(x),
_y(y)
{

}

CVector2::CVector2(int x, int y):
_ix(x),
_iy(y)
{

}

CVector2::~CVector2(void)
{
}

}