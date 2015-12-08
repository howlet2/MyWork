#pragma once
#include "VideoManager.h"
#include "D3D9IndexBuffer.h"
#include "D3D9VertexBuffer.h"
#include "D3D9Device.h"
#include "D3D9Texture.h"
using namespace DreamEngine;

namespace DreamEngineD3D
{
class CD3D9VideoManager : public CVideoManager
{
public:
	CD3D9VideoManager(CD3D9Device* pDevice);
	~CD3D9VideoManager(void);

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

	CD3D9Device*			m_pDevice;

};
}


