#include "SpineMesh.h"
#include "VideoManager.h"
#include "MaterialManager.h"
#include "GpuProgramManager.h"
#include "GpuTypeManager.h"

namespace DreamEngine
{
CSpineMesh::CSpineMesh(const CString& name):
	m_name(name),
	m_trangleCount(0)
{
}


CSpineMesh::~CSpineMesh(void)
{
}

bool CSpineMesh::createFromFile(const CString& altasFile)
{
	CAtlas atlas;
	atlas.loadFromFile(altasFile);

	return createFromAtlas(atlas);
}

bool CSpineMesh::createFromAtlas(const CAtlas& atlas)
{
	CMaterial* pMaterial = CMaterialManager::instancePtr()->create(m_name+"_spinemesh_material") ;
	m_renderData.m_pMaterial = pMaterial;

	//gpu program
	CGpuProgram* pProgram = CGpuProgramManager::instancePtr()->create(false);
	pProgram->initialize(CGpuTypeManager::instancePtr()->defaultVertex(),
						 CGpuTypeManager::instancePtr()->defaultTextureFragment());
	pMaterial->setGpuProgram(pProgram);

	//texture
	CTexture* pTexture =
		CVideoManager::instancePtr()->createTextureFromFile(m_name+"_spinemesh_texture", atlas.getTextureFilePath());
	pTexture->setTexCoordLayer(0);
	pProgram->getShaderParamTable()->setAddressValue("s_texture", pTexture);

	CAtlas::SliceParamIter sliceIter = atlas.getSliceIter();
	int pointCount = sliceIter.caculateCount()*4;
	SpineMeshVertex* pData = new SpineMeshVertex[pointCount];

	int idx = 0;
	while (sliceIter.hasMore())
	{
		const CAtlas::tSlice& val = sliceIter.current();

		float halfWidth		= val.size._x/2;
		float halfHeigh		= val.size._y/2;
		float left		= (-halfWidth);
		float right		= (halfWidth);
		float top		= (halfHeigh);
		float buttom	= (-halfHeigh);

		float offsetX = val.point._x;
		float offsetY = val.point._y;

		pData[idx].x=left;	 pData[idx].y=top;		pData[idx].z=0.0f;
		pData[idx+1].x=right;pData[idx+1].y=top;	pData[idx+1].z=0.0f;
		pData[idx+2].x=left; pData[idx+2].y=buttom;	pData[idx+2].z= 0.0f;
		pData[idx+3].x=right;pData[idx+3].y=buttom;	pData[idx+3].z=0.0f;
	
		for (int i=0; i<4; ++i)
		{
			pData[idx+i].x += offsetX;
			pData[idx+i].y += offsetY;
		}

		int texWidth	= pTexture->getWidth();
		int texHigth	= pTexture->getHeight();
		float u1	= offsetX/texWidth;
		float v1	= offsetY/texHigth;

		if (!val.isRotate)
		{
			float u2	= (offsetX+val.size._x)/texWidth;
			float v2	= (offsetY+val.size._y)/texHigth;

			pData[idx].u=u1;	pData[idx].v=v2;
			pData[idx+1].u=u1;	pData[idx+1].v=v1;	
			pData[idx+2].u=u2;	pData[idx+2].v=v1;	
			pData[idx+3].u=u2;  pData[idx+3].v=v2;
		}
		else
		{
// 			self->uvs[2] = region->x / (float)page->width;
// 			self->uvs[3] = (region->y + region->width) / (float)page->height;
// 			self->uvs[4] = region->x / (float)page->width;
// 			self->uvs[5] = region->y / (float)page->height;
// 			self->uvs[6] = (region->x + region->height) / (float)page->width;
// 			self->uvs[7] = region->y / (float)page->height;
// 			self->uvs[0] = (region->x + region->height) / (float)page->width;
// 			self->uvs[1] = (region->y + region->width) / (float)page->height;

			float u2		= (offsetX+val.size._y)/texWidth;
			float v2		= (offsetY+val.size._x)/texHigth;

			pData[idx].u=u2;	pData[idx].v=v2;
			pData[idx+1].u=u1;	pData[idx+1].v=v2;	
			pData[idx+2].u=u1;	pData[idx+2].v=v1;	
			pData[idx+3].u=u2;  pData[idx+3].v=v1;
		}
		m_scliceNames.push_back(val.name);
		idx+=4;
		sliceIter.Next();
	}

	m_trangleCount = pointCount/4*2;

 	CVertexBuffer* pBuffer = CVideoManager::instancePtr()->
 		createVertexBuffer(VBUF_NAME, pData, pointCount, sizeof(SpineMeshVertex));

	m_renderData.addVertexBuffer(0, pBuffer);
	SAFE_DELETE_ARRY(pData);

	CIndexBuffer* pIdxBuf = CVideoManager::instancePtr()->
		createIndexBuffer(IBUF_NAME);

	m_byte* pIdxData = new m_byte[m_trangleCount*3];
	for (int i=0; i<m_trangleCount; ++i)
	{
		int idxOff			= i*3;
		int begIdx			= i*2-i%2;
		pIdxData[idxOff]	= begIdx;
		pIdxData[idxOff+1]	= begIdx+1;
		pIdxData[idxOff+2]	= begIdx+2;
	}
	pIdxBuf->createBuffer(pIdxData, m_trangleCount*3, IBT_8);
	m_renderData.addIndexBuffer(pIdxBuf);
	SAFE_DELETE_ARRY(pIdxData);
	
	CVertexElement elem[2] = {	CVertexElement(0, 0, DREAMDECLTYPE_FLOAT3,	DREAMDECLMETHOD_DEFAULT, DREAMDECLUSAGE_POSITION, 0),
		CVertexElement(0, 12, DREAMDECLTYPE_FLOAT2,	DREAMDECLMETHOD_DEFAULT, DREAMDECLUSAGE_TEXCOORD, 0) };
	m_renderData.addElement(elem, 2);

	return true;
}

void CSpineMesh::notifyPosition(const CString& scliceName, const CVector3& position)
{
	SpineMeshVertex* pDate	= _getBufferAddress(scliceName);
	if (pDate != MATH_NULL)
	{
		pDate->x = position._x;
		pDate->y = position._y;
		pDate->z = position._z;
	}
	
}

void CSpineMesh::notifyUV(const CString& scliceName, const CVector2& uv)
{
	SpineMeshVertex* pDate	= _getBufferAddress(scliceName);
	if (pDate != MATH_NULL)
	{
		pDate->u = uv._x;
		pDate->v = uv._y;
	}
}

CSpineMesh::SpineMeshVertex* CSpineMesh::_getBufferAddress(const CString& scliceName)
{
	int		idx = 0;
	for (ScliceNameLst::size_type idx=0; idx<m_scliceNames.size(); ++idx)
	{
		if (scliceName==m_scliceNames[idx])
		{
			CVertexBuffer*	 pBuffer	= m_renderData.getVertexBuffer(0);
			SpineMeshVertex* pAddress	= static_cast<SpineMeshVertex*>(pBuffer->getBufferData());	
			return (pAddress+idx);
		}
	}
	return MATH_NULL;
}

}

