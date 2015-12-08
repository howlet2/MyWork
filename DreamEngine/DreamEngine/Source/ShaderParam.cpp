#include "ShaderParam.h"

namespace DreamEngine
{

m_byte CShaderParam::SizeOfParamType(ParamType type, m_byte count/*=1*/)
{
	switch (type)
	{
	case SPT_BOOL:
	case SPT_BOOL_ARRAY:
		{
			return sizeof(bool)*count;
		}break;

	case SPT_INT:
	case SPT_INT_ARRAY:
		{
			return sizeof(int)*count;
		}break;

	case SPT_FLOAT:
	case SPT_FLOAT_ARRAY:
		{
			return sizeof(float)*count;
		}break;

	case SPT_MATRIX16:
	case SPT_MATRIX16_ARRAY:
		{
			return sizeof(CMatrix16)*count;
		}break;

	case SPT_VECTOR3:
	case SPT_VECTOR3_ARRAY:
		{
			return sizeof(CVector3)*count;
		}break;

	case SPT_TEXTURE:
		{
			return sizeof(void*);
		}break;
	}

	return SPT_UNKNOW;
}

CShaderParam::CShaderParam()
{

}

CShaderParam::CShaderParam(const CString& name):
m_name(name)
{

}

CShaderParam::CShaderParam( const CString& name, 
							ParamType type,
							m_uint8 elemCount,
							m_uint8 byteSize, 
							m_uint8 registerIdx,
							m_uint8 stMembers):

							m_name(name),
							m_type(type),
							m_elemCount(elemCount), 
							m_byteSize(byteSize),
							m_registerIdx(registerIdx),
							m_stMembers(stMembers),
							m_pData(MATH_NULL)
{
}

CShaderParam::~CShaderParam(void)
{
}

void CShaderParam::setAll(ParamType type, 
						  m_uint8 elemCount, 
						  m_uint8 byteSize, 
						  m_uint8 stMembers) 
						  
{
	m_type		= type;
	m_elemCount = elemCount;
	m_byteSize	= byteSize;
	m_stMembers = stMembers;
}

void CShaderParam::setUserInfo(m_uint8 userInfo)
{
	m_userInfo = userInfo;
}

void CShaderParam::setVaule(void* pVaule)
{
	if (m_pData == MATH_NULL)return;

	m_byte dataSize = SizeOfParamType(m_type, m_elemCount);
	memcpy((m_byte*)(m_pData), pVaule, dataSize);
}

void CShaderParam::getDataVaule(void* pData)const
{
	memcpy(pData, (m_byte*)(m_pData), m_byteSize);
}

void CShaderParam::setAddressVaule(void* pAddress)
{
	int data = int(pAddress);					
	m_byte dataSize = SizeOfParamType(m_type, m_elemCount);

	memcpy((m_byte*)(m_pData), &data, dataSize);
}

void* CShaderParam::getAddressVaule()const
{
	int data = 0;
	memcpy(&data, (m_byte*)(m_pData), m_byteSize);
	return (void*)data;
}

}

