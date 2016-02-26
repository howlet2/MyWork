#include "Root.h"
#include "WindowEventUtilities.h"
#include "Timer.h"

#ifdef WIN32
#include "vld/include/vld.h"
#endif

namespace DreamEngine
{
CRoot::CRoot(void):
m_pCurRenderSystem(MATH_NULL),
m_pTouchSystem(MATH_NULL),
m_pSceneManager(MATH_NULL),
m_pMaterialManager(MATH_NULL),
m_pTexUnitManager(MATH_NULL),
m_pDynLibManager(MATH_NULL)
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

	
	m_pMaterialManager		= new CMaterialManager;
	m_pTexUnitManager		= new CTexUnitManager;
	m_pTouchSystem			= new CTouchSystem(m_pCurRenderSystem->getActiveRenderWindow()->getWindowModule());

	m_pSceneManager			= new CSceneManager(m_pCurRenderSystem);

	m_pRegisterData			= new CRegisterData;
	

}

void CRoot::shutDown()
{
	SAFE_DELETE(m_pRegisterData);

	SAFE_DELETE(m_pTouchSystem);

	m_pSceneManager->onDestory();
	SAFE_DELETE(m_pSceneManager);

	m_pTexUnitManager->destoryAll();
	SAFE_DELETE(m_pTexUnitManager);

	m_pMaterialManager->destoryAll();
	SAFE_DELETE(m_pMaterialManager);

	m_pDynLibManager->freeAll();
	SAFE_DELETE(m_pDynLibManager);

	
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

	float timeDelay = calculateTimeDelay();

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
	if (m_pTouchSystem != MATH_NULL)
		m_pTouchSystem->update(timeDelay);

	if (m_pSceneManager != MATH_NULL)
		m_pSceneManager->onRender(timeDelay);

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

	pRenderWindow->updateFPS(timeDelay);
}

float CRoot::calculateTimeDelay()
{
	static Math::CTimer time;
	static Math::m_dwrd last = time.getMillisecondsCPU();
	Math::m_dwrd cur		 = time.getMicrosecondsCPU();

	float timeDelay = float(cur-last);
	last = cur;
	return timeDelay;
}

}