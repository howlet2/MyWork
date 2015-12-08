#pragma once
#include "EngineObject.h"
#include "FileDataStream.h"
#include "IteratorWrapper.h"

namespace DreamEngine
{
class _EngineExport  CAtlas  : public CEngineObject
{
public:

struct tSlice
{
	CString		name;
	bool		isRotate;
	CVector2	point;
	CVector2	size;
	CVector2	orig;
	CVector2	offset;
	int			index;
};

typedef std::vector<tSlice> SliceLst;
typedef CIteratorWrapper<SliceLst::iterator, tSlice> SliceParamIter;

public:
	CAtlas(void);
	~CAtlas(void);

	bool			loadFromFile(const CString& file);
	SliceParamIter  getSliceIter(void)const;
	const CString&  getTextureFilePath(void)const;
	
private:

	TEX_FORMAT		stringToTexFormat(const CString& strTexFormat);
	CString			dealToken(CFileDataStream& fileStream);


private:
	
	CString			m_textureFilePath;
	TEX_FORMAT		m_texFormat;
	//filter: Linear,Linear
	//repeat: none

	
	SliceLst		m_region;
	SliceParamIter	m_sliceIter;
};

}

