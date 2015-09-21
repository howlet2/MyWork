#pragma once
#include "meshloader.h"
#include "FileDataStream.h"
#include "DreamMeshDefine.h"

namespace DreamEngine
{
class _EngineExport CDreamMeshLoader : public CMeshLoader
{
public:
	CDreamMeshLoader(void);
	~CDreamMeshLoader(void);

	virtual bool	loadFromFile(const CString& name, CMesh* pMesh);

protected:

	bool			readOneToken(MATH_OUT CString& oneToken);		//返回是否文件读取结束
	void			dealToken(const  CString& token);
	CSubMesh*		readSubMesh(const CString& subMeshName);
	CVertexBuffer*	readVertexBuffer(void);

	CFileDataStream		m_readFile;
	CMesh*				m_pCurMesh;

private:

	DreamMeshToken		m_curToken;


private:

	static const int	m_tokeEndFlag		= 3;

	typedef std::map<CString, DreamMeshToken>	DictionaryLst;
	static DictionaryLst		m_tokens;

	static	void				makeTokens();
	static  DreamMeshToken		getToken(const CString& line, MATH_OUT CString& name);
};

}

