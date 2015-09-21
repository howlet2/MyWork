#include "GLES2IndexBuffer.h"

namespace DreamEngineGLES2
{

CGLES2IndexBuffer::CGLES2IndexBuffer(DreamEngine::HardwareBufferType type/*=TRIANGLE_LIST*/):
									CIndexBuffer(type),
									m_pIndexs(MATH_NULL)
{

}

CGLES2IndexBuffer::~CGLES2IndexBuffer(void)
{
}

bool CGLES2IndexBuffer::createBuffer(void* pDate, m_uint16 count, m_uint16 strade)
{
	SAFE_DELETE_ARRY(m_pIndexs)

	m_dataCount = count;
	m_strade	= strade;

	DreamEngine::IndexBufferType type = static_cast<DreamEngine::IndexBufferType>(strade);
	switch (type)
	{
	case DreamEngine::IBT_8:
		{
			m_pIndexs = new m_byte[m_dataCount];
		}break;

	case DreamEngine::IBT_16:
		{
			m_pIndexs = new m_uint16[m_dataCount];
		}break;

	case DreamEngine::IBT_32:
		{
			m_pIndexs = new m_uint32[m_dataCount];
		}break;

	default:
		return false;
	}
	memcpy(m_pIndexs, pDate, m_strade*m_dataCount);

	return true;
}



void CGLES2IndexBuffer::destory()
{
	SAFE_DELETE(m_pIndexs);
}

void CGLES2IndexBuffer::active()
{
	//m_pDevice->GetD3DDevice()->SetIndices(m_pIndexBuffer); 
}

DreamEngine::IndexBufferType CGLES2IndexBuffer::getBufferType()const
{
	return static_cast<DreamEngine::IndexBufferType>(m_strade);
}

}
