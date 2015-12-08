#include "Input/KeyBoard.h"

namespace DreamEngine
{

CKeyBoard::CKeyBoard(HWINDOW hWnd):
m_hWnd(hWnd)
{
	ZeroMemory(&m_keyBorad, sizeof(m_keyBorad));
	ZeroMemory(&m_oldKeyBorad, sizeof(m_oldKeyBorad));
}


CKeyBoard::~CKeyBoard(void)
{
}

Error CKeyBoard::update()
{
	CheckEngineError(_updateKeyBoardState()); 
	//CheckEngineError(_OnLostDevice());

	return ERROR_OK;
}

bool CKeyBoard::isKeyPushed(KEY key)
{
	return _getIsKeyDown(m_keyBorad, key);
}

bool CKeyBoard::isKeyDown(KEY key)
{
	return (!_getIsKeyDown(m_oldKeyBorad, key) && _getIsKeyDown(m_keyBorad, key));
}

bool CKeyBoard::isKeyUp(KEY key)
{
	return (_getIsKeyDown(m_oldKeyBorad, key) && !_getIsKeyDown(m_keyBorad, key));
}

KEY	CKeyBoard::getKeyDownName(void)
{
	KEY key = KEY_NULL;

	int keyIndex;
	for (keyIndex=0; keyIndex<MAX_KEYBOARD_NUM; ++keyIndex)
	{
		key = KEY(keyIndex);
		if (_getIsKeyDown(m_keyBorad, key) )
			break;
	}

	return key;
}

}

