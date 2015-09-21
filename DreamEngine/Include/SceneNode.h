#pragma once
#include "Node.h"

namespace DreamEngine
{

class _EngineExport CSceneNode : public CNode
{
public:
	CSceneNode(const CString& name, CNode* pParent=MATH_NULL);
	~CSceneNode(void);
};

}


