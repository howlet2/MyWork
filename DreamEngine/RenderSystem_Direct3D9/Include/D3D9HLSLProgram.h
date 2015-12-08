#pragma once
#include "GpuProgram.h"
#include "D3D9RenderSystem.h"
#include "RegisterData.h"
#include "D3D9HLSLShader.h"

using namespace DreamEngine;

namespace DreamEngineD3D
{
class _EngineD3D9Export CD3D9HLSLProgram : public CGpuProgram
{
public:
	CD3D9HLSLProgram(CD3D9Device* pD3D9Device);
	~CD3D9HLSLProgram(void);

protected:

	virtual CShader*	newShader(ShaderType type);

	virtual Error		createParamTable(void);
	virtual void		updateAutoParams(void);
	virtual void		updateParams(void);
	virtual Error		onShaderCreated(void);
	virtual void		onBeforeDestory(void);

	virtual void		_addParams(ID3DXConstantTable* pConstTable, ShaderType type);

	CD3D9Device*		m_pD3D9Device;
};
}
