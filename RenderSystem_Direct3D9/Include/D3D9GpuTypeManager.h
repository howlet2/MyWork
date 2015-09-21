#pragma once
#include "GpuTypeManager.h"
#include "Singleton.h"
#include "D3D9Define.h"
using namespace DreamEngine;

namespace DreamEngineD3D
{

class _EngineD3D9Export CD3D9GpuTypeManager : public CGpuTypeManager
{
public:

	CD3D9GpuTypeManager(void);
	virtual ~CD3D9GpuTypeManager(void);

	virtual const char* defaultVertex();
	virtual const char* defaultFragment();

};

}


