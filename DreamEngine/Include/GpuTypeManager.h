#pragma once
#include "GpuProgram.h"
#include "Singleton.h"

namespace DreamEngine
{

class _EngineExport CGpuTypeManager : public CEngineObject, public CSingleton<CGpuTypeManager>
{
public:

	CGpuTypeManager(void);
	virtual ~CGpuTypeManager(void);

	static CGpuTypeManager&	instance(void);
	static CGpuTypeManager*	instancePtr(void);

	virtual const char* defaultVertex()=0;
	virtual const char* defaultFragment()=0;

};

template<> CGpuTypeManager* CSingleton<CGpuTypeManager>::m_singleton = 0;
}


