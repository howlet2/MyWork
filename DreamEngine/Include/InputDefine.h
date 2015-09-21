#pragma once

namespace DreamEngine
{

#define MAX_KEYBOARD_NUM		256

enum KEY
{
	KEY_NULL	=	0,
	KEY_SPACE	,
	KEY_0		,
	KEY_1		,
	KEY_2		,
	KEY_3		,
	KEY_4		,
	KEY_5		,
	KEY_6		,
	KEY_7		,
	KEY_8		,
	KEY_9		,
	KEY_A		,
	KEY_B		,
	KEY_C		,
	KEY_D		,
	KEY_E		,
	KEY_F		,
	KEY_G		,
	KEY_H		,
	KEY_I		,
	KEY_J		,
	KEY_K		,
	KEY_L		,
	KEY_M		,
	KEY_N		,
	KEY_O		,
	KEY_P		,
	KEY_Q		,
	KEY_R		,
	KEY_S		,
	KEY_T		,
	KEY_U		,
	KEY_V		,
	KEY_W		,
	KEY_X		,
	KEY_Y		,
	KEY_Z		,

	KEY_LEFT	,
	KEY_RIGHT	,
	KEY_UP		,
	KEY_DOWN	,
	KEY_PGDOWN	,
	KEY_PGUP	,

	KEY_LSHIFT	,
	KEY_RSHIFT	,
	KEY_LCTRL   ,
	KEY_RCTRL   ,
	KEY_ESC		,
	KEY_LALT	,
	KEY_RALT	,
	KEY_ENTER	,
	KEY_TAB		,

	KEY_F1		,
	KEY_F2		,
	KEY_F3		,
	KEY_F4		,
	KEY_F5		,
	KEY_F6		,
	KEY_F7		,
	KEY_F8		,
	KEY_F9		,
	KEY_F10		,

	KEY_NUMPAD0 ,
	KEY_NUMPAD1 ,
	KEY_NUMPAD2 ,
	KEY_NUMPAD3 ,
	KEY_NUMPAD4 ,
	KEY_NUMPAD5 ,
	KEY_NUMPAD6 ,
	KEY_NUMPAD7 ,
	KEY_NUMPAD8 ,
	KEY_NUMPAD9 ,
	KEY_ADD		,
	KEY_SUBTRACT,

	KEYBOARD_MAX = 256,
};

#define MAX_MOUSE_BUTTON_NUM	4
enum MouseKey
{
	MKEY_NULL			= 0,
	MKEY_LBUTTON		= 1,
	MKEY_RBUTTON		= 2,
	MKEY_MBUTTON		= 3,

	MOUSE_KEY_MAX       = MAX_MOUSE_BUTTON_NUM,
};

#define EM_EXCLUSIVE     0x00000001
#define EM_NONEXCLUSIVE  0x00000002
#define EM_FOREGROUND    0x00000004
#define EM_BACKGROUND    0x00000008
#define EM_NOWINKEY      0x00000010

}




