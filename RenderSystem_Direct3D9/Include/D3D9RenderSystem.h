#pragma once
#include "D3D9Define.h"
#include "RenderSystem.h"
#include "D3D9RenderWindow.h"
#include "D3D9Device.h"
#include "d3d9.h"
using namespace DreamEngine;

namespace DreamEngineD3D
{

class _EngineD3D9Export CD3D9RenderSystem : public CRenderSystem
{
public:
	CD3D9RenderSystem(void);
	~CD3D9RenderSystem(void);

	virtual Error			initialize(void);
	virtual Error			shutDown(void);
	virtual CRenderWindow*	createRenderWindow(const CString& name,\
										m_uint16 width, m_uint16 heigth, 
										bool isSetActive=true);

	virtual void			beginFrame(void);
	virtual void			endFrame(void);

	virtual void			render(CRenderData* pRenderData);

	static IDirect3D9*		getD3D9(void)	{return m_pd3d;}
	CD3D9Device*			getActiveDevice(void)const;

private: 

	virtual void			_setViewport(CViewport* pViewport);
	
	void					_setRenderState(CMaterial* pMaterial);
	void					_activeVertexBuffer(CRenderData* pRenderData);
	void					_buildShader(CMaterial* pMaterial);
	void					_bulidDeclaration(const CVertexBuffer::ElementLst& elementLst);
	void					_draw(CRenderData* pRenderData);

protected:

	static IDirect3D9*				m_pd3d;
};

}
