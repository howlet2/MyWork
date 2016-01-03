#include "AnimationCompose.h"

#include "FileDataStream.h"
#include<io.h>
#include <direct.h>

CAnimationCompose::CAnimationCompose(void):
	m_pImage(MATH_NULL),
	m_imgNumPerRow(0),
	m_imgNumPerCol(0)
{
}


CAnimationCompose::~CAnimationCompose(void)
{
}

CAnimationCompose& CAnimationCompose::instance(void)
{	
	return (*m_singleton); 
}

CAnimationCompose* CAnimationCompose::instancePtr(void)
{ 
	return m_singleton; 
}

bool CAnimationCompose::compose(const CString& floder, const CString& targetName)
{
	m_floder = floder;
	m_targetName = targetName;

	pickImage(m_floder);
	return composeImage(m_images);
}

void CAnimationCompose::splitFlieNameAndFolder(const CString& fullPath, OUT CString& fileName, OUT CString& floder)
{
	CString::size_type pos = fullPath.rfind('/');
	if (pos==CString::npos)
		pos = fullPath.rfind('\\');
	if (pos==CString::npos)
	{
		fileName = fullPath;
		floder = "";
	}

	if (pos!=CString::npos && (pos+1)<fullPath.length())
	{
		floder.assign(fullPath.c_str(),pos+1); 
		fileName.assign(fullPath.c_str(), pos+1);
	}
}

void CAnimationCompose::setImgNumPerRowAndCol(int rowNum, int colNum)
{
	m_imgNumPerRow = rowNum;
	m_imgNumPerCol = colNum;
}

bool CAnimationCompose::composeImage(const ImageLst& imageFiles)
{
	m_byte* pData = nullptr;
	std::vector<CImages*> images;
	int totalSize		= 0;
	int imgWidth		= 0;
	int imgHeight		= 0;
	int smallImgWidth	= 0;
	int smallImgHeight	= 0;

 	TEX_FORMAT texFormat = TF_UNKOWN;
	for (int i=0; i<int(imageFiles.size()); ++i)
	{
		CImages* pImage = new CImages();
		pImage->loadFromFile(imageFiles[i]);
	
		if (i==0)
		{
			texFormat		= pImage->getTexFormat();

			smallImgWidth	= pImage->getWidth();
			smallImgHeight	= pImage->getHeight();

			imgWidth	= smallImgWidth*m_imgNumPerRow;
			imgHeight	= smallImgHeight*m_imgNumPerCol;
		}
		totalSize += pImage->getDataSize();

		images.push_back(pImage);
	}

	pData = new m_byte[totalSize];
	int offset		= 0;
	int perByteSize	= CImages::formatToPixelPerBytes(texFormat);
	int perRowSize  = perByteSize*smallImgWidth;

	for (int col=0; col<imgHeight; ++col)
	{
		int imgBeginIdx = col/smallImgHeight*m_imgNumPerRow;
		int imgBeginCol = col%(smallImgHeight);
		for (int j = 0; j < m_imgNumPerRow; j++)
		{
			int idx = imgBeginIdx+j;
			int dataSize = smallImgWidth*perByteSize;
			memcpy(pData+offset, images[idx]->getData()+perRowSize*imgBeginCol, dataSize);
			offset+=dataSize;
		}
	}

	for (int i=0; i<int(images.size()); ++i)
		SAFE_DELETE(images[i]);
	
	if(_mkdir((m_floder+"out/").c_str())!=0)
	{
		CImages* pImage = CImages::makeImage(pData, imgWidth, imgHeight, texFormat);
		pImage->saveToFile(m_floder+"out/"+m_targetName);
		SAFE_DELETE(pImage);
	}
	SAFE_DELETE(pData);
	return true;
}

void CAnimationCompose::pickImage(const CString& floder)
{
	CString path = floder+"*.*";
	long handle;
	_finddata_t fileInfo;
	if((handle=_findfirst(path.c_str(),&fileInfo))==-1L)
	{
		std::cout << "folder is empty!" << std::endl;
	}
	else
	{
		std::cout << fileInfo.name << std::endl;
		do 
		{
			CString flieName=fileInfo.name;
			if (  flieName.find(".png")!=CString::npos
				||flieName.find(".tga")!=CString::npos
				||flieName.find(".jpg")!=CString::npos)
			{
				m_images.push_back(floder+fileInfo.name);

				if (int(m_images.size())>=(m_imgNumPerRow*m_imgNumPerCol))
					break;
			}
		} while (_findnext(handle,&fileInfo)==0);
		
		_findclose(handle);
	}
}
