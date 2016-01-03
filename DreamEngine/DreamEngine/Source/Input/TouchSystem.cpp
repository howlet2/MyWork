#include "input/TouchSystem.h"


CTouchSystem::CTouchSystem(HWINDOW hWnd):
	m_hWnd(hWnd)
{
}


CTouchSystem::~CTouchSystem(void)
{
}

CTouchSystem& CTouchSystem::instance(void)
{	
	return (*m_singleton); 
}

CTouchSystem* CTouchSystem::instancePtr(void)
{ 
	return m_singleton; 
}

void CTouchSystem::update(float delay)
{
#ifdef WIN32
	POINT pt;
	::GetCursorPos(&pt);
	::ScreenToClient(m_hWnd, &pt);
	short state = GetKeyState(VK_LBUTTON);

	m_touchState.x		=	pt.x;
	m_touchState.y		=	pt.y;
	(state&0x8000)?m_touchState.state=STATE_DOWN:m_touchState.state=STATE_UP;

#endif 

}