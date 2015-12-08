#pragma once
#include "PLugin.h"
#include "D3D9InputDefine.h"
#include "D3D9InputSystem.h"

using namespace DreamEngineD3D9Input;

namespace DreamEngineD3D9Input
{

class _EngineD3D9InputExport CD3D9InputSysPlugin : public CPLugin
{
public:
	CD3D9InputSysPlugin(void);
	~CD3D9InputSysPlugin(void);

	virtual const CString&	getName() const;
	virtual void			install();
	virtual void			initialise();
	virtual void			uninstall();

private:

	static CString				m_name;

	CD3D9InputSystem*			m_pD3D9InputSystem;
	
};

}


