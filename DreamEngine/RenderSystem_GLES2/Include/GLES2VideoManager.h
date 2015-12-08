#pragma once
#include "VideoManager.h"
#include "GLES2IndexBuffer.h"
#include "GLES2VertexBuffer.h"

using namespace DreamEngine;

namespace DreamEngineGLES2
{
class _EngineGLES2Export CGLES2VideoManager : public CVideoManager
{
public:
	CGLES2VideoManager(void);
	~CGLES2VideoManager(void);

	//virtual	void		   DestoryAll(){}
	virtual CIndexBuffer*  createIndexBuffer(const CString& name,
											 HardwareBufferType type=TRIANGLE_LIST);
	virtual CIndexBuffer*  createIndexBuffer(const CString& name,
											 void* pData, 
											 m_uint16 dataCount, 
											 m_uint16 strade, 
											 HardwareBufferType type=TRIANGLE_LIST);


	virtual CVertexBuffer* createVertexBuffer(const CString& name,
											  HardwareBufferType type=TRIANGLE_LIST);
	virtual CVertexBuffer* createVertexBuffer(const CString& name,	
											  void* pData,
											  m_uint16 dataCount, 
											  m_uint16 strade, 
											  HardwareBufferType type=TRIANGLE_LIST);


	virtual CTexture*		createTexture(const CString&	name,
										  TEX_FORMAT		texFormat, 
										  m_uint16			width, 
										  m_uint16			height, 
										  RSPOOL			pool=RSP_MANAGER,
										  m_dwrd			usage=0, 
										  m_uint16			mipLevel=0);

	virtual CTexture*		createTextureFromFile(const CString&	name,
												  const CString&	fileName, 
												  TEX_FORMAT		texFormat=TF_UNKOWN, 
												  m_uint16			width=0, 
												  m_uint16			height=0,
												  RSPOOL			pool=RSP_MANAGER,
												  m_dwrd			usage=0, 
												  m_uint16			mipLevel=0);

protected:

	//CD3D9Device*			m_pDevice;

};
}


