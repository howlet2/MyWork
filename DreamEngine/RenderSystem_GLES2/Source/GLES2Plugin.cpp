#include "GLES2Plugin.h"
#include "Root.h"

namespace DreamEngineGLES2
{

CString CGLES2RenderSysPlugin::m_name = "GLES2RenderSysPlugin";

CGLES2RenderSysPlugin::CGLES2RenderSysPlugin(void)
{
}


CGLES2RenderSysPlugin::~CGLES2RenderSysPlugin(void)
{
}

const CString& CGLES2RenderSysPlugin::getName()const
{
	return CGLES2RenderSysPlugin::m_name;
}


void CGLES2RenderSysPlugin::initialise()
{

}

void CGLES2RenderSysPlugin::install()
{
	m_pRenderSystem = new CGLES2RenderSystem;
	m_pRenderSystem->initialize();
	CRoot::instancePtr()->setRenderSystem(m_pRenderSystem);
}

void CGLES2RenderSysPlugin::uninstall()
{
	m_pRenderSystem->shutDown();
	SAFE_DELETE(m_pRenderSystem);
}

static CGLES2RenderSysPlugin* pPlugin = MATH_NULL;

extern "C" void _EngineGLES2Export dllStartPlugin(void) throw()
{
	pPlugin = new CGLES2RenderSysPlugin;
	CRoot::instancePtr()->installPlugin(pPlugin);
}

extern "C" void _EngineGLES2Export dllStopPlugin(void)
{
	CRoot::instancePtr()->unInstallPlugin(pPlugin);
	SAFE_DELETE(pPlugin);
}

}