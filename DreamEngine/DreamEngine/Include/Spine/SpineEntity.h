#pragma once
#include "SpineMesh.h"
#include "MovableObject.h"
#include "SpineMeshManager.h"
#include "SpineSkeleton.h"

namespace DreamEngine
{

class _EngineExport CSpineEntity : public CMovableObject
{
public:

	typedef std::vector<CSpineMesh*> SpineMeshLst;

public:
	CSpineEntity(CRenderSystem* pRenderSystem, const CString& name);
	~CSpineEntity(void);

	void					addMesh(CSpineMesh* pSpineMesh);
	const	SpineMeshLst&	getMeshLst(void)const		{return m_meshs;}

	void					setSkeleton(CSpineSkeleton* pSkeleton);
	CSpineSkeleton*			getSkeleton(void)const		{return m_pSkeleton;}

	void		onCreate();
	void		onLostDevice();
	void		onResetDevice();
	void		onDestroy();

private:

	
	SpineMeshLst		m_meshs;

	CSpineSkeleton*		m_pSkeleton;
};
}

