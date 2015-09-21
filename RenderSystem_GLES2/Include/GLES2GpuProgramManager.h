#pragma once
#include "GpuProgramManager.h"
#include "GLES2Define.h"
using namespace DreamEngine;

namespace DreamEngineGLES2
{
class _EngineGLES2Export CGLES2GpuProgramManager : public CGpuProgramManager
{
public:
	CGLES2GpuProgramManager(void);
	~CGLES2GpuProgramManager(void);


protected:

	CGpuProgram*			_newProgram();

};
}


