#include "SpineBone.h"

namespace DreamEngine
{

CSpineBone::CSpineBone(const CString& name, CNode* pParent/* =MATH_NULL */):
CNode(name, pParent),
	m_length(0.0f)
{

}

CSpineBone::CSpineBone(void)
{
}


CSpineBone::~CSpineBone(void)
{
}

void CSpineBone::setLength(float length)
{
	m_length = length;
}

}