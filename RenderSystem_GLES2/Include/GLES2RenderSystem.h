#pragma once
#include "Gles2Define.h"
#include "RenderSystem.h"
#include "GLES2RenderWindow.h"
#include "EGLView.h"
#include "GLES2/gl2.h"
//#include "GLES2/gl2platform.h"

using namespace DreamEngine;

namespace DreamEngineGLES2
{

class _EngineGLES2Export CGLES2RenderSystem : public CRenderSystem
{
public:
	CGLES2RenderSystem(void);
	~CGLES2RenderSystem(void);

	virtual Error			initialize(void);
	virtual Error			shutDown(void);
	virtual CRenderWindow*	createRenderWindow(const CString& name,\
										m_uint16 width, m_uint16 heigth,
										bool isSetActive=true);


	virtual void			beginFrame(void);
	virtual void			endFrame(void);

	virtual void			render(CRenderData* pRenderData);

private: 

	virtual void			_setViewport(CViewport* pViewport);
	
	void					_setRenderState(CMaterial* pMaterial);
	void					_bulidDeclaration(CRenderData* pRenderData);
	void					_activeVertexBuffer(CRenderData* pRenderData);
	void					_updateShaderProgram(CMaterial* pMaterial);
	void					_draw(CRenderData* pRenderData);
	void					_endDraw(CRenderData* pRenderData);

protected:

	CEGLView*				m_pEglView;
};

}
