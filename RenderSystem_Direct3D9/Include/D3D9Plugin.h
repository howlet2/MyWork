#pragma once
#include "PLugin.h"
#include "D3D9RenderSystem.h"
using namespace DreamEngine;

namespace DreamEngineD3D
{

class _EngineD3D9Export CD3D9RenderSysPlugin : public CPLugin
{
public:
	CD3D9RenderSysPlugin(void);
	~CD3D9RenderSysPlugin(void);

	virtual const CString&	getName() const;
	virtual void			install();
	virtual void			initialise();
	virtual void			uninstall();

private:

	static CString		m_name;
	CD3D9RenderSystem*	m_pRenderSystem;
};

}


