#include "SpineSlot.h"

namespace DreamEngine
{
CSpineSlot::CSpineSlot(const CString& name):
	m_name(name)
{
}


CSpineSlot::~CSpineSlot(void)
{
}

void CSpineSlot::setBoneName(const CString& boneName)
{
	m_bone = boneName;
}

void CSpineSlot::setAttachMent(const CString& attachMentName)
{
	m_attachment = attachMentName;
}

}

