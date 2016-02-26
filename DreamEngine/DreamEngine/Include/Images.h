#pragma once
#include "EngineObject.h"
#include "FileDataStream.h"

namespace DreamEngine
{

class _EngineExport CImages : public CEngineObject
{
public:
	enum ImageType
	{
		TYPE_PNG = 0,
		TYPE_JPG = 1,
		TYPE_TGA = 2,
	};

public:
	CImages(void);
	~CImages(void);

	static CImages*	makeImage(m_byte* pData, int width, int height, TEX_FORMAT texFormat);
	static int		formatToPixelPerBytes(TEX_FORMAT format);
	static CString  typeToFileSuffix(ImageType imageType);

	m_byte*		getData()const			{return m_pData;}
	int			getWidth()const			{return m_width;}
	int			getHeight()const		{return m_height;}
	TEX_FORMAT  getTexFormat()const		{return m_texFormat;}
	int			getPixelPerBytes()const	{return m_pixelPerBytes;}
	ImageType   getImageType()const		{return m_imgType;}
	int			getDataSize()const		{return getHeight()*getWidth()*getPixelPerBytes();}

	bool		loadFromFile(const CString& fileName);
	bool		loadFromFileStream(CFileDataStream& fileStream);
	bool		saveToFile(const CString& filePath);

private:
	
	bool		isTga(m_byte* header);
	bool		isPng(m_byte* header);
	bool		isJpeg(m_byte* header);

	m_byte*		initWithTgaFile(CFileDataStream& fileData);
	m_byte*		initWithPngFile(CFileDataStream& fileData);
	m_byte*		initWithJpegFile(CFileDataStream& fileData);

	bool		saveToPng(const CString& filePath);
	bool		saveToJpg(const CString& filePath);

protected:

	void		_initUnComposeTgaFile(m_byte* pData, int dataSize);
	void		_initComposeTgaFile(CFileDataStream& fileData, m_byte* pData, int dataSize);
	void		_flipTagFile(m_byte* pData);

	m_byte*		m_pData;
	int			m_width;
	int			m_height;
	TEX_FORMAT  m_texFormat;
	int			m_pixelPerBytes;
	ImageType   m_imgType;
};
}
