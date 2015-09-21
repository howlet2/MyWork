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
	pCamera->setPosition(0.0f, -0.0f, -23.0f);
	pCamera->lookAt(0.0f, 0.0f, -0.0f);
	   
	CSceneManager* pSceneManager = CRoot::instancePtr()->getSceneManager();
	CTestMovable* pObject = pSceneManager->createTestMovale("xx");
	
 	CEntity*	pEntity = pSceneManager->createEntity("howlet", "../../Media/mesh/cube.dmesh");
	CTexture* pTexture =
			CVideoManager::instancePtr()->createTextureFromFile("xx", "bug886.jpg");
	pTexture->setTexCoordLayer(0);

	pObject->getMaterial()->getGpuProgram()->getShaderParamTable()->setAddressValue("s_texture", pTexture);
	pEntity->getMaterial()->getGpuProgram()->getShaderParamTable()->setAddressValue("s_texture", pTexture);
// 
 //	CTexture* pTexture =
 	//	CRoot::InstancePtr()->GetRenderSystem()->GetActiveRenderWindow()->GetVideoManager()->CreateTextureFromFile("xx","../../Media/mesh/bihull.bmp");
// 	//pEntity->GetMaterial()->GetFragmentProgram()->GetShaderParamTable()->SetValue("$decalTex", pTexture);
 	//pEntity->GetMaterial()->SetFillMode(FILLMODE_SOLID);
 	//pEntity->GetMaterial()->SetCullMode(CULLMODE_NONE);
 	//pEntity->GetMaterial()->SetZTestEnble(false);
 
 	CSceneNode* pSceneNode = pSceneManager->createSceneNode("sceneNode");
 	pEntity->attach(pSceneNode);
 	pSceneNode->setPosition(0, 0, 0);
	pSceneNode->setScale(0.1, 0.1, 0.1);
	pSceneNode->yaw(-MATH_PI/2);
// 
// 	//CTerrain* pTerrain = pSceneManager->CreateTerrain("xx", "terrain.png", 16);
// //	pTerrain->GetMaterial()->m_fillMode = FILLMODE_WIREFRAME;
// 	m_uint16 count = pEntity->GetTriangleCount();
// 	++count;
} 

void CGameListener::onShutDown()
{

}

void CGameListener::onRenderStart(CRenderTarget* rw)
{
	CRoot::instancePtr()->getInputSystem()->update();
}

void CGameListener::onRender(CRenderTarget* rw)
{
	int triangleCount = CRoot::instancePtr()->getSceneManager()->getTriangleCount();
	if (CInputSystem::instancePtr()->getKeyBoard()->isKeyDown(KEY_S))
	{
		rw->getCamera()->fly(-10.0f);
	}

	if (CInputSystem::instancePtr()->getKeyBoard()->isKeyDown(KEY_W))
	{
		rw->getCamera()->fly(10.0f);
	}

	if (CInputSystem::instancePtr()->getKeyBoard()->isKeyDown(KEY_A))
	{
		rw->getCamera()->walk(-10.0f);
	}

	if (CInputSystem::instancePtr()->getKeyBoard()->isKeyDown(KEY_D))
	{
		rw->getCamera()->walk(10.0f);
	}

	if (CInputSystem::instancePtr()->getKeyBoard()->isKeyDown(KEY_Q))
	{
		CMovableObject* pObject = CRoot::instancePtr()->getSceneManager()->getMovableObject("howlet");
		pObject->getSceneNode()->yaw(-MATH_PI/2);
	}

	if (CInputSystem::instancePtr()->getKeyBoard()->isKeyDown(KEY_E))
	{
		CMovableObject* pObject = CRoot::instancePtr()->getSceneManager()->getMovableObject("howlet");
		pObject->getSceneNode()->yaw(MATH_PI/2);
	}

	if (CInputSystem::instancePtr()->getMouse()->isLMouseDown())
	{

	} 
}
 
void CGameListener::onRenderEnd(CRenderTarget* rw)
{

}