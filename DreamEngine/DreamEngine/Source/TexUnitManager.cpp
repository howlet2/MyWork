#include "TexUnitManager.h"

namespace DreamEngine
{

CTexUnitManager::CTexUnitManager(void)
{
}


CTexUnitManager::~CTexUnitManager(void)
{
}


CTexUnitManager& CTexUnitManager::Instance(void)
{	
	return (*m_singleton); 
}

CTexUnitManager* CTexUnitManager::InstancePtr(void)
{ 
	return m_singleton; 
}

CTextureUnitState* CTexUnitManager::Create(const CString& name, CTexture* pTexture/* =MATH_NULL */)
{
	CTextureUnitState* pNewResource = new CTextureUnitState(name, pTexture);
	m_resources.push_back(pNewResource);
	return pNewResource;
}

}