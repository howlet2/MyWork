#pragma once
#include "Singleton.h"
#include "TextureUnitState.h"
#include "ResourceFactory.h"

namespace DreamEngine
{

class CTexUnitManager : public CSingleton<CTexUnitManager>, public CRosourceFactory<CTextureUnitState>
{
public:
	CTexUnitManager(void);
	~CTexUnitManager(void);

	static CTexUnitManager& Instance(void);
	static CTexUnitManager* InstancePtr(void);

	virtual CTextureUnitState* Create(const CString& name, CTexture* pTexture=MATH_NULL);
};

template<> CTexUnitManager* CSingleton<CTexUnitManager>::m_singleton = 0;

}


