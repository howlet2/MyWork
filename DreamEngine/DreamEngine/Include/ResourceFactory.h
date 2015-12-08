#pragma once
#include "EngineObject.h"

namespace DreamEngine
{
template <class ResourceType>
class  CRosourceFactory : public CEngineObject
{
public:

	typedef std::list<ResourceType*> ResourceLst;
	
//	typedef CIteratorWrapper<ResourceLst::iterator, ResourceType> ResourceIter;

	CRosourceFactory()
	{
	}

	virtual ~CRosourceFactory(void)
	{
	//	DestoryAll();
	}

	virtual ResourceType* create(const CString& name)
	{
		ResourceType* pNewResource = get(name);
		if (pNewResource==MATH_NULL)
		{
			pNewResource = new ResourceType(name);
			m_resources.push_back(pNewResource);
		}
		return pNewResource;
	}

	ResourceType* get(const CString& name)const
	{
		ResourceLst::const_iterator iter;
		for (iter=m_resources.begin(); iter!=m_resources.end(); ++iter)
		{
			if ((*iter)->getName()==name)
			{
				return (*iter);
			}
		}
		return NULL;
	}

	virtual bool destory(const CString& name)
	{
		ResourceLst::const_iterator iter;
		for (iter=m_resources.begin(); iter!=m_resources.end(); ++iter)
		{
			if ((*iter)->getName()==name)
			{
				ResourceType* pResource = (*iter);
				m_resources.erase(iter);
				SAFE_DELETE(pResource);
				return true;
			}
		}
		return false;
	}

	virtual void destoryAll(void)
	{
		ResourceLst::iterator iter, tempIter;
	
		for (iter=m_resources.begin(); iter!=m_resources.end();)
		{
			ResourceType* pResource = (*iter);
			tempIter = iter;++iter;

			m_resources.erase(tempIter);
			SAFE_DELETE(pResource);
		}
	}

	const ResourceLst& getResourceLst()const	
	{
		return m_resources;
	}

protected:
	
	ResourceLst				m_resources;
	
};

}

