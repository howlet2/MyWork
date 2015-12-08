#pragma once
#include "Rendertarget.h"

using namespace DreamEngine;

class _EngineExport CAppListener : public CRenderTargetListener
{
public:
	CAppListener(void);
	~CAppListener(void);

	virtual void onInitialize(void)=0;
	virtual void onShutDown(void)=0;
};

