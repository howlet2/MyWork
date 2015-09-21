#pragma once

namespace DreamEngineGLES2
{

enum GLES2Error
{
	ERROR_GLES2_OK						= 0,
	ERROR_GLES2_UNKONW					= 1,

	///-------------------------------EGLœ‡πÿ--------------------------------
	ERROR_EGL_NO_DISPLAY				= 100,
	ERROR_EGL_INIT						= 101,
	ERROR_EGL_CHOOSE_CFG				= 102,
	ERROR_EGL_NO_SURFACE				= 103,
	ERROR_EGL_NO_CONTEXT				= 104,
	ERROR_EGL_MAKE_CURRENT				= 105,
};

}