#include "D3D9Plugin.h"
#include "Root.h"

namespace DreamEngineD3D
{

CString CD3D9RenderSysPlugin::m_name = "D3D9RenderSysPlugin";


CD3D9RenderSysPlugin::CD3D9RenderSysPlugin(void):
m_pRenderSystem(MATH_NULL)
{
}


CD3D9RenderSysPlugin::~CD3D9RenderSysPlugin(void)
{
}

const CString& CD3D9RenderSysPlugin::getName()const
{
	return CD3D9RenderSysPlugin::m_name;
}
	

void CD3D9RenderSysPlugin::initialise()
{

}

void CD3D9RenderSysPlugin::install()
{
	m_pRenderSystem = new CD3D9RenderSystem;
	m_pRenderSystem->initialize();
	CRoot::instancePtr()->setRenderSystem(m_pRenderSystem);
}

void CD3D9RenderSysPlugin::uninstall()
{
	m_pRenderSystem->shutDown();
	SAFE_DELETE(m_pRenderSystem);
}

static CD3D9RenderSysPlugin* pPlugin = MATH_NULL;

extern "C" void _EngineD3D9Export dllStartPlugin(void) throw()
{
	pPlugin = new CD3D9RenderSysPlugin;
	CRoot::instancePtr()->installPlugin(pPlugin);
}

extern "C" void _EngineD3D9Export dllStopPlugin(void)
{
	CRoot::instancePtr()->unInstallPlugin(pPlugin);
	SAFE_DELETE(pPlugin);
}

}

