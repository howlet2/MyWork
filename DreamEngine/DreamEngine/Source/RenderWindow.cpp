#include "RenderWindow.h"

namespace DreamEngine
{

CRenderWindow::CRenderWindow(const CString& name):
	m_pVideoManager(MATH_NULL),
	m_pGpuProgramManager(MATH_NULL),
	m_pGpuTypeManager(MATH_NULL),
	CRenderTarget(name)
{
}


CRenderWindow::~CRenderWindow(void)
{
}

}