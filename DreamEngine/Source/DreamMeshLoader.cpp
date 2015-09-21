#include "DreamMeshLoader.h"
#include "VideoManager.h"

namespace DreamEngine
{
CDreamMeshLoader::DictionaryLst CDreamMeshLoader::m_tokens;

CDreamMeshLoader::CDreamMeshLoader(void)
{
	makeTokens();
}


CDreamMeshLoader::~CDreamMeshLoader(void)
{
}

bool CDreamMeshLoader::loadFromFile(const CString& name, CMesh* pMesh)
{
	m_pCurMesh = pMesh;

	if (m_readFile.isOpen())
		m_readFile.close();

	
	if (m_readFile.open(name, CFileDataStream::READ_BINARY))
	{
		CString token;
		while (!readOneToken(token))
			dealToken(token);
	}
	return true;
}

bool CDreamMeshLoader::readOneToken(MATH_OUT CString& oneToken)
{
	if (!m_readFile.isEnd())
	{
		char	buff[MAX_TOKEN_LENGTH] = "";
		int dataSize = 0;
		m_readFile.read(&dataSize, 1);
		m_readFile.read(buff, dataSize);
		oneToken.assign(buff, dataSize);
	}
	return m_readFile.isEnd();
}

void CDreamMeshLoader::dealToken(const CString& line)
{
	CString tokenName;
	DreamMeshToken token = getToken(line,tokenName);
	if (token != DMT_NONE)
		m_curToken = token;

	switch (m_curToken)
	{
	case DMT_MESH:
		 break;

	case DMT_SUBMESH:
		{
			m_pCurMesh->addSubMesh(readSubMesh(tokenName));
		}break;
	}
	
}

CSubMesh* CDreamMeshLoader::readSubMesh(const CString& subMeshName)
{
	CSubMesh* pSubMesh = new CSubMesh(subMeshName);
	CString line, tokenName;
	bool isSubMeshToken = true;
	while (readOneToken(line))
	{
		DreamMeshToken token = getToken(line,tokenName);
		switch (token)
		{
		case DMT_VECTEX:
			{
				pSubMesh->getRenderDataPtr()->addVertexBuffer(0,)
			}break;

		case DMT_TEXTURECOORD:
			{

			}break;

		case DMT_INDEX:
			{

			}break;

		default:
			{
				return pSubMesh;
			}break;
		}
	} 
	
	return pSubMesh;
}

CVertexBuffer* CDreamMeshLoader::readVertexBuffer(void)
{
	//CVideoManager::instancePtr()->createVertexBuffer();
}

void CDreamMeshLoader::makeTokens()
{
	m_tokens[""]			 = DreamEngine::DMT_NONE;
	m_tokens["mesh"]		 = DreamEngine::DMT_MESH;
	m_tokens["subMesh"]		 = DreamEngine::DMT_SUBMESH;
	m_tokens["vertex"]		 = DreamEngine::DMT_VECTEX;
	m_tokens["textureCoord"] = DreamEngine::DMT_TEXTURECOORD;
	m_tokens["index"]		 = DreamEngine::DMT_INDEX;
}

DreamMeshToken CDreamMeshLoader::getToken(const CString& line,  MATH_OUT CString& name)
{
	DictionaryLst::iterator iter;
	for (iter=m_tokens.begin(); iter!=m_tokens.end(); ++iter)
	{
		if (iter->second!=DMT_NONE && line.find(iter->first) != CString::npos)
		{
			CString::size_type off = line.find(' ');
			if (off != CString::npos)
			{
				for (CString::size_type i=off+1; i<line.length(); ++i)
					name.push_back(line[i]);
			}
			
			return iter->second;
		}
	}
	return DMT_NONE;
}

}

