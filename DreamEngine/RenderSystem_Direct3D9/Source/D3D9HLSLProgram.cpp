#include "CommonFunction.h"
#include "D3D9HLSLProgram.h"
#include "D3D9Texture.h"

namespace DreamEngineD3D
{

CD3D9HLSLProgram::CD3D9HLSLProgram(CD3D9Device* pD3D9Device):
m_pD3D9Device(pD3D9Device)
{
}


CD3D9HLSLProgram::~CD3D9HLSLProgram(void)
{
}


void CD3D9HLSLProgram::_addParams(ID3DXConstantTable* pConstTable, ShaderType type)
{
	D3DXCONSTANTTABLE_DESC desc;
	pConstTable->GetDesc(&desc);

	for (m_uint32 i=0; i<desc.Constants; ++i)
	{
		D3DXHANDLE var = pConstTable->GetConstant(0, i);
		D3DXCONSTANT_DESC desc; UINT decCount=0;
		pConstTable->GetConstantDesc(var, &desc, &decCount);

		CString name(desc.Name); 
		CShaderParam::ParamType paramType = 
			CCommonFunction::D3D9ParamTypeToSPType(desc.Class, desc.Type, desc.Elements);
		m_uint8 elemCount		= desc.Elements;
		m_uint8 byteSize		= desc.Bytes;
		m_uint8 registerIdx		= desc.RegisterIndex;
		m_uint8 stMembers		= desc.StructMembers;

		CShaderParam* pParam = m_pShaderParamTable->addParam(name, paramType, elemCount, byteSize, registerIdx, stMembers);
		pParam->setUserInfo(m_uint8(type));
	}
}

CShader* CD3D9HLSLProgram::newShader(ShaderType type)
{
	switch (type)
	{
	case ST_VERTEX:
		{
			return new CHLSLVertex(m_pD3D9Device);
		}break;

	case ST_FRAGMENT:
		{
			return new CHLSLFragment(m_pD3D9Device);
		}break;
	}

	return MATH_NULL;
}

Error CD3D9HLSLProgram::createParamTable(void)
{
	m_pShaderParamTable = new CShaderParamTable;

	if (m_pFragmentShader!=MATH_NULL)
	{
		CHLSLShaderBase* pHLSLShader = static_cast<CHLSLShaderBase*>(m_pFragmentShader);
		_addParams(pHLSLShader->getConstantTable(), ST_FRAGMENT);
	}

	if (m_pVertexShader!=MATH_NULL)
	{
		CHLSLShaderBase* pHLSLShader = static_cast<CHLSLShaderBase*>(m_pVertexShader);
		_addParams(pHLSLShader->getConstantTable(), ST_VERTEX);
	}

	CheckEngineError(m_pShaderParamTable->_buildDataBuffer())

	return ERROR_OK;
}

void CD3D9HLSLProgram::updateAutoParams()
{
	if (m_pShaderParamTable != MATH_NULL)
	{
		m_pShaderParamTable->setValue(FLAG_LINK_FLAG_STRING($, atp_worldViewProjMatrix),
			CRegisterData::instance().getWorldViewProjMatrix());
		m_pShaderParamTable->setValue(FLAG_LINK_FLAG_STRING($, atp_viewMatrix),
			*CRegisterData::instance().getViewMatrix());
		m_pShaderParamTable->setValue(FLAG_LINK_FLAG_STRING($, atp_worldMatrix),
			*CRegisterData::instance().getWorldMatirx());
		m_pShaderParamTable->setValue(FLAG_LINK_FLAG_STRING($, atp_cameraPos),
			*CRegisterData::instance().getCameraPosition());
	}
}

void CD3D9HLSLProgram::updateParams()
{
	CShaderParamTable::ParamIter paramIter = m_pShaderParamTable->getParamIter();

	while (paramIter.hasMore())
	{
		CShaderParam* pParam = paramIter.current(); 

		const CString& name = pParam->getName();
		m_byte* pDataPtr = (m_byte*)(pParam->getDataPtr());
		m_uint8 dataSize = pParam->getSize();

		CShaderParam::ParamType type = paramIter.current()->getType();
		if (type == CShaderParam::SPT_TEXTURE)
		{
			CD3D9Texture * pTexture = MATH_NULL;
			pParam->getDataVaule(&pTexture);
			IDirect3DTexture9* pTextureBuf = static_cast<IDirect3DTexture9*>(pTexture->getTextureBuf());
			
			m_pD3D9Device->getD3DDevice()->SetTexture(pTexture->getTexCoordLayer(), pTextureBuf);
		}
		else
		{
			ShaderType type = static_cast<ShaderType>(pParam->getUserInfo());
			CHLSLShaderBase* pHLSLShader = MATH_NULL;

			switch (type)
			{
			case ST_FRAGMENT:
				{
					pHLSLShader = static_cast<CHLSLShaderBase*>(m_pFragmentShader);
				}break;
				
			case ST_VERTEX:
				{
					pHLSLShader = static_cast<CHLSLShaderBase*>(m_pVertexShader);
				}break;

			default: break;
			}

			if (pHLSLShader != MATH_NULL)
			{
				pHLSLShader->getConstantTable()->SetValue(m_pD3D9Device->getD3DDevice(),
					name.c_str(), pDataPtr, dataSize);
			}
		}

		paramIter.Next();
	}
}

Error CD3D9HLSLProgram::onShaderCreated()
{
	return ERROR_OK;
}

void CD3D9HLSLProgram::onBeforeDestory()
{

}

}