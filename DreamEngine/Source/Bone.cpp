#include "Bone.h"

namespace DreamEngine
{

CBone::CBone():
		m_pSibling(MATH_NULL)
{

}

CBone::CBone(const CString& name, 
			 CNode* pParent/* =MATH_NULL */,
			 CNode* pSibling/* =MATH_NULL */,
			 CNode* pChild/* =MATH_NULL*/):
			 CNode(name, pParent),
			 m_pSibling(pSibling)
{

}


CBone::~CBone(void)
{
}

void CBone::addChild(CNode* pChild, bool isFlashMat/*=true*/)
{
	//must be has a one child
	removeAllChild(isFlashMat);

	m_childs.push_back(pChild);
	pChild->attach(this);
}

void CBone::updateTransformation()
{
	_updateTransformation(this, m_derivedWorldMat);
}

void CBone::_updateTransformation(CNode* pNode, const CMatrix16& matParent)
{
	// Combine matrix
	CMatrix16::multiply(&m_derivedWorldMat, &m_worldMat, &matParent);

	// Compute inverse combined matrix
	CMatrix16::inverse(&m_matInverse, &m_derivedWorldMat);

	// Combine child
	if(pNode->hasChild())
		_updateTransformation(pNode->getChild(0), m_derivedWorldMat);

	// Combine sibling
	if(m_pSibling != MATH_NULL)
		_updateTransformation(static_cast<CBone*>(pNode)->getSibling(), matParent);
}


}