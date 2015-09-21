#include "AABB.h"
#include <algorithm>

namespace Math
{


CAABB::CAABB(void)
{
	Empty();
}

CAABB::CAABB(const CVector3& min, const CVector3& max):
_min(min), _max(max)
{

}

CAABB::~CAABB(void)
{
}

void CAABB::Empty()
{
	_min._x = _min._y = _min._z	= MATH_FMAX;
	_max._x = _max._y = _max._z = MATH_FMIN;
}

bool CAABB::IsEmpty()const
{
	return (_min._x>=_max._x || _min._y>=_max._y || _min._z>=_max._z);
}

// Bit 0 selects min.x vs. max.x
// Bit 1 selects min.y vs. max.y
// Bit 2 selects min.z vs. max.z
CVector3 CAABB::Corner(int idx)
{
	if (idx>=0 && idx<=7)	
	{
		return CVector3(
						(idx & 1) ?	_max._x	: _min._x,
						(idx & 2) ? _max._y	: _min._y,
						(idx & 4) ? _max._z	: _min._z
						);
		/*CBit8Flag idxData(idx);
		idxData.TestBit(1) ? vec._x=_min._x:vec._x=_max._x;
		idxData.TestBit(2) ? vec._y=_min._y:vec._y=_max._y;
		idxData.TestBit(3) ? vec._z=_min._z:vec._z=_max._z;*/
	}
	else
	{
		return CVector3(MATH_FMIN, MATH_FMIN, MATH_FMIN);
	}

}

void CAABB::AddPoint(const CVector3& point)
{
	if (_min._x > point._x)		_min._x=point._x;
	if (_min._y > point._y)		_min._y=point._y;
	if (_min._z > point._z)		_min._z=point._z;

	if (_max._x < point._x)		_max._x=point._x;
	if (_max._y < point._y)		_max._y=point._y;
	if (_max._z < point._z)		_max._z=point._z;
}

void CAABB::Translation(MATH_OUT CAABB* pRes, const CAABB* pLhs, const CMatrix16* pRhs)
{
	if (pRes==MATH_NULL_PTR || pLhs==MATH_NULL_PTR || pRhs==MATH_NULL_PTR) return;

	CVector3 vecTrans;
	CMatrix16::GetTransition(&vecTrans, pRhs);

	CAABB box(vecTrans, vecTrans);
	
	//calculate X
	if (pRhs->_11>0.0f)
	{
		box._min._x += pLhs->_min._x*pRhs->_11; 
		box._max._x += pLhs->_max._x*pRhs->_11;
	}
	else
	{
		box._min._x += pLhs->_max._x*pRhs->_11;
		box._max._x += pLhs->_min._x*pRhs->_11;
	}

	if (pRhs->_21>0.0f)
	{
		box._min._x += pLhs->_min._y*pRhs->_21; 
		box._max._x += pLhs->_max._y*pRhs->_21;
	}
	else
	{
		box._min._x += pLhs->_max._y*pRhs->_21; 
		box._max._x += pLhs->_min._y*pRhs->_21;
	}

	if (pRhs->_31>0.0f)
	{
		box._min._x += pLhs->_min._z*pRhs->_31; 
		box._max._x += pLhs->_max._z*pRhs->_31;
	}
	else
	{
		box._min._x += pLhs->_max._z*pRhs->_31; 
		box._max._x += pLhs->_min._z*pRhs->_31;
	}

	//calculate Y
	if (pRhs->_12>0.0f)
	{
		box._min._y += pLhs->_min._x*pRhs->_12; 
		box._max._y += pLhs->_max._x*pRhs->_12;
	}
	else
	{
		box._min._y += pLhs->_max._x*pRhs->_12;
		box._max._y += pLhs->_min._x*pRhs->_12;
	}

	if (pRhs->_22>0.0f)
	{
		box._min._y += pLhs->_min._y*pRhs->_22; 
		box._max._y += pLhs->_max._y*pRhs->_22;
	}
	else
	{
		box._min._y += pLhs->_max._y*pRhs->_22; 
		box._max._y += pLhs->_min._y*pRhs->_22;
	}

	if (pRhs->_32>0.0f)
	{
		box._min._y += pLhs->_min._z*pRhs->_32; 
		box._max._y += pLhs->_max._z*pRhs->_32;
	}
	else
	{
		box._min._y += pLhs->_max._z*pRhs->_32; 
		box._max._y += pLhs->_min._z*pRhs->_32;
	}

	//calculate Z
	if (pRhs->_13>0.0f)
	{
		box._min._z += pLhs->_min._x*pRhs->_13; 
		box._max._z += pLhs->_max._x*pRhs->_13;
	}
	else
	{
		box._min._z += pLhs->_max._x*pRhs->_13;
		box._max._z += pLhs->_min._x*pRhs->_13;
	}

	if (pRhs->_23>0.0f)
	{
		box._min._z += pLhs->_min._y*pRhs->_23; 
		box._max._z += pLhs->_max._y*pRhs->_23;
	}
	else
	{
		box._min._z += pLhs->_max._y*pRhs->_23; 
		box._max._z += pLhs->_min._y*pRhs->_23;
	}

	if (pRhs->_33>0.0f)
	{
		box._min._z += pLhs->_min._z*pRhs->_33; 
		box._max._z += pLhs->_max._z*pRhs->_33;
	}
	else
	{
		box._min._z += pLhs->_max._z*pRhs->_33; 
		box._max._z += pLhs->_min._z*pRhs->_33;
	}

	*pRes = box;
}

bool CAABB::Intersect(MATH_OUT CAABB* pInterscet, const CAABB* pLhs, const CAABB* pRhs)
{
	if (pInterscet==MATH_NULL_PTR || pLhs==MATH_NULL_PTR || pRhs==MATH_NULL_PTR)
		return false;

	pInterscet->Empty();

	if (pLhs->_min._x > pRhs->_max._x) return false;
	if (pLhs->_max._x < pRhs->_min._x) return false;
	if (pLhs->_min._y > pRhs->_max._y) return false;
	if (pLhs->_max._y < pRhs->_min._y) return false;
	if (pLhs->_min._z > pRhs->_max._z) return false;
	if (pLhs->_max._z < pRhs->_min._z) return false;

	pInterscet->_min._x = std::max(pLhs->_min._x, pRhs->_min._x);
	pInterscet->_min._y = std::max(pLhs->_min._y, pRhs->_min._y);
	pInterscet->_min._z = std::max(pLhs->_min._z, pRhs->_min._z);

	pInterscet->_max._x = std::min(pLhs->_max._x, pRhs->_max._x);
	pInterscet->_max._y = std::min(pLhs->_max._y, pRhs->_max._y);
	pInterscet->_max._z = std::min(pLhs->_max._z, pRhs->_max._z);

	return true;

 }

}
