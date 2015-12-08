#pragma once
#include "MovableObject/movableobject.h"
#include "Texture.h"

namespace DreamEngine
{
class CSprite : public CMovableObject
{
public:
	CSprite(CRenderSystem* pRenderSystem, const CString& name);
	~CSprite(void);

	void			setTexture(CTexture* pTexture);
	void			setTexture(const CString& texFileName);
	CTexture*		getTexture(void)const;

	virtual void	onCreate();
	virtual void	onLostDevice();
	virtual void	onResetDevice();
	virtual void	onDestroy();

protected:

	CTexture*		m_pTexture;
	bool			m_bAuotCreate;
};

}


