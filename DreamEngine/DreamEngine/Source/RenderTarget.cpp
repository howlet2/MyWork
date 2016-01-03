#include "RenderTarget.h"
#include "Timer.h"

namespace DreamEngine
{


CRenderTarget::CRenderTarget(const CString& name):
	m_name(name),
	m_pViewport(MATH_NULL),
	m_width(0),
	m_heigth(0),
	m_avgFPS(0.0f),
	m_listenerTargetIter(m_pListeners.begin(), m_pListeners.end())
{
}

CRenderTarget::~CRenderTarget(void)
{
	SAFE_DELETE(m_pViewport);
}

//void CRenderTarget::SetViewport(CViewport* pViewport)
//{
//	m_pViewport = pViewport;
//}

CViewport* CRenderTarget::addViewport(CCamera* pCamera)
{
	m_pViewport = new CViewport(pCamera, m_width, m_heigth);
	return m_pViewport;
}

void CRenderTarget::addListener(CRenderTargetListener* pListener)
{
	m_pListeners.push_back(pListener);
	m_listenerTargetIter.set(m_pListeners.begin(), m_pListeners.end());
}

void CRenderTarget::updateFPS(float delay)
{
	static int frameCount = 0;
	static float timeUse  = 0.0f;

	timeUse += delay;
	if (timeUse > 1000.0f)
	{
		m_avgFPS = float(frameCount)/(timeUse)*1000;
		frameCount = 0;
		timeUse = 0.0f;
	}
}

float CRenderTarget::getFPS()const
{
	return m_avgFPS;
}

}
