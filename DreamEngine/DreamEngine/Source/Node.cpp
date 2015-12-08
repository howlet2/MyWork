#include "Node.h"

namespace DreamEngine
{

CNode::CNode(void):
	m_pParent(MATH_NULL),

	m_position(0.0f, 0.0f, 0.0f),
	m_derivedPos(0.0f, 0.0f, 0.0f),
	m_derivedScale(1.0f, 1.0f, 1.0f),
	m_scale(1.0f, 1.0f, 1.0f)
{

}

CNode::CNode(const CString& name, CNode* pParent/* =MATH_NULL */):
	m_name(name),
	m_position(0.0f, 0.0f, 0.0f),
	m_derivedPos(0.0f, 0.0f, 0.0f),
	m_derivedScale(1.0f, 1.0f, 1.0f),
	m_scale(1.0f, 1.0f, 1.0f)
{
	attach(pParent);
}

CNode::~CNode(void)
{
}

void CNode::setName(const CString& name)
{
	m_name = name;
}

CNode* CNode::getChild(const CString& name)const
{
	for (int i=0; i<int(m_childs.size()); ++i)
	{
		if (m_childs[i]->getName() == name)
		{
			return m_childs[i];
		}
	}

	return MATH_NULL;
}

CNode* CNode::getChild(int index)const
{
	if (index<int(m_childs.size()) && index>=0)
	{
		return m_childs[index];
	}

	return MATH_NULL;
}

CNode* CNode::findNode(const CString& name)
{
	return _findNode(this, name);
}

void CNode::attach(CNode* pParent, bool isUpdateTranslate/*=true*/)
{
	if (this==pParent) return;

	m_pParent = pParent;

	if (isUpdateTranslate && m_pParent!=MATH_NULL)
	{
		_updateDerived();
		_updateChilds(this);
	}
}

void CNode::deAttach(bool isUpdateTranslate/*=true*/)
{
	if (isUpdateTranslate && m_pParent!=MATH_NULL)
	{
		m_pParent = MATH_NULL;
		_updateDerived();
		_updateChilds(this);
	}
}

void CNode::addChild(CNode* pChild, bool isUpdateTranslate/*=true*/)
{
	if (this == pChild) return;

	m_childs.push_back(pChild);
	pChild->attach(this, isUpdateTranslate);
	
}

void CNode::removeAllChild(bool isUpdateTranslate/* =true */)
{
	for (int i=0; i<int(m_childs.size()); ++i)
	{
		m_childs[i]->deAttach(isUpdateTranslate);
	}
	m_childs.clear();
}

void CNode::deleteAllNode()
{
	_deleteAllChildNode(this);
}

void CNode::setScale(const CVector3& sacle)
{
	m_derivedScale = m_scale = sacle;
	if (m_pParent != MATH_NULL)
	{
		const CVector3& parentScale = m_pParent->getDerivedScale();
		m_derivedScale._x *= parentScale._x;
		m_derivedScale._y *= parentScale._y;
		m_derivedScale._z *= parentScale._z;
	}
	_updateDerived();
	_updateChilds(this);

	CMatrix16::makeTranslate(&m_worldMat, m_position, m_scale, m_quaternion);
}

void CNode::setScale(float sx, float sy, float sz)
{
	setScale(CVector3(sx, sy, sz));
}

void CNode::setPosition(const CVector3& pos)
{
	m_derivedPos = m_position = pos;

	if (m_pParent != MATH_NULL)
		m_derivedPos+=m_position;
	
	_updateDerived();
	_updateChilds(this);

	CMatrix16::makeTranslate(&m_worldMat, m_position, m_scale, m_quaternion);
}

void CNode::setPosition(float x, float y, float z)
{
	setPosition(CVector3(x,y,z));
}

void CNode::setQuaternion(const CQuaternion& qua)
{
	m_deriveQua = m_quaternion = qua;

	if (m_pParent != MATH_NULL)
		m_deriveQua *= m_pParent->getDerivedQuaternion();
	
	_updateDerived();
	_updateChilds(this);

	CMatrix16::makeTranslate(&m_worldMat, m_position, m_scale, m_quaternion);
}

void CNode::setQuaternion(float w, float x, float y, float z)
{
	setQuaternion(CQuaternion(w, x, y, z));
}

void CNode::yaw(float angle)
{
	CQuaternion qua;
	qua.yaw(angle);
	
	setQuaternion(qua);
}

void CNode::roll(float angle)
{
	CQuaternion qua;
	qua.roll(angle);

	setQuaternion(qua);
}

void CNode::pitch(float angle)
{
	CQuaternion qua;
	qua.pitch(angle);

	setQuaternion(qua);
}

void CNode::rotate(float angle, const CVector3& axis/* =CVector3::NEGATIVE_UNIT_Y */)
{
	CQuaternion qua;
	qua.rotate(axis, angle);

	setQuaternion(qua);
}

void CNode::rotateYawPitchRoll(float yaw, float pitch, float roll)
{
	CQuaternion qua;
	qua.rotateYawPitchRoll(yaw, pitch, roll);

	setQuaternion(qua);
}


//move camera
void CNode::move(const CVector3& vec)		//	by vec
{
	setPosition(m_position+vec);
}

void CNode::_updateChilds(CNode* pParent)
{
	if (pParent==MATH_NULL) return;

	NodeLst::iterator iter;
	CNode::NodeLst& childs = pParent->m_childs;

	for (iter=childs.begin(); iter!=childs.end(); ++iter)
	{
		(*iter)->_updateDerived();

		if ((*iter)->hasChild())
			_updateChilds((*iter));
	}
}

void CNode::_updateDerived()
{
	m_derivedPos	= m_position;
	m_derivedScale	= m_scale;
	m_deriveQua		= m_quaternion;

	if (m_pParent != MATH_NULL)
	{
		m_derivedPos	+= m_pParent->getDerivedPosition();
		
		const CVector3& derivedScale = m_pParent->getDerivedScale();
		m_derivedScale._x *= derivedScale._x;
		m_derivedScale._y *= derivedScale._y;
		m_derivedScale._z *= derivedScale._z;

		m_deriveQua *= m_pParent->getDerivedQuaternion();
	}

	CMatrix16::makeTranslate(&m_derivedWorldMat, m_derivedPos, m_derivedScale, m_deriveQua);
}

CNode* CNode::_findNode(CNode* pParent, const CString& name)const
{
	CNode* pCurrent = pParent;
	if (pCurrent != MATH_NULL)
	{
		if (pCurrent->getName()==name)
			return pCurrent;
		else
		{
			for (int i=0; i<int(pParent->m_childs.size()); ++i)
			{
				pCurrent = pParent->m_childs[i];
				CNode* pNode = _findNode(pCurrent, name);
				if (pNode != MATH_NULL)
					return pNode;
			}
		}
	}

	return MATH_NULL;
}

void CNode::_deleteAllChildNode(CNode* pParent)
{
	if (pParent==MATH_NULL) return;

	CNode* pCurrent = MATH_NULL;
	for (int i=0; i<int(pParent->m_childs.size()); ++i)
	{
		pCurrent = pParent->m_childs[i];
		_deleteAllChildNode(pParent->m_childs[i]);
		pCurrent->deAttach(false);
		SAFE_DELETE(pCurrent);
	}
}

}

