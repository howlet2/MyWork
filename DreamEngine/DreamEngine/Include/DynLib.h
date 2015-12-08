#pragma once
#include "Engineobject.h"
#include "EngineDefine.h"
#include "Singleton.h"
#include "IteratorWrapper.h"

namespace DreamEngine
{

class _EngineExport CDynLib : public CEngineObject
{
public:
	CDynLib(const CString& name);
	~CDynLib(void);
	
	const CString& getName()const	{return m_name;}

	bool	load();
	void	free();
	void*	getSymbol( const CString& strName ) const throw();

protected:

	CString			m_name;
	DynLibHandle	m_libHandle;
};

class _EngineExport CDynLibManager: public CEngineObject, public CSingleton<CDynLibManager>
{
public:
	typedef std::vector<CDynLib*> DynLibLst;
	typedef CIteratorWrapper<DynLibLst::iterator, CDynLib*> DynLibIter;

public:

	CDynLibManager();
	~CDynLibManager();

	static CDynLibManager& instance(void);
	static CDynLibManager* instancePtr(void);

	CDynLib*	load(const CString& libFile);
	CDynLib*	get(const CString& libFile)const;
	DynLibIter& getDynLibIter(void)		{return m_dynLibIter;}

	void		freeAll(void);
	

private:

	bool		_free(CDynLib* pDynLib);
	
private:

	DynLibLst	m_dynlibs;
	DynLibIter  m_dynLibIter;
};

template<> CDynLibManager* CSingleton<CDynLibManager>::m_singleton = 0;

}


