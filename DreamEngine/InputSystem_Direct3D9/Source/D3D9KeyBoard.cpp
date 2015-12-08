#include "D3D9KeyBoard.h"
#include "input/InputDefine.h"
#include "dinput.h"
using namespace DreamEngine;

namespace DreamEngineD3D9Input
{

static m_uint8 KeyToD3D9InputKey(KEY key)
{
	switch (key)
	{
	case KEY_NULL:	return 0;
	case KEY_SPACE:	return	DIK_SPACE;

	case KEY_0: return	DIK_0;
	case KEY_1: return	DIK_1;
	case KEY_2: return	DIK_2;
	case KEY_3: return	DIK_3;
	case KEY_4: return	DIK_4;
	case KEY_5: return	DIK_5;
	case KEY_6: return	DIK_6;
	case KEY_7: return	DIK_7;
	case KEY_8: return	DIK_8;
	case KEY_9: return	DIK_9;
	case KEY_A: return	DIK_A;
	case KEY_B: return	DIK_B;
	case KEY_C: return	DIK_C;
	case KEY_D: return	DIK_D;
	case KEY_E: return	DIK_E;
	case KEY_F: return	DIK_F;
	case KEY_G: return	DIK_G;
	case KEY_H: return	DIK_H;
	case KEY_I: return	DIK_I;
	case KEY_J: return	DIK_J;
	case KEY_K: return	DIK_K;
	case KEY_L: return	DIK_L;
	case KEY_M: return	DIK_M;
	case KEY_N: return	DIK_N;
	case KEY_O: return	DIK_O;
	case KEY_P: return	DIK_P;
	case KEY_Q: return	DIK_Q;
	case KEY_R: return	DIK_R;
	case KEY_S: return	DIK_S;
	case KEY_T: return	DIK_T;
	case KEY_U: return	DIK_U;
	case KEY_V: return	DIK_V;
	case KEY_W: return	DIK_W;
	case KEY_X: return	DIK_X;
	case KEY_Y: return	DIK_Y;
	case KEY_Z: return	DIK_Z;

	case KEY_LEFT:	return	DIK_LEFT;
	case KEY_RIGHT:	return	DIK_RIGHT;
	case KEY_UP:    return	DIK_UP;
	case KEY_DOWN:	return	DIK_DOWN;
	case KEY_PGDOWN:return	DIK_PGDN;
	case KEY_PGUP:	return	DIK_PGUP;

	case KEY_LSHIFT: return	DIK_LSHIFT;
	case KEY_RSHIFT: return  DIK_RSHIFT;
	case KEY_LCTRL:  return  DIK_LCONTROL;
	case KEY_RCTRL:  return  DIK_RCONTROL;
	case KEY_ESC:    return  DIK_ESCAPE;
	case KEY_LALT:	 return	DIK_LALT;
	case KEY_RALT:	 return	DIK_RALT;
	case KEY_ENTER:	 return	DIK_RETURN;
	case KEY_TAB:    return	DIK_TAB;

	case KEY_F1:  return	DIK_F1;
	case KEY_F2:  return	DIK_F2;
	case KEY_F3:  return	DIK_F3;
	case KEY_F4:  return	DIK_F4;
	case KEY_F5:  return	DIK_F5;
	case KEY_F6:  return	DIK_F6;
	case KEY_F7:  return	DIK_F7;
	case KEY_F8:  return	DIK_F8;
	case KEY_F9:  return	DIK_F9;
	case KEY_F10: return	DIK_F10;

	case KEY_NUMPAD0: return   DIK_NUMPAD0;
	case KEY_NUMPAD1: return   DIK_NUMPAD1;
	case KEY_NUMPAD2: return   DIK_NUMPAD2;
	case KEY_NUMPAD3: return   DIK_NUMPAD3;
	case KEY_NUMPAD4: return   DIK_NUMPAD4;
	case KEY_NUMPAD5: return   DIK_NUMPAD5;
	case KEY_NUMPAD6: return   DIK_NUMPAD6;
	case KEY_NUMPAD7: return   DIK_NUMPAD7;
	case KEY_NUMPAD8: return   DIK_NUMPAD8;
	case KEY_NUMPAD9: return   DIK_NUMPAD9;
	case KEY_ADD:	  return   DIK_ADD;
	case KEY_SUBTRACT:return   DIK_SUBTRACT;

	default:	return 0;
	}

	return 0;
}

CD3D9KeyBoard::CD3D9KeyBoard(HWINDOW hWnd):
CKeyBoard(hWnd),
m_pKeyBoard(MATH_NULL)
{
	ZeroMemory(m_keyBorad, sizeof(m_keyBorad));
	ZeroMemory(m_oldKeyBorad, sizeof(m_oldKeyBorad));
}


CD3D9KeyBoard::~CD3D9KeyBoard(void)
{
}

Error	CD3D9KeyBoard::initialize(void)
{
	LPDIRECTINPUT8 DI_Object = MATH_NULL;

	if (DirectInput8Create((HINSTANCE)(::GetWindowLong(m_hWnd, GWL_HINSTANCE)), 
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&DI_Object, MATH_NULL) < 0)        
			return ERROR_CREATE_KEYBOARD_FAILD;

	if (DI_Object->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, MATH_NULL) < 0)  
			return ERROR_CREATE_KEYBOARD_FAILD;

	if (m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard) < 0)					
			return ERROR_CREATE_KEYBOARD_FAILD;
	
	CheckEngineError(setExclusiveMode(EM_FOREGROUND|EM_NONEXCLUSIVE));

	SAFE_RELEASE(DI_Object);

	return ERROR_OK;
}

void	CD3D9KeyBoard::shutDown(void)
{
	m_pKeyBoard->Unacquire();
	SAFE_RELEASE(m_pKeyBoard);
}

Error	CD3D9KeyBoard::setExclusiveMode(m_uint8 exclusiveMode)
{
	if (m_pKeyBoard->SetCooperativeLevel(m_hWnd, exclusiveMode) < 0)
		return ERROR_INPUT_COOPERATE_LEVL_FAILD;

	return ERROR_OK;
}


bool	CD3D9KeyBoard::_getIsKeyDown(char* pKeyBorad, KEY key)
{
	return ( (pKeyBorad[KeyToD3D9InputKey(key)]&0x80) != 0);
}

Error CD3D9KeyBoard::_updateKeyBoardState(void)
{
	if (m_pKeyBoard==MATH_NULL) return ERROR_HAVE_NULL_POINT;

	CopyMemory(m_oldKeyBorad, m_keyBorad, sizeof(m_keyBorad));
	ZeroMemory(m_keyBorad, sizeof(m_keyBorad));
	 
	HRESULT hr = m_pKeyBoard->GetDeviceState(KEYBOARD_MAX, (void*)(m_keyBorad));

	if(hr==DIERR_INPUTLOST || hr==DIERR_NOTACQUIRED) 
	{
		_onLostDevice();
	}

	return ERROR_OK;
}

Error CD3D9KeyBoard::_onLostDevice(void)
{
	HRESULT hr = 0;

	int count = 0;
	do
	{
		hr = m_pKeyBoard->Acquire();		
		count++;
		if (count > 30)
		{
			break;
		}
	}while (hr < 0);
	
	return ERROR_OK;
}

}

