#include "MathFunction.h"

namespace Math
{
CMathFunction::CMathFunction(void)
{
}


CMathFunction::~CMathFunction(void)
{
}

float CMathFunction::safeAcos(float x)
{
	// Check limit conditions

	if (x <= -1.0f) {
		return MATH_PI;
	}
	if (x >= 1.0f) {
		return 0.0f;
	}

	// Value is in the domain - use standard C function

	return acos(x);
}

void CMathFunction::limit(MATH_OUT float& vaule, float min, float max)
{
	if (vaule<min)vaule=min;

	if (vaule>max)vaule=max;
}

bool CMathFunction::isZore(float vaule)
{
	return fabs(vaule)<MATH_FZORE;
}

}

