#pragma once
#include "EngineObject.h"

namespace DreamEngine
{
//由CShaderParamTable自动创建和分配内存，设置m_pData指向的地址的值实际上是设置CShaderParamTable分配的内存的值
class _EngineExport CShaderParam
{
public:

enum ParamType
{
	SPT_UNKNOW			= 0,

	SPT_BOOL			= 1,
	SPT_INT				= 2,
	SPT_FLOAT			= 3,
	SPT_MATRIX16		= 4,
	SPT_VECTOR3			= 5,
	SPT_TEXTURE			= 6,

	SPT_ARRY_BASE_VAULE = 20,
	SPT_BOOL_ARRAY		= 21,
	SPT_INT_ARRAY		= 22,
	SPT_FLOAT_ARRAY		= 23,
	SPT_MATRIX16_ARRAY	= 24,
	SPT_VECTOR3_ARRAY	= 25,
};

static m_byte		SizeOfParamType(ParamType type, m_byte count=1);

friend class CShaderParamTable;

public:

	void					setAll( ParamType type, 
								    m_uint8 elemCount,
									m_uint8 byteSize, 
									m_uint8 stMembers);
									
	void*					getDataPtr(void)const		{return m_pData;}
	const CString&			getName(void)const			{return m_name;}
	ParamType				getType(void)const			{return m_type;}
	m_uint8					getElemCount(void)const		{return m_elemCount;}
	m_uint8					getSize(void)const			{return m_byteSize;}
	m_uint8					getRegisterIdx(void)const	{return m_registerIdx;}
	m_uint8					getStMembers(void)const		{return m_stMembers;}

	void					setUserInfo(m_uint8 userInfo);
	m_uint8					getUserInfo(void)const		{return m_userInfo;}

	void					getDataVaule(void* pData)const;
	void					setVaule(void* pVaule);					//存储指向的内容

	void* 					getAddressVaule()const;
	void					setAddressVaule(void* pAddress);		//存储地址本身的值
	


protected:

	CShaderParam();
	CShaderParam(const CString& name);

	void					setDataPtr(void* pData)		{m_pData=pData;}

	CShaderParam(const CString& name, 
		ParamType type, 
		m_uint8 elemCount,
		m_uint8 byteSize,
		m_uint8 registerIdx,
		m_uint8 stMembers);

	~CShaderParam(void);

protected:

	void*				m_pData;						// data address point to CShaderParamTable::m_pDataBuffer
						
	CString				m_name;							// var name
	ParamType			m_type;							// pram type
	m_uint8				m_elemCount;                    // number of elements
	m_uint8				m_byteSize;						// size of param data
	m_uint8				m_registerIdx;					// register index (equal CVertexElement.m_usageIndex in dx)(var local in gles)
	m_uint8				m_stMembers;					//number of structure member sub-parameters

	m_uint8				m_userInfo;						// ex information						
};

}


