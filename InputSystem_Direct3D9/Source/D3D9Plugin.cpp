#include "D3D9Plugin.h"
#include "Root.h"

namespace DreamEngineD3D9Input
{

CString CD3D9InputSysPlugin::m_name = "D3D9InputSysPlugin";


CD3D9InputSysPlugin::CD3D9InputSysPlugin(void):
m_pD3D9InputSystem(MATH_NULL)
{
}


CD3D9InputSysPlugin::~CD3D9InputSysPlugin(void)
{
}

const CString& CD3D9InputSysPlugin::getName()const
{
	return CD3D9InputSysPlugin::m_name;
}
	

void CD3D9InputSysPlugin::initialise()
{

}

void CD3D9InputSysPlugin::install()
{
	m_pD3D9InputSystem = new CD3D9InputSystem;
	CRoot::instancePtr()->setInputSystem(m_pD3D9InputSystem);
}

void CD3D9InputSysPlugin::uninstall()
{
	m_pD3D9InputSystem->shutDown();
	SAFE_DELETE(m_pD3D9InputSystem);
}

static CD3D9InputSysPlugin* pPlugin = MATH_NULL;

extern "C" void _EngineD3D9InputExport dllStartPlugin(void) throw()
{
	pPlugin = new CD3D9InputSysPlugin;
	CRoot::instancePtr()->installPlugin(pPlugin);
}

extern "C" void _EngineD3D9InputExport dllStopPlugin(void)
{
	CRoot::instancePtr()->unInstallPlugin(pPlugin);
	SAFE_DELETE(pPlugin);
}

}

