#pragma once
#include "PLugin.h"
#include "Gles2Define.h"
#include "GLES2RenderSystem.h"
using namespace DreamEngine;

namespace DreamEngineGLES2
{

class _EngineGLES2Export CGLES2RenderSysPlugin : public CPLugin
{
public:
	CGLES2RenderSysPlugin(void);
	~CGLES2RenderSysPlugin(void);

	virtual const CString&	getName() const;
	virtual void			install();
	virtual void			initialise();
	virtual void			uninstall();

private:

	static CString		m_name;
	CGLES2RenderSystem*	m_pRenderSystem;
};

};

