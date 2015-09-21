#pragma once
#include "GLES2Define.h"
#include "HardwareBuffer.h"

namespace DreamEngineGLES2
{
class _EngineGLES2Export CGLES2IndexBuffer : public DreamEngine::CIndexBuffer
{
public:

	CGLES2IndexBuffer(DreamEngine::HardwareBufferType type=DreamEngine::TRIANGLE_LIST);
	~CGLES2IndexBuffer(void);

	virtual bool				createBuffer(void* pDate, m_uint16 count, m_uint16 strade);
	virtual void				destory();
	virtual void				active();
		
	virtual void*				getBufferData()const	{return m_pIndexs;}

	DreamEngine::IndexBufferType getBufferType()const;
protected:

	void*		m_pIndexs;
};
}

