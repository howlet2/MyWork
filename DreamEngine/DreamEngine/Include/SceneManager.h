#pragma once
#include "EngineObject.h"
#include "MovableObject/MovableObject.h"
#include "MovableObject/MovableRect.h"
#include "MovableObject/Sprite.h"
#include "MovableObject/FrameAniSprite.h"

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

	CTestMovable*		createTestMovale(const CString& name);
	CSprite*			createSprite(const CString& name, const CString& fileName);
	CFrameAniSprite*	createFrameAniSprite(const CString& name, const char* pFileName, ...);

	virtual void		onRender(float delay);
	virtual void		onLostDevice();
	virtual void		onResetDevice();
	virtual void		onDestory();

	virtual	int			getTriangleCount()const;
	CRenderSystem*		getRenderSystem(void)const	{return m_pRenderSystem;}

protected:

	void				_updateRegisterData(const CRenderData* pRenderData,
											const CMovableObject* pObjOwner);

	void				_onDestoryMoveObject(CMovableObject* pObject);

protected:

	typedef std::list<CMovableObject*> MovableObjectLst;
	MovableObjectLst	m_movableLsts;

	typedef std::vector<CCamera*> CameraLst;
	CameraLst			m_cameras;
	CRenderSystem*		m_pRenderSystem;

	CNode::NodeLst		m_nodes;
};

}

