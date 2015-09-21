#pragma once
#include "EngineObject.h"
#include "VertexElement.h"

namespace DreamEngine
{

enum HardwareBufferType
{
	BUFFERTYPE_NULL= 0,
	POINT_LIST     = 1,
	LINE_LIST	   = 2,
	LINE_SHRIP	   = 3,
	TRIANGLE_LIST  = 4,
	TRIANGLE_STRIP = 5,
	TRIANGLE_FAN   = 6,
};

class _EngineExport CHardwareBuffer : public CEngineObject
{
public:

	CHardwareBuffer(HardwareBufferType type=TRIANGLE_LIST);
	virtual ~CHardwareBuffer(void);

	m_uint16					elementCount()const;
	m_uint16					trangleCount()const;
	m_uint16					dataCount()const		{return m_dataCount;}
	m_uint16					getStrade()const		{return m_strade;}			

	HardwareBufferType			getType()const			{return m_type;}
	void						setType(HardwareBufferType type);
	
	virtual bool				createBuffer(void* pDate, 
											m_uint16 dataCount, 
											m_uint16 strade)=0;


	virtual void				destory(void)=0;
	virtual void*				getBufferData()const = 0;

protected:

	m_uint16					m_dataCount;									
	m_uint16					m_strade;										//相邻两个数据间隔的大小
	HardwareBufferType			m_type;
};

////////////////////////////////////////////////////////////////////////// IndexBuffer
class _EngineExport CIndexBuffer : public CHardwareBuffer
{

public:
	CIndexBuffer(HardwareBufferType type=TRIANGLE_LIST);
	virtual ~CIndexBuffer(void);

	bool createSingleStripGrid(m_uint16 xVerts, m_uint16 yVerts, m_uint16 xStep, m_uint16 yStep);
	bool createSingleFanGrid(m_uint16 xCenter, m_uint16 yCenter,
							 m_uint16 xVerts,  m_uint16 yVerts,
							 m_uint16 xStep,   m_uint16 yStep);
	
	virtual void  active()=0;
};

////////////////////////////////////////////////////////////////////////// VertexBuffer
class _EngineExport CVertexBuffer : public CHardwareBuffer
{
public:

	typedef std::vector<CVertexElement> ElementLst;

	CVertexBuffer(HardwareBufferType type=TRIANGLE_LIST);
	virtual ~CVertexBuffer(void);

	virtual void		active(m_uint16 index=0)=0;

protected:

	ElementLst			m_elementLst;
};
}


