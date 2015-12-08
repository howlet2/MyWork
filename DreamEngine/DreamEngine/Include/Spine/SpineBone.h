#pragma once
#include "EngineObject.h"
#include "Node.h"

namespace DreamEngine
{

class _EngineExport CSpineBone : public CNode
{
public:
	CSpineBone(const CString& name, CNode* pParent=MATH_NULL);
	CSpineBone(void);

	~CSpineBone(void);

	float		getLength(void)const				{return m_length;}
	void		setLength(float length);

private:

	float		m_length;
};

}
