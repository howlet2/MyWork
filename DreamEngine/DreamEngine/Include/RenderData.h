#pragma once
#include "EngineObject.h"
#include "HardwareBuffer.h"
#include "Material.h"

namespace DreamEngine
{
/*
	if   m_indexStream count great then zero, we need draw with index buffer
	else we need draw with vertex buffer
*/
class _EngineExport CRenderData : public CEngineObject
{
public:

	typedef std::vector<CVertexElement>		ElementLst;
	typedef std::map<int, CVertexBuffer*>	VertexStream;
	typedef std::vector<CIndexBuffer*>		IndexStream;

public:

	CRenderData(void);
	~CRenderData(void);
	
	bool				isUseIndexBuffer(void)const;		
	bool				isEmpty(void)const;				

	CVertexBuffer*		getVertexBuffer(int index)const;
	void				addVertexBuffer(int index, CVertexBuffer* pVertexBuffer);

	CIndexBuffer*		getIndexBuffer(int index)const;		
	void				addIndexBuffer(CIndexBuffer* pIndexBuffer);

	m_uint16			getPatch(void)const;

	HardwareBufferType	getRenderType(int index)const;
	void				setRenderType(HardwareBufferType type);
	void				setRenderType(HardwareBufferType type, int index);

	m_uint16			getElemCount(int index)const;
	m_uint16			caculateTrangleCount(void)const;
	
	void				destory();

	const ElementLst&	getElementLst(void)const					{return m_elementLst;}
	void				addElement(CVertexElement* pElement,
								   m_uint16 count);

public:

	VertexStream	m_vertexStream;
	ElementLst      m_elementLst;

	//CMatrix16		m_worldMat;
	IndexStream		m_indexStream;
	CMaterial*		m_pMaterial;
};

}

