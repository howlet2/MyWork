#include "D3D9Device.h"
#include "d3d9types.h"
#include "CommonFunction.h"

namespace DreamEngineD3D
{
CD3D9Device::CDeviceSetting::CDeviceSetting()
{
	DeviceType		= D3DDEVTYPE_HAL;
	BehaviorFlag	= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	Windowed		= TRUE;
	BackBufferCount = 1;
	SwapEffect		= D3DSWAPEFFECT_DISCARD;  

	isImmitPreant	= false;
	MultiSampleType = D3DMULTISAMPLE_NONE;
	AutoDepthStencilFormat = D3DFMT_D16;
}

CD3D9Device::CDeviceSetting::~CDeviceSetting()
{

}

CD3D9Device::CD3D9Device(void):
m_pDevice(MATH_NULL)
{

}


CD3D9Device::~CD3D9Device()
{

}

Error CD3D9Device::initialize(CD3D9RenderWindow* pD3D9RenderWindow, const CDeviceSetting* pDeviceSetting)
{
	if (pD3D9RenderWindow==MATH_NULL || pDeviceSetting==MATH_NULL 
		|| CD3D9RenderSystem::getD3D9() == MATH_NULL)
	{
		return ERROR_HAVE_NULL_POINT;
	}

	IDirect3D9* pd3d = CD3D9RenderSystem::getD3D9();
	if (pd3d == MATH_NULL)
	{
		return ERROR_HAVE_NULL_POINT;
	}

	D3DDISPLAYMODE mode;
	pd3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);

	::ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
	m_d3dpp.Windowed                   = pDeviceSetting->Windowed;
	if (m_d3dpp.Windowed)
	{
		m_d3dpp.BackBufferWidth        = 0;
		m_d3dpp.BackBufferHeight       = 0;
	}
	else
	{
		m_d3dpp.BackBufferWidth			= mode.Width;
		m_d3dpp.BackBufferHeight		= mode.Height;
	}
	m_d3dpp.BackBufferFormat           = mode.Format;
	m_d3dpp.BackBufferCount            = pDeviceSetting->BackBufferCount;
	m_d3dpp.SwapEffect                 = pDeviceSetting->SwapEffect; 
	m_d3dpp.hDeviceWindow              = pD3D9RenderWindow->getWindowModule();
	m_d3dpp.MultiSampleType            = pDeviceSetting->MultiSampleType;
	m_d3dpp.MultiSampleQuality         = 0;
	m_d3dpp.EnableAutoDepthStencil     = true; 
	m_d3dpp.AutoDepthStencilFormat     = pDeviceSetting->AutoDepthStencilFormat;
	m_d3dpp.Flags                      = 0;
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	if (pDeviceSetting->isImmitPreant)
	{
		m_d3dpp.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		m_d3dpp.PresentationInterval	= D3DPRESENT_INTERVAL_DEFAULT;
	}

	if ((pd3d->CreateDevice(D3DADAPTER_DEFAULT, pDeviceSetting->DeviceType,\
		pD3D9RenderWindow->getWindowModule(), \
		pDeviceSetting->BehaviorFlag, &m_d3dpp, &m_pDevice)) < 0)
	{
		return ERROR_CREATE_DEVICE_FAILD;
	}

	
	return ERROR_OK;
}

void CD3D9Device::shutDown()
{
	SAFE_RELEASE(m_pDevice);
}

void CD3D9Device::createVertexDeclaration(IDirect3DVertexDeclaration9* &pDecl, 
										  const CVertexBuffer::ElementLst& elementLst)
{
	if (m_pDevice == MATH_NULL)
		return;

	m_uint16 count = m_uint16(elementLst.size())+1;
	D3DVERTEXELEMENT9* pElem = new D3DVERTEXELEMENT9[count];
	CCommonFunction::vertexElementToD3D9Element(pElem, elementLst, true);

	m_pDevice->CreateVertexDeclaration(pElem, &pDecl);
	SAFE_DELETE_ARRY(pElem);
}

Error CD3D9Device::testDeviceIsLost()
{
	if (m_pDevice == MATH_NULL)
	{
		return ERROR_HAVE_NULL_POINT;
	}

	switch (m_pDevice->TestCooperativeLevel())
	{
	case D3D_OK:
		{
			return ERROR_DEVICE_TEST_OK;
		}break;

	case D3DERR_DEVICELOST:
		{
			return ERROR_DEVICE_TEST_LOST;
		}break;

	case D3DERR_DEVICENOTRESET:
		{
			//destory resource here...
			m_pDevice->Reset(&m_d3dpp);
			//reset resource here...

			return ERROR_DEVICE_TEST_CAN_NOT_REST;
		}break;
	default:
		{
			return ERROR_UNKONW;
		}break;
	}

	return ERROR_DEVICE_TEST_OK;
}

}
