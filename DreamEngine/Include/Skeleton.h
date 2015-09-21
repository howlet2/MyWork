#pragma once
#include "EngineObject.h"
#include "Animation.h"

namespace DreamEngine
{
class _EngineExport CSkeleton : public CEngineObject
{
public:
	CSkeleton(void);
	~CSkeleton(void);

	void			setRootBone(CBone* pBone)				{m_pRootBone=pBone;}

protected:

	CBone*			m_pRootBone;

	typedef	std::vector<CAnimation*> AnimationLst;
	AnimationLst	m_animations;
};
}



