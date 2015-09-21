#include "D3D9VideoManager.h"

namespace DreamEngineD3D
{
CD3D9VideoManager::CD3D9VideoManager(CD3D9Device* pDevice):
m_pDevice(pDevice)
{
}


CD3D9VideoManager::~CD3D9VideoManager(void)
{
}

CIndexBuffer* CD3D9VideoManager::createIndexBuffer(HardwareBufferType type/*=TRIANGLE_LIST*/)
{
	CD3D9IndexBuffer* pIndexBuffer = new CD3D9IndexBuffer(m_pDevice, type);
	m_indexBuffers.push_back(pIndexBuffer);

	return pIndexBuffer;
}


CIndexBuffer* CD3D9VideoManager::createIndexBuffer( void* pDate,
													m_uint16 dataCount, 
													m_uint16 strade, 
													HardwareBufferType type/*=TRIANGLE_LIST*/)
{
	CD3D9IndexBuffer* pIndexBuffer = new CD3D9IndexBuffer(m_pDevice, type);

	pIndexBuffer->createBuffer(pDate, dataCount,strade );
	m_indexBuffers.push_back(pIndexBuffer);

	return pIndexBuffer;
}

CVertexBuffer* CD3D9VideoManager::createVertexBuffer(HardwareBufferType type/*=TRIANGLE_LIST*/)
{
	CD3D9VertexBuffer* pVertexBuffer = new CD3D9VertexBuffer(m_pDevice, type);
	m_vertexBuffers.push_back(pVertexBuffer);

	return pVertexBuffer;
}

CVertexBuffer* CD3D9VideoManager::createVertexBuffer(void* pDate, m_uint16 dataCount, 
	m_uint16 strade, HardwareBufferType type/*=TRIANGLE_LIST*/)
{
	CD3D9VertexBuffer* pVertexBuffer = new CD3D9VertexBuffer(m_pDevice, type);

	pVertexBuffer->createBuffer(pDate, dataCount, strade);
	m_vertexBuffers.push_back(pVertexBuffer);

	return pVertexBuffer;
}

CTexture* CD3D9VideoManager::createTexture(const CString& name, 
											TEX_FORMAT texFormat, 
											m_uint16 width, 
											m_uint16 height, 
											RSPOOL pool/* =RSP_MANAGER */,
											m_dwrd usage/* =0 */, 
											m_uint16 mipLevel/* =0 */)
{
	CD3D9Texture* pD3D9Texture = new CD3D9Texture(name, m_pDevice);
	pD3D9Texture->create(texFormat, 
						  width, 
						  height, 
						  pool, 
						  usage, 
						  mipLevel);

	m_textures.push_back(pD3D9Texture);

	return pD3D9Texture;
}

CTexture* CD3D9VideoManager::createTextureFromFile( const CString& name, 
													const CString& fileName, 
													TEX_FORMAT texFormat/*=TF_UNKOWN*/, 
													m_uint16 width/* =0 */,
													m_uint16 height/* =0 */, 
													RSPOOL pool/* =RSP_MANAGER */, 
													m_dwrd usage/* =0 */, 
													m_uint16 mipLevel/* =0 */
												   )
{
	CD3D9Texture* pD3D9Texture = new CD3D9Texture(name, m_pDevice);
	pD3D9Texture->createFromFile(
								  fileName,
								  texFormat, 
								  width, 
							      height, 
								  pool, 
								  usage, 
								  mipLevel);

	m_textures.push_back(pD3D9Texture);

	return pD3D9Texture;
}

}

