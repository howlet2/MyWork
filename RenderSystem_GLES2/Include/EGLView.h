#pragma once
#include "PLugin.h"
#include "Gles2Define.h"
#include "EGL/egl.h"
#include "EGL/eglplatform.h"
#include "GLES2Error.h"

using namespace DreamEngine;

namespace DreamEngineGLES2
{

class CEGLView
{
public:
	CEGLView(void);
	~CEGLView(void);

	GLES2Error initializeEGL(HWINDOW nativeWindow);
	void	   swapBuffers();
	void	   shutDown();

};

}
