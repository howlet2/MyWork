#pragma once
#include "TerrainSection.h"
#include "MovableObject.h"
#include "HardwareBuffer.h"
#include "Texture.h"

namespace DreamEngine
{

struct TerrainVertex
{
	float x, z;
};

class _EngineExport CTerrain : public CMovableObject
{
public:
	CTerrain(const CString& name, CRenderSystem* pRenderSystem);
	~CTerrain(void);

	void		build(CTexture* pHighMap, m_uint16 sectoinSqrtCount);
	void		build(const CString& highMapFile, m_uint16 sectoinSqrtCount);
	float		getHeighAt(int x, int y);

	void		onCreate();
	void		onLostDevice();
	void		onResetDevice();
	void		onDestroy();

protected:


	void		_initializeData(CTexture* pHighMap, m_uint16 sectoinSqrtCount);

	void		_readHeighValue(CTexture* pHighMap, float* pHighMapTable);
	void		_buildVertexBuffer(m_uint16 mapSizeX, m_uint16 mapSizeY);
	void		_buildIndexBuffer(m_uint16 sectionSizeX, m_uint16 sectionSizeY);

protected:

	TerrainVertex*				m_pTerrainVertex;
	CVertexBuffer*				m_pVertexBuffer;
	CRenderData::IndexStream	m_IndexStream;

	float*						m_pHighMapTable;
	CVector3					m_worldSize;
	CVector3					m_setpSize;

	m_uint16					m_mapSizeX;
	m_uint16					m_mapSizeY;
	m_uint16					m_sectionSizeX;
	m_uint16					m_sectionSizeY;
	m_uint16					m_sectoinSqrtCount;

	static CVertexElement		DefaultTerrainElem[1];
};

}

