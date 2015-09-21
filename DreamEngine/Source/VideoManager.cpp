#include "VideoManager.h"

namespace DreamEngine
{
CVideoManager::CVideoManager(void)
{} 

CVideoManager::~CVideoManager()
{
	
}

void CVideoManager::destoryAll()
{
	IndexBufferLst::iterator iterIdx;
	for (iterIdx=m_indexBuffers.begin(); iterIdx!=m_indexBuffers.end(); ++iterIdx)
	{
		(*iterIdx)->destory();
	}

	VertexBufferLst::iterator iterVec;
	for (iterVec=m_vertexBuffers.begin(); iterVec!=m_vertexBuffers.end(); ++iterVec)
	{
		(*iterVec)->destory();
	}


	TextureLst::iterator iterTex;
	for (iterTex=m_textures.begin(); iterTex!=m_textures.end(); ++iterTex)
	{
		(*iterTex)->release();
	}
}

CVideoManager& CVideoManager::instance(void)
{	
	return (*m_singleton); 
}

CVideoManager* CVideoManager::instancePtr(void)
{ 
	return m_singleton; 
}


}