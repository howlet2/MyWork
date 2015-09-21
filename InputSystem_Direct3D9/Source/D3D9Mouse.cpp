#include "D3D9Mouse.h"

namespace DreamEngineD3D9Input
{

static m_uint8 KeyToMKeyInedx(MouseKey key)
{
	switch (key)
	{
	case MKEY_LBUTTON:
		return 0;

	case MKEY_RBUTTON:
		return 1;

	case MKEY_MBUTTON:
		return 2;

	default: return 0;
	}
}

CD3D9Mouse::CD3D9Mouse(HWINDOW hWnd):
CMouse(hWnd),
m_pMouse(MATH_NULL)
{
	ZeroMemory(&m_mouseState, sizeof(m_mouseState));
	ZeroMemory(&m_oldMouseState, sizeof(m_oldMouseState));
}


CD3D9Mouse::~CD3D9Mouse(void)
{
}

Error	CD3D9Mouse::initialize(void)
{
	LPDIRECTINPUT8 DI_Object = MATH_NULL;

	if (DirectInput8Create((HINSTANCE)(::GetWindowLong(m_hWnd, GWL_HINSTANCE)), 
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&DI_Object, MATH_NULL) < 0)        
		return ERROR_CREATE_MOUSE_FAILD;

	if (DI_Object->CreateDevice(GUID_SysMouse, &m_pMouse, MATH_NULL) < 0)  
		return ERROR_CREATE_MOUSE_FAILD;

	if (m_pMouse->SetDataFormat(&c_dfDIMouse2) < 0)					
		return ERROR_CREATE_MOUSE_FAILD;

	CheckEngineError(setExclusiveMode(EM_FOREGROUND|EM_NONEXCLUSIVE));

	SAFE_RELEASE(DI_Object);

	return ERROR_OK;
}

void	CD3D9Mouse::shutDown(void)
{
	m_pMouse->Unacquire();
	SAFE_RELEASE(m_pMouse);
}

Error	CD3D9Mouse::setExclusiveMode(m_uint8 exclusiveMode)
{
	if (m_pMouse->SetCooperativeLevel(m_hWnd, exclusiveMode) < 0)
		return ERROR_INPUT_COOPERATE_LEVL_FAILD;

	return ERROR_OK;
}

void    CD3D9Mouse::getMousePosition(long& x, long& y)
{
	POINT pt;
	RECT client;
	::GetCursorPos(&pt);
	::GetClientRect(m_hWnd, &client);
	::ScreenToClient(m_hWnd, &pt);
	x = pt.x;
	y = pt.y;

	if (pt.x < client.left)
		x = 0;
	if (pt.x > client.right)
		x = client.right;
	if (pt.y < client.top)
		y = 0;
	if (pt.y > client.bottom)
		y = client.bottom;
}


bool	CD3D9Mouse::_getMouseIsDown(m_uint8* pMouse, MouseKey key)
{
	return ((pMouse[KeyToMKeyInedx(key)]&0x80) != 0);
}

Error	CD3D9Mouse::_updateMouseState(void)
{
	if (m_pMouse==MATH_NULL) return ERROR_HAVE_NULL_POINT;

	CopyMemory(&m_oldMouseState, &m_mouseState, sizeof(m_oldMouseState));
	ZeroMemory(&m_mouseState, sizeof(m_mouseState));

	HRESULT hr = m_pMouse->GetDeviceState(sizeof(m_mouseState), (void*)(&m_mouseState));
	
	if(hr==DIERR_INPUTLOST || hr==DIERR_NOTACQUIRED) 
	{
		_onLostDevice();
	}

	return ERROR_OK;
}

Error   CD3D9Mouse::_onLostDevice(void)
{
	HRESULT hr = 0;
	int count = 0;

	do
	{
		hr = m_pMouse->Acquire();		
		count++;
		if (count > 30)
		{
			break;
		}
	}while (hr < 0);

	return ERROR_OK;
}

}
