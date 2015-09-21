#pragma once
#include "EngineObject.h"
#include "MovableObject.h"
#include "MovableRect.h"
#include "Entity.h"
#include "Terrain.h"
#include "RenderSystem.h"
#include "Camera.h"
#include "SceneNode.h"

namespace DreamEngine
{

class _EngineExport CSceneManager : public CEngineObject
{
public:

	CSceneManager(CRenderSystem* pRenderSystem);
	virtual ~CSceneManager(void);

	CSceneNode*			createSceneNode(const CString& name);

	CCamera*			createCamera(const CString& name,
									 CFrustum::ProjectionType type=CFrustum::PT_PERSPECTIVE);
	CCamera*			getCamera(const CString& name)const;
	CCamera*			getCamera(m_uint8 index)const;

	CMovableObject*		getMovableObject(const CString& name)const;
	CEntity*			createEntity(const CString& name, const CString& fileName);
	CTerrain*			createTerrain(const CString& name, 
									  const CString& highMap, 
									  int sectionSqrtCount);

	CTestMovable*		createTestMovale(const CString& name)
	{
		CTestMovable* pTestMovable = new CTestMovable(m_pRenderSystem, name);
		pTestMovable->onCreate();

		m_movableLsts.push_back(pTestMovable);
		return pTestMovable;
	}



	//void				SetAmbientColor(CColor color);

	virtual void		onRender(void);
	virtual void		onLostDevice();
	virtual void		onResetDevice();
	virtual void		onDestory();

	virtual	int			getTriangleCount()const;
	CRenderSystem*		getRenderSystem(void)const	{return m_pRenderSystem;}

protected:

	void				_updateRegisterData(const CRenderData* pRenderData,
											const CMovableObject* pObjOwner);

protected:

	typedef std::list<CMovableObject*> MovableObjectLst;
	MovableObjectLst	m_movableLsts;

	typedef std::vector<CCamera*> CameraLst;
	CameraLst			m_cameras;
	CRenderSystem*		m_pRenderSystem;

	CNode::NodeLst		m_nodes;
};

}

