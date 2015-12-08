#include "Entity.h"
#include "MaterialManager.h"
#include "GpuProgramManager.h"

namespace DreamEngine
{
CEntity::CEntity(CRenderSystem* pRenderSystem, const CString& name):
CMovableObject(pRenderSystem, name)
{
}


CEntity::~CEntity(void)
{
}

void CEntity::onCreate()
{
	m_pMaterial = CMaterialManager::instancePtr()->create("default");

	CGpuProgram* pProgram = CGpuProgramManager::instancePtr()->create(true);

	m_pMaterial->setGpuProgram(pProgram);

	MeshLst::iterator mIter;
	for (mIter=m_meshs.begin(); mIter!=m_meshs.end(); ++mIter)
	{
		CMesh::SubMeshLst::const_iterator sbIter;
		const CMesh::SubMeshLst& subMeshs = (*mIter)->getSubMeshs();

		for (sbIter=subMeshs.begin(); sbIter!=subMeshs.end(); ++sbIter)
		{
			(*sbIter)->getRenderDataPtr()->m_pMaterial = m_pMaterial;
			m_renderData.push_back((*sbIter)->getRenderDataPtr());
		}
	}
	
	m_trangleCount = caculateTrangleCount();
}

void CEntity::onLostDevice()
{

}

void CEntity::onResetDevice()
{

}

void CEntity::onDestroy()
{

}

void CEntity::addMesh(CMesh* pMesh)
{
	if (pMesh != MATH_NULL)
	{
		m_meshs.push_back(pMesh);
		m_trangleCount += pMesh->getTrangleCount();
	}
}


}

