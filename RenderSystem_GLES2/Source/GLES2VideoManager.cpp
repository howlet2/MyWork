#include "GLES2VideoManager.h"
#include "GLES2Texture.h"

namespace DreamEngineGLES2
{
CGLES2VideoManager::CGLES2VideoManager(void)
{
}


CGLES2VideoManager::~CGLES2VideoManager(void)
{
}

CIndexBuffer* CGLES2VideoManager::createIndexBuffer(HardwareBufferType type/*=TRIANGLE_LIST*/)
{
	CGLES2IndexBuffer* pIndexBuffer = new CGLES2IndexBuffer(type);
	m_indexBuffers.push_back(pIndexBuffer);

	return pIndexBuffer;
}


CIndexBuffer* CGLES2VideoManager::createIndexBuffer( void* pDate,
													m_uint16 dataCount, 
													m_uint16 strade, 
													HardwareBufferType type/*=TRIANGLE_LIST*/)
{
	CGLES2IndexBuffer* pIndexBuffer = new CGLES2IndexBuffer( type);

	pIndexBuffer->createBuffer(pDate, dataCount,strade );
	m_indexBuffers.push_back(pIndexBuffer);

	return pIndexBuffer;
}

CVertexBuffer* CGLES2VideoManager::createVertexBuffer(HardwareBufferType type/*=TRIANGLE_LIST*/)
{
	CGLES2VertexBuffer* pVertexBuffer = new CGLES2VertexBuffer(type);
	m_vertexBuffers.push_back(pVertexBuffer);

	return pVertexBuffer;
}

CVertexBuffer* CGLES2VideoManager::createVertexBuffer(void* pDate, m_uint16 dataCount, 
	m_uint16 strade, HardwareBufferType type/*=TRIANGLE_LIST*/)
{
	CGLES2VertexBuffer* pVertexBuffer = new CGLES2VertexBuffer(type);

	pVertexBuffer->createBuffer(pDate, dataCount, strade);
	m_vertexBuffers.push_back(pVertexBuffer);

	return pVertexBuffer;
}

 CTexture* CGLES2VideoManager::createTexture(const CString& name, 
 											TEX_FORMAT texFormat, 
 											m_uint16 width, 
 											m_uint16 height, 
 											RSPOOL pool/* =RSP_MANAGER */,
 											m_dwrd usage/* =0 */, 
 											m_uint16 mipLevel/* =0 */)
 {
 	CGLES2Texture* pGles2Texture = new CGLES2Texture(name);
 	pGles2Texture->create(texFormat, 
 						  width, 
 						  height, 
 						  pool, 
 						  usage, 
 						  mipLevel);
 
 	m_textures.push_back(pGles2Texture);
 
 	return pGles2Texture;
 }

CTexture* CGLES2VideoManager::createTextureFromFile( const CString& name, 
													const CString& fileName, 
													TEX_FORMAT texFormat/*=TF_UNKOWN*/, 
													m_uint16 width/* =0 */,
													m_uint16 height/* =0 */, 
													RSPOOL pool/* =RSP_MANAGER */, 
													m_dwrd usage/* =0 */, 
													m_uint16 mipLevel/* =0 */
												   )
{
	CGLES2Texture* pGles2Texture = new CGLES2Texture(name);
	pGles2Texture->createFromFile(
								  fileName,
								  texFormat, 
								  width, 
							      height, 
								  pool, 
								  usage, 
								  mipLevel);

	m_textures.push_back(pGles2Texture);

	return pGles2Texture;
}

}

