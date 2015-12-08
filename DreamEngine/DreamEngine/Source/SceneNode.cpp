#include "SceneNode.h"

namespace DreamEngine
{
CSceneNode::CSceneNode(const CString& name, CNode* pParent/*=MATH_NULL*/):
CNode(name, pParent)
{
}


CSceneNode::~CSceneNode(void)
{
}

}
