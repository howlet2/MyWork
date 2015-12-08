#pragma once
#include <d3dx9.h>
#include "D3D9Define.h"
#include "Shader.h"
#include "D3D9Device.h"
#include "D3D9Enum.h"
using namespace DreamEngine;

namespace DreamEngineD3D
{

class _EngineD3D9Export CHLSLShaderBase : public CShader
{
public:

	CHLSLShaderBase(CD3D9Device* pD3D9Device, ShaderProfile profile);
	virtual ~CHLSLShaderBase();

	LPD3DXCONSTANTTABLE getConstantTable()const		{return m_pConstantTable;}

protected:

	Error compileShader(const CString& strSource);

	LPD3DXBUFFER				m_pShaderBuffer;
	LPD3DXBUFFER				m_pErrorBuffer;
	LPD3DXCONSTANTTABLE			m_pConstantTable;
	ShaderProfile				m_profile;

	CD3D9Device*				m_pD3D9Device;
};

class _EngineD3D9Export CHLSLFragment :  public CHLSLShaderBase
{
public:
	CHLSLFragment(CD3D9Device* pD3D9Device, ShaderProfile profile=SP_PS_2_0);
	~CHLSLFragment(void);

	IDirect3DPixelShader9*	getD3D9Shader(void)const		{return m_pShader;}

protected:

	virtual Error			onInitializeShader();

	IDirect3DPixelShader9*		m_pShader;
};

class _EngineD3D9Export CHLSLVertex : public CHLSLShaderBase
{
public:

	CHLSLVertex(CD3D9Device* pD3D9Device, ShaderProfile profile=SP_VS_2_0);
	~CHLSLVertex(void);

	IDirect3DVertexShader9*		getD3D9Shader(void)const		{return m_pShader;}

protected:

	virtual Error				onInitializeShader();

	IDirect3DVertexShader9*		m_pShader;

};

}


