#include "Material.h"

namespace DreamEngine
{

CMaterial::CMaterial(const CString& name):
m_name(name),
m_pGupProgram(MATH_NULL),
m_cullMode(CULLMODE_NONE),
m_fillMode(FILLMODE_SOLID),
m_isZTestEnble(false)
{
}

CMaterial::~CMaterial(void)
{
}

void CMaterial::setGpuProgram(CGpuProgram* pGpuProgram)
{
	m_pGupProgram = pGpuProgram;
}

void CMaterial::setCullMode(CULLMODE mode)
{
	m_cullMode = mode;
}

void CMaterial::setFillMode(FILLMODE mode)
{
	m_fillMode = mode;
}

void CMaterial::setZTestEnble(bool isEnable)
{
	m_isZTestEnble = isEnable;
}

}

