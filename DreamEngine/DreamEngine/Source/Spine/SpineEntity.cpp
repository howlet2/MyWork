#include "SpineEntity.h"
#include "Root.h"

namespace DreamEngine
{
CSpineEntity::CSpineEntity(CRenderSystem* pRenderSystem, const CString& name):
	CMovableObject(pRenderSystem, name),
		m_pSkeleton(MATH_NULL)
{
}


CSpineEntity::~CSpineEntity(void)
{
	//CSpineSkeletonManager::instancePtr()->
}

void CSpineEntity::addMesh(CSpineMesh* pSpineMesh)
{
	m_meshs.push_back(pSpineMesh);
	m_trangleCount += pSpineMesh->getTrangleCount();
}

void CSpineEntity::setSkeleton(CSpineSkeleton* pSkeleton)
{
	m_pSkeleton = pSkeleton;

	const CSpineSkeleton::SpineSlotLst& slots = m_pSkeleton->getSpineSlotLst();
	for (CSpineSkeleton::SpineSlotLst::size_type i=0; i<slots.size(); ++i)
	{
		SpineMeshLst::iterator mIter;
		for (mIter=m_meshs.begin(); mIter!=m_meshs.end(); ++mIter)
		{
			CSpineBone* pBone = static_cast<CSpineBone*>(m_pSkeleton->getRootBone()->findNode(slots[i]->getBoneName()));
			if (pBone != nullptr)
			{
				//(*mIter)->notifyPosition(slots[i]->getAttachMent(), pBone->getPosition());
			}
		}
	}
}


void CSpineEntity::onCreate()
{
	SpineMeshLst::iterator mIter;
	for (mIter=m_meshs.begin(); mIter!=m_meshs.end(); ++mIter)
			m_renderData.push_back(const_cast<CRenderData*>((*mIter)->getRenderDataPtr()));

	m_trangleCount = caculateTrangleCount();
}

void CSpineEntity::onLostDevice()
{

}

void CSpineEntity::onResetDevice()
{

}

void CSpineEntity::onDestroy()
{
	SpineMeshLst::iterator mIter;
	for (mIter=m_meshs.begin(); mIter!=m_meshs.end(); ++mIter)
	{
		//CSpineMeshManager::instancePtr()->destory((*mIter)->getName());
			//(*mIter)->destory();
	}
}

}

