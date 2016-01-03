#pragma once
#include "DreamEngine.h"
#include "Images.h"
using namespace DreamEngine;

class CAnimationCompose : public CSingleton<CAnimationCompose>
{
typedef std::vector<CString> ImageLst;

public:
	CAnimationCompose(void);
	~CAnimationCompose(void);

	static CAnimationCompose& instance(void);
	static CAnimationCompose* instancePtr(void);

	bool			compose(const CString& floder, const CString& targetName);
	static void		splitFlieNameAndFolder(const CString& fullPath, OUT CString& fileName, OUT CString& floder);

	void			setImgNumPerRowAndCol(int rowNum, int colNum);

private:

	void		pickImage(const CString& floder);
	bool		composeImage(const ImageLst& imageFiles);

private:

	int			m_imgNumPerRow;
	int			m_imgNumPerCol;

	CString		m_floder;
	CString		m_targetName;

	ImageLst	m_images;
	CImages*	m_pImage;
};
template<> CAnimationCompose* CSingleton<CAnimationCompose>::m_singleton = 0;
