#pragma once
#include "Singleton.h"
#include "Material.h"
#include "ResourceFactory.h"

namespace DreamEngine
{
class CMaterialManager : public CSingleton<CMaterialManager>, public CRosourceFactory<CMaterial>
{
public:

	CMaterialManager(void);
	~CMaterialManager(void);

	static CMaterialManager& instance(void);
	static CMaterialManager* instancePtr(void);
};

template<> CMaterialManager* CSingleton<CMaterialManager>::m_singleton = 0;
}

