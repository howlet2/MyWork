#pragma once
#include "EngineObject.h"
#include "RenderSystem.h"
#include "Mesh.h"

namespace DreamEngine
{

class CMesh;

class _EngineExport CMeshLoader : public CEngineObject
{
public:
	CMeshLoader(void);
	virtual ~CMeshLoader(void);

	virtual bool loadFromFile(const CString& name, CMesh* pMesh)=0;

protected:


};
}


