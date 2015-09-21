#pragma once
#include "engineobject.h"
#include "InputDefine.h"

namespace DreamEngine
{
class _EngineExport CKeyBoard : public CEngineObject
{
public:
	CKeyBoard(HWINDOW hWnd);
	virtual ~CKeyBoard(void);

public:

		virtual Error	initialize(void)=0;
		virtual void	shutDown(void)=0;
		virtual Error	setExclusiveMode(m_uint8 exclusiveMode)=0;

		Error			update(void);

		//! Pushed it means only care the key whether be pressed at current								
		bool			isKeyPushed(KEY key);	

		//! Down it means the key is pressed at current and not pressed at previously
		bool			isKeyDown(KEY key);		

		//! Up it means the key is not pressed at current and  pressed at previously
		bool			isKeyUp(KEY key);

		//! get which key is pressed at current 
		KEY				getKeyDownName(void); 

protected:

		HWINDOW			m_hWnd;
		char			m_keyBorad[MAX_KEYBOARD_NUM];
		char			m_oldKeyBorad[MAX_KEYBOARD_NUM];

protected:

		virtual	bool	_getIsKeyDown(char* pKeyBorad, KEY key)=0;
		virtual Error	_updateKeyBoardState(void)=0;
		virtual Error   _onLostDevice(void)=0;
};

}


