#pragma once
#include "D3D9Define.h"
#include "RenderWindow.h"
#include "Viewport.h"
#include "D3D9RenderSystem.h"
#include "D3D9Device.h"
#include "d3d9.h"
using namespace DreamEngine;

namespace DreamEngineD3D
{
class CD3D9Device;

class _EngineD3D9Export CD3D9RenderWindow : public CRenderWindow
{
public:
	CD3D9RenderWindow(const CString& name);
	~CD3D9RenderWindow(void);

	void				showWindow();

	//void			SetDevice(CD3D9Device* pD3D9Device);
	 CD3D9Device*		getDevice(void)const		{return m_pD3D9Dveice;}

	virtual Error		initialize(int width,  int height);
	virtual void		shutDown();

protected:

	Error				createMianWindow(const CString& name, int width, int heigth);
	Error				createDevice(void);

	CD3D9Device*		m_pD3D9Dveice;

};

}
