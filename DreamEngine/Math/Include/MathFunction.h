#pragma once
#include <cmath>
#include "MathDefine.h"

namespace Math
{
class CMathFunction
{
public:
	CMathFunction(void);
	~CMathFunction(void);

	static float safeAcos(float x);
	static void  limit(MATH_OUT float& vaule, float min, float max);
	static bool  isZore(float vaule);
};
}


