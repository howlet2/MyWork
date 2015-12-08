#pragma once
#include "EngineObject.h"
#include "Camera.h"

namespace DreamEngine 
{

class _EngineExport  CViewport : public CEngineObject
{
public:

	CViewport(CCamera* pCamera, 
			  m_uint32 width, 
			  m_uint32 height, 
			  m_uint32 left=0, 
			  m_uint32 top=0);

	CViewport(CCamera* pCamera);
	~CViewport(void);

	m_uint32	getLeft()	const				{return m_left;}
	m_uint32	getTop()	const				{return m_top;}
	m_uint32	getWidth()	const				{return m_width;}
	m_uint32	getHeight()const				{return m_height;}
	float		getMaxZ()	const				{return m_maxZ;}
	float		getMinZ()	const				{return m_minZ;}

	void		setTop(m_uint32 top);
	void		setLeft(m_uint32 left);
	void		setWidth(m_uint32 width);	
	void		setHeight(m_uint32 height);
	void		setMaxZ(float maxZ);		
	void		setMinZ(float minZ);

	CColor		getBackColor() const			{return m_backColour;}
	void		setBackColor(CColor backColor);
	void		setClearBuffers(m_uint16 clearBuffers);

	void		setCamera(CCamera* pCamera);
	CCamera*	getCamera(void)const			{return m_pCamera;}

	bool		isChanged(void)const			{return m_isChanged;}
	void		setChanged(bool isChanged)		{m_isChanged = isChanged;}

protected:

	m_uint32		m_left;
	m_uint32		m_top;
	m_uint32		m_width;
	m_uint32		m_height;
	float			m_maxZ;
	float			m_minZ;

	CColor			m_backColour;
	bool			m_isChanged;

	CCamera*		m_pCamera;
};

}

