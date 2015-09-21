#pragma once
#include "RenderTarget.h"
#include "VideoManager.h"
#include "GpuProgramManager.h"
#include "GpuTypeManager.h"

namespace DreamEngine
{

class _EngineExport CRenderWindow : public CRenderTarget
{
public:
	CRenderWindow(const CString& name);
	virtual ~CRenderWindow(void);

	virtual Error			initialize(int width, int height) = 0;
	virtual void			shutDown(void) =0;
	virtual void			showWindow(void)=0;

	HWINDOW					getWindowModule(void)const			{return m_hWnd;}
	CVideoManager*			getVideoManager(void)const			{return m_pVideoManager;}
	CGpuProgramManager*		getGpuProgramManager(void)const		{return m_pGpuProgramManager;}
	CGpuTypeManager*		getGpuTypeManager(void)const		{return m_pGpuTypeManager;}

protected:

	HWINDOW					m_hWnd;
	CVideoManager*			m_pVideoManager;
	CGpuProgramManager*		m_pGpuProgramManager;
	CGpuTypeManager*		m_pGpuTypeManager;
};

}