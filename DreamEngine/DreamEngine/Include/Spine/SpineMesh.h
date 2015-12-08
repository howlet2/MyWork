#pragma once
#include "RenderData.h"
#include "Atlas.h"

namespace DreamEngine
{
class _EngineExport CSpineMesh : public CEngineObject
{
public:

	struct SpineMeshVertex
	{
		float x,  y,  z;
		float u, v;

		SpineMeshVertex():x(0.0f),y(0.0f),z(0.0f),u(0.0f),v(0.0f){}
	};

public:

	CSpineMesh(const CString& name);
	~CSpineMesh(void);

	const CString&		getName(void)const						{return m_name;}

	bool				createFromFile(const CString& altasFile);
	bool				createFromAtlas(const CAtlas& altas);
	
	const CRenderData*	getRenderDataPtr()const					{return &m_renderData;}
	int					getTrangleCount()const					{return m_trangleCount;}

	void				notifyPosition(const CString& scliceName, const CVector3& position);
	void				notifyUV(const CString& scliceName, const CVector2& uv);


private:

	SpineMeshVertex*	_getBufferAddress(const CString& scliceName);

	CRenderData		m_renderData;
	CString			m_name;

	typedef	std::vector<CString> ScliceNameLst;
	ScliceNameLst	m_scliceNames;

	int				m_trangleCount;
};
}


