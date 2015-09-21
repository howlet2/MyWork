#include "D3D9HLSLShader.h"
#include "FileDataStream.h"
#include "CommonFunction.h"
#include "RegisterData.h"

namespace DreamEngineD3D
{

CHLSLShaderBase::CHLSLShaderBase(CD3D9Device* pD3D9Device, ShaderProfile profile):
CShader(CCommonFunction::profileToType(profile)),
m_pD3D9Device(pD3D9Device),
m_profile(profile),
m_pShaderBuffer(MATH_NULL),
m_pErrorBuffer(MATH_NULL),
m_pConstantTable(MATH_NULL)
{

}

CHLSLShaderBase::~CHLSLShaderBase()
{

}

Error CHLSLShaderBase::compileShader(const CString& strSource)
{
	m_dwrd flags = D3DXSHADER_SKIPOPTIMIZATION;
	 	#if defined( DEBUG ) || defined( _DEBUG )
	 		flags |= D3DXSHADER_DEBUG;
	 	#endif
	
	CString enterFun = CCommonFunction::profileToEnterFun(m_profile);
	CString profile  = CCommonFunction::profileToString(m_profile);

	if (D3DXCompileShader(strSource.c_str(), strSource.size(), 0, 0, enterFun.c_str(), 
	 	profile.c_str(), flags, 
	 	&m_pShaderBuffer, &m_pErrorBuffer, &m_pConstantTable)<0)
	{
	 	if (m_pErrorBuffer != MATH_NULL)
	 	{
	 		MessageBox(0, (char*)m_pErrorBuffer->GetBufferPointer(), "Create CD3D9HLSLProgram", 0);
	 		m_pErrorBuffer->Release();
	 	}
	 
	 	return ERROR_COMPILE_SHADER_ERROR;
	}
	 
	return ERROR_OK;
}

Error CHLSLFragment::onInitializeShader()
{
	CheckEngineError(compileShader(m_strSource));

	if (m_pD3D9Device->getD3DDevice()->CreatePixelShader(
		(m_uint32*)m_pShaderBuffer->GetBufferPointer(), &m_pShader) < 0)
	{
		return ERROR_CREATE_FRAGMENT_SHADER_FAILD;
	}
	
	return ERROR_OK;
}

CHLSLFragment::CHLSLFragment(CD3D9Device* pD3D9Device, ShaderProfile profile/*=SP_PS_2_0*/):
CHLSLShaderBase(pD3D9Device, profile),
m_pShader(MATH_NULL)
{
}


CHLSLFragment::~CHLSLFragment(void)
{
	SAFE_RELEASE(m_pShader);
}



CHLSLVertex::CHLSLVertex(CD3D9Device* pD3D9Device, ShaderProfile profile/*=SP_VS_2_0*/):
CHLSLShaderBase(pD3D9Device,profile),
m_pShader(MATH_NULL)
{

}

CHLSLVertex::~CHLSLVertex(void)
{
	SAFE_RELEASE(m_pShader);
}

Error CHLSLVertex::onInitializeShader()
{
	CheckEngineError(compileShader(m_strSource));

	if (m_pD3D9Device->getD3DDevice()->CreateVertexShader(
		(m_uint32*)m_pShaderBuffer->GetBufferPointer(), &m_pShader) < 0)
	{
		return ERROR_CREATE_VERTEX_SHADER_FAILD;
	}

	return ERROR_OK;
}

}
