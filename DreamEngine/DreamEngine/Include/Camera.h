#pragma once
#include "EngineObject.h"
#include "Frustum.h"

namespace DreamEngine
{
class CSceneManager;

class _EngineExport CCamera : public CFrustum
{
	 
public:
	CCamera(const CString& name, CSceneManager* pSceneManager, ProjectionType type=PT_PERSPECTIVE);
	virtual ~CCamera(void);

	//get view matrix
	const CMatrix16&	getViewMatrix()const							{return m_viewMatrix;}
	void				getViewProjectMatrix(MATH_OUT CMatrix16& mat)const;

	//set and get camera position
	const CVector3&		getPosition(void) const							{return m_position;}

	virtual void		setPosition(const CVector3& position);
	virtual void		setPosition(float x, float y, float z);

	//set camera look at point
	virtual void		lookAt( const CVector3& targetPoint );
	virtual void		lookAt(float x, float y, float z);

	//get camera up/right/direction vec
	CVector3			getUp(void) const		{return m_up;}
	CVector3			getRight(void)const		{return m_right;}
	CVector3			getDirection(void)const {return m_direction;}

	//set camera direction
	virtual void		setDirection(const CVector3& direction);	
	virtual void		setDirection(float x, float y, float z);

	//move camera
	virtual void		move(const CVector3& vec);		//	by vec
	virtual void		strafe(float units);			//	left/right
	virtual void		fly(float units);				//	up/down
	virtual void		walk(float units);				//	forward/backward

	// Rolls the camera anticlockwise, around its local z axis.
	virtual void		roll(float angle);

	// Rotates the camera anticlockwise around it's local y axis.
	virtual void		yaw(float angle);

	// Pitches the camera up/down anticlockwise around it's local z axis.
	virtual void		pitch(float angle);

	CSceneManager*		getSceneManager(void)const {return m_pSceneManager;}


	virtual void		updateView(void);

protected:

	CVector3			m_position;
	CVector3			m_direction;
	CVector3			m_right;
	CVector3			m_up;

	CMatrix16			m_viewMatrix;
	CSceneManager*		m_pSceneManager;

};

}
