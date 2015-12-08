#include "D3D9RenderWindow.h"
#include "WindowEventUtilities.h"
#include "D3D9VideoManager.h"
#include "D3D9GpuProgramManager.h"
#include "D3D9GpuTypeManager.h"

namespace DreamEngineD3D
{


CD3D9RenderWindow::CD3D9RenderWindow(const CString& name):
CRenderWindow(name),
m_pD3D9Dveice(MATH_NULL)
{
	
}


CD3D9RenderWindow::~CD3D9RenderWindow(void)
{
}

void CD3D9RenderWindow::showWindow()
{
	::ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(m_hWnd);
}

Error CD3D9RenderWindow::initialize(int width,  int height)
{
	createMianWindow(m_name, width, height);
	createDevice();
	
	m_pGpuProgramManager = new CD3D9GpuProgramManager(m_pD3D9Dveice);
	m_pVideoManager		 = new CD3D9VideoManager(m_pD3D9Dveice);
	m_pGpuTypeManager    = new CD3D9GpuTypeManager();

	return ERROR_OK;
}

void CD3D9RenderWindow::shutDown()
{
	m_pGpuProgramManager->destoryAll();
	SAFE_DELETE(m_pGpuProgramManager);

	m_pVideoManager->destoryAll();
	SAFE_DELETE(m_pVideoManager);

	SAFE_DELETE(m_pGpuTypeManager);

	m_pD3D9Dveice->shutDown();
	SAFE_DELETE(m_pD3D9Dveice);
}

Error CD3D9RenderWindow::createMianWindow(const CString& name, int windowWidth, int windowHeigth)
{
	m_heigth = windowHeigth;
	m_width  = windowWidth;

	WNDCLASSEX wndClass = { sizeof(WNDCLASSEX), CS_CLASSDC|CS_HREDRAW|CS_VREDRAW, CWindowEventUtilities::msgProc, 0L, 0L, 
		GetModuleHandle(MATH_NULL), MATH_NULL, MATH_NULL, MATH_NULL, MATH_NULL,
		TEXT(name.c_str()), MATH_NULL };
	RegisterClassEx( &wndClass );

	m_hWnd = ::CreateWindow( TEXT(name.c_str()), TEXT(name.c_str()), 
		WS_OVERLAPPEDWINDOW-WS_MAXIMIZEBOX-WS_SIZEBOX, CW_USEDEFAULT, 0, m_width, m_heigth,
		GetDesktopWindow(), MATH_NULL, wndClass.hInstance, MATH_NULL );

	CWindowEventUtilities::addRenderWindow(this);

	return ERROR_OK;
}

Error CD3D9RenderWindow::createDevice()
{
	m_pD3D9Dveice = new CD3D9Device;

	CD3D9Device::CDeviceSetting setting;
	m_pD3D9Dveice->initialize(this, &setting);

	return ERROR_OK;
}

}
