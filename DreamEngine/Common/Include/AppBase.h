#pragma once

#include "Root.h"
#include "dynlib.h"
#include "AppListener.h"

using namespace DreamEngine;

class _EngineExport CAppBase
{
public:
	CAppBase(void);
	~CAppBase(void);

	virtual	Error	run(CAppListener* pAppListener);
	virtual Error	shutDown(void);


protected:
	
	CRoot*			m_pRoot;
	CAppListener*	m_pAppListener;
};

