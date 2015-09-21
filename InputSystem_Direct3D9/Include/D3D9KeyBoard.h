#pragma once
#include "KeyBoard.h"
#include "InputDefine.h"
#include "D3D9InputDefine.h"
#include "dinput.h"

using namespace DreamEngine;

namespace DreamEngineD3D9Input
{

class _EngineD3D9InputExport CD3D9KeyBoard : public CKeyBoard
{
public:
	CD3D9KeyBoard(HWINDOW hWnd);
	virtual ~CD3D9KeyBoard(void);

public:

		virtual Error	initialize(void);
		virtual void	shutDown(void);
		virtual Error	setExclusiveMode(m_uint8 exclusiveMode);

protected:

		virtual	bool	_getIsKeyDown(char* pKeyBorad, KEY key);
		virtual Error	_updateKeyBoardState(void);
		virtual Error   _onLostDevice(void);

protected:

		LPDIRECTINPUTDEVICE8	m_pKeyBoard;
};

}


