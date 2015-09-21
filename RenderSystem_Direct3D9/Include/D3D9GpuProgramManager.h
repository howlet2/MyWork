#pragma once
#include "GpuProgramManager.h"
#include "D3D9HLSLShader.h"
#include "D3D9Device.h"

using namespace DreamEngine;

namespace DreamEngineD3D
{
class _EngineD3D9Export CD3D9GpuProgramManager : public CGpuProgramManager
{
public:
	CD3D9GpuProgramManager(CD3D9Device* pDevice);
	~CD3D9GpuProgramManager(void);


protected:

	CGpuProgram*			_newProgram();

	CD3D9Device*			m_pD3D9Device;

};
}


