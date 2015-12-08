#include "FileDataStream.h"

namespace DreamEngine
{
	CFileDataStream::CFileDataStream(void):
m_size(0)
{
}


CFileDataStream::~CFileDataStream(void)
{
	close();
}


bool CFileDataStream::open(const CString& fileName, AccessMode mode/* =READ */)
{
	m_fileName	= fileName;
	m_mode		= mode;

	m_fstream.open(m_fileName.c_str(), m_mode);
	if (!m_fstream.is_open())return false;

	seek(0, END);
	m_size = (int)tell();
	seek(0, BEGIN);

	return true;
}

bool CFileDataStream::close()
{
	if (m_fstream.is_open())
	{
		m_fstream.close();
	}
	return true;
}

bool CFileDataStream::isOpen()const
{
	return m_fstream.is_open();
}

int  CFileDataStream::tell()
{
	int pos = 0;
	if (m_mode&CFileDataStream::WRITE)
	{
		pos = int(m_fstream.tellp());
	}
	else
	{
		pos = int(m_fstream.tellg());
	}
	
	return pos;
}

void CFileDataStream::seek(int offset, FilePos fromPos)
{
	if (m_mode&CFileDataStream::WRITE)
	{
		m_fstream.seekp(std::fstream::off_type(offset),\
			std::ios_base::seekdir(fromPos));
	}
	else
	{
		m_fstream.seekg(std::fstream::off_type(offset),\
			std::ios_base::seekdir(fromPos));
	}
}

bool CFileDataStream::read(void* pBuffer, int dateSize)
{
	if (isEnd() || pBuffer==MATH_NULL)
		return false;

	m_fstream.read((char*)(pBuffer), dateSize);
	return true;
}

bool CFileDataStream::readLine(void* pBuffer, int maxCharLen)
{
	if (isEnd() || pBuffer==MATH_NULL)
		return false;

	m_fstream.getline((char*)(pBuffer), maxCharLen, '\n');

	return true;
}

bool CFileDataStream::readLine(MATH_OUT CString& buf, int maxCharLen/*=128*/)
{
	if (isEnd())
		return false;

	char* pBuf = new char[maxCharLen];
	readLine(pBuf, maxCharLen);

	buf.assign(pBuf);

	return true;
}

bool CFileDataStream::readString(MATH_OUT CString& buf, char endChar/* ='' */)
{
	int cur			= getOffset();
	int remainSize = m_size-getOffset();

	if (remainSize != 0)
	{
		m_fstream.ignore(remainSize, endChar);

		int off = getOffset();
		int size = off-cur;
		if (size > 0)
		{
			seek(-size, CUR);
			char* pBuf = new char[size+1];
			read(pBuf, size);
			pBuf[size] = '\0';
			buf.assign(pBuf);
			SAFE_DELETE_ARRY(pBuf);
		}

		return true;
	}

	return false;
}

void CFileDataStream::write(const void* pBuffer, int dateSize)
{
	if (pBuffer==NULL)
		return;
	
	//m_fstream << pBuffer;
	//m_fstream.write()
	m_fstream.write((const char*)(pBuffer), dateSize);
}

void CFileDataStream::moveToBegin()
{
	seek(0, BEGIN);
}

void CFileDataStream::moveToEnd()
{
	seek(0, END);
}

bool CFileDataStream::isEnd()
{
	return (tell()==m_size);
}

int CFileDataStream::getOffset(int relatPos/* =0 */)
{
	int cur = int(tell());

	return (cur-relatPos);
}

int CFileDataStream::getSize()const
{
	return m_size;
}

void CFileDataStream::getAsString(CString& str)
{
	int off = getOffset();
	moveToBegin();
	char szLine[1024] = {0};  
	while (readLine(szLine, 1024))
	{
		str.append(szLine);
		memset(szLine, 0, 1024);
	}
	seek(off, BEGIN);
}

CString CFileDataStream::getAsString(void)
{
	// 	char* buffer = new char[m_size+1];
	// 
	// 	CString str;
	// 	m_fstream.read(buffer, m_size);
	// 	str.assign(buffer, m_size);
	// 
	// 	delete []buffer;
	CString str;
	int off = getOffset();
	moveToBegin();
	char szLine[1024] = {0};  
	while (m_fstream.getline(szLine, 1024, '\n'))
	{
		str.append(szLine);
		memset(szLine, 0, 1024);
	}
	seek(off, BEGIN);

	return str;
}

}

