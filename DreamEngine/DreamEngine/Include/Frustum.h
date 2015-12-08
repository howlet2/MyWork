#pragma once
#include "EngineObject.h"

namespace DreamEngine
{
class _EngineExport CFrustum : public CEngineObject
{
public:
	enum ProjectionType
	{
		PT_ORTHOGRAPHIC,
		PT_PERSPECTIVE
	};

public:

	CFrustum(const CString& name, ProjectionType type=PT_PERSPECTIVE);
	virtual ~CFrustum(void);


	const CString&		getName(void)const				{return m_name;}


	ProjectionType		getProjectionType(void)const	{return m_type;}
	const CMatrix16&	getViewProjectMatrix(void)const	{return m_projectMatrix;}
	

	//get attributes
	float				getFOVy(void)const				{return m_fovY;}
	float				getAspectRatio(void)const		{return m_projectAspectRatio;}
	float				getFarClipDistance(void)const	{return m_far;}
	float				getNearClipDistance(void)const	{return m_near;}
	

	//set attributes
	virtual void		setProjectionType(ProjectionType type);
	virtual void		setFOVy(float fovy);
	//virtual void		SetAspectRatio(float AspectRatio);
    virtual void		setNearClipDistance(float nearDist);
    virtual void		setFarClipDistance(float farDist);
    virtual void		setWidth(float width);
	virtual void		setHeight(float height);

	bool				isProChange(void)const		{return m_isProjectChanged;}
	virtual void		setProChange(bool isChanged=false);
	virtual void		updateProjection(void);

protected:

	CString				m_name;

	ProjectionType		m_type;
	float				m_projectAspectRatio;
	float				m_width;
	float				m_height;
	float				m_fovY;
	float				m_near;
	float				m_far;

	CMatrix16			m_projectMatrix;
	bool				m_isProjectChanged;

};

}

