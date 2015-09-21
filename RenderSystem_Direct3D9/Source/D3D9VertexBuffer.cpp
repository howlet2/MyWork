#include "D3D9VertexBuffer.h"

namespace DreamEngineD3D
{
CD3D9VertexBuffer::CD3D9VertexBuffer(CD3D9Device* pDevice, 
									 HardwareBufferType type/*=TRIANGLE_LIST*/):
									 CVertexBuffer(type),
									 m_pDevice(pDevice),
									 m_pVertexBuffer(MATH_NULL)
{
}

CD3D9VertexBuffer::~CD3D9VertexBuffer(void)
{
}


bool CD3D9VertexBuffer::createBuffer(void* pDate, m_uint16 count, m_uint16 strade)
{
	if (m_pDevice==MATH_NULL)return false;
	SAFE_RELEASE(m_pVertexBuffer);

	m_dataCount = count;
	m_strade	= strade;

	if( (m_pDevice->getD3DDevice()->CreateVertexBuffer(m_strade*m_dataCount,0, 0,
		D3DPOOL_MANAGED, &m_pVertexBuffer, MATH_NULL)) < 0)
	{
		return false;
	}
	void* pVBData = MATH_NULL;
	m_pVertexBuffer->Lock(0, m_dataCount*m_strade, &pVBData, 0);
	memcpy(pVBData, pDate, m_dataCount*m_strade);
	m_pVertexBuffer->Unlock();

	return true;
}

void CD3D9VertexBuffer::active(m_uint16 index/*=0*/)
{
	if (m_pDevice==MATH_NULL || m_pVertexBuffer==MATH_NULL)return;

	m_pDevice->getD3DDevice()->SetStreamSource(index, m_pVertexBuffer, 0, m_strade);
}

void CD3D9VertexBuffer::destory()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
}

