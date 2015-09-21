#include "D3D9GpuProgramManager.h"
#include "D3D9HLSLProgram.h"

namespace DreamEngineD3D
{

CD3D9GpuProgramManager::CD3D9GpuProgramManager(CD3D9Device* pD3D9Device):
m_pD3D9Device(pD3D9Device)
{
}


CD3D9GpuProgramManager::~CD3D9GpuProgramManager(void)
{
}

CGpuProgram* CD3D9GpuProgramManager::_newProgram()
{
	if (m_pD3D9Device==MATH_NULL)return MATH_NULL;
	
	return new CD3D9HLSLProgram(m_pD3D9Device);
}

}

