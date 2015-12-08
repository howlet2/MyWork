#include "VertexElement.h"

namespace DreamEngine
{
CVertexElement::CVertexElement(void):
m_stream(0xFF), m_offset(0), m_type(DREAMDECLTYPE_UNUSED), m_method(0), \
	m_usage(0), m_usageIndex(0)
{
}

CVertexElement::CVertexElement(m_uint16 stream, m_uint16 offset, m_byte type, m_byte method,\
	m_byte usage, m_byte usageIndex):
	m_stream(stream), m_offset(offset), m_type(type), m_method(method), \
	m_usage(usage), m_usageIndex(usageIndex)
{

}


CVertexElement::~CVertexElement(void)
{
}

void CVertexElement::toEndDeclElement()
{
	m_stream=0xFF; m_offset=0; m_type=DREAMDECLTYPE_UNUSED; m_method=0;
	m_usage=0; m_usageIndex=0;
}

}
