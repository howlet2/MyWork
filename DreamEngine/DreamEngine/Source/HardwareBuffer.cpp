#include "HardwareBuffer.h"

namespace DreamEngine
{
CHardwareBuffer::CHardwareBuffer(const CString& name, HardwareBufferType type/*=TRIANGLE_STRIP*/):
m_type(type),
m_strade(0),
m_dataCount(0),
m_name(name)
{

}


CHardwareBuffer::~CHardwareBuffer(void)
{
}

m_uint16 CHardwareBuffer::elementCount()const
{
	int count = 0;

	switch(m_type)
	{
	case TRIANGLE_LIST:
	case LINE_LIST:
		{
			count = dataCount()/3;
		}break;

	case TRIANGLE_STRIP:
	case TRIANGLE_FAN:
	case LINE_SHRIP:
		{
			count = dataCount()-2;
		}break;

	case POINT_LIST:
		{
			count = dataCount();
		}break;
	}

	return count;
}

m_uint16 CHardwareBuffer::trangleCount()const
{
	if (m_type==TRIANGLE_FAN || m_type==TRIANGLE_LIST || m_type==TRIANGLE_STRIP)
		return elementCount();

	return 0;
}

void CHardwareBuffer::setType(HardwareBufferType type)
{
	m_type = type;
}

////////////////////////////////////////////////////////////////////////// CIndexBuffer

CIndexBuffer::CIndexBuffer(const CString& name, HardwareBufferType type/*=TRIANGLE_STRIP*/):
CHardwareBuffer(name, type)
{

}

CIndexBuffer::~CIndexBuffer(void)
{
}

bool CIndexBuffer::createSingleStripGrid(m_uint16 xVerts, m_uint16 yVerts, m_uint16 xStep, m_uint16 yStep)
{
	if (xVerts<2 || yVerts<2)
		return false;

	m_type = TRIANGLE_STRIP;

	int m_count = (yVerts-1)*(xVerts)*2+(yVerts-2)*2;

	WORD* pIndexs = new WORD[m_count];

	int offset = 0;
	int start = 0;
	int lineStep = xVerts;
	for (int row=0; row<yVerts-1; ++row)
	{
		int col = 0;
		while (true)
		{
			pIndexs[offset++] = start+col;
			pIndexs[offset++] = start+col+lineStep;

			if (col+1 >= xVerts)break;

			col += 1;
		}

		if (row < yVerts-2)
		{
			pIndexs[offset++] = start+col+lineStep;
			pIndexs[offset++] = start+col+1;
		}
		start += lineStep;
	}

	createBuffer(pIndexs, m_count, m_strade);

	delete []pIndexs;

	return true;
}

bool CIndexBuffer::createSingleFanGrid(m_uint16 xCenter, m_uint16 yCenter, 
									   m_uint16 xVerts, m_uint16 yVerts,
									   m_uint16 xStep, m_uint16 yStep)
{
	m_type = TRIANGLE_FAN;
	WORD centerIdx = xCenter*xVerts+yCenter;

	m_uint16 xStepLen = xVerts*xStep;
	m_uint16 yStepLen = yStep;

	int count = 10;
	WORD* pIndexs = new WORD[count];

	pIndexs[0]	= centerIdx;						//center
	pIndexs[1]	= centerIdx+xStepLen-yStepLen;	//left down
	pIndexs[2]	= centerIdx-yStepLen;				//left
	pIndexs[3]	= centerIdx-xStepLen-yStepLen;	//left up
	pIndexs[4]	= centerIdx-xStepLen;				//up
	pIndexs[5]	= centerIdx-xStepLen+yStepLen;	//right up
	pIndexs[6]	= centerIdx+yStepLen;				//right
	pIndexs[7]	= centerIdx+xStepLen+yStepLen;	//right down
	pIndexs[8]	= centerIdx+xStepLen;				//down
	pIndexs[9]	= centerIdx+xStepLen-yStepLen;	//left down

	createBuffer(pIndexs, count, m_strade);
	delete []pIndexs;

	return true;
}

////////////////////////////////////////////////////////////////////////// CVertexBuffer
CVertexBuffer::CVertexBuffer(const CString& name, HardwareBufferType type/*=TRIANGLE_STRIP*/):
CHardwareBuffer(name, type)
{
}

CVertexBuffer::~CVertexBuffer(void)
{
}

}

