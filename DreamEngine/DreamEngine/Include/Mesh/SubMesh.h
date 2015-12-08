#pragma once
#include "EngineObject.h"
#include "RenderData.h"
#include "HardwareBuffer.h"

namespace DreamEngine
{

class _EngineExport CSubMesh : public CEngineObject
{
public:
	CSubMesh(void);
	CSubMesh(const CString& name);
	~CSubMesh(void);

	CRenderData*	getRenderDataPtr(void)		{return &m_renderData;}
	const CString&  getName()const				{return m_name;}		
protected:

	CRenderData		m_renderData;
	CString			m_name;
	//CMesh*			m_pParent;

};

}


