#include "MovableObject/MovableObject.h"

namespace DreamEngine
{
CMatrix16 CMovableObject::m_defaultTrans;

CMovableObject::CMovableObject(CRenderSystem* pRenderSystem, const CString& name):
	m_name(name),
	m_pRenderSystem(pRenderSystem),
	m_pSceneNode(MATH_NULL),
	m_pMaterial(MATH_NULL),
	m_trangleCount(0)
{

}


CMovableObject::~CMovableObject(void)
{
}

void CMovableObject::onDestroy()
{
	RenderDataLst::iterator iter;
	for (iter=m_renderData.begin(); iter!=m_renderData.end(); ++iter)
	{
		(*iter)->destory();
		SAFE_DELETE(*iter);
	}
	m_renderData.clear();
}

void CMovableObject::setTypeName(const CString& typeName)
{
	m_typeName = typeName;
}

void CMovableObject::attach(CSceneNode* pNode)
{
	m_pSceneNode = pNode;
}

const CMatrix16& CMovableObject::getWorldTransform()const
{
	if (m_pSceneNode != MATH_NULL)
	{
		return m_pSceneNode->getDerivedWorldMatrix();
	}
	else
	{
		return m_defaultTrans;
	}
}

m_uint16 CMovableObject::caculateTrangleCount()
{
	m_uint16 trangleCount = 0;
	for (RenderDataLst::const_iterator iter=m_renderData.begin();
		 iter != m_renderData.end(); ++iter)
	{
		trangleCount += (*iter)->caculateTrangleCount();
	}
	
	return trangleCount;
}

}
