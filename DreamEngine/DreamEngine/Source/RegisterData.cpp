#include "RegisterData.h"

namespace DreamEngine
{
//const CMatrix16*	CRegisterData::pWorldMatirx		= MATH_NULL;
//const CMatrix16*	CRegisterData::pViewMatrix			= MATH_NULL;
//CMatrix16			CRegisterData::WorldViewProjMatrix;
//const CVector3*		CRegisterData::pCameraPosition		= MATH_NULL;
//CMaterial*			CRegisterData::pCurMaterial		= MATH_NULL;


CRegisterData::CRegisterData(void)
{
}


CRegisterData::~CRegisterData(void)
{
}

CRegisterData& CRegisterData::instance(void)
{	
	return (*m_singleton); 
}

CRegisterData* CRegisterData::instancePtr(void)
{ 
	return m_singleton; 
}

}

