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

	CSceneNode* pNode = pSceneManager->createSceneNode("xxNode");
	CFrameAniSprite* pSprite = pSceneManager->createFrameAniSprite("xxSprite",
								"../../Media/picture/Evil_000.png",
								"../../Media/picture/Evil_001.png",
								"../../Media/picture/Evil_002.png",
								MATH_NULL);
	pSprite->attach(pNode);
	pNode->setPosition(-400, -300, 0);

} 

void CGameListener::onShutDown()
{

}

void CGameListener::onRenderStart(CRenderTarget* rw)
{

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
		pSceneManager->getMovableObject("xxSprite")->getSceneNode()->setPosition(x,y,0);
	} 
}
 
void CGameListener::onRenderEnd(CRenderTarget* rw)
{

}