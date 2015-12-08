#pragma once
#include "GLES2Define.h"
#include "HardwareBuffer.h"
using namespace DreamEngine;

namespace DreamEngineGLES2
{
class _EngineGLES2Export CGLES2IndexBuffer : public CIndexBuffer
{
public:

	CGLES2IndexBuffer(const CString& name, HardwareBufferType type=TRIANGLE_LIST);
	~CGLES2IndexBuffer(void);

	virtual bool				createBuffer(void* pData, m_uint16 count, m_uint16 strade);
	virtual void				destroy();
	virtual void				active();
		
	virtual void*				getBufferData()const	{return m_pIndexs;}

	IndexBufferType				getBufferType()const;
protected:

	void*		m_pIndexs;
};
}

