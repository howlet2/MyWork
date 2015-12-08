#pragma once
#include "EngineObject.h"
#include "Images.h"

namespace DreamEngine 
{
class _EngineExport CTexture : public CEngineObject
{

public:

	struct TexRect 
	{
		int     pitch;
		void*   pBits;
	};

	CTexture(const CString& name);
	virtual ~CTexture(void);

	virtual Error	create( TEX_FORMAT		texFormat, 
							m_uint32		width, 
							m_uint32		height, 
							RSPOOL			pool=RSP_MANAGER,
							m_dwrd			usage=0,			
							m_uint16		mipLevel=0);

	virtual Error	createFromFile(const CString&	fileName, 
								   TEX_FORMAT		texFormat=TF_UNKOWN, 
								   m_uint32			width=0, 
								   m_uint32			height=0,
								   RSPOOL			pool=RSP_MANAGER,
								   m_dwrd			usage=0, 
								   m_uint16			mipLevel=0);

	virtual void	release()=0;
	virtual	void	lockTexBuf(TexRect* pTexRect, int mipLevel=0)=0;
	virtual void	unLockTexBuf(int mipLevel=0)=0;
	virtual void*	getTextureBuf(void)const=0;

	CColor			getPixelColor(int x, int y);
	void			getPixelColor(MATH_OUT CColor& color, int x, int y);
	void			setPixelColor(int x, int y, const CColor& color);

	//void			CopyFrom(CRenderSystem* pRenderSystem, CTexture* pSourceTexture);
	//void			SaveToFile(const CString& fileName, D3DXIMAGE_FILEFORMAT fileFormat=D3DXIFF_DDS);
	

	const CString&	getName(void)const			{ return m_name;}

	m_uint32		getWidth(void)const			{return m_width;}
	m_uint32		getHeight(void)const		{return m_height;}
	m_uint16		getMipLevel(void)const		{return m_mipLevels;}
	TEX_FORMAT		getFormat(void)const		{return m_format;}
	m_dwrd			getUsage(void)const			{return m_usage;}

	void			setTexCoordLayer(int layer)			{m_texCoordLayer = layer;}
	int				getTexCoordLayer(void)const			{return m_texCoordLayer;}

	static	int		caculatePixelByte(CTexture* pTexture);

protected:

	virtual Error	_createTexture( TEX_FORMAT		texFormat, 
									m_uint32		width, 
									m_uint32		height, 
									RSPOOL			pool=RSP_MANAGER,
									m_dwrd			usage=0, 
									m_uint16		mipLevel=0)=0;		

	virtual Error	_createTextureFromFile( const CString&	fileName, 
											TEX_FORMAT		textureFormat, 
											m_uint32		width=0, 
											m_uint32		height=0,
											RSPOOL			pool=RSP_MANAGER,
											m_dwrd			usage=0, 
											m_uint16		mipLevel=0)=0;
	
protected:

	CString				m_name;

	m_uint32			m_width;
	m_uint32			m_height;
	m_uint16			m_mipLevels;
	m_dwrd				m_usage;					//texture use way like RENDERTARGET, TEXTURE2D
	RSPOOL				m_pool;

	m_uint16			m_texCoordLayer;					//texture layer

	TEX_FORMAT			m_format;

	TexRect				m_texRect;
	
};

}

