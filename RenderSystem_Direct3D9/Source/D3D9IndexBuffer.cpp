#include "D3D9IndexBuffer.h"

namespace DreamEngineD3D
{

CD3D9IndexBuffer::CD3D9IndexBuffer( CD3D9Device* pDevice, 
									HardwareBufferType type/*=TRIANGLE_LIST*/):
									CIndexBuffer(type),
									m_pDevice(pDevice),
									m_pIndexBuffer(MATH_NULL)
{

}



CD3D9IndexBuffer::~CD3D9IndexBuffer(void)
{
}

bool CD3D9IndexBuffer::createBuffer(void* pDate, m_uint16 count, m_uint16 strade)
{
	if (m_pDevice==MATH_NULL)return false;
	SAFE_RELEASE(m_pIndexBuffer);

	m_dataCount = count;

	D3DFORMAT idxType = strade<=16?D3DFMT_INDEX16:D3DFMT_INDEX32;
	m_strade = strade<=16?m_strade=2:m_strade=4;

	if((m_pDevice->getD3DDevice()->CreateIndexBuffer(m_dataCount*m_strade,
		0, idxType,  
		D3DPOOL_MANAGED, &m_pIndexBuffer,MATH_NULL)) < 0)
	{
		return false;
	}

	void* pVIData = MATH_NULL;
	m_pIndexBuffer->Lock(0, m_dataCount*m_strade, &pVIData, 0);
	memcpy(pVIData, pDate, m_dataCount*m_strade);
	m_pIndexBuffer->Unlock();

	return true;
}



void CD3D9IndexBuffer::destory()
{
	SAFE_RELEASE(m_pIndexBuffer);
}

void CD3D9IndexBuffer::active()
{
	m_pDevice->getD3DDevice()->SetIndices(m_pIndexBuffer); 
}

}
