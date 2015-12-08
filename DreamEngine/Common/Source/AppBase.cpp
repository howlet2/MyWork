#include "AppBase.h"

CAppBase::CAppBase(void)
{
}


CAppBase::~CAppBase(void)
{
}

Error CAppBase::run(CAppListener* pAppListener)
{
	if (pAppListener==MATH_NULL)return ERROR_HAVE_NULL_POINT;

	m_pAppListener = pAppListener;
	
	m_pRoot = new CRoot;

	#ifdef _DEBUG
		m_pRoot->loadPlugin("RenderSystem_GLES2_d.dll");
		//m_pRoot->loadPlugin("InputSystem_Direct3D9_d.dll");
	#else
		m_pRoot->LoadPlugin("RenderSystem_GLES2.dll");
		//m_pRoot->LoadPlugin("InputSystem_Direct3D9.dll");
	#endif // _DEBUG
	
	m_pRoot->initialize("DefaultWindow(800*600)", 800, 600);

	CRenderWindow* pRenderWindow = m_pRoot->getRenderSystem()->getActiveRenderWindow();
	pRenderWindow->addListener(m_pAppListener);
	CCamera* pCamera = m_pRoot->getSceneManager()->createCamera("MainCamera");
	pCamera->setProjectionType(CFrustum::PT_ORTHOGRAPHIC);
	pCamera->setHeight(600); pCamera->setWidth(800);
	pRenderWindow->addViewport(pCamera);

	//m_pRoot->getTouchSystem()->initialize(pRenderWindow->getWindowModule());

	m_pAppListener->onInitialize();
	m_pRoot->go();

	return ERROR_OK;
}

Error CAppBase::shutDown()
{
	if (m_pAppListener != MATH_NULL)m_pAppListener->onShutDown();

	m_pRoot->shutDown();
	m_pRoot->loadPlugin("RenderSystem_GLES2_d.dll");
	m_pRoot->loadPlugin("InputSystem_Direct3D9_d.dll");
	SAFE_DELETE(m_pRoot);

	return ERROR_OK;
}

