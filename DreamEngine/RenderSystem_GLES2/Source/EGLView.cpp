#include "EGLView.h"

namespace DreamEngineGLES2
{

CEGLView::CEGLView(void)
{
}


CEGLView::~CEGLView(void)
{
}

GLES2Error CEGLView::initializeEGL(HWINDOW nativeWindow)
{
	EGLint majorVision, minorVision;
	EGLDisplay dsp =  eglGetDisplay(EGL_DEFAULT_DISPLAY);	
	if (dsp==EGL_NO_DISPLAY)
		return ERROR_EGL_NO_DISPLAY;

	if (!eglInitialize(dsp, &majorVision, &minorVision))	
		return ERROR_EGL_INIT;

	EGLint configAttribute[] = 
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		//EGL_DEPTH_SIZE, 16,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};
	EGLConfig cfg[1];
	EGLint    cfgNum;
	if (!eglChooseConfig(dsp, configAttribute, &cfg[0], 1, &cfgNum))
		return ERROR_EGL_CHOOSE_CFG;

	EGLSurface winSurface;
	winSurface = eglCreateWindowSurface(dsp, cfg[0], (EGLNativeWindowType)nativeWindow, NULL);	
	if (winSurface==EGL_NO_SURFACE)
		return ERROR_EGL_NO_SURFACE;

	const EGLint contextAttribute[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};
	EGLContext context;
	context = eglCreateContext(dsp, cfg[0], EGL_NO_CONTEXT, contextAttribute);
	if (context==EGL_NO_CONTEXT)
		return ERROR_EGL_NO_CONTEXT;

	if(!eglMakeCurrent(dsp, winSurface, winSurface, context))		
		return ERROR_EGL_MAKE_CURRENT;
	
	return ERROR_GLES2_OK;
}

void CEGLView::swapBuffers()
{
	EGLDisplay dsp		= eglGetCurrentDisplay();
	EGLSurface surface	= eglGetCurrentSurface(EGL_READ);
	eglSwapBuffers(dsp, surface);
} 

void CEGLView::shutDown()
{
	EGLDisplay dsp		= eglGetCurrentDisplay();
	EGLSurface surface	= eglGetCurrentSurface(0);

	if (dsp!=EGL_NO_DISPLAY && surface!=EGL_NO_SURFACE)
	{
		eglMakeCurrent(dsp, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroyContext(dsp, eglGetCurrentContext());
		eglDestroySurface(dsp, surface);
		eglTerminate(dsp);
	}
}

}