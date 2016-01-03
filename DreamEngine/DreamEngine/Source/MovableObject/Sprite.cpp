#include "MovableObject/Sprite.h"
#include "VideoManager.h"
#include "MaterialManager.h"
namespace DreamEngine
{
struct strTextureData
{
	float x, y, z;
	float u, v;
};

CSprite::CSprite(CRenderSystem* pRenderSystem, const CString& name):
	CMovableObject(pRenderSystem, name),
		m_pTexture(nullptr),
		m_bAuotCreate(false)
{
}


CSprite::~CSprite(void)
{
}

void CSprite::onCreate()
{
	CVector2 size;
	if (m_pTexture != MATH_NULL)
	{
		size._x = static_cast<float>(m_pTexture->getWidth());
		size._y = static_cast<float>(m_pTexture->getHeight());
	}
	strTextureData data[4];
	data[0].x=-size._x; data[0].y=size._y;  data[0].z=0.0f; data[0].u = 0.0f; data[0].v=0.0f;
	data[1].x=size._x;	data[1].y=size._y;  data[1].z=0.0f; data[1].u = 1.0f; data[1].v=0.0f;
	data[2].x=-size._x; data[2].y=-size._y; data[2].z=0.0f; data[2].u = 0.0f; data[2].v=1.0f;
	data[3].x=size._x;  data[3].y=-size._y; data[3].z=0.0f; data[3].u = 1.0f; data[3].v=1.0f;

	CRenderData* pRenderData = new CRenderData;
	m_pMaterial = pRenderData->m_pMaterial = CMaterialManager::instancePtr()->create(MATERIAL_NAME);

	CVertexBuffer* pVertexBuffer = CVideoManager::instancePtr()
		->createVertexBuffer(VBUF_NAME,data, 4, sizeof(strTextureData), TRIANGLE_STRIP);
	pRenderData->addVertexBuffer(0, pVertexBuffer);

	m_byte idx[4] = {0,1,2,3};
	CIndexBuffer* pIndxBuffer = CVideoManager::instancePtr()->createIndexBuffer(IBUF_NAME,TRIANGLE_STRIP);
	pIndxBuffer->createBuffer(idx, 4, 1);

	pRenderData->addIndexBuffer(pIndxBuffer);

	CGpuTypeManager* pGpuTypeManager = CGpuTypeManager::instancePtr();
	CGpuProgram* pProgram = CGpuProgramManager::instancePtr()->
		createAndInitialize(pGpuTypeManager->defaultVertex(), pGpuTypeManager->defaultTextureFragment());
	m_pMaterial->setGpuProgram(pProgram);

	if (m_pTexture != MATH_NULL)
	{
		CShaderParam* pParam = pProgram->getShaderParamTable()->getParam("s_texture");
		pParam->setAddressVaule(m_pTexture);
	}
	
	CVertexElement elem[2] = {	CVertexElement(0, 0, DREAMDECLTYPE_FLOAT3,	DREAMDECLMETHOD_DEFAULT, DREAMDECLUSAGE_POSITION, 0),
		CVertexElement(0, 12, DREAMDECLTYPE_FLOAT2,	DREAMDECLMETHOD_DEFAULT, DREAMDECLUSAGE_TEXCOORD, 0) };
	pRenderData->addElement(elem, 2);

	m_renderData.push_back(pRenderData);

	m_trangleCount = caculateTrangleCount();
}

void CSprite::onLostDevice()
{

}

void CSprite::onResetDevice()
{

}

void CSprite::onDestroy()
{
	if (m_bAuotCreate && m_pTexture!=nullptr)
	{
		CVideoManager::instancePtr()->destoryTexture(m_pTexture->getName());
		m_bAuotCreate = false;
	}
	CMovableObject::onDestroy();
}

void CSprite::setTexture(CTexture* pTexture)
{
	if (m_bAuotCreate && m_pTexture!=MATH_NULL)
		CVideoManager::instancePtr()->destoryTexture(m_pTexture->getName());

	if (m_pMaterial != MATH_NULL)
	{
		CShaderParam* pParam = m_pMaterial->getGpuProgram()->getShaderParamTable()->getParam("s_texture");
		pParam->setAddressVaule(m_pTexture);
	}

	m_bAuotCreate = false;
	m_pTexture = pTexture;
}

void CSprite::setTexture(const CString& texFileName)
{
	CTexture* pTexture = CVideoManager::instancePtr()->createTextureFromFile(TEXTURE_NAME, texFileName);
	setTexture(pTexture);
	m_bAuotCreate = true;
}

}
