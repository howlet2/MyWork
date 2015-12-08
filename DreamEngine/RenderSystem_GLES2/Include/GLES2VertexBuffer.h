#pragma once
#include "GLES2Define.h"
#include "HardwareBuffer.h"
#include "GLES2/gl2.h"
using namespace DreamEngine;

namespace DreamEngineGLES2
{
class _EngineGLES2Export CGLES2VertexBuffer : public CVertexBuffer
{
public:
	CGLES2VertexBuffer(const CString& name, HardwareBufferType type=TRIANGLE_LIST);
	~CGLES2VertexBuffer(void);

	virtual bool			createBuffer(void* pDate, m_uint16 count, m_uint16 strade);
	virtual void			destroy(void);
	virtual void			active(m_uint16 index=0);

	virtual void*			getBufferData()const	{return m_pDatas;}

protected:

	void*					m_pDatas;
};
}

