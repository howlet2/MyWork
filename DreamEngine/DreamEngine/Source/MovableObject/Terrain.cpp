#include "Terrain.h"
#include "MaterialManager.h"

namespace DreamEngine
{

CVertexElement CTerrain::DefaultTerrainElem[1] = 
{
	CVertexElement(0, 0, DREAMDECLTYPE_FLOAT2, DREAMDECLMETHOD_DEFAULT, DREAMDECLUSAGE_POSITION,0),
};

CTerrain::CTerrain(const CString& name, CRenderSystem* pRenderSystem):
CMovableObject(pRenderSystem, name),
m_pTerrainVertex(MATH_NULL),
m_pVertexBuffer(MATH_NULL),
m_pHighMapTable(MATH_NULL),
m_mapSizeX(0), m_mapSizeY(0),
m_sectionSizeX(0), m_sectionSizeY(0),
m_sectoinSqrtCount(0)
{
	m_worldSize._x=100; m_worldSize._y= 100.0f; m_worldSize._z=100;
}


CTerrain::~CTerrain(void)
{
}

void CTerrain::build(CTexture* pHeighMapTex, m_uint16 sectionSqrtCount)
{
	_initializeData(pHeighMapTex, sectionSqrtCount);
	_buildVertexBuffer(m_sectionSizeX, m_sectionSizeY);
	_buildIndexBuffer(m_sectionSizeX, m_sectionSizeY);
}

void CTerrain::build(const CString& highMapFile, m_uint16 sectoinSqrtCount)
{
	CTexture* pHeighMapTex = CVideoManager::instancePtr()->\
							  createTextureFromFile("tempHighMap", highMapFile);
	
	build(pHeighMapTex, sectoinSqrtCount);
}

void CTerrain::_initializeData(CTexture* pHighMap, m_uint16 sectionSqrtCount)
{
	if (pHighMap==MATH_NULL) return;

	m_sectoinSqrtCount = sectionSqrtCount;

	m_mapSizeX = static_cast<m_uint16>(pHighMap->getWidth()); 
	m_mapSizeY = static_cast<m_uint16>(pHighMap->getHeight());

	m_sectionSizeX = (m_mapSizeX-1)/m_sectoinSqrtCount+1;
	m_sectionSizeY = (m_mapSizeY-1)/m_sectoinSqrtCount+1;

	m_setpSize._x=m_worldSize._x/m_mapSizeX;
	m_setpSize._z=m_worldSize._z/m_mapSizeY;

	m_pHighMapTable = new float[m_mapSizeY*m_mapSizeX];
	ZeroMemory(m_pHighMapTable, sizeof(float)*m_mapSizeX*m_mapSizeY);
	_readHeighValue(pHighMap, m_pHighMapTable);
}

void CTerrain::_readHeighValue(CTexture* pHighMap, float* pHighMapTable)
{
	if (pHighMap==MATH_NULL || pHighMapTable==MATH_NULL) return;

	CColor color;
	
	for(m_uint16 x=0; x<m_mapSizeX; x++ )
	{
		for(m_uint16 y=0; y<m_mapSizeY; y++ )
		{
			pHighMap->getPixelColor(color, x, y);
			m_pHighMapTable[x*m_mapSizeX+y]=color._a/255.0f*m_worldSize._y;
		}
	}
}

void CTerrain::_buildVertexBuffer(m_uint16 sectionSizeX, m_uint16 sectionSizeY)
{
	m_pTerrainVertex = new TerrainVertex[sectionSizeX*sectionSizeY];

	for (m_uint16 i=0; i<sectionSizeX; ++i)
	{
		for (m_uint16 j=0; j<sectionSizeY; ++j)
		{
			m_pTerrainVertex[i*sectionSizeX+j].x = m_setpSize._x*i;
			m_pTerrainVertex[i*sectionSizeX+j].z = m_setpSize._z*j;
		}
	}

	m_pVertexBuffer = CVideoManager::instancePtr()->createVertexBuffer(VBUF_NAME,m_pTerrainVertex, 
		m_sectionSizeX*m_sectionSizeY,
		sizeof(TerrainVertex),
		DreamEngine::TRIANGLE_FAN);
}

void CTerrain::_buildIndexBuffer(m_uint16 sectionSizeX, m_uint16 sectionSizeY)
{
	for (int x=4; x<m_sectionSizeX; x+=8)
	{
		for (int y=4; y<m_sectionSizeY; y+=8)
		{
			CIndexBuffer* pIndexBuffer = CVideoManager::instancePtr()->createIndexBuffer(IBUF_NAME,DreamEngine::TRIANGLE_FAN);
			pIndexBuffer->createSingleFanGrid(x,y, m_sectionSizeX, m_sectionSizeY, 4, 4);
			m_IndexStream.push_back(pIndexBuffer);
		}
	}
}


void CTerrain::onCreate()
{
	m_pMaterial = CMaterialManager::instancePtr()->create("terrainMaterial");


	CGpuProgram* pProgram = CGpuProgramManager::instancePtr()->createAndInitFromFile("Terrain_Vertex.hlsl", "Terrain_Pixel.hlsl");
	m_pMaterial->setGpuProgram(pProgram);

	
	//m_pMaterial->m_isZTestEnble = true;
	CRenderData* pRenderData = new CRenderData;

	pRenderData->addElement(DefaultTerrainElem, 1);
	pRenderData->addVertexBuffer(0, m_pVertexBuffer);

	for (int i=0; i<int(m_IndexStream.size()); ++i)
		pRenderData->addIndexBuffer(m_IndexStream[i]);

	pRenderData->m_pMaterial = m_pMaterial;

	m_renderData.push_back(pRenderData);

	m_trangleCount = caculateTrangleCount();
}

void CTerrain::onLostDevice()
{

}

void CTerrain::onResetDevice()
{

}

void CTerrain::onDestroy()
{

}
}