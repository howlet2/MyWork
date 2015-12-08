#include "VideoManager.h"

namespace DreamEngine
{
CVideoManager::CVideoManager(void)
{} 

CVideoManager::~CVideoManager()
{
	
}

bool CVideoManager::destoryIndexBuffer(const CString& name)
{
	IndexBufferLst::iterator iter = m_indexBuffers.find(name);
	if (iter!=m_indexBuffers.end())
	{
		iter->second->destroy();
		SAFE_DELETE(iter->second);
		m_indexBuffers.erase(iter);
		return true;
	}
	return false;
}

bool CVideoManager::destoryVertexBuffer(const CString& name)
{
	VertexBufferLst::iterator iter = m_vertexBuffers.find(name);
	if (iter!=m_vertexBuffers.end())
	{
		iter->second->destroy();
		SAFE_DELETE(iter->second);
		m_vertexBuffers.erase(iter);
		return true;
	}
	return false;
}

bool CVideoManager::destoryTexture(const CString& name)
{
	TextureLst::iterator iter = m_textures.find(name);
	if (iter!=m_textures.end())
	{
		iter->second->release();
		SAFE_DELETE(iter->second);
		m_textures.erase(iter);
		return true;
	}
	return false;
}

void CVideoManager::destoryAll()
{
	for (IndexBufferLst::iterator iterIdx=m_indexBuffers.begin(); iterIdx!=m_indexBuffers.end(); ++iterIdx)
	{
		iterIdx->second->destroy();
		SAFE_DELETE(iterIdx->second);
	}

	for (VertexBufferLst::iterator iterVec=m_vertexBuffers.begin(); iterVec!=m_vertexBuffers.end(); ++iterVec)
	{
		iterVec->second->destroy();
		SAFE_DELETE(iterVec->second);
	}

	for (TextureLst::iterator iterTex=m_textures.begin(); iterTex!=m_textures.end(); ++iterTex)
	{
		iterTex->second->release();
		SAFE_DELETE(iterTex->second);
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