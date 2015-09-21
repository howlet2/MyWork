#pragma once
#include "EngineError.h"
#include "D3D9Define.h"
#include "D3D9RenderSystem.h"
#include "D3D9RenderWindow.h"
#include "VertexElement.h"
#include "HardwareBuffer.h"
#include "d3d9.h"
using namespace DreamEngine;

namespace DreamEngineD3D
{
class CD3D9RenderWindow;

class _EngineD3D9Export CD3D9Device 
{
public:

	class _EngineD3D9Export CDeviceSetting
	{

	public:
		CDeviceSetting(void);
		~CDeviceSetting(void);

		D3DDEVTYPE		DeviceType;		
		WORD			BehaviorFlag;

		BOOL			Windowed;
		UINT			BackBufferCount;
		D3DSWAPEFFECT   SwapEffect;
		BOOL			isImmitPreant;	//is need immediately render(true get high fps, but use much more CPU)

		D3DMULTISAMPLE_TYPE MultiSampleType;

		D3DFORMAT       AutoDepthStencilFormat;
	};

public:

	CD3D9Device(void);
	virtual ~CD3D9Device(void);

	Error				initialize(CD3D9RenderWindow* pD3D9RenderWindow,
								   const CDeviceSetting* pDeviceSetting);
	void				shutDown(void);
	LPDIRECT3DDEVICE9	getD3DDevice(void)const {return m_pDevice;}

	void				createVertexDeclaration(IDirect3DVertexDeclaration9* &pDecl,
												const CVertexBuffer::ElementLst& elementLst);

	Error				testDeviceIsLost(void);

protected:

	D3DPRESENT_PARAMETERS	m_d3dpp;
	LPDIRECT3DDEVICE9		m_pDevice;
};

}