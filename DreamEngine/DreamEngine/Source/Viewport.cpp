#include "Viewport.h"

namespace DreamEngine
{
CViewport::CViewport(CCamera* pCamera):
	m_pCamera(pCamera),
	m_left(0), m_top(0),
	m_width(0), m_height(0),
	m_minZ(0.0f), m_maxZ(1.0f),
	m_backColour(0xffffffff),
	m_isChanged(true)
{
}

CViewport::CViewport(CCamera* pCamera, m_uint32 width, m_uint32 height, m_uint32 left/* =0 */, m_uint32 top/* =0 */):
	m_pCamera(pCamera),
	m_left(left), m_top(top),
	m_width(width), m_height(height),
	m_minZ(0.0f), m_maxZ(1.0f),
	m_backColour(0xffffffff),
	m_isChanged(true)
{
}


CViewport::~CViewport(void)
{
}

void CViewport::setTop(m_uint32 top)			
{
	m_top = top;
	m_isChanged = true;
}

void CViewport::setLeft(m_uint32 left)			
{
	m_left = left;
	m_isChanged = true;
}

void CViewport::setWidth(m_uint32 width)		
{
	m_width = width;
	m_isChanged = true;
}

void CViewport::setHeight(m_uint32 height)		
{
	m_height = height;
	m_isChanged = true;
}

void CViewport::setMaxZ(float maxZ)			
{
	m_maxZ = maxZ;
	m_isChanged = true;
}

void CViewport::setMinZ(float minZ)			
{
	m_minZ = minZ;
	m_isChanged = true;
}

void CViewport::setBackColor(CColor backColor)	
{
	m_backColour = backColor;
}

void CViewport::setCamera(CCamera* pCamera)
{
	m_pCamera = pCamera;
}

}
