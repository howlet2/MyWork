#include "DynLib.h"
#include "EngineDefine.h"

namespace DreamEngine
{

CDynLib::CDynLib(const CString& name):
m_name(name),
m_libHandle(MATH_NULL)
{
}


CDynLib::~CDynLib(void)
{
}

bool CDynLib::load()
{
	m_libHandle = LoadLib(m_name.c_str());

	if (m_libHandle == MATH_NULL)
		return false;

	return true;
}

void CDynLib::free()
{
	FreeLib(m_libHandle);
}

void* CDynLib::getSymbol( const CString& strName )const throw()
{
	return (void*)(GetLibSymbol(m_libHandle, strName.c_str()));
}



CDynLibManager::CDynLibManager()
{

}

CDynLibManager::~CDynLibManager()
{

}

CDynLibManager& CDynLibManager::instance(void)
{	
	return (*m_singleton); 
}

CDynLibManager* CDynLibManager::instancePtr(void)
{ 
	return m_singleton; 
}

CDynLib* CDynLibManager::load(const CString& libFile)
{
	CDynLib* pDynlib = new CDynLib(libFile);
	
	if (pDynlib->load()) 
	{
		m_dynlibs.push_back(pDynlib);
	}
	else
	{
		SAFE_DELETE(pDynlib);
	}

	return pDynlib;
}

bool CDynLibManager::free(const CString& libFile)
{
	DynLibLst::iterator iter;
	for (iter=m_dynlibs.begin(); iter!=m_dynlibs.end(); ++iter)
	{
		if (libFile==(*iter)->getName())
		{
			(*iter)->free();
			return true;
		}
	}
	return false;
}

CDynLib* CDynLibManager::get(const CString& libFile)const
{
	DynLibLst::const_iterator iter;
	for (iter=m_dynlibs.begin(); iter!=m_dynlibs.end(); ++iter)
	{
		if (libFile==(*iter)->getName())
		{
			return (*iter);
		}
	}

	return MATH_NULL;
}

void CDynLibManager::freeAll()
{
	DynLibLst::const_iterator iter;
	for (iter=m_dynlibs.begin(); iter!=m_dynlibs.end(); ++iter)
	{
		(*iter)->free();
	}
}

}

