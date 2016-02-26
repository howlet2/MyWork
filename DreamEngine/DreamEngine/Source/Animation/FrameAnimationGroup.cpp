#include "Animation/FrameAnimationGroup.h"

namespace DreamEngine
{
CFrameAnimationGroup::CFrameAnimationGroup(const CString& name):
	m_name(name),
	m_frameNum(0),
	m_accumulateTime(0.0f),
	m_animationNum(0.0f),
	m_intervalSec(0.0f),
	m_frameIndex(0),
	m_pImageData(MATH_NULL)
{
}


CFrameAnimationGroup::~CFrameAnimationGroup(void)
{
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

}

void CFrameAnimationGroup::destory(void)
{

}

CTexture*	CFrameAnimationGroup::getCurrentTexture(void)const
{

}
int	CFrameAnimationGroup::getFrameIndex(void)const
{

}
int	CFrameAnimationGroup::getFrameNum(void)const
{

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

		m_pImageData = new CImages;
		m_pImageData->loadFromFileStream(fileStream);

		

		fileStream.close();

		return true;
	}
	return false;
}
}