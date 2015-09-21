#include "GpuProgramManager.h"
#include "GpuTypeManager.h"

namespace DreamEngine
{
CGpuProgramManager::CGpuProgramManager(void)
{
}


CGpuProgramManager::~CGpuProgramManager(void)
{
}

CGpuProgramManager& CGpuProgramManager::instance(void)
{	
	return (*m_singleton); 
}

CGpuProgramManager* CGpuProgramManager::instancePtr(void)
{ 
	return m_singleton; 
}

CGpuProgram* CGpuProgramManager::create(bool needInit/*=false*/)
{
	CGpuProgram* pGpuProgram = _newProgram();
	m_gpuPrograms.push_back(pGpuProgram);

	if (needInit)
	{
		CGpuTypeManager* pTypeManager = CGpuTypeManager::instancePtr();
		if (pTypeManager != MATH_NULL)
			pGpuProgram->initialize(pTypeManager->defaultVertex(), pTypeManager->defaultFragment());
	}

	return pGpuProgram;
}

CGpuProgram* CGpuProgramManager::createAndInitialize(const CString& vertexSource, const CString& framgeSource)
{
	CGpuProgram* pGpuProgram = _newProgram();
	pGpuProgram->initialize(vertexSource, framgeSource);
	m_gpuPrograms.push_back(pGpuProgram);

	return pGpuProgram;
}

CGpuProgram* CGpuProgramManager::createAndInitFromFile(const CString& vertexFileName, const CString& framgeFileName)
{
	CGpuProgram* pGpuProgram = _newProgram();
	pGpuProgram->initializeFromFile(vertexFileName, framgeFileName);
	m_gpuPrograms.push_back(pGpuProgram);

	return pGpuProgram;
}

void CGpuProgramManager::destoryAll()
{
	GpuProgramLst::iterator iter;
	for (iter=m_gpuPrograms.begin(); iter!=m_gpuPrograms.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
}

void CGpuProgramManager::update()
{
	GpuProgramLst::iterator iter;
	for (iter=m_gpuPrograms.begin(); iter!=m_gpuPrograms.end(); ++iter)
	{
		(*iter)->update();
	}
}

}

