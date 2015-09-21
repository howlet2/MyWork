#include "WindowEventUtilities.h"

namespace DreamEngine
{


CWindowEventUtilities::WindowListeners CWindowEventUtilities::m_windowListeners;
bool	CWindowEventUtilities::m_isQuit = false;

CWindowEventUtilities::CWindowEventUtilities(void)
{
}


CWindowEventUtilities::~CWindowEventUtilities(void)
{
}

#ifdef WIN32
LRESULT CALLBACK CWindowEventUtilities::msgProc(HWINDOW hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			WindowListeners::iterator iter;
			for (iter=m_windowListeners.begin(); iter!=m_windowListeners.end(); ++iter)
			{
				if (iter->second != MATH_NULL)
				{
					iter->second->onWinodwCreate(iter->first);
				}
			}
		}break;

	case WM_PAINT:
		{
			WindowListeners::iterator iter;
			for (iter=m_windowListeners.begin(); iter!=m_windowListeners.end(); ++iter)
			{
				if (iter->second != MATH_NULL)
				{
					iter->second->onWindowPaint(iter->first);
				}
			}
			::ValidateRect(hWnd, MATH_NULL);
		}break;

	case WM_SIZE:
		{
			WindowListeners::iterator iter;
			for (iter=m_windowListeners.begin(); iter!=m_windowListeners.end(); ++iter)
			{
				if (iter->second != MATH_NULL)
				{
					iter->second->onWinodwSize(iter->first);
				}
			}
		}break;

	case WM_CLOSE:
		{
			WindowListeners::iterator iter;
			for (iter=m_windowListeners.begin(); iter!=m_windowListeners.end(); ++iter)
			{
				if (iter->second != MATH_NULL)
				{
					iter->second->onWinodwClose(iter->first);
				}
			}
			
			::DestroyWindow(hWnd);
		}break;

	case WM_ACTIVATE:
		{

		}break;

	case WM_LBUTTONUP:
		{
			::ReleaseCapture();
		}break;

	case WM_LBUTTONDOWN:
		{
			::SetCapture(hWnd);
		}break;

	case  WM_DESTROY :
		{
			m_isQuit = true;
			::PostQuitMessage(0);
		}break;
	}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}
#endif //WIN32

void CWindowEventUtilities::addListener(CRenderWindow* pRenderWindow, CWindowEventListener* pListener)
{
	m_windowListeners[pRenderWindow] = pListener;
}

void CWindowEventUtilities::addRenderWindow(CRenderWindow* pRenderWindow)
{
	m_windowListeners[pRenderWindow] = MATH_NULL;
}

void CWindowEventUtilities::pumpMessage()
{

#ifdef WIN32

	MSG  msg;
	if (PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	
#endif
	
}

bool CWindowEventUtilities::isQuit()
{
	return m_isQuit;
}

}

