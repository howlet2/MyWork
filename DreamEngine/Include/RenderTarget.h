#pragma once
#include "EngineObject.h"
#include "Viewport.h"
#include "IteratorWrapper.h"

namespace DreamEngine
{

class CRenderTarget;

class _EngineExport CRenderTargetListener
{
public:

	CRenderTargetListener(){}
	virtual ~CRenderTargetListener(){}
	
	virtual void		onRenderStart(CRenderTarget* rw)=0;
	virtual void		onRender(CRenderTarget* rw)=0;
	virtual void		onRenderEnd(CRenderTarget* rw)=0;
};

class _EngineExport CRenderTarget : public CEngineObject
{

public:

	typedef std::vector<CRenderTargetListener*> ListenerLst;
	typedef CIteratorWrapper<ListenerLst::iterator, CRenderTargetListener*> ListenerTargetIter;


public:

	CRenderTarget(const CString& name);
	~CRenderTarget(void);

	CCamera*			getCamera(void)const		{return m_pViewport->getCamera();}
	CViewport*			getViewport(void)const		{return m_pViewport;}
	m_uint16			getWidth(void)const			{return m_width;}
	m_uint16			getHeigth(void)const		{return m_heigth;}
	ListenerTargetIter& getListenerIter(void)		{return m_listenerTargetIter;}

	void				addListener(CRenderTargetListener* pListener);
	CViewport*			addViewport(CCamera* pCamera);

	void				updateFPS(void);
	float				getFPS(void)const;

protected:

	CString					m_name;
	CViewport*				m_pViewport;

	ListenerLst				m_pListeners;
	ListenerTargetIter		m_listenerTargetIter;

	m_uint16				m_heigth;
	m_uint16				m_width;

	
	float					m_avgFPS;
		
	

};


}

