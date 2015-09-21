#pragma once
#include "Gles2Define.h"
#include "RenderWindow.h"
#include "Viewport.h"
using namespace DreamEngine;

namespace DreamEngineGLES2
{
class _EngineGLES2Export CGLES2RenderWindow : public CRenderWindow
{
public:
	CGLES2RenderWindow(const CString& name);
	~CGLES2RenderWindow(void);

	void				showWindow();

	virtual Error		initialize(int width,  int height);
	virtual void		shutDown();

protected:

	Error				createMianWindow(const CString& name, int width, int heigth);

};
}