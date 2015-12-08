#pragma once
#include "EngineObject.h"
#include "RenderWindow.h"
#include "RenderData.h"
#include "PLugin.h"
#include "DynLib.h"

namespace DreamEngine
{
class CVideoManager;

class _EngineExport CRenderSystem : public CEngineObject
{
public:

	CRenderSystem(void);
	virtual ~CRenderSystem(void);

public:

	virtual Error			initialize(void)		=0;

	virtual CRenderWindow*	createRenderWindow(const CString& name,
			m_uint16 width, m_uint16 heigth, bool isSetActive=true)=0;

	virtual void			beginFrame()	=0;
	virtual void			endFrame()		=0;

	virtual void			render(CRenderData* pRenderData)=0;
	virtual Error			shutDown(void);

	CRenderWindow*			getActiveRenderWindow()const		{return m_pActiveWindow;}

private:

	virtual void			_setViewport(CViewport* pViewport)=0;

protected:

	typedef std::vector<CRenderWindow*>  RenderWindowLst;
	RenderWindowLst			m_renderWindows;

	CRenderWindow*			m_pActiveWindow;
	
};

}

