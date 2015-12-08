#pragma once
#include "ResourceFactory.h"
#include "SpineMesh.h"

namespace DreamEngine
{
class _EngineExport CSpineMeshManager : public CRosourceFactory<CSpineMesh>
{
public:
	CSpineMeshManager(void);
	~CSpineMeshManager(void);

	CSpineMesh*		createFromFile(const CString& name, const CString& altasFile);
	CSpineMesh*		createFromAltas(const CString& name, const CAtlas& altas);

};

}

