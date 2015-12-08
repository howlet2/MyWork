#pragma once
#include "meshloader.h"
#include "MS3D.h"
#include "FileDataStream.h"

namespace DreamEngine
{

class _EngineExport CMS3DMeshLoader : public CMeshLoader
{
public:
	CMS3DMeshLoader(void);
	~CMS3DMeshLoader(void);

	virtual bool loadFromFile(const CString& name,  CMesh* pMesh);

protected:

	void		startLoad(const CString& fileName);
	void		endLoad();

	bool		readHeader(void);
	void		readVertex(void);
	void		readFace(void);
	void		readGroup(void);
	void		readMaterial(void);
	void		readAnimationInfo(void);
	void		readBones(void);
	
	void		parseToMesh(CMesh* pMesh);

protected:

	void		_createMeshVertex(CMesh* pMesh);
	void		_createBone(CMesh* pMesh);

	CFileDataStream m_meshFile;

	MS3DVertex*		m_pVertexs;
	m_uint16		m_vertexNum;

	MS3DFace*		m_pFaces;
	m_uint16		m_faceNum;

	MS3DGroup*		m_pGroups;
	m_uint16		m_groupNum;

	MS3DMaterial*	m_pMaterials;
	m_uint16		m_materialNum;

	float			m_animationFPS;
	float			m_currentTime;
	m_uint32		m_totalFrames;

	MS3DBone*		m_pBones;
	m_uint16		m_boneNum;

//	MS3DMeshVertex* m_pMeshVertex;
};

}

