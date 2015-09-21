#pragma once

#include "HardwareBuffer.h"
#include "D3D9Device.h"

namespace DreamEngineD3D
{
class _EngineD3D9Export CD3D9VertexBuffer : public DreamEngine::CVertexBuffer
{
public:
	CD3D9VertexBuffer(CD3D9Device* pDevice, 
					  HardwareBufferType type=TRIANGLE_LIST);
	~CD3D9VertexBuffer(void);

	virtual bool			createBuffer(void* pDate, m_uint16 count, m_uint16 strade);
	virtual void			destory(void);
	virtual void			active(m_uint16 index=0);

	virtual void*			getBufferData()const {return m_pVertexBuffer;}

protected:

	IDirect3DVertexBuffer9*			m_pVertexBuffer;
	CD3D9Device*				    m_pDevice;
};
}

