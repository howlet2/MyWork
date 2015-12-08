#pragma once

#include "EngineObject.h"
#include "RenderWindow.h"
#include "RenderSystem.h"
#include "SceneManager.h"
#include "MaterialManager.h"
#include "TexUnitManager.h"
#include "Singleton.h"
#include "DynLib.h"
#include "RegisterData.h"
#include "Input/TouchSystem.h"


namespace DreamEngine
{

class _EngineExport CRoot : public CEngineObject , public CSingleton<CRoot>
{
public:
	CRoot(void);
	~CRoot(void);

	static CRoot&			instance(void);
	static CRoot*			instancePtr(void);

	void					setRenderSystem(CRenderSystem* pRenderSystem);

	CRenderSystem*			getRenderSystem(void)const			{return m_pCurRenderSystem;}
	CTouchSystem*			getTouchSystem(void)const			{return m_pTouchSystem;}
	CSceneManager*			getSceneManager(void)const			{return m_pSceneManager;}
	CMaterialManager*		getMaterialManager(void)const		{return m_pMaterialManager;}
	CRegisterData*			getRegisterData(void)const			{return m_pRegisterData;}

	void					initialize(const CString& windowName, m_uint16 width, m_uint16 height);
	void					shutDown(void);

	bool					loadPlugin(const CString& name);
	void					installPlugin(CPLugin* pLugin);
	void					unInstallPlugin(CPLugin* pLugin);


	void					go(void);
	void					loop(void);

protected:

	CRenderSystem*			m_pCurRenderSystem;
	CTouchSystem*			m_pTouchSystem;
	CSceneManager*			m_pSceneManager;
	CMaterialManager*		m_pMaterialManager;
	CTexUnitManager*		m_pTexUnitManager;
	CRegisterData*			m_pRegisterData;

	

	typedef std::list<CPLugin*> PluginLst;
	PluginLst				m_plugins;
	CDynLibManager*			m_pDynLibManager;
};

template<> CRoot* CSingleton<CRoot>::m_singleton = 0;

}


