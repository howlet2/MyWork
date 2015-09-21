#pragma once
#include "EngineObject.h"
#include "ShaderParam.h"
#include "IteratorWrapper.h"
#include "Texture.h"

namespace  DreamEngine
{
//class CShaderParam;

class _EngineExport CShaderParamTable : public CEngineObject
{
public:

	typedef std::vector<CShaderParam*>								  ShaderParamLst;
	typedef CIteratorWrapper<ShaderParamLst::iterator, CShaderParam*> ParamIter;

	CShaderParamTable(void);
	~CShaderParamTable(void);

	ParamIter		getParamIter(void)const				{return m_paramIter;}
	CShaderParam*	getParam(const CString& name)const;

	void			setValue(const CString& name, const void* pVaule, m_uint8 vauleSize);
	void			setValue(const CString& name, bool vaule);
	void			setValue(const CString& name, int vaule);
	void			setValue(const CString& name, float vaule);
	void			setValue(const CString& name, const CVector3& vaule);
	void			setValue(const CString& name, const CMatrix16& vaule);
	//void			setValue(const CString& name, CTexture* pTexture);
	void			setAddressValue(const CString& name, void* pVaule);

	CShaderParam*	addParam(const CString& name, 
							 CShaderParam::ParamType type,
							 m_uint8 elemCount,
							 m_uint8 byteSize,
							 m_uint8 registerIdx,
							 m_uint8 stMembers 
							 );

	void			destory();
	Error			_buildDataBuffer(void);

protected:


	ShaderParamLst		m_shaderParams;
	ParamIter			m_paramIter;

	m_uint16			m_dateSizeNum;
	m_byte*				m_pDataBuffer;

};

}


