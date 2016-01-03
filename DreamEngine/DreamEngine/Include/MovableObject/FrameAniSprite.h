#pragma once
#include "Sprite.h"
#include "Animation/FrameAnimation.h"

namespace DreamEngine
{
class _EngineExport CFrameAniSprite : public CSprite
{
public:
	CFrameAniSprite(CRenderSystem* pRenderSystem, const CString& name);
	~CFrameAniSprite(void);

	bool			initWithFiles(const char* pFileName, ...);
	bool			initWithFilesByValst(const char* pFileName, va_list args);
	bool			initWithAnimationFile(const CString& fileName);

	virtual void	update(float delay);
	virtual void	onDestroy();

private:

	CFrameAnimation*	m_pFrameAnimation;
};
}


