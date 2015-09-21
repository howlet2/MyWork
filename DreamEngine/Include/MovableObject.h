#pragma once
#include "EngineObject.h"
#include "RenderData.h"
#include "RenderSystem.h"
#include "Material.h"
#include "SceneNode.h"

namespace DreamEngine
{

class _EngineExport CMovableObject : public CEngineObject
{
public:
	typedef std::vector<CRenderData*>	RenderDataLst;

	CMovableObject(CRenderSystem* pRenderSystem, const CString& name);
	virtual ~CMovableObject(void);

	//rewrite by child class
	virtual void		onCreate()=0;
	virtual void		onLostDevice()=0;
	virtual void		onResetDevice()=0;
	virtual void		onDestroy()= 0;

	//get name
	const CString&		getName(void)					{return m_name;}

	CSceneNode*			getSceneNode(void)const			{return m_pSceneNode;}
	void				attach(CSceneNode* pNode);
	const CMatrix16&    getWorldTransform(void)const;
	
	CMaterial*			getMaterial(void)const			{return m_pMaterial;}
	void				setMaterial(CMaterial* pMaterial);	

	const RenderDataLst& getRenderData(void)const		{return m_renderData;}
	m_uint16			 getTriangleCount(void)const	{return m_trangleCount;}

	m_uint16			 caculateTrangleCount(void);
		
protected:

	CString				m_name;

	CMaterial*			m_pMaterial;
	CRenderSystem*		m_pRenderSystem;

	CSceneNode*			m_pSceneNode;

	RenderDataLst		m_renderData;
	m_uint16			m_trangleCount;

	static CMatrix16	m_defaultTrans;
};

}
