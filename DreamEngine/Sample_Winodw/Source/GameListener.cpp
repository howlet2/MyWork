#include "GameListener.h"
#include "HardwareBuffer.h"

CGameListener::CGameListener(void)
{
} 
 

CGameListener::~CGameListener(void)
{    
}
 
void CGameListener::onInitialize()
{
	CCamera* pCamera = CRoot::instancePtr()->getRenderSystem()->getActiveRenderWindow()->getCamera();
	pCamera->setPosition(0.0f, -0.0f, -100.0f);
	pCamera->lookAt(0.0f, 0.0f, -0.0f);
	   
	CSceneManager* pSceneManager = CRoot::instancePtr()->getSceneManager();
	CSceneNode* pNode = pSceneManager->createSceneNode("xx");
	CSprite* pSprite = pSceneManager->createSprite("xx","../../Media/picture/spineboy.png");
	pSprite->attach(pNode);
	pNode->setScale(0.3f, 0.3f, 1.0f);
	pNode->setPosition(-400, -300, 0);
} 

void CGameListener::onShutDown()
{

}

void CGameListener::onRenderStart(CRenderTarget* rw)
{
	CRoot::instancePtr()->getTouchSystem()->update();
}

void CGameListener::onRender(CRenderTarget* rw)
{
	int triangleCount = CRoot::instancePtr()->getSceneManager()->getTriangleCount();

	CTouchSystem* pInputSystem = CTouchSystem::instancePtr();
	
	int x = pInputSystem->getPositionX()-400;
	int y = -(pInputSystem->getPositionY()-300);
	CSceneManager* pSceneManager = CRoot::instancePtr()->getSceneManager();
	if (pInputSystem->getState()==CTouchSystem::STATE_DOWN)
	{
		CSceneManager* pSceneManager = CRoot::instancePtr()->getSceneManager();
		pSceneManager->getMovableObject("xx")->getSceneNode()->setPosition(x,y,0);
	} 
}
 
void CGameListener::onRenderEnd(CRenderTarget* rw)
{

}