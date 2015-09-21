#pragma once
#include "EngineObject.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace DreamEngine
{
class _EngineExport CNode : public CEngineObject
{
public:

	typedef std::vector<CNode*>	NodeLst;

public:
	CNode(void);
	CNode(const CString& name, CNode* pParent=MATH_NULL);
	virtual ~CNode(void);

	const CString&		getName(void)const						{return m_name;}
	void				setName(const CString& name);

	bool				hasChild(void)const						{return int(m_childs.size())>0;}
	CNode*				getChild(const CString& name)const;
	CNode*				getChild(int index)const;
	CNode*				getParent(void)const					{return m_pParent;}


	virtual void		attach(CNode* pParent, bool isFlashMat=true);				
	virtual void		deAttach(bool isFlashMat=true);
	virtual void		addChild(CNode* pChild, bool isFlashMat=true);	
	virtual void		removeAllChild(bool isFlashMat=true);

	void				setScale(const CVector3& sacle);	
	void				setScale(float sx, float sy, float sz);
	const CVector3&		getScale(void)const						{return m_scale;}

	void				setPosition(const CVector3& pos);
	void				setPosition(float x, float y, float z);
	const CVector3&		getPosition(void)const					{return m_position;}

	void				setQuaternion(const CQuaternion& qua);
	void				setQuaternion(float w, float x, float y, float z);
	const CQuaternion&  getQuaternion(void)const				{return m_quaternion;}

	void				yaw(float angle);
	void				roll(float angle);
	void				pitch(float angle);
	void				rotate(float angle, const CVector3& axis=CVector3::NEGATIVE_UNIT_Y);
	void				rotateYawPitchRoll(float yaw, float pitch, float roll);

	//move camera
	void				move(const CVector3& vec);		//	by vec

	const CVector3&		getDerivedScale(void)const					{return m_derivedScale;}
	const CVector3&		getDerivedPosition(void)const				{return m_derivedPos;}
	const CQuaternion&  getDerivedQuaternion(void)const				{return m_deriveQua;}

	const CMatrix16&	getWorldMatrix(void)const					{return m_worldMat;}
	const CMatrix16&	getDerivedWorldMatrix(void)const			{return m_derivedWorldMat;}
	
	void				_updateChilds(CNode* pParent);
	void				_updateDerived(void);

protected:

	CString				m_name;

	CVector3			m_position;
	CVector3			m_scale;
	CQuaternion			m_quaternion;

	CVector3			m_derivedPos;
	CVector3			m_derivedScale;
	CQuaternion			m_deriveQua;

	CMatrix16			m_worldMat;
	CMatrix16			m_derivedWorldMat;
		
	CNode*				m_pParent;

	NodeLst				m_childs;
};

}

