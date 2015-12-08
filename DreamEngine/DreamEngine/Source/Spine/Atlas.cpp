#include "Atlas.h"
#include "StringHelper.h"

namespace DreamEngine
{
CAtlas::CAtlas(void):
m_sliceIter(m_region.begin(), m_region.end())
{
}


CAtlas::~CAtlas(void)
{
}

bool CAtlas::loadFromFile(const CString& file)
{
	CFileDataStream fileStream;
	fileStream.open(file);
	if (fileStream.isOpen())
	{
		CString curVaule;
		if (!fileStream.isEnd())
		{
			dealToken(fileStream);						//first line is empty
			m_textureFilePath	= dealToken(fileStream);	//texture name;
			curVaule		= dealToken(fileStream);	//texture format
			m_texFormat		= stringToTexFormat(curVaule);

			curVaule		= dealToken(fileStream);	//filters
			curVaule		= dealToken(fileStream);	//repeat;

			//pages start
			while (!fileStream.isEnd())
			{
				tSlice curSlice;
					
				curSlice.name = dealToken(fileStream);
				
				curVaule = dealToken(fileStream);
				curSlice.isRotate = CStringHelper::stringToBool(curVaule);

				curVaule = dealToken(fileStream);
				sscanf_s(curVaule.c_str(), "%f, %f", &curSlice.point._x, &curSlice.point._y);

				curVaule = dealToken(fileStream);
				sscanf_s(curVaule.c_str(), "%f, %f", &curSlice.size._x, &curSlice.size._y);

				curVaule = dealToken(fileStream);
				sscanf_s(curVaule.c_str(), "%f, %f", &curSlice.orig._x, &curSlice.orig._y);

				curVaule = dealToken(fileStream);
				sscanf_s(curVaule.c_str(), "%f, %f", &curSlice.offset._x, &curSlice.offset._y);

				curVaule = dealToken(fileStream);
				curSlice.index = CStringHelper::stringToInt(curVaule);

				m_region.push_back(curSlice);
			}
		}

		fileStream.close();
		m_sliceIter.set(m_region.begin(), m_region.end());

		return true;
	}

	return false;
}

CAtlas::SliceParamIter CAtlas::getSliceIter()const
{
	return m_sliceIter;
}

const CString& CAtlas::getTextureFilePath()const
{
	return m_textureFilePath;
}

TEX_FORMAT CAtlas::stringToTexFormat(const CString& strTexFormat)
{
	if (strTexFormat=="RGBA8888")
	{
		return TF_R8G8B8A8;
	}
	else
	{
		return TF_UNKOWN;
	}
}

CString CAtlas::dealToken(CFileDataStream& fileStream)
{
	CString line;
	fileStream.readLine(line);

	CString::size_type pos = line.find(": ");
	if (pos != CString::npos)
		line.erase(0, pos+2);
	return line;
}

}

