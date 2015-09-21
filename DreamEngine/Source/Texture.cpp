#include "Texture.h"

namespace DreamEngine
{


CTexture::CTexture(const CString& name):
	m_name(name),
	m_format(TF_R8G8B8),
	m_width(0),
	m_height(0),
	m_usage(0),
	m_mipLevels(0),
	m_texCoordLayer(0),
	m_pool(RSP_MANAGER)
{
	ZeroMemory(&m_texRect, sizeof(m_texRect));
}

CTexture::~CTexture(void)
{

}

Error	CTexture::create(
						 TEX_FORMAT		texFormat, 
						 m_uint32		width, 
						 m_uint32		height, 
						 RSPOOL			pool/*=RSP_MANAGER*/,
						 m_dwrd			usage/*=0*/, 
						 m_uint16		mipLevel/*=0*/)
{
	m_format	=	texFormat;
	m_width		=	width;
	m_height	=	height;
	m_usage		=	usage;
	m_pool		=	pool;
	m_mipLevels	=	mipLevel;

	return _createTexture(texFormat, width, height, pool, usage, mipLevel);
}

Error CTexture::createFromFile(
								const CString&	fileName, 
								TEX_FORMAT		texFormat/*=TF_UNKOWN*/, 
								m_uint32		width/*=0*/, 
								m_uint32		height/*=0*/,
								RSPOOL			pool/*=RSP_MANAGER*/,
								m_dwrd			usage/*=0*/, 
								m_uint16		mipLevel/*=0*/)
{
	m_format	=	texFormat;
	m_width		=	width;
	m_height	=	height;
	m_usage		=	usage;
	m_pool		=	pool;
	m_mipLevels	=	mipLevel;

	return _createTextureFromFile(fileName, texFormat, width, height, pool, usage, mipLevel);
}

CColor CTexture::getPixelColor(int x, int y)
{
	int pixelByte = caculatePixelByte(this);
	lockTexBuf(&m_texRect);
	m_byte* pDestData = static_cast<m_byte*>(m_texRect.pBits);

	m_dwrd color = 0;
	if (pDestData != NULL)
	{
		for (int iRepeat=0; iRepeat<pixelByte; ++iRepeat)
		{
			color <<= 8;
			color |= pDestData[(y*m_texRect.pitch)+(x*pixelByte)+iRepeat];
		}
	}
	unLockTexBuf(0);

	return color;
}

void CTexture::getPixelColor(MATH_OUT CColor& color, int x, int y)
{
	m_dwrd dColor = getPixelColor(x, y)._color;
	m_dwrd mask = 0x000000ff;

	//dColor(r,g,b,a)
	color._a = static_cast<m_byte>(mask&dColor);
	dColor >>= 8;
	color._b =static_cast<m_byte>(mask&dColor);
	dColor >>= 8;
	color._g = static_cast<m_byte>(mask&dColor);
	dColor >>= 8;
	color._r = static_cast<m_byte>(mask&dColor);
}

void CTexture::setPixelColor(int x, int y, const CColor& color)
{
	int pixelByte = caculatePixelByte(this);
	lockTexBuf(&m_texRect);
	m_byte* pDesData = static_cast<m_byte*>(m_texRect.pBits);

	m_dwrd dColor = color._color;
	if (pDesData != NULL)
	{
		for (int iRepeat=0; iRepeat<pixelByte; ++iRepeat)
		{
			m_byte vaule = static_cast<m_byte>((dColor & 0xff000000)>>24);
			pDesData[(y*m_texRect.pitch)+(x*pixelByte)+iRepeat] = vaule;
			dColor <<= 8;
		}
	}
	unLockTexBuf();
}

//void CTexture::CopyFrom(CRenderSystem* pRenderSystem, CTexture* pSourceTexture)
//{
//	if (pSourceTexture!=NULL && this!=pSourceTexture)
//	{
//		D3DSURFACE_DESC d3dsdsrc;
//		pSourceTexture->GetLevelDesc(d3dsdsrc);
//		D3DLOCKED_RECT lockedRectSrc;
//		pSourceTexture->GetD3DTexture()->LockRect(0, &lockedRectSrc, 0, 0);
//		m_byte* pSrcData = static_cast<m_byte*>(lockedRectSrc.pBits);
//		int pixelByte = CaculatePixelByte(pSourceTexture);
//
//		Create(pRenderSystem, d3dsdsrc.Format,d3dsdsrc.Height, d3dsdsrc.Width, d3dsdsrc.Pool, d3dsdsrc.Usage);
//		
//		D3DSURFACE_DESC d3dsddes;
//		GetLevelDesc(d3dsddes);
//		D3DLOCKED_RECT lockedRectDes;
//		m_pTexture->LockRect(0, &lockedRectDes, 0, 0);
//		m_byte* pDestData = static_cast<m_byte*>(lockedRectDes.pBits);
//
//		if (pSrcData!=NULL && pDestData!=NULL)
//		{
//			int sizex = d3dsdsrc.Width<d3dsddes.Width?d3dsdsrc.Width:d3dsddes.Width;
//			int sizey = d3dsdsrc.Height<d3dsddes.Height?d3dsdsrc.Height:d3dsddes.Height;
//
//			for(int y=0; y<sizey; y++ )
//			{
//				for(int x=0; x<sizex; x++ )
//				{
//					for (int iRepeat=0; iRepeat<pixelByte; ++iRepeat)
//					{
//						pDestData[(y*lockedRectDes.Pitch)+(x*pixelByte)+iRepeat] = \
//							pSrcData[(y*lockedRectSrc.Pitch)+(x*pixelByte)+iRepeat];
//					}
//				}
//			}
//			m_pTexture->UnlockRect(0);
//			pSourceTexture->GetD3DTexture()->UnlockRect(0);
//		}
//	}
//}


int CTexture::caculatePixelByte(CTexture* pTexture)
{
	if (pTexture == MATH_NULL)
		return 0;
	
	switch(pTexture->getFormat())
	{
	case TF_A8R8G8B8:
	case TF_X8R8G8B8:
	case TF_X8L8V8U8:
	case TF_R8G8B8A8:
		return 4;

	case TF_R8G8B8:
		return 3;

	case TF_L8:
		return 1;

	default:
		return 0;
	}

	return 0;
}

}
