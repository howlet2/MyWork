#pragma once

#include "Mouse.h"
#include "KeyBoard.h"
#include "Singleton.h"

namespace DreamEngine
{

class _EngineExport CInputSystem : public CEngineObject, public CSingleton<CInputSystem>
{
public:
	CInputSystem(void);
	virtual ~CInputSystem(void);

	static CInputSystem& CInputSystem::instance(void);
	static CInputSystem* CInputSystem::instancePtr(void);

	virtual Error	initialize(HWINDOW hWnd)=0;

	CMouse*			getMouse(void)const			{return m_pMouse;}
	CKeyBoard*		getKeyBoard(void)const		{return m_pKeyBoard;}

	Error			shutDown(void);
	Error			setExclusiveMode(m_uint8 exclusiveMode);

	Error			update(void);

protected:

	CKeyBoard*		m_pKeyBoard;
	CMouse*			m_pMouse;
};
template<> CInputSystem* CSingleton<CInputSystem>::m_singleton = 0;
}


