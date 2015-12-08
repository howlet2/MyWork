#pragma once

#include "D3D9Define.h"
#include "MathEngine.h"
#include "HardwareBuffer.h"
#include "D3D9Device.h"
#include <d3d9.h>
using namespace Math;

namespace DreamEngineD3D
{
class _EngineD3D9Export CD3D9IndexBuffer : public DreamEngine::CIndexBuffer
{

public:

	CD3D9IndexBuffer(const CString& name,
					 CD3D9Device* pDevice, 
					 HardwareBufferType type=TRIANGLE_LIST);
	~CD3D9IndexBuffer(void);

	virtual bool			createBuffer(void* pData, m_uint16 count, m_uint16 strade);	
	virtual void			destroy();
	virtual void			active();

	void*					getBufferData(void)const {return m_pIndexBuffer;}

protected:

	CD3D9Device*			m_pDevice;
	LPDIRECT3DINDEXBUFFER9  m_pIndexBuffer;
};
}

