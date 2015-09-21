#pragma once
#include "engineobject.h"
#include "InputDefine.h"

namespace DreamEngine
{
class _EngineExport CMouse : public CEngineObject
{
public:

	struct MouseState
	{
		long		lX;
		long		lY;
		long		lZ;
		m_uint8		rgbButtons[4];
	};

	struct MouseDoubleClick
	{
		clock_t		m_mouseLastDownTime;
		bool		m_isMouseDoubleDwon;
		long		x;
		long		y;
	};

public:
	CMouse(HWINDOW hWnd);
	virtual ~CMouse(void);

public:

	virtual Error	initialize(void)=0;
	virtual void	shutDown(void)=0;
	virtual Error	setExclusiveMode(m_uint8 exclusiveMode)=0;
	virtual void    getMousePosition(long& x, long& y)=0;	

	Error			update(void);

	/*	
		Pushed it means only care the key whether be pressed at current
		Down   it means the key is pressed at current and not pressed at previously
		Up     it means the key is not pressed at current and pressed at previously
	*/
	bool			isLMousePushed();
	bool			isRMousePushed();
	bool			isMMousePushed();
	bool			isLMouseDown();
	bool			isRMouseDown();
	bool			isMMouseDown();

	bool			isLMouseDoubleClick();
	bool			isRMouseDoubleClick();
	bool			isMMouseDoubleClick();

	bool			isLMouseUp();
	bool			isRMouseUp();
	bool			isMMouseUp();

	void			getXYTraveled(long& x, long& y); //! get mouse move distance between current and  previously
	void			getZTraveled(long& z);			 //! get mouse wheel scroll distance between current and  previously

	void			setDoubleClickInterval(long time);
	MouseKey		getMKeyDownName(void);  

protected:

	void			_updateMouseDoubleClick(void);

	virtual bool	_getMouseIsDown(m_uint8* pMouse, MouseKey key)=0;
	virtual Error	_updateMouseState(void)=0;
	virtual Error   _onLostDevice(void)=0;

protected:

	HWINDOW				m_hWnd;

	MouseState			m_mouseState;
	MouseState			m_oldMouseState;
	long				m_doubleClickInterval;

	/* 
		index 0 is LMouse
		index 1 is RMouse
		index 2 is MMouse
	*/
	MouseDoubleClick	m_mouseDoubleClick[3];
};
}


