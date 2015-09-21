#include "Timer.h"

namespace Math
{
CTimer::CTimer(void)
{
	reset();
}


CTimer::~CTimer(void)
{
}

void CTimer::reset(void)
{
	m_zeroClock  = clock();
}

m_dwrd CTimer::getMillisecondsCPU()
{
	m_dwrd nowTime = clock();
	return m_dwrd (float((nowTime-m_zeroClock))*float((MATH_CLOCKS_PER_SEC/1000000.0f)));
}

m_dwrd CTimer::getMicrosecondsCPU()
{
	m_dwrd nowTime = clock();
	return m_dwrd (float((nowTime-m_zeroClock))*float((MATH_CLOCKS_PER_SEC/1000.0f)));
}

m_dwrd CTimer::getSecondsCPU()
{
	m_dwrd nowTime = clock();
	return m_dwrd (float((nowTime-m_zeroClock))*float((MATH_CLOCKS_PER_SEC/1.0f)));
}

}

