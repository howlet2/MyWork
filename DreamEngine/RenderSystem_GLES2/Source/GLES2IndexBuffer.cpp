#include "GLES2IndexBuffer.h"

namespace DreamEngineGLES2
{

CGLES2IndexBuffer::CGLES2IndexBuffer(const CString& name, HardwareBufferType type/*=TRIANGLE_LIST*/):
									CIndexBuffer(name, type),
									m_pIndexs(MATH_NULL)
{

}

CGLES2IndexBuffer::~CGLES2IndexBuffer(void)
{
}

bool CGLES2IndexBuffer::createBuffer(void* pData, m_uint16 count, m_uint16 strade)
{
	SAFE_DELETE_ARRY(m_pIndexs)

	m_dataCount = count;
	m_strade	= strade;

	DreamEngine::IndexBufferType type = static_cast<IndexBufferType>(strade);
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
	memcpy(m_pIndexs, pData, m_strade*m_dataCount);

	return true;
}



void CGLES2IndexBuffer::destroy()
{
	SAFE_DELETE(m_pIndexs);
}

void CGLES2IndexBuffer::active()
{
	//m_pDevice->GetD3DDevice()->SetIndices(m_pIndexBuffer); 
}

IndexBufferType CGLES2IndexBuffer::getBufferType()const
{
	return static_cast<IndexBufferType>(m_strade);
}

}
