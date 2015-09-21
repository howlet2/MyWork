#include "D3D9RenderSystem.h"
#include "D3D9VertexBuffer.h"
#include "D3D9IndexBuffer.h"
#include "D3D9HLSLShader.h"
#include "CommonFunction.h"
#include "D3D9HLSLProgram.h"

namespace DreamEngineD3D
{

IDirect3D9*	CD3D9RenderSystem::m_pd3d = MATH_NULL;

CD3D9RenderSystem::CD3D9RenderSystem(void)
{
}


CD3D9RenderSystem::~CD3D9RenderSystem(void)
{
}

Error CD3D9RenderSystem::initialize()
{
	m_pd3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pd3d == MATH_NULL)
	{
		return ERROR_CREATE_D3D_FAILD;
	}

	return ERROR_OK;
}

Error CD3D9RenderSystem::shutDown()
{
	SAFE_RELEASE(m_pd3d);

	return ERROR_OK;
}

CRenderWindow* CD3D9RenderSystem::createRenderWindow(const CString& name,\
	m_uint16 width, m_uint16 heigth, bool isSetActive/*=true*/)
{
	CD3D9RenderWindow* pRenderWindow = new CD3D9RenderWindow(name);
	pRenderWindow->initialize(width, heigth);

	m_pActiveWindow = pRenderWindow;
	m_renderWindows.push_back(pRenderWindow);

	return pRenderWindow;

}

void CD3D9RenderSystem::beginFrame()
{
	LPDIRECT3DDEVICE9 pD3DDevice = static_cast<CD3D9RenderWindow*>(m_pActiveWindow)\
		->getDevice()->getD3DDevice();

	CViewport* pViewport = m_pActiveWindow->getViewport();
	if (pViewport!=MATH_NULL && pViewport->isChanged())
	{
		_setViewport(pViewport);
		pViewport->setChanged(false);
	}

	if (pD3DDevice != MATH_NULL)
	{ 
		pD3DDevice->Clear( 0, MATH_NULL, D3DCLEAR_TARGET, 0x00ffff00, 1.0f, 0 );
		pD3DDevice->BeginScene();
	}
	
}

void CD3D9RenderSystem::endFrame()
{
	LPDIRECT3DDEVICE9 pD3DDevice = static_cast<CD3D9RenderWindow*>(m_pActiveWindow)\
		->getDevice()->getD3DDevice();

	if (pD3DDevice != MATH_NULL)
	{
		pD3DDevice->EndScene();
		pD3DDevice->Present( MATH_NULL, MATH_NULL, MATH_NULL, MATH_NULL );
	}
}

void CD3D9RenderSystem::render(CRenderData* pRenderData)
{
	if (pRenderData==MATH_NULL || pRenderData->isEmpty()) return;
	
	LPDIRECT3DDEVICE9 pDevice = getActiveDevice()->getD3DDevice();
	if (pDevice==MATH_NULL)return;

	_setRenderState(pRenderData->m_pMaterial);
	_activeVertexBuffer(pRenderData);
	_buildShader(pRenderData->m_pMaterial);
	_bulidDeclaration(pRenderData->getElementLst());
	_draw(pRenderData);
}

CD3D9Device* CD3D9RenderSystem::getActiveDevice()const
{
	CD3D9RenderWindow* pD3DRenderWindow = static_cast<CD3D9RenderWindow*>(m_pActiveWindow);
	return pD3DRenderWindow->getDevice();
}

void CD3D9RenderSystem::_setViewport(CViewport* pViewport)
{
	if (pViewport==MATH_NULL)return;

	LPDIRECT3DDEVICE9  pDevice = (static_cast<CD3D9RenderWindow*>(m_pActiveWindow)->getDevice())->getD3DDevice();
	
	D3DVIEWPORT9 vp;
	vp.Height	= DWORD(pViewport->getHeight());
	vp.Width	= DWORD(pViewport->getWidth());
	vp.MaxZ		= pViewport->getMaxZ();
	vp.MinZ		= pViewport->getMinZ();
	vp.X		= pViewport->getLeft();
	vp.Y		= pViewport->getTop();

	pDevice->SetViewport(&vp);
}

void CD3D9RenderSystem::_setRenderState(CMaterial* pMaterial)
{
	if (pMaterial==MATH_NULL)return;

	LPDIRECT3DDEVICE9 pDevice = getActiveDevice()->getD3DDevice();
	pDevice->SetRenderState(D3DRS_ZENABLE, pMaterial->getZTestEnble());
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL(pMaterial->getCullMode()));	
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE(pMaterial->getFillMode()));
}

void CD3D9RenderSystem::_activeVertexBuffer(CRenderData* pRenderData)
{
	if (pRenderData==MATH_NULL)return;

	CRenderData::VertexStream::iterator iter;
	for (iter=pRenderData->m_vertexStream.begin(); 
		iter!=pRenderData->m_vertexStream.end(); ++iter)
	{
		iter->second->active(iter->first);
	}
}

void CD3D9RenderSystem::_buildShader(CMaterial* pMaterial)
{
	if (pMaterial==MATH_NULL) return;

	LPDIRECT3DDEVICE9 pDevice = getActiveDevice()->getD3DDevice();
	
	CD3D9HLSLProgram* pProgram = static_cast<CD3D9HLSLProgram*>(pMaterial->getGpuProgram());
	if (pProgram != MATH_NULL)
	{
		CHLSLVertex*	pVertex = static_cast<CHLSLVertex*>
			(pProgram->getVertexShader());
		CHLSLFragment*	pFragment = static_cast<CHLSLFragment*>
			(pProgram->getFragmentShader());

		IDirect3DVertexShader9* pVertexShader = pVertex?pVertex->getD3D9Shader():MATH_NULL;
		IDirect3DPixelShader9*	pPixelShader =  pFragment?pFragment->getD3D9Shader():MATH_NULL;
		pDevice->SetVertexShader(pVertexShader);
		pDevice->SetPixelShader(pPixelShader);

		if (pProgram !=  MATH_NULL)
			pProgram->update();
	}
}

void CD3D9RenderSystem::_bulidDeclaration(const CVertexBuffer::ElementLst& elementLst)
{
	CD3D9Device* pDevice = getActiveDevice();

	if (pDevice != MATH_NULL)
	{
		IDirect3DVertexDeclaration9* pDecl = MATH_NULL;
		pDevice->createVertexDeclaration(pDecl, elementLst);
		pDevice->getD3DDevice()->SetVertexDeclaration(pDecl);
		pDecl->Release();
	}
}

void CD3D9RenderSystem::_draw(CRenderData* pRenderData)
{
	if (pRenderData==MATH_NULL || pRenderData->isEmpty())return;

	LPDIRECT3DDEVICE9 pDevice = getActiveDevice()->getD3DDevice();

	
	if (!pRenderData->isUseIndexBuffer())
	{
		D3DPRIMITIVETYPE priType =
			CCommonFunction::HDBufTypeToD3DPriType(pRenderData->getRenderType(0));

		m_uint8 streamNum = m_uint8(pRenderData->m_vertexStream.size());
		pDevice->DrawPrimitive(priType, 0, pRenderData->getElemCount(0));
	}
	else
	{
		for (m_uint16 i=0; i<pRenderData->getPatch(); ++i)
		{
			D3DPRIMITIVETYPE priType =
				CCommonFunction::HDBufTypeToD3DPriType(pRenderData->getRenderType(i));

			pRenderData->getIndexBuffer(i)->active();

			pDevice->DrawIndexedPrimitive(priType, 0, 0,
				pRenderData->getVertexBuffer(0)->dataCount(), 0, pRenderData->getElemCount(i));
		}
	}
}
}