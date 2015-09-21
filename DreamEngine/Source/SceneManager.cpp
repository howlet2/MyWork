#include "SceneManager.h"
#include "MeshManager.h"
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
	MovableObjectLst::iterator moveableIter;
	for (moveableIter=m_movableLsts.begin(); moveableIter!=m_movableLsts.end(); ++moveableIter)
	{
		SAFE_DELETE(*moveableIter);
	}

	CameraLst::iterator camerasIter;
	for (camerasIter=m_cameras.begin(); camerasIter!=m_cameras.end(); ++camerasIter)
	{
		SAFE_DELETE(*camerasIter);
	}

	CNode::NodeLst::iterator iter;
	for (iter=m_nodes.begin(); iter!=m_nodes.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
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
	return NULL;
}

CEntity* CSceneManager::createEntity(const CString& name, const CString& fileName)
{
	CMesh* pMesh = CMeshManager::instancePtr()->createFromFile(name, fileName);

	CEntity* pEntity = new CEntity(m_pRenderSystem, name);
	pEntity->addMesh(pMesh);

	pEntity->onCreate();

	m_movableLsts.push_back(pEntity);

	return pEntity;
}


CTerrain* CSceneManager::createTerrain(const CString& name, 
									   const CString& highMap, 
									   int sectionSqrtCount)
{
	CTerrain* pTerrain = new CTerrain(name, m_pRenderSystem);
	pTerrain->build(highMap, sectionSqrtCount);

	pTerrain->onCreate();
	m_movableLsts.push_back(pTerrain);

	return pTerrain;
}

void CSceneManager::onRender()
{
	MovableObjectLst::iterator objIter;
	for (objIter=m_movableLsts.begin(); objIter!=m_movableLsts.end(); ++objIter)
	{
		//(*iter)->OnRender();
		const CMovableObject::RenderDataLst& renderData = (*objIter)->getRenderData();
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
	{
		(*iter)->onLostDevice();
	}
}

void CSceneManager::onResetDevice()
{
	MovableObjectLst::iterator iter;
	for (iter=m_movableLsts.begin(); iter!=m_movableLsts.end(); ++iter)
	{
		(*iter)->onResetDevice();
	}
}

void CSceneManager::onDestory()
{
	MovableObjectLst::iterator iter;
	for (iter=m_movableLsts.begin(); iter!=m_movableLsts.end(); ++iter)
	{
		(*iter)->onDestroy();
	}
}

int CSceneManager::getTriangleCount()const
{
	int triangleCount = 0;
	MovableObjectLst::const_iterator iter;
	for (iter=m_movableLsts.begin(); iter!=m_movableLsts.end(); ++iter)
	{
		triangleCount += (*iter)->getTriangleCount();
	}
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

}
