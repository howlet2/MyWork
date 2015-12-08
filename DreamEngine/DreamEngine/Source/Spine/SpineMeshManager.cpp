#include "SpineMeshManager.h"

namespace DreamEngine
{
CSpineMeshManager::CSpineMeshManager(void)
{
}


CSpineMeshManager::~CSpineMeshManager(void)
{
}

CSpineMesh*	CSpineMeshManager::createFromFile(const CString& name, const CString& altasFile)
{
	CSpineMesh* pSpineMesh = create(name);
	pSpineMesh->createFromFile(altasFile);
	return pSpineMesh;
}

CSpineMesh*	CSpineMeshManager::createFromAltas(const CString& name, const CAtlas& altas)
{
	CSpineMesh* pSpineMesh = create(name);
	pSpineMesh->createFromAtlas(altas);
	return pSpineMesh;
}



}

