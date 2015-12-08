#pragma once
#include "GpuProgram.h"
#include "Singleton.h"

namespace DreamEngine
{

class _EngineExport CGpuProgramManager : public CEngineObject, public CSingleton<CGpuProgramManager>
{
public:

	CGpuProgramManager(void);
	virtual ~CGpuProgramManager(void);

	static CGpuProgramManager&	instance(void);
	static CGpuProgramManager*	instancePtr(void);

	CGpuProgram*	create(bool needInit=false);

	CGpuProgram*	createAndInitialize(const CString& vertexSource, const CString& framgeSource);
	CGpuProgram*	createAndInitFromFile(const CString& vertexFileName, const CString& framgeFileName);

	void			destoryAll(void);
	void			update();			

protected:

	typedef std::vector<CGpuProgram*>  GpuProgramLst;
	GpuProgramLst				m_gpuPrograms;

	virtual CGpuProgram*		_newProgram()=0;
};

template<> CGpuProgramManager* CSingleton<CGpuProgramManager>::m_singleton = 0;
}


