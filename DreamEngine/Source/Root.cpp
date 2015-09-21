#include "Root.h"
#include "WindowEventUtilities.h"

namespace DreamEngine
{
CRoot::CRoot(void):
m_pCurRenderSystem(MATH_NULL),
m_pInputSystem(MATH_NULL),
m_pSceneManager(MATH_NULL),
m_pMaterialManager(MATH_NULL),
m_pTexUnitManager(MATH_NULL),
m_pDynLibManager(MATH_NULL),
m_pMeshManager(MATH_NULL)
{
	m_pDynLibManager	= new CDynLibManager;
}


CRoot::~CRoot(void)
{
	
}

CRoot& CRoot::instance(void)
{	
	return (*m_singleton); 
}

CRoot* CRoot::instancePtr(void)
{ 
	return m_singleton; 
}


void CRoot::setRenderSystem(CRenderSystem* pRenderSystem)
{
	m_pCurRenderSystem = pRenderSystem;
}

void CRoot::setInputSystem(CInputSystem* pInputSystem)
{
	m_pInputSystem = pInputSystem;
}

bool CRoot::loadPlugin(const CString& name)
{
	if (m_pDynLibManager != MATH_NULL)
	{
		CDynLib* pDynLib = m_pDynLibManager->load(name);
		if (pDynLib!=MATH_NULL)
		{
			DLL_PLUGIN_FUNC pFunc = (DLL_PLUGIN_FUNC)(pDynLib->getSymbol("dllStartPlugin"));

			if (pFunc != MATH_NULL)
			{
				pFunc();
				return true;
			}
		}
	}

	return false;
}

void CRoot::initialize(const CString& windowName, m_uint16 width, m_uint16 height)
{
	if (m_pCurRenderSystem != MATH_NULL)
		m_pCurRenderSystem->createRenderWindow(windowName, width, height, true);

	m_pSceneManager		= new CSceneManager(m_pCurRenderSystem);
	m_pMaterialManager	= new CMaterialManager;
	m_pTexUnitManager	= new CTexUnitManager;
	m_pMeshManager		= new CMeshManager;
	m_pRegisterData		= new CRegisterData;

}

void CRoot::shutDown()
{
	SAFE_DELETE(m_pRegisterData);

	m_pSceneManager->onDestory();
	SAFE_DELETE(m_pSceneManager);

	m_pMaterialManager->destoryAll();
	SAFE_DELETE(m_pMaterialManager);

	m_pDynLibManager->freeAll();
	SAFE_DELETE(m_pDynLibManager);

	m_pMeshManager->destroyAll();
	SAFE_DELETE(m_pMeshManager);
}

void CRoot::installPlugin(CPLugin* pLugin)
{
	if (pLugin==MATH_NULL) return;
	
	pLugin->install();
	m_plugins.push_back(pLugin);
}

void CRoot::unInstallPlugin(CPLugin* pLugin)
{
	PluginLst::iterator iter = find(m_plugins.begin(), m_plugins.end(), pLugin);
	
	if (iter != m_plugins.end())
	{
		(*iter)->uninstall();
		m_plugins.erase(iter);
	}
}

void CRoot::go()
{
	if (m_pCurRenderSystem==MATH_NULL)return;

	CRenderWindow* pRenderWindow = m_pCurRenderSystem->getActiveRenderWindow();

	if (pRenderWindow != MATH_NULL)
	{
		pRenderWindow->showWindow();
	}

	while (true)
	{
		CWindowEventUtilities::pumpMessage();

		if (CWindowEventUtilities::isQuit())break;

		loop();
	}
}

void CRoot::loop()
{
	if (m_pCurRenderSystem==MATH_NULL)return;

	CRenderWindow* pRenderWindow = m_pCurRenderSystem->getActiveRenderWindow();
	CRenderTarget::ListenerTargetIter& rtEventLst = pRenderWindow->getListenerIter();

	//start render
	rtEventLst.moveToBegin();
	while (rtEventLst.hasMore())
	{
		rtEventLst.current()->onRenderStart(pRenderWindow);
		rtEventLst.Next();
	}
	m_pCurRenderSystem->beginFrame();

	//rendering
	if (m_pSceneManager != MATH_NULL)
		m_pSceneManager->onRender();

	rtEventLst.moveToBegin();
	while (rtEventLst.hasMore())
	{
		rtEventLst.current()->onRender(pRenderWindow);
		rtEventLst.Next();
	}

	//end rendering
	m_pCurRenderSystem->endFrame();
	rtEventLst.moveToBegin();
	while (rtEventLst.hasMore())
	{
		rtEventLst.current()->onRenderEnd(pRenderWindow);
		rtEventLst.Next();
	}

	pRenderWindow->updateFPS();
}

}