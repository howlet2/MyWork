#include "RenderSystem.h"

namespace DreamEngine
{

CRenderSystem::CRenderSystem(void):
m_pActiveWindow(MATH_NULL)
{
}


CRenderSystem::~CRenderSystem(void)
{
}

Error CRenderSystem::shutDown()
{
	for (RenderWindowLst::iterator iter=m_renderWindows.begin(); iter!=m_renderWindows.end(); ++iter)
	{
		(*iter)->shutDown();
		SAFE_DELETE(*iter);
	}
	return ERROR_OK;
}

}

