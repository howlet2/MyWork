#include "D3D9Texture.h"
#include "D3D9RenderSystem.h"
#include "CommonFunction.h"

namespace DreamEngineD3D
{

CD3D9Texture::CD3D9Texture(const CString& name, CD3D9Device* pDevice):
CTexture(name),
m_pDevice(pDevice),
m_pTexture(MATH_NULL)
{
}


CD3D9Texture::~CD3D9Texture(void)
{
}

void CD3D9Texture::release()
{
	SAFE_RELEASE(m_pTexture);
}

void CD3D9Texture::lockTexBuf(TexRect* pTexRect, int mipLevel/* =0 */)
{
	D3DLOCKED_RECT lockedRectDes;
	m_pTexture->LockRect(mipLevel, &lockedRectDes, 0, 0);

	pTexRect->pBits = lockedRectDes.pBits;
	pTexRect->pitch = lockedRectDes.Pitch;
}

void CD3D9Texture::unLockTexBuf(int mipLevel/* =0 */)
{
	m_pTexture->UnlockRect(mipLevel);
}

Error CD3D9Texture::_createTexture( TEX_FORMAT texFormat,
									m_uint32 width,
									m_uint32 height, 
									RSPOOL pool/* =RSP_MANAGER */, 
									m_dwrd usage/* =0 */,
									m_uint16 mipLevel/* =0 */)
{
	D3DFORMAT d3dTexFmt = CCommonFunction::texFormatToD3DFormat(texFormat);
	D3DPOOL   d3dpool	 = CCommonFunction::RSPOOLToD3DPool(pool);

	if ((m_pDevice->getD3DDevice()->CreateTexture(width, height, mipLevel,
		usage, d3dTexFmt, d3dpool, &m_pTexture, MATH_NULL))<0)
	{
		return ERROR_CREATE_TEXTURE_FAILD;
	}

	return ERROR_OK;
}

Error CD3D9Texture::_createTextureFromFile( const CString& fileName, 
											TEX_FORMAT texFormat/*=TF_UNKOWN*/, 
											m_uint32 width/* =0 */, 
											m_uint32 height/* =0 */, 
											RSPOOL pool/* =RSP_MANAGER */, 
											m_dwrd usage/* =0 */, 
											m_uint16 mipLevel/* =0 */)
{
	D3DXIMAGE_INFO srcInfo;
	D3DXGetImageInfoFromFile(fileName.c_str(), &srcInfo);

	D3DFORMAT d3dTexFmt;
	if (texFormat==TF_UNKOWN)
	{
		d3dTexFmt = srcInfo.Format;
		m_format   = CCommonFunction::D3DFormatToTexFormat(d3dTexFmt);
	}
	else
	{
		d3dTexFmt = CCommonFunction::texFormatToD3DFormat(texFormat);
	}

	if (mipLevel<0 || width<=0 || height<=0)
	{
		m_width		= srcInfo.Width;
		m_height	= srcInfo.Height;
	}

	D3DPOOL   d3dpool	 = CCommonFunction::RSPOOLToD3DPool(pool);

	if ((D3DXCreateTextureFromFileEx(m_pDevice->getD3DDevice(), 
											  fileName.c_str(),
											  m_width, m_height, 
											  mipLevel, usage, 
											  d3dTexFmt,
											  d3dpool, 
											  D3DX_DEFAULT, D3DX_DEFAULT,
											  0xFF000000,
											  &srcInfo, MATH_NULL, 
											  &m_pTexture)) < 0)
	{
		return ERROR_CREATE_TEXTURE_FAILD;
	}
	
	return ERROR_OK;
}

}

