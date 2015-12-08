#pragma once
#include "AppListener.h"
#include "Root.h"

class CGameListener : public CAppListener
{ 
public:
	CGameListener(void);
	~CGameListener(void);

	void onInitialize(void);
	void onShutDown(void);

	void onRenderStart(CRenderTarget* rw);
	void onRender(CRenderTarget* rw);
	void onRenderEnd(CRenderTarget* rw);
};

