#pragma once
#include "Texture.h"
#include "D3D9Device.h"
#include "d3dx9.h"
#include "D3D9Define.h"

using namespace DreamEngine;

namespace DreamEngineD3D
{

class _EngineD3D9Export CD3D9Texture : public CTexture
{
public:
	CD3D9Texture(const CString& name, CD3D9Device* pDevice);
	~CD3D9Texture(void);


	virtual void	release();
	virtual	void	lockTexBuf(TexRect* pTexRect, int mipLevel=0);
	virtual void	unLockTexBuf(int mipLevel=0);
	virtual void*	getTextureBuf(void)const				{return m_pTexture;}

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

protected:

	LPDIRECT3DTEXTURE9		m_pTexture;
	CD3D9Device*			m_pDevice;
};

}

