#include "TextureUnitState.h"

namespace DreamEngine
{


CTextureUnitState::CTextureUnitState(const std::string& name/*=""*/, CTexture* pTexture/*=NULL*/):
	m_name(name),
	m_pTexture(pTexture),
	m_textureAddressMode(TEXTURE_ADDRESS_WRAP)
{

}


CTextureUnitState::~CTextureUnitState(void)
{
}

void CTextureUnitState::setTexture(CTexture* pTexture)
{
	m_pTexture = pTexture;
}

void CTextureUnitState::setTextureAdress(TextureAddress address)
{
	m_textureAddressMode = address;
}


}
