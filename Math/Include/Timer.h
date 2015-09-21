#pragma once
#include "MathDefine.h"
#include <ctime>

namespace Math
{

class CTimer
{
public:
	CTimer(void);
	~CTimer(void);

	void		reset(void);
	m_dwrd		getMillisecondsCPU();
	m_dwrd		getMicrosecondsCPU();
	m_dwrd		getSecondsCPU();

protected:

	clock_t m_zeroClock;
};

}


