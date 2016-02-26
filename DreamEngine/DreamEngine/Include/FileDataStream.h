#pragma once
#include <fstream>
#include "EngineObject.h"

namespace DreamEngine
{
class _EngineExport CFileDataStream : public CEngineObject
{

public:
	enum AccessMode
	{
		READ	= std::ios::in,					//read
		WRITE	= std::ios::out,				//write
		APP	    = std::ios::app,				//open pos to end (can not change pos)
		ATE	    = std::ios::ate,				//open pos to end (can change pos)
		TRUNC   = std::ios::trunc,				//remove all data before open 

		READ_BINARY		= std::ios::in|std::ios::binary, 
		WRITE_BINARY	= std::ios::out|std::ios::binary, 
		WRITE_TRUNC		= std::ios::out|std::ios::trunc,
		WRITE_APP		= std::ios::out|std::ios::app,
		WRITE_APP_BINARY= std::ios::out|std::ios::app|std::ios::binary,
	};

	enum FilePos
	{
		END		=	std::ios::end, 
		CUR		=	std::ios::cur,
		BEGIN	=	std::ios::beg,
	};

public:
	CFileDataStream(void);
	~CFileDataStream(void);

	template <class T>
	CFileDataStream& operator << (const T& vaule)
	{
		if (isOpen())
			m_fstream << vaule;

		return *this;
	}

	template <class T>
	CFileDataStream& operator >> (T& vaule)
	{
		if (isOpen())
			m_fstream >> vaule;

		return *this;
	}

	bool		open(const CString& fileName, AccessMode mode=READ);
	bool		close(void);
	bool		isOpen(void)const;

	int			tell(void);
	void		seek(int offset, FilePos fromPos);
 
	bool		read(void* pBuffer, int dateSize);
	bool		readLine(void* pBuffer, int maxCharLen);
	bool		readLine(MATH_OUT CString& buf, int maxCharLen=128);
	bool		readString(MATH_OUT CString& buf, char endChar='\0');
	void		write(const void* pBuffer, int dateSize);
	
	void		moveToBegin(void);
	void		moveToEnd(void);

	int			getOffset(int relatPos=0);
	int			getSize()const;
	bool		isEnd(void);

	void        getAsString(CString& str);								//line max length is 1024
	CString     getAsString(void);

protected:

	int				m_size;
	CString			m_fileName;
	std::fstream	m_fstream;

	AccessMode		m_mode;
};
}
