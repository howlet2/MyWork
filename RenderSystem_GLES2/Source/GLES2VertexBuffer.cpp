#include "GLES2VertexBuffer.h"

namespace DreamEngineGLES2
{
CGLES2VertexBuffer::CGLES2VertexBuffer(DreamEngine::HardwareBufferType type/*=DreamEngine::TRIANGLE_LIST*/):
									 CVertexBuffer(type),
									 m_pDatas(MATH_NULL)
{
}

CGLES2VertexBuffer::~CGLES2VertexBuffer(void)
{
}

//array of structures
bool CGLES2VertexBuffer::createBuffer(void* pDate, m_uint16 count, m_uint16 strade)
{
	m_dataCount = count;
	m_strade	= strade;

	m_pDatas = new m_byte[m_dataCount*m_strade];
	memcpy(m_pDatas, pDate, m_dataCount*m_strade);

	return true;
}

void CGLES2VertexBuffer::active(m_uint16 index/*=0*/)
{
	//glEnableVertexAttribArray(index);
}

void CGLES2VertexBuffer::destory()
{
	SAFE_DELETE_ARRY(m_pDatas)
}
}

