#pragma once

#include "D3D9Mouse.h"
#include "D3D9KeyBoard.h"
#include "input/InputSystem.h"
#include "D3D9InputDefine.h"
using namespace DreamEngine;

namespace DreamEngineD3D9Input
{

class _EngineD3D9InputExport CD3D9InputSystem : public CInputSystem
{
public:
	CD3D9InputSystem(void);
	virtual ~CD3D9InputSystem(void);

	virtual Error	initialize(HWINDOW hWnd);

protected:

};

}


