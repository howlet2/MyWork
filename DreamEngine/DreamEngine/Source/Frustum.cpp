#include "Frustum.h"

namespace DreamEngine
{

CFrustum::CFrustum(const CString& name, ProjectionType type/*=PT_PERSPECTIVE*/):
	m_type(type),
	m_width(1024),
	m_height(768),
	m_fovY(MATH_PI/4),
	m_near(1.0f),
	m_far(1000.0f)
{
	m_projectAspectRatio = m_height/m_width;

	updateProjection();

	m_isProjectChanged = true;
}


CFrustum::~CFrustum(void)
{

}

void CFrustum::setProjectionType(ProjectionType type)
{
	m_type = type;
	updateProjection();
}

void CFrustum::setFOVy(float fovy)
{
	m_fovY = fovy;
	updateProjection();
}

//void CFrustum::SetAspectRatio(float aspectRatio)
//{
//	m_projectAspectRatio = aspectRatio;
//	UpdateProjection();
//}

void CFrustum::setNearClipDistance(float nearDist)
{
	m_near = nearDist;
	updateProjection();
}

void CFrustum::setFarClipDistance(float farDist)
{
	m_far = farDist;
	updateProjection();
}

void CFrustum::setWidth(float width)
{
	m_width = width;
	m_projectAspectRatio = m_height/m_width;
	updateProjection();
}

void CFrustum::setHeight(float height)
{
	m_height = height;
	m_projectAspectRatio = m_height/m_width;
	updateProjection();
}

void CFrustum::setProChange(bool isChanged/* =false */)
{
	m_isProjectChanged = isChanged;
}

void CFrustum::updateProjection()
{
	switch (m_type)
	{
	case PT_PERSPECTIVE:
		{
			CMatrix16::matrixPerspectiveFovLH(&m_projectMatrix, m_fovY,\
				m_projectAspectRatio, m_near, m_far);
		}break;

	case PT_ORTHOGRAPHIC:
		{
			CMatrix16::matrixOrthoLH(&m_projectMatrix, m_width, m_height,\
				m_near, m_far);
		}break;
	}
	m_isProjectChanged = true;
}

}

