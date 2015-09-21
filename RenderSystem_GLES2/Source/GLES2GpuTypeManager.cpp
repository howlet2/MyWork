#include "GLES2GpuTypeManager.h"

namespace DreamEngineGLES2
{
CGLES2GpuTypeManager::CGLES2GpuTypeManager(void)
{
}


CGLES2GpuTypeManager::~CGLES2GpuTypeManager(void)
{
}

const char* CGLES2GpuTypeManager::defaultVertex()
{
	return																
	"attribute vec3 aPosition0;											\
	attribute vec2 aTexcoord0;											\
	varying	  vec2 vTexCoord;											\
	uniform mat4 atp_worldViewProjMatrix;								\
	void main()															\
	{																	\
		vTexCoord = aTexcoord0;											\
		gl_Position = atp_worldViewProjMatrix *vec4(aPosition0,1.0f);	\
	}";

}

const char* CGLES2GpuTypeManager::defaultFragment()
{
	return																
		"precision mediump float;							\
		varying vec2		vTexCoord;						\
		uniform sampler2D	s_texture;						\
		void main()											\
		{													\
			gl_FragColor = texture2D(s_texture, vTexCoord);	\
			/*gl_FragColor = vec4(1,0,1,1);	*/				\
		}";
}


}

