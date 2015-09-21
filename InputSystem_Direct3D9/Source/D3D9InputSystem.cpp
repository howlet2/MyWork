#include "D3D9InputSystem.h"

namespace DreamEngineD3D9Input
{
CD3D9InputSystem::CD3D9InputSystem(void)
{
}


CD3D9InputSystem::~CD3D9InputSystem(void)
{
}

Error	CD3D9InputSystem::initialize(HWINDOW hWnd)
{
	m_pKeyBoard		= new CD3D9KeyBoard(hWnd);
	m_pMouse		= new CD3D9Mouse(hWnd);

	CheckEngineError(m_pKeyBoard->initialize());
	CheckEngineError(m_pMouse->initialize());

	return ERROR_OK;
}

}

