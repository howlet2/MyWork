#pragma once
#include "EngineObject.h"
#include "Texture.h"

namespace DreamEngine
{
class _EngineExport CFrameAnimationGroup : public CEngineObject
{

public:
	CFrameAnimationGroup(const CString& name);
	~CFrameAnimationGroup(void);

	bool				loadFromFile(const std::string& animationFile);
	
	virtual void		update(float delay);
	void				onFrameChange(int frameIdx);
	void				destory(void);

	CTexture*			getCurrentTexture(void)const;
	int					getFrameIndex(void)const;
	int					getFrameNum(void)const;

protected:

	bool		parseFromFile(const std::string& animationFile);

protected:

	CString			m_name;

	CString			m_animationName;
	int				m_animationNum;
	int				m_frameNum;
	CVector2		m_imageSize;
	CVector2		m_frameImageSize;
	CImages*		m_pImageData;
	int				m_frameIndex;

	float			m_intervalSec;
	float			m_accumulateTime;
	
};
}

