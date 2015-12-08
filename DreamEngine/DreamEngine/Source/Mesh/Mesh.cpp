#include "Mesh.h"

namespace DreamEngine
{

CVertexElement CMesh::DefaultMeshElem[2] = 
{
	CVertexElement(0, 0,  DREAMDECLTYPE_FLOAT3,DREAMDECLMETHOD_DEFAULT,DREAMDECLUSAGE_POSITION,0),
	//CVertexElement(0, 12, DREAMDECLTYPE_FLOAT3,DREAMDECLMETHOD_DEFAULT,DREAMDECLUSAGE_NORMAL,0),
	CVertexElement(0, 24, DREAMDECLTYPE_FLOAT2,DREAMDECLMETHOD_DEFAULT,DREAMDECLUSAGE_TEXCOORD,0)
};

CMesh::CMesh(const CString& name):
	m_name(name),
	m_trangleCount(0)
{
	m_pSkeleton = new CSkeleton;
}


CMesh::~CMesh(void)
{
	SAFE_DELETE(m_pSkeleton);
}

void CMesh::loadFromFile(CMeshLoader* pMeshLoader, const CString& fileName)
{
	if (pMeshLoader==MATH_NULL) return;
	
	pMeshLoader->loadFromFile(fileName, this);
}

void CMesh::destory()
{
	for (SubMeshLst::iterator iter=m_subMeshs.begin(); iter!=m_subMeshs.end(); ++iter)
	{
		SAFE_DELETE(*iter);
		m_trangleCount = 0;
	}
}

void CMesh::addSubMesh(CSubMesh* pSubMesh)
{
	if (pSubMesh != MATH_NULL)
	{
		m_subMeshs.push_back(pSubMesh);

		m_trangleCount += pSubMesh->getRenderDataPtr()->caculateTrangleCount();
	}
}
}