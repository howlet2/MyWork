#include "GLES2GLSLShader.h"
namespace DreamEngineGLES2
{
CGLSLShaderBase::CGLSLShaderBase(ShaderType type):
CShader(type)
{

}

CGLSLShaderBase::~CGLSLShaderBase()
{

}

Error CGLSLShaderBase::loadShader(ShaderType type)
{
	GLenum glShaderType = 0;
	switch (type)
	{
	case ST_FRAGMENT:
		{
			glShaderType=GL_FRAGMENT_SHADER;
		}break;

	case ST_VERTEX:
		{
			glShaderType = GL_VERTEX_SHADER;
		}break;
	}
	
	m_glShader = glCreateShader(glShaderType);
	const char* pSource = m_strSource.c_str();
	glShaderSource(m_glShader, 1, &pSource, NULL);						
	glCompileShader(m_glShader);										

	GLint compiler = GL_TRUE;
	glGetShaderiv(m_glShader, GL_SHADER_COMPILER, &compiler);			
	if (compiler != GL_TRUE)
	{
		GLint infoLen;
		glGetShaderiv(m_glShader, GL_INFO_LOG_LENGTH, &infoLen);		
		if (infoLen > 0)
		{
			char* info = new char[infoLen];
			glGetShaderInfoLog(m_glShader, infoLen, NULL, info);		
			//std::cout << info << std::endl;
			delete []info;
		}
		glDeleteShader(m_glShader);
		return ERROR_CREATE_FRAGMENT_SHADER_FAILD;
	}

	return ERROR_OK;
}

CGLSLFragment::CGLSLFragment(void):
CGLSLShaderBase(ST_FRAGMENT)
{
}


CGLSLFragment::~CGLSLFragment(void)
{
}

Error CGLSLFragment::onInitializeShader()
{
	CheckEngineError(loadShader(ST_FRAGMENT))

	return ERROR_OK;
}

CGLSLVertex::CGLSLVertex(void):
CGLSLShaderBase(ST_VERTEX)
{

}

CGLSLVertex::~CGLSLVertex()
{

}

Error CGLSLVertex::onInitializeShader()
{
	CheckEngineError(loadShader(ST_VERTEX))

	return ERROR_OK;
}

}