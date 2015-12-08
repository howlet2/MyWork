#pragma once
#include "GpuTypeManager.h"
#include "Singleton.h"
#include "GLES2Define.h"
using namespace DreamEngine;

namespace DreamEngineGLES2
{

class _EngineGLES2Export CGLES2GpuTypeManager : public CGpuTypeManager
{
public:

	CGLES2GpuTypeManager(void);
	virtual ~CGLES2GpuTypeManager(void);

	virtual const char* defaultVertex();
	virtual const char* defaultFragment();
	virtual const char* defaultTextureFragment();

};

}


