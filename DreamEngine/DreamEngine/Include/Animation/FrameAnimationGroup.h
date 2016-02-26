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

	bool				setAinimationIndex(int index);

	int					getAnimationIndex(void)const;
	int					getAnimationNum(void)const;
	int					getFrameIndex(void)const;
	int					getFrameNum(void)const;

	const CVector2&		getUV(void)const;

protected:

	bool		parseFromFile(const std::string& animationFile);
	CVector2	caculateUV(int animationIdx, int frameIdx);

protected:

	CString			m_name;

	CString			m_animationName;
	int				m_animationNum;
	int				m_frameNum;
	CVector2		m_imageSize;
	CVector2		m_frameImageSize;
	CTexture*		m_pTexture;

	int				m_animationIndex;
	int				m_frameIndex;

	CVector2		m_uv;

	float			m_intervalSec;
	float			m_accumulateTime;
	
};
}

