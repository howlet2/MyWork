#pragma once
#include "Mesh.h"
#include "MovableObject.h"

namespace DreamEngine
{
class _EngineExport CEntity : public CMovableObject
{
public:
	CEntity(CRenderSystem* pRenderSystem, const CString& name);
	~CEntity(void);

	//rewrite by child class
	void		onCreate();
	void		onLostDevice();
	void		onResetDevice();
	void		onDestroy();

	void		addMesh(CMesh* pMesh);

protected:

	typedef std::vector<CMesh*> MeshLst;
	MeshLst		m_meshs;
};
}


