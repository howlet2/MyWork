#pragma once
#include "Texture.h"
#include "GLES2Define.h"
#include "GLES2/gl2.h"
using namespace DreamEngine;

namespace DreamEngineGLES2
{

class _EngineGLES2Export CGLES2Texture : public CTexture
{
public:
	CGLES2Texture(const CString& name);
	~CGLES2Texture(void);

	virtual void	release();
	virtual	void	lockTexBuf(TexRect* pTexRect, int mipLevel=0);
	virtual void	unLockTexBuf(int mipLevel=0);
	virtual void*	getTextureBuf(void)const				{return (void*)&m_texture;}

	virtual void    setPixelColor(int x, int y, const CColor& color);
	void			setPixelColorRect(int x, int y, int width, int height, void* pDatas);
	GLuint			getGLTexture(void)const					{return m_texture;}

protected:


	virtual Error	_createTexture( TEX_FORMAT		texFormat, 
									m_uint32		width, 
									m_uint32		height, 
									RSPOOL			pool=RSP_MANAGER,
									m_dwrd			usage=0, 
									m_uint16		mipLevel=0);		

	virtual Error	_createTextureFromFile(	const CString&	fileName, 
											TEX_FORMAT		textureFormat=TF_UNKOWN, 
											m_uint32		width=0, 
											m_uint32		height=0,
											RSPOOL			pool=RSP_MANAGER,
											m_dwrd			usage=0, 
											m_uint16		mipLevel=0);

private:

	int				caulateUnpackAlignment(GLint widht);

protected:

	GLuint					m_texture;
	GLubyte*				m_pData;
};

}

