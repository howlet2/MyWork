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

void CRenderTarget::updateFPS()
{
	static Math::CTimer time;
	static Math::m_dwrd last = time.getMillisecondsCPU();
	static int frameCount = 0;

	++frameCount;

	Math::m_dwrd cur = time.getMicrosecondsCPU();
	float timeUse = float(cur-last);

	if (timeUse > 1000.0f)
	{
		m_avgFPS = float(frameCount)/(cur-last)*1000;
		last = cur;
	}
}

float CRenderTarget::getFPS()const
{
	return m_avgFPS;
}

}
