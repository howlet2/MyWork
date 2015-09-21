#pragma once
#include "meshloader.h"
#include "MS3D.h"
#include "FileDataStream.h"

namespace DreamEngine
{

class _EngineExport COgreMeshLoader : public CMeshLoader
{
public:
	COgreMeshLoader(void);
	~COgreMeshLoader(void);

	virtual bool loadFromFile(const CString& fileName,  CMesh* pMesh);

protected:

	void		startLoad(const CString& fileName);
	void		endLoad(void);

	m_uint16	readChunk(void);
	void		backReadChunk(void);
	void		dealChunk(m_uint16 stream);

	CMesh*		readMesh(void);
	CSubMesh*	readSubMesh(void);
	void		readGeometry(CSubMesh* pSubMesh);
	void		readGeometryVertexDeclaration(CSubMesh* pSubMesh);
	void		readGeometryVertexBuffer(CSubMesh* pSubMesh, m_uint32 vertexCount);
	void		readGeometryVertexElement(CSubMesh* pSubMesh);
	void		readSubMeshOperation(CSubMesh* pSubMesh);


protected:

	CFileDataStream		m_meshFile;
	int					m_curstreamLen;
	CMesh*				m_pCurMesh;
};

}

