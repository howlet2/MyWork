#pragma once
#include "Bone.h"

namespace DreamEngine
{

class _EngineExport CAnimation : public CEngineObject
{
public:
	CAnimation(void);
	~CAnimation(void);

protected:

	CString			m_name;
	m_uint32		m_keyNum;
	m_uint32		m_keyType;

	CBone*			m_pBone;
};

}