#include "GLES2GpuProgramManager.h"
#include "GLES2GLSLProgram.h"

namespace DreamEngineGLES2
{

CGLES2GpuProgramManager::CGLES2GpuProgramManager()
{
}


CGLES2GpuProgramManager::~CGLES2GpuProgramManager(void)
{
}

CGpuProgram* CGLES2GpuProgramManager::_newProgram()
{
	return new CGLES2GLSLProgram();
}

}

