#pragma once
#include "Mouse.h"
#include "InputDefine.h"
#include "D3D9InputDefine.h"
#include "dinput.h"

using namespace DreamEngine;

namespace DreamEngineD3D9Input
{

class _EngineD3D9InputExport CD3D9Mouse : public CMouse
{
public:
	CD3D9Mouse(HWINDOW hWnd);
	virtual ~CD3D9Mouse(void);

public:

	virtual Error	initialize(void);
	virtual void	shutDown(void);
	virtual Error	setExclusiveMode(m_uint8 exclusiveMode);
	virtual void    getMousePosition(long& x, long& y);	

protected:

	virtual bool	_getMouseIsDown(m_uint8* pMouse, MouseKey key);
	virtual Error	_updateMouseState(void);
	virtual Error   _onLostDevice(void);

protected:

	LPDIRECTINPUTDEVICE8	m_pMouse;
};

}


