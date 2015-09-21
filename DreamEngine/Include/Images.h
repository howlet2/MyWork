#pragma once
#include "EngineObject.h"
#include "FileDataStream.h"

namespace DreamEngine
{
enum TEX_FORMAT
{
	TF_UNKOWN	   = 0,
	TF_R8G8B8      = 1,
	TF_A8R8G8B8    = 2,
	TF_R8G8B8A8	   = 3,
	TF_X8R8G8B8    = 4,
	TF_L8          = 5,
	TF_X8L8V8U8    = 6,
};

class _EngineExport CImages : public CEngineObject
{
public:
	CImages(void);
	~CImages(void);

	m_byte*		getData()const			{return m_pData;}
	int			getWidth()const			{return m_width;}
	int			getHeight()const		{return m_height;}
	TEX_FORMAT  getTexFormat()const		{return m_texFormat;}
	int			getPixelPerBytes()const	{return m_pixelPerBytes;}

	m_byte*		loadFromFile(const CString& fileName);

private:
	
	bool		isTga(m_byte* header);
	bool		isPng(m_byte* header);
	bool		isJpeg(m_byte* header);

	m_byte*		initWithTgaFile(CFileDataStream& fileData);
	m_byte*		initWithPngFile(CFileDataStream& fileData);
	m_byte*		initWithJpegFile(CFileDataStream& fileData);

protected:

	void		_initUnComposeTgaFile(m_byte* pData, int dataSize);
	void		_initComposeTgaFile(CFileDataStream& fileData, m_byte* pData, int dataSize);
	void		_flipTagFile(m_byte* pData);

	m_byte*		m_pData;
	int			m_width;
	int			m_height;
	TEX_FORMAT  m_texFormat;
	int			m_pixelPerBytes;
};
}
