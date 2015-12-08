#include "MovableObject/MovableRect.h"
#include "MaterialManager.h"
#include "GpuProgramManager.h"
#include "VideoManager.h"
#include "Texture.h"

namespace DreamEngine
{
struct strData
{
	float x, y, z;
	float u, v;
};

CTestMovable::CTestMovable(CRenderSystem* pRenderSystem, const CString& name):
	CMovableObject(pRenderSystem, name)
{
	
}

CTestMovable::~CTestMovable(void)
{
}

void CTestMovable::onCreate()
{
	strData data[4];
	data[0].x=-0.5f; data[0].y=0.5f;  data[0].z=1.0f; data[0].u = 0.0f; data[0].v=0.0f;
	data[1].x=0.5f;	 data[1].y=0.5f;  data[1].z=1.0f; data[1].u = 1.0f; data[1].v=0.0f;
	data[2].x=-0.5f; data[2].y=-0.5f; data[2].z=1.0f; data[2].u = 0.0f; data[2].v=1.0f;
	data[3].x=0.5f;  data[3].y=-0.5f; data[3].z=1.0f; data[3].u = 1.0f; data[3].v=1.0f;
	 
	CRenderData* pRenderData = new CRenderData;
	m_pMaterial = pRenderData->m_pMaterial = CMaterialManager::instancePtr()->create("default");

	CVertexBuffer* pVertexBuffer = CVideoManager::instancePtr()
		->createVertexBuffer(VBUF_NAME,data, 4, sizeof(strData), TRIANGLE_STRIP);
	pRenderData->addVertexBuffer(0, pVertexBuffer);

	m_byte idx[4] = {0,1,2,3};
	CIndexBuffer* pIndxBuffer = CVideoManager::instancePtr()->createIndexBuffer(IBUF_NAME,TRIANGLE_STRIP);
	pIndxBuffer->createBuffer(idx, 4, 1);

	pRenderData->addIndexBuffer(pIndxBuffer);

	
	CGpuTypeManager* pGpuTypeManager = CGpuTypeManager::instancePtr();
	CGpuProgram* pProgram = CGpuProgramManager::instancePtr()->
							createAndInitialize(pGpuTypeManager->defaultVertex(), pGpuTypeManager->defaultTextureFragment());
	m_pMaterial->setGpuProgram(pProgram);

	CVertexElement elem[2] = {	CVertexElement(0, 0, DREAMDECLTYPE_FLOAT3,	DREAMDECLMETHOD_DEFAULT, DREAMDECLUSAGE_POSITION, 0),
							    CVertexElement(0, 12, DREAMDECLTYPE_FLOAT2,	DREAMDECLMETHOD_DEFAULT, DREAMDECLUSAGE_TEXCOORD, 0) };
	pRenderData->addElement(elem, 2);

	m_renderData.push_back(pRenderData);

	m_trangleCount = caculateTrangleCount();
}

void CTestMovable::onLostDevice()
{

}

void CTestMovable::onResetDevice()
{

}


}
