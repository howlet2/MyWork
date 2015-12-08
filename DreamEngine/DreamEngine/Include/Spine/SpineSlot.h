#pragma once
#include "EngineObject.h"

namespace DreamEngine
{
class _EngineExport CSpineSlot : public CEngineObject
{
public:
	CSpineSlot(const CString& name);
	~CSpineSlot(void);

	const CString&	getBoneName(void)const		{return m_bone;}
	void			setBoneName(const CString& boneName);

	const CString&	getAttachMent(void)const	{return m_attachment;}
	void			setAttachMent(const CString& attachMentName);


private:

	CString		m_name;
	CString		m_bone;
	CString		m_attachment;
};

}

