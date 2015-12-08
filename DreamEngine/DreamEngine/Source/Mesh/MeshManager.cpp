#include "MeshManager.h"

namespace DreamEngine
{
CMeshManager::CMeshManager(void)
{
	m_pMeshLoader = new CDreamMeshLoader();
}


CMeshManager::~CMeshManager(void)
{
	SAFE_DELETE(m_pMeshLoader);
}

CMeshManager& CMeshManager::instance(void)
{	
	return (*m_singleton); 
}

CMeshManager* CMeshManager::instancePtr(void)
{ 
	return m_singleton; 
}

CMesh*	CMeshManager::create(const CString& name)
{
	CMesh* pMesh = new CMesh(name);
	m_meshs.push_back(pMesh);

	return pMesh;
}

CMesh*	CMeshManager::createFromFile(const CString& name, const CString& fileName)
{
	CMesh* pMesh = MATH_NULL;

	FileMeshLst::iterator iter = m_filesOfMeshs.find(fileName);
	if (iter != m_filesOfMeshs.end())
		pMesh = iter->second;
	else
	{
		pMesh = new CMesh(name);
		pMesh->loadFromFile(m_pMeshLoader, fileName);

		m_meshs.push_back(pMesh);
		m_filesOfMeshs[name] = pMesh;
	}
	return pMesh;
}

void CMeshManager::destory(const CString& name)
{
	MeshLst::iterator iter;
	for (iter=m_meshs.begin(); iter!=m_meshs.end(); ++iter)
	{
		if ((*iter)->getName()==name)
		{
			SAFE_DELETE(*iter);
			m_meshs.erase(iter);
			break;
		}
	}
}

void CMeshManager::destroyAll()
{
	MeshLst::iterator iter;
	for (iter=m_meshs.begin(); iter!=m_meshs.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_meshs.clear();
}


}

