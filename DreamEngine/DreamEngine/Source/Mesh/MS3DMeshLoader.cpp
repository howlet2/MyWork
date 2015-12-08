#include "MS3DMeshLoader.h"
#include "VideoManager.h"

namespace DreamEngine
{

CMS3DMeshLoader::CMS3DMeshLoader():
m_pVertexs(MATH_NULL),
m_pFaces(MATH_NULL),
m_pGroups(MATH_NULL),
m_pMaterials(MATH_NULL),
m_pBones(MATH_NULL),

m_vertexNum(0),
m_faceNum(0),
m_groupNum(0),
m_materialNum(0),

m_animationFPS(0.0f),
m_currentTime(0.0f),
m_totalFrames(0),

m_boneNum(0)

{
}


CMS3DMeshLoader::~CMS3DMeshLoader(void)
{
	
}

void CMS3DMeshLoader::startLoad(const CString& fileName)
{
	m_meshFile.open(fileName, CFileDataStream::READ_BINARY);

	m_pVertexs		=	MATH_NULL;
	m_vertexNum		=	0;

	m_pFaces		=	MATH_NULL;
	m_faceNum		=	0;

	m_pGroups		=	MATH_NULL;
	m_groupNum		=	0;

	m_pMaterials	=	MATH_NULL;
	m_materialNum	=	0;

	m_pBones		=	MATH_NULL;
	m_boneNum		=	0;
}

void CMS3DMeshLoader::endLoad()
{	//m_meshVertexs

	m_meshFile.close();

	SAFE_DELETE_ARRY(m_pBones);
	SAFE_DELETE_ARRY(m_pVertexs);
	SAFE_DELETE_ARRY(m_pFaces);
	SAFE_DELETE_ARRY(m_pGroups);
	SAFE_DELETE_ARRY(m_pMaterials);
}

bool CMS3DMeshLoader::readHeader(void)
{
	// read header
	MS3DHeader		header;
	m_meshFile.read(&header, sizeof(header));
	if(memcmp(header.signature, "MS3D000000", 10))
		return false;

	return true;
}

void CMS3DMeshLoader::readVertex()
{
	//read vertex data
	m_meshFile.read(&m_vertexNum, sizeof(m_vertexNum));
	if (m_vertexNum > 0)
	{
		m_pVertexs = new MS3DVertex[m_vertexNum];
		for (m_uint16 i=0; i<m_vertexNum; ++i)
		{
			m_meshFile.read((m_pVertexs+i), sizeof(MS3DVertex));
		}
	}
}

void CMS3DMeshLoader::readFace()
{
	//read face data
	m_meshFile.read(&m_faceNum, sizeof(m_faceNum));
	if (m_faceNum > 0)
	{
		m_pFaces = new MS3DFace[m_faceNum];
		for (m_uint16 i=0; i<m_faceNum; ++i)
		{
			m_meshFile.read((m_pFaces+i), sizeof(MS3DFace));
		}
	}
}

void CMS3DMeshLoader::readGroup()
{
	m_meshFile.read(&m_groupNum, sizeof(m_groupNum));
	if (m_groupNum > 0)
	{
		m_pGroups = new MS3DGroup[m_groupNum];
		for (m_uint16 i=0; i<m_groupNum; ++i)
		{
			m_meshFile.read((m_pGroups+i), sizeof(m_pGroups->Header));

			m_uint16 numFaces = m_pGroups[i].Header.numFaces;
			m_pGroups[i].pIndices = new unsigned short[numFaces];

			for (m_uint16 j=0; j<numFaces; ++j)
			{
				m_meshFile.read(&m_pGroups[i].pIndices[j], sizeof(unsigned short));
			}
			m_meshFile.read(&m_pGroups[i].material, sizeof(m_pGroups[i].material));
		}
	}
}

void CMS3DMeshLoader::readMaterial()
{
	m_meshFile.read(&m_materialNum, sizeof(m_materialNum));

	if (m_materialNum==0)
	{
		m_materialNum = 1;
		m_pMaterials  = new MS3DMaterial[m_materialNum];
		::ZeroMemory(m_pMaterials, sizeof(MS3DMaterial)*m_materialNum);
		m_pMaterials[0].diffuse[0] = m_pMaterials[0].diffuse[1] = m_pMaterials[0].diffuse[2] = 1.0f;
		if(m_groupNum != 0) 
		{
			for(int i=0;i<m_groupNum; i++)
				m_pGroups[i].material = 0;
		}
	}
	else
	{
		m_pMaterials = new MS3DMaterial[m_materialNum];
		for(int i=0;i<m_materialNum; i++)
		{
			m_meshFile.read(&m_pMaterials[i], sizeof(MS3DMaterial));
		}
	}
}

void CMS3DMeshLoader::readAnimationInfo()
{
	m_meshFile.read(&m_animationFPS,sizeof(m_animationFPS));
	m_meshFile.read(&m_currentTime, sizeof(m_currentTime));
	m_meshFile.read(&m_totalFrames, sizeof(m_totalFrames));
}

void CMS3DMeshLoader::readBones()
{
	m_meshFile.read(&m_boneNum, sizeof(m_boneNum));
	if (m_boneNum != 0)
	{
		m_pBones = new MS3DBone[m_boneNum];
		for (int i=0; i<m_boneNum; ++i)
		{
			m_meshFile.read(m_pBones+i, sizeof(m_pBones[i].Header));

			int numRot = m_pBones[i].Header.numRotFrames;
			if (numRot > 0)
			{
				m_pBones[i].pRotKeyFrames = new MS3DKeyFrame[numRot];
				for (int j=0; j<numRot; ++j)
				{
					m_meshFile.read(&m_pBones[i].pRotKeyFrames[j], sizeof(MS3DKeyFrame));
				}
			}

			int numPos = m_pBones[i].Header.numPosFrames;
			if (numPos > 0)
			{
				m_pBones[i].pPosKeyFrames = new MS3DKeyFrame[numPos];
				for (int j=0; j<numPos; ++j)
				{
					m_meshFile.read(&m_pBones[i].pPosKeyFrames[j], sizeof(MS3DKeyFrame));
				}
			}
		}
	}
}

void CMS3DMeshLoader::parseToMesh(CMesh* pMesh)
{
	if (pMesh == MATH_NULL)return;
	
	_createMeshVertex(pMesh);
	_createBone(pMesh);
}

void CMS3DMeshLoader::_createMeshVertex(CMesh* pMesh)
{
	for (m_uint16 i=0; i<m_groupNum; ++i)
	{
		CSubMesh* pSubMesh = new CSubMesh;

		CRenderData* pRenderData = pSubMesh->getRenderDataPtr(); 
		pRenderData->addElement(CMesh::DefaultMeshElem, 2);

		DefaultMeshVertex* pData = MATH_NULL;
		m_uint16 numFaces	= m_pGroups[i].Header.numFaces;
		m_uint16 numVertex = numFaces*3;
		pData = new DefaultMeshVertex[numVertex];
		for (m_uint16 j=0; j<numFaces; ++j)
		{
			MS3DFace* pFace = &m_pFaces[m_pGroups[i].pIndices[j]];

			if (pFace != MATH_NULL)
			{
				for (int k=0; k<3; ++k)
				{
					int idxOff = j*3+k;
					pData[idxOff].x = m_pVertexs[pFace->vertexIndices[k]].pos[0];
					pData[idxOff].y = m_pVertexs[pFace->vertexIndices[k]].pos[1];
					pData[idxOff].z = m_pVertexs[pFace->vertexIndices[k]].pos[2];

					pData[idxOff].u = pFace[j].u[k];
					pData[idxOff].v = pFace[j].v[k];

					//pData[idxOff].nx = pFace[j].vertexNormals[k][0];
					//pData[idxOff].ny = pFace[j].vertexNormals[k][1];
					//pData[idxOff].nz = pFace[j].vertexNormals[k][2];
				}
			}
		}

		CVertexBuffer* pVertexBuffer = CVideoManager::instancePtr()
			->createVertexBuffer("",pData, numVertex, sizeof(DefaultMeshVertex));

		pRenderData->addVertexBuffer(0, pVertexBuffer);

		SAFE_DELETE_ARRY(pData);

		pMesh->addSubMesh(pSubMesh);
	}
}

void CMS3DMeshLoader::_createBone(CMesh* pMesh)
{
	CBone*  pBones		 =	MATH_NULL;

	if (m_boneNum > 0)
	{
		pBones = new CBone[m_boneNum];

		for(m_uint16 i=0; i<m_boneNum; ++i) 
		{
			pBones[i].setName(m_pBones[i].Header.name);
			pBones[i].rotateYawPitchRoll(m_pBones[i].Header.rotation[0],
										  m_pBones[i].Header.rotation[1],
										  m_pBones[i].Header.rotation[2]);
			
			pBones[i].setPosition(m_pBones[i].Header.position[0],
								   m_pBones[i].Header.position[1],
								   m_pBones[i].Header.position[2]);
		}//for

		for(m_uint16 i=0;i<m_boneNum; ++i) 
		{
			if(m_pBones[i].Header.parent[0]) 
			{
				for(m_uint16 j=0; j<m_boneNum; ++j) 
				{
					if(strcmp(m_pBones[i].Header.parent, m_pBones[j].Header.name)==0)
					{
						// Link sibling
						pBones[i].setSilbling(pBones[j].getChild(0));

						// Link child
						pBones[j].addChild(&pBones[i], false);
					}//if
				}//for
			}//if
		}//for

		pBones[0].updateTransformation();
		pMesh->getSkeleton()->setRootBone(&pBones[0]);
	}
}

bool CMS3DMeshLoader::loadFromFile(const CString& name, CMesh* pMesh)
{
	if (pMesh == MATH_NULL)return false;

	startLoad(name);

	readHeader();
	readVertex();
	readFace();
	readGroup();
	readMaterial();
	readAnimationInfo();
	readBones();
	
	parseToMesh(pMesh);

	endLoad();

	return true;
}

}