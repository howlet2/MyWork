#pragma once
#include "RenderWindow.h"
#include "EngineDefine.h"

#ifdef WIN32
	#include "windows.h"
#endif

namespace DreamEngine
{

class _EngineExport CWindowEventListener
{
public:

	CWindowEventListener(){}
	virtual ~CWindowEventListener(){}

	virtual void	onWinodwCreate(CRenderWindow* rw)=0;
	virtual void	onWinodwSize(CRenderWindow* rw)=0;
	virtual void	onWinodwClose(CRenderWindow* rw)=0;
	virtual void	onWindowPaint(CRenderWindow* rw)=0;
};


class _EngineExport CWindowEventUtilities
{
public:
	CWindowEventUtilities(void);
	~CWindowEventUtilities(void);

#ifdef WIN32
	static LRESULT	CALLBACK msgProc(HWINDOW hWnd, 
									 UINT message, 
									 WPARAM wParam,
									 LPARAM lParam);
#endif

	static void			addListener(CRenderWindow* pRenderWindow,
									CWindowEventListener* pListener);

	static void			addRenderWindow(CRenderWindow* pRenderWindow);
	static void			pumpMessage(void);
	static bool			isQuit(void);

protected:

	typedef std::map<CRenderWindow*, CWindowEventListener*> WindowListeners;
	static WindowListeners	m_windowListeners;

	static bool				m_isQuit;
	
};

}
