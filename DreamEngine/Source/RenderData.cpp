#include "RenderData.h"

namespace DreamEngine
{
CRenderData::CRenderData(void):
m_pMaterial(MATH_NULL)
{
} 


CRenderData::~CRenderData(void)
{
} 

bool CRenderData::isUseIndexBuffer()const
{
	return m_indexStream.size()>0;
}

bool CRenderData::isEmpty()const
{
	return m_vertexStream.size()<=0;
}

CVertexBuffer* CRenderData::getVertexBuffer(int index)const
{
	VertexStream::const_iterator iter = m_vertexStream.find(index);
	if (iter != m_vertexStream.end())
	{
		return (iter)->second;
	}

	return MATH_NULL;
}

void CRenderData::addVertexBuffer(int index, CVertexBuffer* pVertexBuffer)
{
	m_vertexStream[index] = pVertexBuffer; 
}

CIndexBuffer* CRenderData::getIndexBuffer(int index)const
{
	if (index>=0 && index<=int(m_indexStream.size()))
	{
		return m_indexStream[index];
	}

	return MATH_NULL;
}

void CRenderData::addIndexBuffer(CIndexBuffer* pIndexBuffer)
{
	m_indexStream.push_back(pIndexBuffer);
}

m_uint16 CRenderData::getPatch()const
{
	return static_cast<m_uint16>(m_indexStream.size());
}

HardwareBufferType CRenderData::getRenderType(int index)const
{
	if (index>=0 && index<int(m_indexStream.size()))
	{
		return m_indexStream[index]->getType();
	}
	else if (m_vertexStream.size() > 0)
	{
		return (m_vertexStream.begin())->second->getType();
	}

	return BUFFERTYPE_NULL;
}

void CRenderData::setRenderType(HardwareBufferType type)
{
	if (isUseIndexBuffer())
	{
		IndexStream::iterator iter;
		for (iter=m_indexStream.begin(); iter!=m_indexStream.end(); ++iter)
		{
			(*iter)->setType(type);
		}
	}
	else
	{
		VertexStream::iterator iter;
		for (iter=m_vertexStream.begin(); iter!=m_vertexStream.end(); ++iter)
		{
			iter->second->setType(type);
		}
	}
}

void CRenderData::setRenderType(HardwareBufferType type, int index)
{
	if (index>=0 && index<int(m_indexStream.size()))
	{
		m_indexStream[index]->setType(type);
	}
	else if (m_vertexStream.size() > 0)
	{
		m_vertexStream[index]->setType(type);
	}

}

m_uint16 CRenderData::getElemCount(int index)const
{
	if (index>=0 && index<int(m_indexStream.size()))
	{
		return m_indexStream[index]->elementCount();
	}
	else if (m_vertexStream.size() > 0)
	{
		return (m_vertexStream.begin())->second->elementCount();
	}

	return 0;
}

m_uint16 CRenderData::caculateTrangleCount()const
{
	m_uint16 trangleCount = 0;

	if (m_indexStream.size() > 0)
	{
		for (int idx=0; idx<int(m_indexStream.size()); ++idx)
		{
			trangleCount += m_indexStream[idx]->trangleCount();
		}
	}
	else
	{
		VertexStream::const_iterator iter;
		for (iter=m_vertexStream.begin(); iter!=m_vertexStream.end(); ++iter)
		{
			trangleCount += iter->second->trangleCount();
		}
	}

	return trangleCount;
}

void CRenderData::destory()
{
	VertexStream::iterator iter;
	for (iter=m_vertexStream.begin(); iter!=m_vertexStream.end(); ++iter)
	{
		iter->second->destory();
		SAFE_DELETE(iter->second);
	}
	m_vertexStream.clear();

	for (int i=0; i<int(m_indexStream.size()); ++i)
	{
		m_indexStream[i]->destory();
		SAFE_DELETE(m_indexStream[i]);
	}
}

void CRenderData::addElement(CVertexElement* pElement, m_uint16 count)
{
	if (pElement==MATH_NULL) return;

	for (int i=0; i<count; ++i)
	{
		m_elementLst.push_back(pElement[i]);
	}
}

}

