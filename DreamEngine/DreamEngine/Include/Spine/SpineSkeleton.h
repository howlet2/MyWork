#pragma once
#include "EngineObject.h"
#include "SpineBone.h"
#include "SpineSlot.h"

namespace DreamEngine
{

class _EngineExport CSpineSkeleton : public CEngineObject 
{
public: 

	typedef std::vector<CSpineSlot*> SpineSlotLst;

public:
	CSpineSkeleton(const CString& name);
	~CSpineSkeleton(void);

	CString				getName()const								{return m_name;}
	CSpineBone*			getRootBone(void)const						{return m_pRootBone;}
	const SpineSlotLst& getSpineSlotLst(void)const					{return m_slots;}

	void				setRootBone(CSpineBone* pRootBone); 

	CSpineBone*			loadFromFile(const CString& fileName);

private:

	SpineSlotLst		m_slots;
	CSpineBone*			m_pRootBone;	
	CString				m_name;
};

}