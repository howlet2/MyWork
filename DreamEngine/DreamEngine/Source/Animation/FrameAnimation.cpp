#include "Animation/FrameAnimation.h"
#include "StringHelper.h"

namespace DreamEngine
{
CFrameAnimation::CFrameAnimation(const CString& name):
	m_name(name),
	m_frameIdx(0),
	m_frameNum(0),
	m_intervalSec(0.2f),
	m_accumulateTime(0.0f),
	m_fileType(TP_UNKOWN)
{
}


CFrameAnimation::~CFrameAnimation(void)
{
}

bool CFrameAnimation::initWithFiles(const char* pFileName, ...)
{
	bool ret = true;

	m_frameNum=0;
	m_frameIdx=0;
	m_fileType = TP_TEXTURE_FILES;

	va_list args; 
	va_start(args,pFileName); 
	ret = initWithFilesByVaLst(pFileName,args);
	va_end(args);
	

	return ret;
}

bool CFrameAnimation::initWithFilesByVaLst(const char* pFileName, va_list fileNames)
{
	for (const char* pFile=pFileName; pFile!=MATH_NULL; pFile=static_cast<const char*>(va_arg(fileNames, const char*))) 
		addFrame(pFile);

	return true;
}

bool CFrameAnimation::initWithAnimationFile(const CString& fileName)
{
	m_fileType = TP_ANIMATION_FILE;
	return true;
}

CTexture* CFrameAnimation::addFrame(const char* pTextureFile)
{
	if (pTextureFile!=MATH_NULL) 
	{ 
		CString strNumber = CStringHelper::intToString(m_frameNum);
		CTexture* pTexture = CVideoManager::instancePtr()->createTextureFromFile((m_name+strNumber), pTextureFile);
		m_textures.push_back(pTexture);
		++m_frameNum;

		return pTexture;
	}   

	return MATH_NULL;
}

void CFrameAnimation::update(float delay)
{
	m_accumulateTime += delay;
	if (m_accumulateTime>m_intervalSec*1000)
	{
		m_frameIdx++;
		if (m_frameIdx>=m_frameNum)
			m_frameIdx = 0;
		m_accumulateTime = 0;
		onFrameChange(m_frameIdx);
	}
}

void CFrameAnimation::destory()
{
	for (int i=0; i<int(m_textures.size()); ++i)
		CVideoManager::instancePtr()->destoryTexture(m_textures[i]->getName());

	m_textures.clear();
}

CTexture* CFrameAnimation::getCurrentTexture(void)const
{
	if (m_frameIdx<int(m_textures.size()))
		return m_textures[m_frameIdx];
	
	return MATH_NULL;
}

int	CFrameAnimation::getFrameIndex(void)const
{
	return m_frameIdx;
}

int	CFrameAnimation::getFrameNum(void)const
{
	return m_frameNum;
}

void CFrameAnimation::onFrameChange(int curFrameIdx)
{

}


}