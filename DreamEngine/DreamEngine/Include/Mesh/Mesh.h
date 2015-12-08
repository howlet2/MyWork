#pragma once
#include "MeshLoader.h"
#include "SubMesh.h"
#include "VertexElement.h"
#include "Skeleton.h"

namespace DreamEngine
{
class CMeshLoader;

struct DefaultMeshVertex
{
	float x,  y,  z;
	//float nx, ny, nz;
	float u, v;
};

class _EngineExport CMesh : public CEngineObject
{
public:

	typedef std::vector<CSubMesh*> SubMeshLst;

	CMesh(const CString& name);
	~CMesh(void);

	void				loadFromFile(CMeshLoader* pMeshLoader, const CString& fileName);
	void				destory(void);

	void				addSubMesh(CSubMesh* pSubMesh);
	const SubMeshLst&	getSubMeshs(void)const				{return m_subMeshs;}

	const CString&		getName(void)const					{return m_name;}

	CSkeleton*			getSkeleton(void)const				{return m_pSkeleton;}
	int					getTrangleCount()const				{return m_trangleCount;}

	static		CVertexElement DefaultMeshElem[2];

protected: 

	SubMeshLst			m_subMeshs;
	CString				m_name;

	CSkeleton*			m_pSkeleton;
	int					m_trangleCount;
};

}


