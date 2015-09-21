#include "Mouse.h"

namespace DreamEngine
{

CMouse::CMouse(HWINDOW hWnd):
m_hWnd(hWnd)
{
}


CMouse::~CMouse(void)
{
}

Error CMouse::update()
{
	CheckEngineError(_updateMouseState()); 
	_updateMouseDoubleClick();
	//CheckEngineError(_OnLostDevice());

	return ERROR_OK;
}

bool CMouse::isLMousePushed()
{
	return _getMouseIsDown(m_mouseState.rgbButtons, MKEY_LBUTTON);
}

bool CMouse::isRMousePushed()
{
	return _getMouseIsDown(m_mouseState.rgbButtons, MKEY_RBUTTON);
}

bool CMouse::isMMousePushed()
{
	return _getMouseIsDown(m_mouseState.rgbButtons, MKEY_MBUTTON);
}

bool CMouse::isLMouseDown()
{
	return (_getMouseIsDown(m_mouseState.rgbButtons, MKEY_LBUTTON) &&
		    !_getMouseIsDown(m_oldMouseState.rgbButtons, MKEY_LBUTTON));
}

bool CMouse::isRMouseDown()
{
	return (_getMouseIsDown(m_mouseState.rgbButtons, MKEY_RBUTTON) &&
		   !_getMouseIsDown(m_oldMouseState.rgbButtons, MKEY_RBUTTON));
}

bool CMouse::isMMouseDown()
{
	return (_getMouseIsDown(m_mouseState.rgbButtons, MKEY_MBUTTON) &&
		   !_getMouseIsDown(m_oldMouseState.rgbButtons, MKEY_MBUTTON));
}

bool CMouse::isLMouseDoubleClick()
{
	return m_mouseDoubleClick[0].m_isMouseDoubleDwon;
}

bool CMouse::isRMouseDoubleClick()
{
	return m_mouseDoubleClick[1].m_isMouseDoubleDwon;
}

bool CMouse::isMMouseDoubleClick()
{
	return m_mouseDoubleClick[2].m_isMouseDoubleDwon;
}

bool CMouse::isLMouseUp()
{
	return (!_getMouseIsDown(m_mouseState.rgbButtons, MKEY_LBUTTON) &&
		    _getMouseIsDown(m_oldMouseState.rgbButtons, MKEY_LBUTTON));
}

bool CMouse::isRMouseUp()
{
	return (!_getMouseIsDown(m_mouseState.rgbButtons, MKEY_RBUTTON) &&
		    _getMouseIsDown(m_oldMouseState.rgbButtons, MKEY_RBUTTON));
}

bool CMouse::isMMouseUp()
{
	return (!_getMouseIsDown(m_mouseState.rgbButtons, MKEY_MBUTTON) &&
		    _getMouseIsDown(m_oldMouseState.rgbButtons, MKEY_MBUTTON));
}

//! get mouse move distance between current and  previously
void CMouse::getXYTraveled(long& x, long& y)
{
	x = m_mouseState.lX;
	y = m_mouseState.lY;
}

//! get mouse wheel scroll distance between current and  previously
void CMouse::getZTraveled(long& z)
{
	z = m_mouseState.lZ;
}

void CMouse::setDoubleClickInterval(long time)
{
	m_doubleClickInterval = time;
}

MouseKey CMouse::getMKeyDownName()
{
	MouseKey key = MKEY_NULL;

	if (isLMouseDown())
		key = MKEY_LBUTTON;
	if (isRMouseDown())
		key = MKEY_RBUTTON;
	if (isMMouseDown())
		key = MKEY_MBUTTON;

	return key;
}

void CMouse::_updateMouseDoubleClick()
{
	m_mouseDoubleClick[0].m_isMouseDoubleDwon = false;
	if (isLMouseDown())
	{
		clock_t curTime = clock();
		long x, y;
		getMousePosition(x, y);
		if (m_mouseDoubleClick[0].m_mouseLastDownTime>0 && curTime-m_mouseDoubleClick[0].m_mouseLastDownTime<m_doubleClickInterval
			&& m_mouseDoubleClick[0].x==x && m_mouseDoubleClick[0].y==y)
		{
			m_mouseDoubleClick[0].m_mouseLastDownTime = 0;
			m_mouseDoubleClick[0].m_isMouseDoubleDwon = true;
		}
		else
		{
			m_mouseDoubleClick[0].m_mouseLastDownTime = clock();
			getMousePosition(m_mouseDoubleClick[0].x, m_mouseDoubleClick[0].y);
		}
	}

	m_mouseDoubleClick[1].m_isMouseDoubleDwon = false;
	if (isRMouseDown())
	{
		clock_t curTime = clock();
		long x, y;
		getMousePosition(x, y);
		if (m_mouseDoubleClick[1].m_mouseLastDownTime>0 && curTime-m_mouseDoubleClick[1].m_mouseLastDownTime<m_doubleClickInterval
			&& m_mouseDoubleClick[1].x==x && m_mouseDoubleClick[1].y==y)
		{
			m_mouseDoubleClick[1].m_mouseLastDownTime = 0;
			m_mouseDoubleClick[1].m_isMouseDoubleDwon = true;
		}
		else
		{
			m_mouseDoubleClick[1].m_mouseLastDownTime = clock();
			getMousePosition(m_mouseDoubleClick[1].x, m_mouseDoubleClick[1].y);
		}
	}


	m_mouseDoubleClick[2].m_isMouseDoubleDwon = false;
	if (isMMouseDown())
	{
		clock_t curTime = clock();
		long x, y;
		getMousePosition(x, y);
		if (m_mouseDoubleClick[2].m_mouseLastDownTime>0 && curTime-m_mouseDoubleClick[2].m_mouseLastDownTime<m_doubleClickInterval
			&& m_mouseDoubleClick[2].x==x && m_mouseDoubleClick[2].y==y)
		{
			m_mouseDoubleClick[2].m_mouseLastDownTime = 0;
			m_mouseDoubleClick[2].m_isMouseDoubleDwon = true;
		}
		else
		{
			m_mouseDoubleClick[2].m_mouseLastDownTime = clock();
			getMousePosition(m_mouseDoubleClick[2].x, m_mouseDoubleClick[2].y);
		}
	}
}

}
