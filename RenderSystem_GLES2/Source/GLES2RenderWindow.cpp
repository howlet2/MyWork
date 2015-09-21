#include "GLES2RenderWindow.h"
#include "WindowEventUtilities.h"
#include "EngineError.h"
#include "GLES2VideoManager.h"
#include "GLES2GpuProgramManager.h"
#include "GLES2GpuTypeManager.h"

namespace DreamEngineGLES2
{

CGLES2RenderWindow::CGLES2RenderWindow(const CString& name):
CRenderWindow(name)
{

}


CGLES2RenderWindow::~CGLES2RenderWindow(void)
{
}

void CGLES2RenderWindow::showWindow()
{
#ifdef WIN32
	::ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(m_hWnd);
#endif
}

Error CGLES2RenderWindow::initialize(int width,  int height)
{
	createMianWindow(m_name, width, height);

	m_pGpuProgramManager = new CGLES2GpuProgramManager();
	m_pVideoManager		 = new CGLES2VideoManager();
	m_pGpuTypeManager	 = new CGLES2GpuTypeManager();

	return ERROR_OK;
}

void CGLES2RenderWindow::shutDown()
{
 	m_pGpuProgramManager->destoryAll();
 	SAFE_DELETE(m_pGpuProgramManager);
// 
 	m_pVideoManager->destoryAll();
 	SAFE_DELETE(m_pVideoManager);

	SAFE_DELETE(m_pGpuTypeManager);
}

Error CGLES2RenderWindow::createMianWindow(const CString& name, int windowWidth, int windowHeigth)
{
	m_heigth = windowHeigth;
	m_width  = windowWidth;

#ifdef WIN32 

	WNDCLASSEX wndClass = { sizeof(WNDCLASSEX), CS_CLASSDC|CS_HREDRAW|CS_VREDRAW, CWindowEventUtilities::msgProc, 0L, 0L, 
		GetModuleHandle(MATH_NULL), MATH_NULL, MATH_NULL, MATH_NULL, MATH_NULL,
		TEXT(name.c_str()), MATH_NULL };
	RegisterClassEx( &wndClass );

	m_hWnd = ::CreateWindow( TEXT(name.c_str()), TEXT(name.c_str()), 
		WS_OVERLAPPEDWINDOW-WS_MAXIMIZEBOX-WS_SIZEBOX, CW_USEDEFAULT, 0, m_width, m_heigth,
		GetDesktopWindow(), MATH_NULL, wndClass.hInstance, MATH_NULL );

#endif
	
	CWindowEventUtilities::addRenderWindow(this);

	return ERROR_OK;
}


}

