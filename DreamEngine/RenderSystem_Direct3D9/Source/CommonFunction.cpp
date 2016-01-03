#include "CommonFunction.h"
#include "StringHelper.h"

namespace DreamEngineD3D
{
CCommonFunction::CCommonFunction(void)
{
}


CCommonFunction::~CCommonFunction(void)
{
}

void CCommonFunction::vertexElementToD3D9Element(MATH_OUT D3DVERTEXELEMENT9* pElement, 
												 const CVertexBuffer::ElementLst& elemLst, 
												 bool isAddEndDecl/*=false*/)
{
	m_uint16 count = m_uint16(elemLst.size());

	for (m_uint16 i=0; i<count; ++i)
	{
		pElement[i].Type		= elemLst[i].m_type;
		pElement[i].Method		= elemLst[i].m_method;
		pElement[i].Offset		= elemLst[i].m_offset;
		pElement[i].Stream		= elemLst[i].m_stream;
		pElement[i].Usage		= elemLst[i].m_usage;
		pElement[i].UsageIndex	= elemLst[i].m_usageIndex;
	}

	if (isAddEndDecl)
	{
		CVertexElement endDecl; 
		endDecl.toEndDeclElement();
		pElement[count].Type		= endDecl.m_type;
		pElement[count].Method		= endDecl.m_method;
		pElement[count].Offset		= endDecl.m_offset;
		pElement[count].Stream		= endDecl.m_stream;
		pElement[count].Usage		= endDecl.m_usage;
		pElement[count].UsageIndex	= endDecl.m_usageIndex;
	}
	
}

CShaderParam::ParamType CCommonFunction::D3D9ParamTypeToSPType(
	D3DXPARAMETER_CLASS SPClass, D3DXPARAMETER_TYPE SPType, m_uint8 elemCount)
{
	CShaderParam::ParamType type;
	
	if(SPClass == D3DXPC_VECTOR)
		type = CShaderParam::SPT_VECTOR3;
	else if(SPClass==D3DXPC_MATRIX_ROWS || SPClass==D3DXPC_MATRIX_COLUMNS)
		type = CShaderParam::SPT_MATRIX16;
	else if (SPType==D3DXPT_BOOL)
		type = CShaderParam::SPT_BOOL;
	else if (SPType==D3DXPT_FLOAT)
		type = CShaderParam::SPT_FLOAT;
	else if (SPType==D3DXPT_INT)
		type = CShaderParam::SPT_INT;
	else if (SPType==D3DXPT_TEXTURE || SPType==D3DXPT_SAMPLER2D)
		type = CShaderParam::SPT_TEXTURE;
	else
		type = CShaderParam::SPT_UNKNOW;

	if (elemCount > 1)
	{
		int typeVaule = int(type);
		typeVaule += int(CShaderParam::SPT_ARRY_BASE_VAULE);
		type = CShaderParam::ParamType(typeVaule);
	}

	return type;
}

D3DPRIMITIVETYPE CCommonFunction::HDBufTypeToD3DPriType(HardwareBufferType type)
{
	switch (type)
	{
	case POINT_LIST:
		return D3DPT_POINTLIST;

	case LINE_LIST:
		return D3DPT_LINELIST;

	case LINE_SHRIP:
		return D3DPT_LINESTRIP;

	case TRIANGLE_LIST:
		return D3DPT_TRIANGLELIST;

	case TRIANGLE_STRIP:
		return D3DPT_TRIANGLESTRIP;

	case TRIANGLE_FAN:
		return D3DPT_TRIANGLEFAN;

	default: return D3DPT_FORCE_DWORD;
	}
}

D3DPOOL CCommonFunction::RSPOOLToD3DPool(RSPOOL pool)
{
	switch (pool)
	{
	case RSP_DEFAULT:
		{
			return D3DPOOL_DEFAULT;			
		}break;

	case RSP_MANAGER:
		{
			return D3DPOOL_MANAGED;
		}break;

	default: return D3DPOOL_FORCE_DWORD;
	}
}

D3DFORMAT	CCommonFunction::texFormatToD3DFormat(TEX_FORMAT texFormat)
{
	switch (texFormat)
	{
	case TF_R8G8B8:
		return D3DFMT_R8G8B8;

	case TF_A8R8G8B8:
		return  D3DFMT_A8B8G8R8;

	case TF_L8:
		return D3DFMT_L8;

	default: return D3DFMT_FORCE_DWORD;
	}
}

TEX_FORMAT	CCommonFunction::D3DFormatToTexFormat(D3DFORMAT texFormat)
{
	switch (texFormat)
	{
	case D3DFMT_R8G8B8:
		return TF_R8G8B8;

	case D3DFMT_A8B8G8R8:
		return  TF_A8R8G8B8;

	case D3DFMT_L8:
		return  TF_L8;

	default: return TF_UNKOWN;
	}
}

CString	CCommonFunction::profileToString(ShaderProfile profile)
{
	switch(profile)
	{
	case  SP_PS_2_0:
		return "ps_2_0";

	case SP_PS_3_0:
		return "ps_3_0";

	case SP_VS_2_0:
		return "vs_2_0";

	case SP_VS_3_0:
		return "vs_3_0";

	default: return "unknown";
	}
}

CString	CCommonFunction::profileToEnterFun(ShaderProfile profile)
{
	switch(profile)
	{
	case SP_PS_2_0:
	case SP_PS_3_0:
		return "PS_MAIN";

	case SP_VS_2_0:
	case SP_VS_3_0:
		return "VS_MAIN";

	default: return "main";
	}
}

ShaderType CCommonFunction::profileToType(ShaderProfile profile)
{
	switch (profile)
	{
	case SP_VS_3_0:
	case SP_VS_2_0:
		return ST_VERTEX;
		break;

	case SP_PS_2_0:
	case SP_PS_3_0:
		return ST_FRAGMENT;
		break;

	default: return ST_UNKOWN;
	}
}

}

