#include "Input/InputSystem.h"

namespace DreamEngine
{
CInputSystem::CInputSystem(void):
m_pKeyBoard(MATH_NULL),
m_pMouse(MATH_NULL)
{
}


CInputSystem::~CInputSystem(void)
{
}

CInputSystem& CInputSystem::instance(void)
{	
	return (*m_singleton); 
}

CInputSystem* CInputSystem::instancePtr(void)
{ 
	return m_singleton; 
}

Error CInputSystem::shutDown()
{
	m_pKeyBoard->shutDown();
	m_pMouse->shutDown();

	SAFE_DELETE(m_pKeyBoard);
	SAFE_DELETE(m_pMouse);

	return ERROR_OK;
}

Error CInputSystem::setExclusiveMode(m_uint8 exclusiveMode)
{
	CheckEngineError(m_pKeyBoard->setExclusiveMode(exclusiveMode));
	CheckEngineError(m_pMouse->setExclusiveMode(exclusiveMode));

	return ERROR_OK;
}

Error CInputSystem::update()
{
	CheckEngineError(m_pMouse->update());
	CheckEngineError(m_pKeyBoard->update());

	return ERROR_OK;
}

}

