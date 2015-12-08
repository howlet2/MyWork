#pragma once
#include "Shader.h"
#include "GLES2Define.h"
#include "GLES2/gl2.h"
using namespace DreamEngine;

namespace DreamEngineGLES2
{
class _EngineGLES2Export CGLSLShaderBase : public CShader
{
public:
	CGLSLShaderBase(ShaderType type);
	~CGLSLShaderBase(void);

	GLint					getGLES2Shader(void)const		{return m_glShader;}

protected:

	Error					loadShader(ShaderType type);

	GLint					m_glShader;
};

class _EngineGLES2Export CGLSLFragment :  public CGLSLShaderBase
{
public:
	CGLSLFragment(void);
	~CGLSLFragment(void);

protected:

	virtual Error			onInitializeShader();
};

class _EngineGLES2Export CGLSLVertex : public CGLSLShaderBase
{
public:

	CGLSLVertex(void);
	~CGLSLVertex(void);

protected:

	virtual Error				onInitializeShader();

};
}