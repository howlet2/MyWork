#include "ShaderParamTable.h"

namespace DreamEngine
{
CShaderParamTable::CShaderParamTable(void):
m_dateSizeNum(0),
m_pDataBuffer(MATH_NULL),
m_paramIter(m_shaderParams.begin(), m_shaderParams.end())
{
	
}


CShaderParamTable::~CShaderParamTable(void)
{
	
}

CShaderParam* CShaderParamTable::getParam(const CString& name)const
{
	ShaderParamLst::const_iterator iter;
	for (iter=m_shaderParams.begin(); iter!=m_shaderParams.end(); ++iter)
	{
		if ((*iter)->getName()==name)
		{
			return *iter;
		}
	}
	return MATH_NULL;
}

void CShaderParamTable::setValue(const CString& name, const void* pVaule, m_uint8 vauleSize)
{
	CShaderParam* pShaderParam = getParam(name);
	if (pShaderParam != MATH_NULL)
	{
		void* pDate = pShaderParam->getDataPtr();
		if (pDate != MATH_NULL) memcpy(pDate, pVaule, vauleSize);
	}
}

void CShaderParamTable::setValue(const CString& name, bool vaule)
{
	setValue(name, &vaule, sizeof(vaule));
}

void CShaderParamTable::setValue(const CString& name, int vaule)
{
	setValue(name, &vaule, sizeof(vaule));
}

void CShaderParamTable::setValue(const CString& name, float vaule)
{
	setValue(name, &vaule, sizeof(vaule));
}

void CShaderParamTable::setValue(const CString& name, const CVector3& vaule)
{
	setValue(name, &vaule, sizeof(vaule));
}

void CShaderParamTable::setValue(const CString& name, const CMatrix16& vaule)
{
	setValue(name, &vaule, sizeof(vaule));
}

// void CShaderParamTable::setValue(const CString& name, CTexture* pTexture)
// {
// 	setValue(name, (const void*)(pTexture), sizeof(CTexture*));
// }

void CShaderParamTable::setAddressValue(const CString& name, void* pVaule)
{
	CShaderParam* pShaderParam = getParam(name);
	if (pShaderParam != MATH_NULL)
	{
		pShaderParam->setAddressVaule(pVaule);
	}
}

CShaderParam* CShaderParamTable::addParam(const CString& name,
										  CShaderParam::ParamType type, 
										  m_uint8 elemCount, 
										  m_uint8 byteSize,
										  m_uint8 registerIdx,
										  m_uint8 stMembers
										 )
{
	CShaderParam* pShaderParam = new CShaderParam( 
		name, type, elemCount, byteSize, registerIdx, stMembers);
	
	m_shaderParams.push_back(pShaderParam);
	m_dateSizeNum += byteSize;

	m_paramIter.set(m_shaderParams.begin(), m_shaderParams.end());

	return pShaderParam;
}

void CShaderParamTable::destory()
{
	ShaderParamLst::iterator iter;
	for (iter=m_shaderParams.begin(); iter!=m_shaderParams.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	SAFE_DELETE(m_pDataBuffer);
}

Error CShaderParamTable::_buildDataBuffer()
{
	SAFE_DELETE(m_pDataBuffer);
	m_pDataBuffer = new m_byte[m_dateSizeNum+1];

	int dateOffset = 0;
	ShaderParamLst::iterator iter;
	for (iter=m_shaderParams.begin(); iter!=m_shaderParams.end(); ++iter)
	{
		(*iter)->setDataPtr((m_byte*)(m_pDataBuffer)+dateOffset);
		dateOffset += (*iter)->getSize();

		if (dateOffset > m_dateSizeNum)
		{
			return ERROR_MEMORY_ADDRESS_OUT_RANGE;
		}
	}

	return ERROR_OK;
	
}

}

