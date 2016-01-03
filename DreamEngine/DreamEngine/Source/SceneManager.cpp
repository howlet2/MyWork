#include "SceneManager.h"
#include "RegisterData.h"
#include "Root.h"

namespace DreamEngine
{

CSceneManager::CSceneManager(CRenderSystem* pRenderSytem):
m_pRenderSystem(pRenderSytem)
{

}


CSceneManager::~CSceneManager(void)
{

}

CSceneNode* CSceneManager::createSceneNode(const CString& name)
{
	CSceneNode* pNode = new CSceneNode(name);
	m_nodes.push_back(pNode);
	return pNode;
}

CCamera* CSceneManager::createCamera(const CString& name, CFrustum::ProjectionType type/* =CFrustum::PT_PERSPECTIVE */)
{
	CCamera* pCamera = new CCamera(name, this, type);
	if (pCamera != NULL)
	{
		m_cameras.push_back(pCamera);
	}
	return pCamera;
}

CCamera* CSceneManager::getCamera(const CString& name)const
{
	for (CameraLst::const_iterator iter=m_cameras.begin(); iter!=m_cameras.end(); ++iter)
	{
		if ((*iter)->getName()==name)
		{
			return (*iter);
		}
	}

	return MATH_NULL;
}

CCamera* CSceneManager::getCamera(m_uint8 index)const
{
	if (index<m_uint8(m_cameras.size()))
	{
		return m_cameras[index];
	}

	return MATH_NULL;
}

CMovableObject* CSceneManager::getMovableObject(const CString& name)const
{
	MovableObjectLst::const_iterator iter;
	for (iter=m_movableLsts.begin(); iter!=m_movableLsts.end();  ++iter)
	{
		if ((*iter)->getName()==name)
		{
			return (*iter);
		}
	}
	return MATH_NULL;
}

CTestMovable* CSceneManager::createTestMovale(const CString& name)
{
	CTestMovable* pTestMovable = new CTestMovable(m_pRenderSystem, name);
	pTestMovable->onCreate();

	m_movableLsts.push_back(pTestMovable);
	return pTestMovable;
}

CSprite* CSceneManager::createSprite(const CString& name, const CString& fileName)
{
	CSprite* pSprite = new CSprite(m_pRenderSystem, name);
	pSprite->setTexture(fileName);
	pSprite->onCreate();

	m_movableLsts.push_back(pSprite);
	return pSprite;
}

CFrameAniSprite* CSceneManager::createFrameAniSprite(const CString& name, const char* pFileName, ...)
{
	CFrameAniSprite* pFrameAniSprite = new CFrameAniSprite(m_pRenderSystem, name);
	
	va_list argp; 
	va_start (argp, pFileName); 
	pFrameAniSprite->initWithFilesByValst(pFileName, argp);
	va_end (argp); 

	pFrameAniSprite->onCreate();

	m_movableLsts.push_back(pFrameAniSprite);
	return pFrameAniSprite;
}

CFrameAniSprite* CSceneManager::createFrameAniSprite(const CString& name, const CString& fileName)
{
	CFrameAniSprite* pFrameAniSprite = new CFrameAniSprite(m_pRenderSystem, name);
	pFrameAniSprite->initWithAnimationFile(fileName);

	m_movableLsts.push_back(pFrameAniSprite);
	return pFrameAniSprite;
}

void CSceneManager::onRender(float delay)
{
	MovableObjectLst::iterator objIter;
	for (objIter=m_movableLsts.begin(); objIter!=m_movableLsts.end(); ++objIter)
	{
		//(*iter)->OnRender();
		CFrameAniSprite* pFrameAniSprite = dynamic_cast<CFrameAniSprite*>(*objIter);
		if (pFrameAniSprite!=MATH_NULL)
			pFrameAniSprite->update(delay);

		const CMovableObject::RenderDataLst& renderData = (*objIter)->getRenderDataLst();
		CMovableObject::RenderDataLst::const_iterator iter;
		for (iter=renderData.begin(); iter!=renderData.end(); ++iter)
		{
			_updateRegisterData(*iter, *objIter);
			m_pRenderSystem->render(*iter);
		}
	}
}

void CSceneManager::onLostDevice()
{
	MovableObjectLst::iterator iter;
	for (iter=m_movableLsts.begin(); iter!=m_movableLsts.end(); ++iter)
		(*iter)->onLostDevice();
}

void CSceneManager::onResetDevice()
{
	MovableObjectLst::iterator iter;
	for (iter=m_movableLsts.begin(); iter!=m_movableLsts.end(); ++iter)
		(*iter)->onResetDevice();
}

void CSceneManager::onDestory()
{
	for (MovableObjectLst::iterator iter=m_movableLsts.begin(); iter!=m_movableLsts.end(); ++iter)
	{
		_onDestoryMoveObject(*iter);
		(*iter)->onDestroy();
		SAFE_DELETE(*iter);
	}

	CameraLst::iterator camerasIter;
	for (CameraLst::iterator camerasIter=m_cameras.begin(); camerasIter!=m_cameras.end(); ++camerasIter)
		SAFE_DELETE(*camerasIter);

	for (CNode::NodeLst::iterator iter=m_nodes.begin(); iter!=m_nodes.end(); ++iter)
		SAFE_DELETE(*iter);
}

int CSceneManager::getTriangleCount()const
{
	int triangleCount = 0;
	MovableObjectLst::const_iterator iter;
	for (iter=m_movableLsts.begin(); iter!=m_movableLsts.end(); ++iter)
		triangleCount += (*iter)->getTriangleCount();

	return triangleCount;
}

void CSceneManager::_updateRegisterData(const CRenderData* pRenderData,
										const CMovableObject* pObjOwner)
{
	if (pRenderData==MATH_NULL || pObjOwner==MATH_NULL) return;

	CRenderWindow* pActiveRenderWindow = CRoot::instancePtr()->getRenderSystem()->getActiveRenderWindow();

	CRegisterData::instancePtr()->setCurMaterial(pRenderData->m_pMaterial);
	CRegisterData::instancePtr()->setWorldMatirx(&pObjOwner->getWorldTransform());
	CRegisterData::instancePtr()->setViewMatrix(&pActiveRenderWindow->getCamera()->getViewMatrix());
	CRegisterData::instancePtr()->setCameraPosition(&pActiveRenderWindow->getCamera()->getPosition());		

	CMatrix16 viewProjMat;
	pActiveRenderWindow->getCamera()->getViewProjectMatrix(viewProjMat);
	const CMatrix16& worldMat = pObjOwner->getWorldTransform();
	CMatrix16 mat = worldMat*viewProjMat;
	CRegisterData::instancePtr()->setWorldViewProjMatrix(mat);
}

void CSceneManager::_onDestoryMoveObject(CMovableObject* pObject)
{

}

}
