#pragma once
#include "Engineobject.h"
#include "Material.h"
#include "Singleton.h"

namespace DreamEngine
{
class _EngineExport CRegisterData : public CEngineObject, public CSingleton<CRegisterData>
{
public:
	CRegisterData(void);
	~CRegisterData(void);

	static CRegisterData&	instance(void);
	static CRegisterData*	instancePtr(void);

	void					setWorldViewProjMatrix(CMatrix16 worldViewProjMatrix)
										{m_worldViewProjMatrix=worldViewProjMatrix;}
	const CMatrix16&		getWorldViewProjMatrix(void)const						
										{return m_worldViewProjMatrix;}

	void					setWorldMatirx(const CMatrix16* pWorldMatirx)	
										{m_pWorldMatirx=pWorldMatirx;}
	const CMatrix16*		getWorldMatirx(void)const						
										{return m_pWorldMatirx;}	

	void					setViewMatrix(const CMatrix16* pViewMatrix)	
										{m_pViewMatrix=pViewMatrix;}
	const CMatrix16*		getViewMatrix(void)const						
										{return m_pViewMatrix;}

	void					setCameraPosition(const CVector3* pCameraPosition)
										{m_pCameraPosition=pCameraPosition;}
	const CVector3*			getCameraPosition(void)const						
										{return m_pCameraPosition;}

	void					setCurMaterial(CMaterial* pMaterial)
										{m_pCurMaterial = pMaterial;}
	CMaterial*				getCurMaterial(void)const
										{return m_pCurMaterial;}

protected:

	CMatrix16				m_worldViewProjMatrix;
	const CMatrix16*		m_pWorldMatirx;
	const CMatrix16*		m_pViewMatrix;
	const CVector3*			m_pCameraPosition;
	CMaterial*				m_pCurMaterial;

};
template<> CRegisterData* CSingleton<CRegisterData>::m_singleton = 0;

}


