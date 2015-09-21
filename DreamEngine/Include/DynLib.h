#pragma once
#include "Engineobject.h"
#include "EngineDefine.h"
#include "Singleton.h"

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

	CDynLibManager();
	~CDynLibManager();

	static CDynLibManager& instance(void);
	static CDynLibManager* instancePtr(void);

	CDynLib*	load(const CString& libFile);
	bool		free(const CString& libFile);
	CDynLib*	get(const CString& libFile)const;
	void		freeAll(void);

private:

	typedef std::vector<CDynLib*> DynLibLst;
	DynLibLst	m_dynlibs;
};

template<> CDynLibManager* CSingleton<CDynLibManager>::m_singleton = 0;

}


