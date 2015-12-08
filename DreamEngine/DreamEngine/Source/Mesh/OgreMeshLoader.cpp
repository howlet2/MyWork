#include "OgreMeshLoader.h"
#include "OgreMeshDefine.h"
#include "MaterialManager.h"
#include "VideoManager.h"
#include "StringHelper.h"

namespace DreamEngine
{

static DREAMDECLTYPE OgreMeshVEToEngineVE(OgreVertexElementType ogreMeshVE)
{
	switch (ogreMeshVE)
	{
	case VET_FLOAT1:
		return DREAMDECLTYPE_FLOAT1;
	case VET_FLOAT2:
		return DREAMDECLTYPE_FLOAT2;
	case VET_FLOAT3:
		return DREAMDECLTYPE_FLOAT3;
	case VET_FLOAT4:
		return DREAMDECLTYPE_FLOAT4;

	case VET_COLOUR:
		return DREAMDECLTYPE_COLOR;
	case VET_SHORT2:
		return DREAMDECLTYPE_SHORT2;
	case VET_SHORT4:
		return DREAMDECLTYPE_SHORT4;
	case VET_UBYTE4:
		return DREAMDECLTYPE_UBYTE4;

	//case VET_SHORT1:
	//case VET_SHORT3:
	//case VET_COLOUR_ARGB:
	//case VET_COLOUR_ABGR:
	}

	return DREAMDECLTYPE_UNUSED;
}

static DREAMDDECLUSAGE OgreMeshVESToEngineVES(OgreVertexElementSemantic ves)
{
	switch (ves)
	{
	case VES_POSITION:
		return DREAMDECLUSAGE_POSITION;
	case VES_BLEND_WEIGHTS:
		return DREAMDECLUSAGE_BLENDWEIGHT;
	case VES_BLEND_INDICES:
		return DREAMDECLUSAGE_BLENDINDICES;
	case VES_NORMAL:
		return DREAMDECLUSAGE_NORMAL;

	case VES_DIFFUSE:
	case VES_SPECULAR:
		return DREAMDECLUSAGE_COLOR;
	case VES_TEXTURE_COORDINATES:
		return DREAMDECLUSAGE_TEXCOORD;
	case VES_BINORMAL:
		return DREAMDECLUSAGE_BINORMAL;
	case VES_TANGENT:
		return DREAMDECLUSAGE_TANGENT;
	}

	return DREAMDECLUSAGE_UNSUED;
}

static HardwareBufferType OgreRenderOPToEngineOP(OgreOperationType renderType)
{
	return static_cast<HardwareBufferType>(renderType);
}

COgreMeshLoader::COgreMeshLoader():
m_pCurMesh(MATH_NULL)
{
}


COgreMeshLoader::~COgreMeshLoader(void)
{
}

bool COgreMeshLoader::loadFromFile(const CString& fileName, CMesh* pMesh)
{
	m_pCurMesh	=	pMesh;
	if (m_pCurMesh == MATH_NULL) return false;

	startLoad(fileName);


	return true;
}

void COgreMeshLoader::startLoad(const CString& fileName)
{
	m_meshFile.open(fileName, CFileDataStream::READ_BINARY);

	if (m_meshFile.getOffset() != 0)
		return;
	
	 //file header
	 m_uint16 headerID;
	 m_meshFile.read(&headerID, sizeof(m_uint16));

	 //MeshSerializer_v1.41
	 CString ver;
	 m_meshFile.readString(ver, '\n');
	 CStringHelper::trimString(ver);

	 if (!m_meshFile.isEnd())
	 {
		 m_uint16 stream = readChunk();
		 dealChunk(stream);
	 }

}

void COgreMeshLoader::endLoad()
{
	m_meshFile.close();
}

m_uint16 COgreMeshLoader::readChunk()
{
	
	m_uint16 id;
	m_meshFile.read(&id, sizeof(m_uint16));

	m_meshFile.read(&m_curstreamLen, sizeof(int));

	return id;
	
}

void  COgreMeshLoader::backReadChunk()
{
	int chunkSize = static_cast<int>((sizeof(m_uint16)+sizeof(int)));
	m_meshFile.seek(-chunkSize, CFileDataStream::CUR);
}

void COgreMeshLoader::dealChunk(m_uint16 stream)
{
	switch (stream)
	{
	case M_MESH:
		{
			readMesh();
		}break;
	}
}

CMesh* COgreMeshLoader::readMesh()
{
	bool isUseAnimation = false;
	m_meshFile.read(&isUseAnimation, sizeof(bool));

	m_uint16 streamID;
	if (!m_meshFile.isEnd())
	{
		streamID = readChunk();

		while(!m_meshFile.isEnd() &&
			(streamID == M_GEOMETRY ||
			streamID == M_SUBMESH ||
			streamID == M_MESH_SKELETON_LINK ||
			streamID == M_MESH_BONE_ASSIGNMENT ||
			streamID == M_MESH_LOD ||
			streamID == M_MESH_BOUNDS ||
			streamID == M_SUBMESH_NAME_TABLE ||
			streamID == M_EDGE_LISTS ||
			streamID == M_POSES ||
			streamID == M_ANIMATIONS ||
			streamID == M_TABLE_EXTREMES))
		{
			switch (streamID)
			{
			case M_SUBMESH:
				{
					m_pCurMesh->addSubMesh(readSubMesh());
				}break;
			}

			if (!m_meshFile.isEnd())
			{
				streamID = readChunk();
			}
		}

		if (!m_meshFile.isEnd())
		{
			backReadChunk();
		}
	}

	return MATH_NULL;
}

CSubMesh* COgreMeshLoader::readSubMesh()
{
	CSubMesh* pSubMesh = new CSubMesh;

	//material
	CString material; 
	m_meshFile.readString(material, '\n');
	CStringHelper::trimString(material);

	CRenderData* pRenderData = pSubMesh->getRenderDataPtr();
	pRenderData->m_pMaterial = CMaterialManager::instancePtr()->create(material);

	bool useSharedVertices;
	m_meshFile.read(&useSharedVertices, sizeof(bool));

	m_uint32 idxCount = 0;
	m_meshFile.read(&idxCount, sizeof(m_uint32));

	bool	 idx32bit   = false;
	m_meshFile.read(&idx32bit, sizeof(bool));

	//build index buffer
	if (idxCount > 0)
	{
		m_uint16 idxBufSize = idx32bit?sizeof(m_uint32):sizeof(m_uint16);
		CIndexBuffer* pIdxBuf = CVideoManager::instancePtr()->createIndexBuffer("");

		void*	pData = MATH_NULL;
		if (idx32bit)
			pData = new m_uint32[idxCount];
		else
			pData = new m_uint16[idxCount];

		m_meshFile.read(pData, idxBufSize*idxCount);
		pIdxBuf->createBuffer(pData, m_uint16(idxCount), idxBufSize);

		SAFE_DELETE_ARRY(pData)
		pSubMesh->getRenderDataPtr()->addIndexBuffer(pIdxBuf);
	}

	if (!useSharedVertices)
	{
		int stream = readChunk();
		if (stream != M_GEOMETRY) return MATH_NULL;

		readGeometry(pSubMesh);
	}

	if (!m_meshFile.isEnd())
	{
		int stream = readChunk();
		while(!m_meshFile.isEnd() &&
			 (stream == M_SUBMESH_BONE_ASSIGNMENT ||
			  stream == M_SUBMESH_OPERATION ||
			  stream == M_SUBMESH_TEXTURE_ALIAS))
		{
			switch(stream)
			{
			case M_SUBMESH_OPERATION:
				readSubMeshOperation(pSubMesh);
				break;
			case M_SUBMESH_BONE_ASSIGNMENT:
				//readSubMeshBoneAssignment(stream, pMesh, sm);
				break;
			case M_SUBMESH_TEXTURE_ALIAS:
				//readSubMeshTextureAlias(stream, pMesh, sm);
				break;
			}

			if (!m_meshFile.isEnd())
			{
				stream = readChunk();
			}

		}
		if (!m_meshFile.isEnd())
		{
			// Backpedal back to start of stream
			backReadChunk();
		}
	}

	return pSubMesh;
}

void COgreMeshLoader::readGeometry(CSubMesh* pSubMesh)
{
	if (pSubMesh == MATH_NULL)return;

	m_uint32 vertexCount = 0;
	m_meshFile.read(&vertexCount, sizeof(vertexCount));

	if (!m_meshFile.isEnd())
	{
		m_uint16 streamID = readChunk();
		while(!m_meshFile.isEnd() &&
			 (streamID == M_GEOMETRY_VERTEX_DECLARATION ||
			  streamID == M_GEOMETRY_VERTEX_BUFFER ))
		{
			switch (streamID)
			{
			case M_GEOMETRY_VERTEX_DECLARATION:
				readGeometryVertexDeclaration(pSubMesh);
				break;
			case M_GEOMETRY_VERTEX_BUFFER:
				readGeometryVertexBuffer(pSubMesh, vertexCount);
				break;
			}

			if (!m_meshFile.isEnd())
			{
				streamID = readChunk();
			}
		}
		if (!m_meshFile.isEnd())
		{
			backReadChunk();
		}
	}

	//// Perform any necessary colour conversion for an active rendersystem
	//if (Root::getSingletonPtr() && Root::getSingleton().getRenderSystem())
	//{
	//	// We don't know the source type if it's VET_COLOUR, but assume ARGB
	//	// since that's the most common. Won't get used unless the mesh is
	//	// ambiguous anyway, which will have been warned about in the log
	//	dest->convertPackedColour(VET_COLOUR_ARGB, 
	//		VertexElement::getBestColourVertexElementType());
	//}
}

void COgreMeshLoader::readGeometryVertexDeclaration(CSubMesh* pSubMesh)
{
	m_uint16 streamID = readChunk();
	while(!m_meshFile.isEnd() &&
		(streamID == M_GEOMETRY_VERTEX_ELEMENT ))
	{
		switch (streamID)
		{
		case M_GEOMETRY_VERTEX_ELEMENT:
			readGeometryVertexElement(pSubMesh);
			break;
		}
		
		if (!m_meshFile.isEnd())
		{
			streamID = readChunk();
		}
	}
	if (!m_meshFile.isEnd())
	{
		backReadChunk();
	}
}

void COgreMeshLoader::readGeometryVertexBuffer(CSubMesh* pSubMesh, m_uint32 vertexCount)
{
	m_uint16 bindIndex, vertexSize;
	// Index to bind this buffer to
	m_meshFile.read(&bindIndex, sizeof(m_uint16));
	
	// Per-vertex size, must agree with declaration at this index
	m_meshFile.read(&vertexSize, sizeof(m_uint16));

	// Check for vertex data header
	m_uint16 headerID;
	headerID = readChunk();
	if (headerID != M_GEOMETRY_VERTEX_BUFFER_DATA)
		return;

	// Check that vertex size agrees
	//if (dest->vertexDeclaration->getVertexSize(bindIndex) != vertexSize)
	//return;

	void* pData = new m_byte[vertexCount*vertexSize];
	m_meshFile.read(pData, vertexCount*vertexSize);
	CVertexBuffer* pBuffer = CVideoManager::instancePtr()->
		createVertexBuffer("", pData, m_uint16(vertexCount), vertexSize);

	SAFE_DELETE_ARRY (pData)

	pSubMesh->getRenderDataPtr()->addVertexBuffer(bindIndex, pBuffer);

	//// Create / populate vertex buffer

	//CVertexBuffer* pVertex = CVideoManager::InstancePtr()->CreateVertexBuffer()
	//HardwareVertexBufferSharedPtr vbuf;
	//vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(
	//	vertexSize,
	//	dest->vertexCount,
	//	pMesh->mVertexBufferUsage,
	//	pMesh->mVertexBufferShadowBuffer);
	//void* pBuf = vbuf->lock(HardwareBuffer::HBL_DISCARD);
	//stream->read(pBuf, dest->vertexCount * vertexSize);

	//// Set binding
	//dest->vertexBufferBinding->setBinding(bindIndex, vbuf);
}

void COgreMeshLoader::readGeometryVertexElement(CSubMesh* pSubMesh)
{
	m_uint16 source, offset, index, tmp;
	DREAMDECLTYPE	vType;
	DREAMDDECLUSAGE vSemantic;
	
	m_meshFile.read(&source, sizeof(m_uint16));
	m_meshFile.read(&tmp,    sizeof(m_uint16));

	vType = OgreMeshVEToEngineVE(static_cast<OgreVertexElementType>(tmp));
	m_meshFile.read(&tmp,  sizeof(m_uint16));
	vSemantic = OgreMeshVESToEngineVES(static_cast<OgreVertexElementSemantic>(tmp));

	m_meshFile.read(&offset, sizeof(m_uint16));
	m_meshFile.read(&index, sizeof(m_uint16));

	CVertexElement elem[1] = {	CVertexElement(source, m_byte(offset), vType, DREAMDECLMETHOD_DEFAULT, vSemantic, m_byte(index))};
	pSubMesh->getRenderDataPtr()->addElement(elem,1);

}

//---------------------------------------------------------------------
void COgreMeshLoader::readSubMeshOperation(CSubMesh* pSubMesh)
{
	// unsigned short operationType
	m_uint16 opType;
	m_meshFile.read(&opType, sizeof(m_uint16));
	OgreOperationType type = static_cast<OgreOperationType>(opType);
	pSubMesh->getRenderDataPtr()->setRenderType(OgreRenderOPToEngineOP(type));
}

}
