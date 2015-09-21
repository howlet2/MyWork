#include "MaterialManager.h"

namespace DreamEngine
{
CMaterialManager::CMaterialManager(void)
{
}


CMaterialManager::~CMaterialManager(void)
{
}

CMaterialManager& CMaterialManager::instance(void)
{	
	return (*m_singleton); 
}

CMaterialManager* CMaterialManager::instancePtr(void)
{ 
	return m_singleton; 
}
}

