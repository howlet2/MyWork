#include "Camera.h"

namespace DreamEngine
{

CCamera::CCamera(const CString& name,  CSceneManager* pSceneManager, ProjectionType type/*=PT_PERSPECTIVE*/):
	CFrustum(name, type),
	m_pSceneManager(pSceneManager),
	m_position(0, 0, 0),
	m_direction(0,0,1),
	m_up(0,1,0),
	m_right(1,0,0)
{
	updateView();
}


CCamera::~CCamera(void)
{
}

void  CCamera::getViewProjectMatrix(MATH_OUT CMatrix16& mat)const
{
	CMatrix16::multiply(&mat, &m_viewMatrix, &m_projectMatrix);
}

void CCamera::setPosition(const CVector3& position)
{
	m_position = position;
	updateView();
}

void CCamera::setPosition(float x, float y, float z)
{
	setPosition(CVector3(x, y, z));
}

void CCamera::lookAt( const CVector3& targetPoint )
{
	setDirection(targetPoint-m_position);
}

void CCamera::lookAt(float x, float y, float z)
{
	lookAt(CVector3(x, y, z));
}

void CCamera::move(const CVector3& vec)
{
	m_position += vec;
	updateView();
}

void CCamera::strafe(float units)
{
	m_position += m_right*units;
	updateView();
}

void CCamera::fly(float units)
{
	m_position += m_up*units;
	updateView();
}

void CCamera::walk(float units)
{
	m_position += m_direction*units;
	updateView();
}

void CCamera::setDirection(const CVector3& direction)
{
	m_direction = direction;
	updateView();
}

void CCamera::setDirection(float x, float y, float z)
{
	setDirection(CVector3(x, y, z));
}


void CCamera::pitch(float angle)
{
	CMatrix16 T;
	CMatrix16::rotationAxis(&T, &m_right, angle);

	// rotate _up and _look around _right vector
	CMatrix16::transformCoord(&m_up,&m_up, &T);
	CMatrix16::transformCoord(&m_direction,&m_direction, &T);

	updateView();
}

void CCamera::yaw(float angle)
{
	CMatrix16 T;
	// rotate around own up vector for aircraft

	CMatrix16::rotationAxis(&T, &m_up, angle);

	// rotate _right and _look around _up or y-axis
	CMatrix16::transformCoord(&m_right,&m_right, &T);
	CMatrix16::transformCoord(&m_direction,&m_direction, &T);

	updateView();
}

void CCamera::roll(float angle)
{
	CMatrix16 T;
	CMatrix16::rotationAxis(&T, &m_direction, angle);

	// rotate _up and _right around _look vector
	CMatrix16::transformCoord(&m_right,&m_right, &T);
	CMatrix16::transformCoord(&m_up,&m_up, &T);

	updateView();
}

void CCamera::updateView(void)
{
	// Keep camera's axes orthogonal to each other
	CVector3::normalize(&m_direction, &m_direction);

	CVector3::cross(&m_right, &m_up, &m_direction);
	CVector3::normalize(&m_right, &m_right);

	CVector3::cross(&m_up, &m_direction, &m_right);
	CVector3::normalize(&m_up, &m_up);


	// Build the view matrix:
	
	float x = -CVector3::dot(&m_right, &m_position);
	float y = -CVector3::dot(&m_up, &m_position);
	float z = -CVector3::dot(&m_direction, &m_position);

	m_viewMatrix._11=m_right._x; m_viewMatrix._12=m_up._x; m_viewMatrix._13=m_direction._x; m_viewMatrix._14=0.0f;
	m_viewMatrix._21=m_right._y; m_viewMatrix._22=m_up._y; m_viewMatrix._23=m_direction._y; m_viewMatrix._24=0.0f;
	m_viewMatrix._31=m_right._z; m_viewMatrix._32=m_up._z; m_viewMatrix._33=m_direction._z; m_viewMatrix._34=0.0f;
	m_viewMatrix._41=x; m_viewMatrix._42=y; m_viewMatrix._43=z; m_viewMatrix._44=1.0f; 
}

}
