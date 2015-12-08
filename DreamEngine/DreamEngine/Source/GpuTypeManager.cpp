#include "GpuTypeManager.h"

namespace DreamEngine
{
CGpuTypeManager::CGpuTypeManager(void)
{
}


CGpuTypeManager::~CGpuTypeManager(void)
{
}

CGpuTypeManager& CGpuTypeManager::instance(void)
{	
	return (*m_singleton); 
}

CGpuTypeManager* CGpuTypeManager::instancePtr(void)
{ 
	return m_singleton; 
}


}

