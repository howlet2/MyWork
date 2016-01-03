#include "MovableObject/FrameAniSprite.h"

namespace DreamEngine
{
CFrameAniSprite::CFrameAniSprite(CRenderSystem* pRenderSystem, const CString& name):
	CSprite(pRenderSystem, name),
	m_pFrameAnimation(MATH_NULL)
{
}


CFrameAniSprite::~CFrameAniSprite(void)
{
}

bool CFrameAniSprite::initWithFiles(const char* pFileName, ...)
{
	bool ret = true;

	m_pFrameAnimation = new CFrameAnimation(m_name+"_animation");

	va_list argp; 
	va_start (argp, pFileName); 
	ret = m_pFrameAnimation->initWithFilesByVaLst(pFileName, argp);
	va_end (argp); 

	return ret;
}

bool  CFrameAniSprite::initWithFilesByValst(const char* pFileName, va_list arg)
{
	bool ret = true;

	m_pFrameAnimation = new CFrameAnimation(m_name+"_animation");
	ret = m_pFrameAnimation->initWithFilesByVaLst(pFileName, arg);
	setTexture(m_pFrameAnimation->getCurrentTexture());

	return ret;
}

bool CFrameAniSprite::initWithAnimationFile(const CString& fileName)
{
	bool ret = true;

	m_pFrameAnimation = new CFrameAnimation(m_name+"_animation");
	ret = m_pFrameAnimation->initWithAnimationFile(fileName);

	return ret;
}

void CFrameAniSprite::update(float delay)
{
	//CFrameAnimation::update(delay);
	if (m_pFrameAnimation!=MATH_NULL)
	{
		m_pFrameAnimation->update(delay);
		setTexture(m_pFrameAnimation->getCurrentTexture());
	}
}

void CFrameAniSprite::onDestroy()
{
	if (m_pFrameAnimation != NULL)
	{
		m_pFrameAnimation->destory();
		SAFE_DELETE(m_pFrameAnimation);
	}
	
	CSprite::onDestroy();
}
}

