#pragma once
#include "EngineObject.h"
#include "ResourceFactory.h"
#include "RenderStateDefine.h"
#include "TextureUnitState.h"
#include "GpuProgram.h"

namespace DreamEngine
{
class _EngineExport CMaterial : public CEngineObject 
{
public:
	typedef	std::vector<CTextureUnitState*> TexUnitLst;

	CMaterial(const CString& name);
	~CMaterial(void);

	const CString&		getName(void)const					{return m_name;}

	CGpuProgram*		getGpuProgram(void)const			{return m_pGupProgram;}
	void				setGpuProgram(CGpuProgram* pGpuProgram);


	CULLMODE			getCullMode(void)const			{return m_cullMode;}
	void				setCullMode(CULLMODE mode);

	FILLMODE			getFillMode(void)const			{return m_fillMode;}
	void				setFillMode(FILLMODE mode);

	bool				getZTestEnble(void)const		{return m_isZTestEnble;}
	void				setZTestEnble(bool isEnable);	
	
	TexUnitLst::size_type getTextureUnitSize(void)const	{return m_texUnits.size();}
	CTextureUnitState	  getTextureUnitState(int index)const;
	void				  addTextureUnitState(CTextureUnitState* pTexUnit);
	void				  setTextureUnitState(CTextureUnitState* pTexUnit);

	void				destory();

private:

	CString				m_name;

	CGpuProgram*		m_pGupProgram;

	CULLMODE			m_cullMode;
	FILLMODE			m_fillMode;
	bool				m_isZTestEnble;

	TexUnitLst			m_texUnits;

	//typedef CIteratorWrapper<TexUnitLst::iterator, CTextureUnitState> TexUnitIter;
	//TexUnitIter		m_texUnitsIter;
};


}


