#include "GpuProgramManager.h"

namespace DreamEngine
{
CGpuProgramManager::CGpuProgramManager(void)
{
}


CGpuProgramManager::~CGpuProgramManager(void)
{
}

CGpuProgramManager& CGpuProgramManager::Instance(void)
{	
	return (*m_singleton); 
}

CGpuProgramManager* CGpuProgramManager::InstancePtr(void)
{ 
	return m_singleton; 
}

CGpuProgram* CGpuProgramManager::CreateGpuProgram()
{
	CGpuProgram* pGpuProgram = _NewProgram();
	m_gpuPrograms.push_back(pGpuProgram);

	return pGpuProgram;
}

CGpuProgram* CGpuProgramManager::CreateAndInitialize(const CString& vertexSource, const CString& framgeSource)
{
	CGpuProgram* pGpuProgram = _NewProgram();
	pGpuProgram->Initialize(vertexSource, framgeSource);
	m_gpuPrograms.push_back(pGpuProgram);

	return pGpuProgram;
}

CGpuProgram* CGpuProgramManager::CreateAndInitFromFile(const CString& vertexFileName, const CString& framgeFileName)
{
	CGpuProgram* pGpuProgram = _NewProgram();
	pGpuProgram->InitializeFromFile(vertexFileName, framgeFileName);
	m_gpuPrograms.push_back(pGpuProgram);

	return pGpuProgram;
}

void CGpuProgramManager::DestoryAll()
{
	GpuProgramLst::iterator iter;
	for (iter=m_gpuPrograms.begin(); iter!=m_gpuPrograms.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
}

void CGpuProgramManager::Update()
{
	GpuProgramLst::iterator iter;
	for (iter=m_gpuPrograms.begin(); iter!=m_gpuPrograms.end(); ++iter)
	{
		(*iter)->Update();
	}
}

}

