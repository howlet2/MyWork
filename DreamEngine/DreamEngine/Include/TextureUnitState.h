#pragma once
#include "EngineObject.h"
#include "Texture.h"

namespace DreamEngine
{

class _EngineExport CTextureUnitState : public CEngineObject
{
public:

	enum TextureOpType
	{
		TEXTURE_OP_TYPE_COLOR,
		TEXTURE_OP_TYPE_ALPHA,
	};

	enum TextureAddress
	{
		TEXTURE_ADDRESS_WRAP            = 1,
		TEXTURE_ADDRESS_MIRROR          = 2,
		TEXTURE_ADDRESS_CLAMP           = 3,
		TEXTURE_ADDRESS_BORDER          = 4,
		TEXTURE_ADDRESS_MIRRORONCE      = 5,
		TEXTURE_ADDRESS_FORCE_DWORD     = 0x7fffffff,
	};

public:
	CTextureUnitState(const std::string& name="", CTexture* pTexture=MATH_NULL);
	~CTextureUnitState(void);

	const CString&		getName(void)const				{return m_name;}

	CTexture*			getTexture()const				{return m_pTexture;}
	void				setTexture(CTexture* pTexture);

	TextureAddress		getTextureAdress() const		{return m_textureAddressMode;}
	void				setTextureAdress(TextureAddress address);

protected:

	std::string					m_name;
	CTexture*					m_pTexture;

	TextureAddress				m_textureAddressMode;
};

}

