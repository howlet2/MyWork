#pragma once
#include "MathDefine.h"

namespace Math
{
class CVector2
{
public:

	union 
	{
		struct
		{
			float _x, _y;
		};
		struct
		{
			int _ix, _iy;
		};
		float v[2];
	};

	CVector2(void);
	CVector2(float x, float y);
	CVector2(int x, int y);
	~CVector2(void);

};

}