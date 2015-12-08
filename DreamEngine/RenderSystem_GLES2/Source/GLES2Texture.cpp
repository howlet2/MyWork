#include "GLES2Texture.h"
#include "CommonFunction.h"
#include "Images.h"

namespace DreamEngineGLES2
{

CGLES2Texture::CGLES2Texture(const CString& name):
CTexture(name),
m_texture(0),
m_pData(MATH_NULL)
{
}


CGLES2Texture::~CGLES2Texture(void)
{
}

void CGLES2Texture::release()
{
	glDeleteTextures(1, &m_texture);
	SAFE_DELETE_ARRY(m_pData);
}

void CGLES2Texture::lockTexBuf(TexRect* pTexRect, int mipLevel/* =0 */)
{
	//D3DLOCKED_RECT lockedRectDes;
	//m_pTexture->LockRect(mipLevel, &lockedRectDes, 0, 0);

	m_texRect.pitch = caculatePixelByte(this)*m_width;
	m_texRect.pBits = m_pData;

	pTexRect = &m_texRect;
}

void CGLES2Texture::unLockTexBuf(int mipLevel/* =0 */)
{
	m_texRect.pBits = MATH_NULL;
	m_texRect.pitch = 0;
}

Error CGLES2Texture::_createTexture( TEX_FORMAT texFormat,
									m_uint32 width,
									m_uint32 height, 
									RSPOOL pool/* =RSP_MANAGER */, 
									m_dwrd usage/* =0 */,
									m_uint16 mipLevel/* =0 */)
{
	int piexByte = caculatePixelByte(this);
	int dataSize = width*height*piexByte;

	SAFE_DELETE_ARRY(m_pData)
	m_pData = new GLubyte[dataSize];
	memset(m_pData, 0, dataSize);

	GLint glTexFormat = CCommonFunction::TexFormatToGLES2Format(m_format);
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE0, m_texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, caulateUnpackAlignment(m_width));												
	glTexImage2D(GL_TEXTURE_2D, m_mipLevels, glTexFormat, m_width, m_height, 0, glTexFormat, GL_UNSIGNED_BYTE, m_pData); 

	return ERROR_OK;
}

Error CGLES2Texture::_createTextureFromFile(const CString& fileName, 
											TEX_FORMAT texFormat/*=TF_UNKOWN*/, 
											m_uint32 width/* =0 */, 
											m_uint32 height/* =0 */, 
											RSPOOL pool/* =RSP_MANAGER */, 
											m_dwrd usage/* =0 */, 
											m_uint16 mipLevel/* =0 */)
{
	

	CImages img;
	GLubyte* pData = img.loadFromFile(fileName);
	

	if (m_format==TF_UNKOWN)
		m_format=img.getTexFormat();

	if (m_width==0)
		m_width = img.getWidth();
	if (m_height==0)
		m_height = img.getHeight();

	SAFE_DELETE_ARRY(m_pData)
	int dataSize = m_width*m_height*img.getPixelPerBytes();
	m_pData = new GLubyte[dataSize];
	memset(m_pData, 0, dataSize);
	memcpy(m_pData, pData, dataSize);

	GLint glTexFormat = CCommonFunction::TexFormatToGLES2Format(m_format);
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE0, m_texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, caulateUnpackAlignment(m_width));												
	glTexImage2D(GL_TEXTURE_2D, m_mipLevels, glTexFormat, m_width, m_height, 0, glTexFormat, GL_UNSIGNED_BYTE, m_pData); 

	return ERROR_OK;
}

void CGLES2Texture::setPixelColor(int x, int y, const CColor& color)
{
	CTexture::setPixelColor(x, y, color);

	GLint texFormat = CCommonFunction::TexFormatToGLES2Format(m_format);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, 1, 1, texFormat, GL_UNSIGNED_BYTE, &m_pData[x*m_width+y]);  
}

void CGLES2Texture::setPixelColorRect(int x, int y, int width, int height, void* pDatas)
{
	GLint texFormat = CCommonFunction::TexFormatToGLES2Format(m_format);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, GLint(width), GLint(height), texFormat, GL_UNSIGNED_BYTE, pDatas);
}

int CGLES2Texture::caulateUnpackAlignment(GLint width)
{
	for (int i=1; i<=width; i<<=1)
	{
		if (width%8 != 0)
			return i>>=1;
	}

	return 1;
}

}

