#include "Animation/FrameAnimationGroup.h"
#include "VideoManager.h"

namespace DreamEngine
{
CFrameAnimationGroup::CFrameAnimationGroup(const CString& name):
	m_name(name),
	m_frameNum(0),
	m_accumulateTime(0.0f),
	m_animationNum(0),
	m_intervalSec(0.0f),
	m_frameIndex(0),
	m_animationIndex(0),
	m_pTexture(MATH_NULL)
{
}


CFrameAnimationGroup::~CFrameAnimationGroup(void)
{
	destory();
}

bool CFrameAnimationGroup::loadFromFile(const std::string& animationFile)
{
	if (!parseFromFile(animationFile)) 
		return false;
	
	return true;
}

void CFrameAnimationGroup::update(float delay)
{
	m_accumulateTime += delay;
	if (m_accumulateTime>m_intervalSec*1000)
	{
		m_frameIndex++;
		if (m_frameIndex>=m_frameNum)
			m_frameIndex = 0;
		m_accumulateTime = 0;
		onFrameChange(m_frameIndex);
	}
}

void CFrameAnimationGroup::onFrameChange(int frameIdx)
{
	m_uv = caculateUV(m_animationIndex, m_frameIndex);
}

void CFrameAnimationGroup::destory(void)
{
	if (m_pTexture != MATH_NULL)
		CVideoManager::instancePtr()->destoryTexture(m_pTexture->getName());
}

CTexture*	CFrameAnimationGroup::getCurrentTexture(void)const
{
	return m_pTexture;
}

bool CFrameAnimationGroup::setAinimationIndex(int index)
{
	if (index<0 || index>m_animationNum)
		return false;

	m_frameIndex = 0;
	m_animationIndex = 0;

	return true;
}

int CFrameAnimationGroup::getAnimationIndex()const
{
	return m_animationIndex;
}

int CFrameAnimationGroup::getAnimationNum()const
{
	return m_animationNum;
}

int	CFrameAnimationGroup::getFrameIndex(void)const
{
	return m_frameIndex;
}
int	CFrameAnimationGroup::getFrameNum(void)const
{
	return m_frameNum;
}

const CVector2& CFrameAnimationGroup::getUV()const
{
	return m_uv;
}

bool CFrameAnimationGroup::parseFromFile(const std::string& animationFile)
{
	CFileDataStream fileStream;
	if (fileStream.open(animationFile, CFileDataStream::READ_BINARY))
	{
		int nameLen = 0;
		fileStream.read((char*)(&nameLen), sizeof(nameLen));			//target name length
		char* pName = new char[nameLen];
		fileStream.read(pName, nameLen);
		m_animationName.assign(pName, nameLen);							//name
		SAFE_DELETE_ARRY(pName);

		fileStream.read(&m_animationNum, sizeof(m_animationNum));		//animation num
		fileStream.read(&m_frameNum, sizeof(m_frameNum));				//frameNum
		fileStream.read(&m_imageSize, sizeof(m_imageSize));				//imageSize 
		fileStream.read(&m_frameImageSize, sizeof(m_frameImageSize));	//frame images size

		CImages image;
		image.loadFromFileStream(fileStream);
		m_pTexture = CVideoManager::instancePtr()->createTextureFromImage(m_name+"_texture", &image);
		
		fileStream.close();

		return true;
	}
	return false;
}

CVector2 CFrameAnimationGroup::caculateUV(int animationIdx, int frameIdx)
{
	CVector2 uv;
	uv._x = 1.0f/getFrameNum()*frameIdx;
	uv._y = 1.0f/getAnimationNum()*animationIdx;
	return uv;
}

}