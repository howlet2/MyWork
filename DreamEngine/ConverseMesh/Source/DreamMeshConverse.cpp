#include "DreamMeshConverse.h"

static char* g_dMeshTokens[DMT_NUM] = {"", "mesh", "subMesh", "vertex", "textureCoord", "index"};

CDreamMeshConverse::CDreamMeshConverse(void)
{
}


CDreamMeshConverse::~CDreamMeshConverse(void)
{
}

void CDreamMeshConverse::converseToTxt(const CString& fileName)
{
	
}

void CDreamMeshConverse::converseToBinary(const CString& fileName)
{
	m_inputFile.open(fileName);

	if (m_inputFile.isOpen())
	{
		CString outFile = makeOutFileName(fileName);
		m_outputFile.open(outFile, CFileDataStream::WRITE_BINARY);

		if (m_outputFile.isOpen())
		{
			CString line;
			CString oneToken;
			while (readNextValidLine(line))
			{
				if (isTokenLine(line))
				{
					if (oneToken.length()>0)
					{
						oneToken.pop_back();		//弹出末尾多出的一个空格
						writeData(oneToken);
						oneToken.clear();
					}

					if (line.length()>0)
						writeData(line);
				}
				else
				{
					oneToken.append(line);
					oneToken.push_back(' ');
				}
			}
			m_inputFile.close();
			m_outputFile.close();
		}
	}
	else
	{
		std::cout << "input file not exist" << std::endl;
	}

}

bool CDreamMeshConverse::readNextValidLine(MATH_OUT  CString& line)
{
	while (!m_inputFile.isEnd())
	{
		m_inputFile.readLine(line, MAX_TOKEN_LENGTH);
		if (makeValidLine(line))
			break;
	}

	return !m_inputFile.isEnd();
}

bool CDreamMeshConverse::makeValidLine(MATH_OUT CString& line)
{
	CString::size_type off = -1;

	//delete note
	const char* strParse = "//";
	off = line.find(strParse,0);
	if (off != CString::npos)
		line.erase(off,line.length()-off);

	//delete'{', '}'
	off = line.find('{', 0);
	if (off != CString::npos)
		line.erase(off, 1);
	off = line.find('}', 0);
	if (off != CString::npos)
		line.erase(off, 1);

	if (line.length()<=0) 
		return false;

	//delete front spaces and tab
	int bCount = 0;
	for (CString::size_type i=0; i<line.length(); ++i)
	{
		if (line[i] == ' ' || line[i]==9)
			bCount++;
		else
			break;
	}
	if (bCount>0)
		line.erase(0, bCount);
	if (line.length()<=0) 
		return false;

	//delete end spaces and tab
	bCount = 0;
	for (CString::size_type i=line.length()-1; i>=0; --i)
	{
		if (line[i] == ' ' ||  line[i]==9)
			bCount++;
		else
			break;
	}
	if (bCount>0)
		line.erase(line.length()-bCount, bCount);
	if (line.length()<=0) 
		return false;

	return (line.length()>0);
}

bool CDreamMeshConverse::isTokenLine(const CString& line)
{
	for (int idx=1; idx<int(DMT_NUM); ++idx)
	{
		if (line.find(g_dMeshTokens[idx]) != CString::npos)
			return true;
	}
	return false;
}

void CDreamMeshConverse::writeData(const CString& data)
{
	m_byte  bLine[MAX_TOKEN_LENGTH+1];
	if (data.length()>0)
	{
		m_byte dataSize = static_cast<m_byte>(data.length());
		bLine[0]=dataSize;
		memcpy(bLine+1, data.c_str(), dataSize);
		m_outputFile.write(bLine, dataSize+1) ;
	}
}

CString CDreamMeshConverse::makeOutFileName(const CString& inFileName)
{
	CString outFile;
	for (CString::size_type i=0; i<inFileName.length(); ++i)
	{
		if (inFileName[i] != '.')
			outFile.push_back(inFileName[i]);
		else
			break;
	}

	if (inFileName.find(".dmesh") != CString::npos)
	{
		outFile.append(".txt");
	}
	else if(inFileName.find(".txt") != CString::npos)
	{
		outFile.append(".dmesh");
	}

	return outFile;
}







