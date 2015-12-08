#pragma once
#include "FileDataStream.h"
#include "MathDefine.h"
#include "DreamMeshDefine.h"
using namespace DreamEngine;

class CDreamMeshConverse
{
public:
	CDreamMeshConverse(void);
	~CDreamMeshConverse(void);

	void		converseToTxt(const CString& fileName);
	void		converseToBinary(const CString& fileName);

private:

	bool		readNextValidLine(MATH_OUT  CString& line);			//���ص�ǰ�����ļ�β
	bool		makeValidLine(MATH_OUT CString& line);				//���ص�ǰ���Ƿ���Ч
	bool		isTokenLine(const CString& line);
	void		writeData(const CString& data);

	CString		makeOutFileName(const CString& inFileName);

private:

	static const int	m_tokeEndFlag		= 3;

	CFileDataStream		m_inputFile;
	CFileDataStream		m_outputFile;
};

