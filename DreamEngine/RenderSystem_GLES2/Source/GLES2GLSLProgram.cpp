#include "GLES2GLSLProgram.h"
#include "FileDataStream.h"
#include "CommonFunction.h"
#include "RegisterData.h"
#include "GLES2GLSLShader.h"
#include "ShaderParam.h"
#include "GLES2Texture.h"

namespace DreamEngineGLES2
{
CGLES2GLSLProgram::CGLES2GLSLProgram():
	m_glProgram(0),
	m_pAttriParamTable(MATH_NULL)
{
}

CGLES2GLSLProgram::~CGLES2GLSLProgram()
{

}

CShader* CGLES2GLSLProgram::newShader(ShaderType type)
{
	switch (type)
	{
	case ST_VERTEX:
		{
			return new CGLSLVertex();
		}break;

	case ST_FRAGMENT:
		{
			return new CGLSLFragment();
		}break;
	}

	return MATH_NULL;
}

GLuint CGLES2GLSLProgram::getAttributeLocal(const CString& name)const
{
	return glGetAttribLocation(m_glProgram, name.c_str());
}

Error CGLES2GLSLProgram::createParamTable(void)
{
	m_pShaderParamTable = new CShaderParamTable;
	m_pAttriParamTable  = new CShaderParamTable;
	_addParams();
	CheckEngineError(m_pShaderParamTable->_buildDataBuffer())
	//CheckEngineError(m_pAttriParamTable->_BuildDataBuffer())			//属性数据存放在CVertexBuffer里面

	return ERROR_OK;
}

void CGLES2GLSLProgram::updateAutoParams()
{
	m_pShaderParamTable->setValue(FLAG_TO_STRING(atp_worldViewProjMatrix),
		CRegisterData::instance().getWorldViewProjMatrix());
	m_pShaderParamTable->setValue(FLAG_TO_STRING(atp_viewMatrix),
		*CRegisterData::instance().getViewMatrix());
	m_pShaderParamTable->setValue(FLAG_TO_STRING(atp_worldMatrix),
		*CRegisterData::instance().getWorldMatirx());
	m_pShaderParamTable->setValue(FLAG_TO_STRING(atp_cameraPos),
		*CRegisterData::instance().getCameraPosition());
}

void CGLES2GLSLProgram::updateParams()
{
	CShaderParamTable::ParamIter paramIter = m_pShaderParamTable->getParamIter();

	while (paramIter.hasMore())
	{
		CShaderParam* pParam = paramIter.current(); 
		m_byte* pDatePtr = (m_byte*)(pParam->getDataPtr());
		
		CShaderParam::ParamType type = paramIter.current()->getType();
		
		PointType pointType = static_cast<PointType>(pParam->getUserInfo());
		if (pointType==PT_UNIFROM)
		{
			_updateUniformParams(pParam);
		}
		
		paramIter.Next();
	}
}

Error CGLES2GLSLProgram::onShaderCreated()
{
	m_glProgram = glCreateProgram();

	CGLSLShaderBase* pVertexShader	 = static_cast<CGLSLShaderBase*>(m_pVertexShader);
	CGLSLShaderBase* pFragmentShader = static_cast<CGLSLShaderBase*>(m_pFragmentShader);

	if (pVertexShader==MATH_NULL || pFragmentShader==MATH_NULL)
		return ERROR_HAVE_NULL_POINT;
	
	GLint glVertexShader   = pVertexShader->getGLES2Shader();
	GLint glFragmentShader = pFragmentShader->getGLES2Shader();
	
	glAttachShader(m_glProgram, glVertexShader);	
	glAttachShader(m_glProgram, glFragmentShader);	
	
	glLinkProgram(m_glProgram);	
	GLint link = GL_TRUE;
	glGetProgramiv(m_glProgram, GL_LINK_STATUS, &link);				
	if (link != GL_TRUE)
	{
		int len;
		glGetProgramiv(m_glProgram, GL_INFO_LOG_LENGTH,&len);
		if (len>0)
		{
			char* info = new char[len];
			glGetProgramInfoLog(m_glProgram, len, NULL, info);
			//std::cout << "create program:" << info;
			delete[]info;

			return ERROR_LINK_SHADER_ERROR;
		}
	}
	return ERROR_OK;
}

void CGLES2GLSLProgram::onBeforeDestory()
{
	if (m_pAttriParamTable != MATH_NULL)
	{
		m_pAttriParamTable->destory();
		delete m_pAttriParamTable;
		m_pAttriParamTable = MATH_NULL;
	}
	CGLSLShaderBase* pVertexShader	 = static_cast<CGLSLShaderBase*>(m_pVertexShader);
	CGLSLShaderBase* pFragmentShader = static_cast<CGLSLShaderBase*>(m_pFragmentShader);

	GLint glVertexShader	= pVertexShader->getGLES2Shader();
	GLint glFragmentShader	= pFragmentShader->getGLES2Shader();

	glDetachShader(m_glProgram, glVertexShader);
	glDetachShader(m_glProgram, glFragmentShader);
	glDeleteProgram(m_glProgram);
}

void CGLES2GLSLProgram::_addParams()
{
	//////////////////////////////////////////////////////////////////////////attributes
	GLint attributeNum = 0;
	GLint maxNameLen   = 0;
	char* pAttributeName = NULL;
	glGetProgramiv(m_glProgram, GL_ACTIVE_ATTRIBUTES, &attributeNum);
	glGetProgramiv(m_glProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxNameLen);

	if (maxNameLen>0)
		pAttributeName = new char[maxNameLen];

	for (GLint index=0; index<attributeNum; ++index)
	{
		memset(pAttributeName, 0, maxNameLen);
		GLint nameLen = 0;
		GLint bufSize = 0;
		GLenum type   = 0;

		glGetActiveAttrib(m_glProgram, index, maxNameLen, &nameLen, &bufSize, &type, pAttributeName);

		CCommonFunction::ParamTypeInfo paramAndsize = CCommonFunction::GLES2ParamDataTypeToParamType(type);
		bufSize = CCommonFunction::CaculateParamBufferSize(paramAndsize)*bufSize;

		CShaderParam::ParamType paramType = paramAndsize.first;
		CShaderParam* pParam = m_pAttriParamTable->addParam(pAttributeName, paramAndsize.first, 
															 m_uint8(paramAndsize.second), m_uint8(bufSize), 
															 m_uint8(index), 0);
		pParam->setUserInfo(m_uint8(PT_ATTRIBUTE));
	}
	SAFE_DELETE_ARRY(pAttributeName);

	//////////////////////////////////////////////////////////////////////////uniforms
	GLint numUniforms=0;
	GLint maxUniformLen=100;
	char* pUniformName = NULL;

	//glGetProgramiv(m_glProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLen);	
	glGetProgramiv(m_glProgram, GL_ACTIVE_UNIFORMS, &numUniforms);				
	if (maxUniformLen>0)
		pUniformName = new char[maxUniformLen];

	for (int index=0; index<numUniforms; ++index)
	{
		memset(pUniformName, 0, maxUniformLen);
		int		bufSize = 0;
		GLenum	type	= 0; 

		glGetActiveUniform(m_glProgram, index, maxUniformLen, NULL, &bufSize, &type, pUniformName);

		CCommonFunction::ParamTypeInfo paramAndsize = CCommonFunction::GLES2ParamDataTypeToParamType(type);
		bufSize = CCommonFunction::CaculateParamBufferSize(paramAndsize)*bufSize;

		CShaderParam* pParam = m_pShaderParamTable->addParam(pUniformName, paramAndsize.first, 
															 m_uint8(paramAndsize.second), m_uint8(bufSize),
															 m_uint8(index), 0);
		pParam->setUserInfo(m_uint8(PT_UNIFROM));
	}
	SAFE_DELETE_ARRY(pUniformName)
}

void CGLES2GLSLProgram::_updateUniformParams(CShaderParam* pParam)
{
	/*GL_FLOAT, GL_FLOAT_VEC2, GL_FLOAT_VEC3, GL_FLOAT_VEC4
		GL_INT, GL_INT_VEC2, GL_INT_VEC3, GL_INT_VEC4, GL_BOOL
		GL_BOOL_VEC2, GL_BOOL_VEC3, GL_BOOL_VEC4,
		GL_FLOAT_MAT2, GL_FLOAT_MAT3, GL_FLOAT_MAT4,
		GL_SAMPLER_2D, GL_SAMPLER_CUBE*/
	GLenum	count		= pParam->getElemCount();
	GLint   paramType	= CCommonFunction::ParamTypeToGLES2DataType(pParam->getType());
	GLint	iLocal		= pParam->getRegisterIdx();

	switch (paramType)
	{
	case GL_SAMPLER_2D:
		{
			CGLES2Texture * pTexture = static_cast<CGLES2Texture *>(pParam->getAddressVaule());
			GLuint texture = pTexture->getGLTexture();

			int layer = pTexture->getTexCoordLayer();
			glActiveTexture(GL_TEXTURE0+layer);										
			
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(iLocal, layer);	
		}break;

	case GL_FLOAT:
		{
			GLfloat* pValue =  static_cast<GLfloat*>(pParam->getDataPtr());
			switch (count)
			{
			case 1: glUniform1fv(iLocal, 1, pValue);break;
			case 2: glUniform2fv(iLocal, 1, pValue);break;
			case 3:	glUniform3fv(iLocal, 1, pValue);break;
			case 4:	glUniform4fv(iLocal, 1, pValue);break;
			}
		}break;

	case GL_INT:
		{
			GLint* pValue =  static_cast<GLint*>(pParam->getDataPtr());
			switch (count)
			{
			case 1:glUniform1iv(iLocal, 1, pValue);break;
			case 2:glUniform2iv(iLocal, 1, pValue);break;
			case 3:glUniform3iv(iLocal, 1, pValue);break;
			case 4:glUniform4iv(iLocal, 1, pValue);break;
			}
		}break;

	case GL_FLOAT_MAT2:
		{
			GLfloat* pValue =  static_cast<GLfloat*>(pParam->getDataPtr());
			glUniformMatrix2fv(iLocal, 1, GL_FALSE, pValue);
		}break;
		
	case GL_FLOAT_MAT3:
		{
			GLfloat* pValue =  static_cast<GLfloat*>(pParam->getDataPtr());
			glUniformMatrix3fv(iLocal, 1, GL_FALSE, pValue);
		}break;

	case GL_FLOAT_MAT4:
		{
			GLfloat* pValue =  static_cast<GLfloat*>(pParam->getDataPtr());
			glUniformMatrix4fv(iLocal, 1, GL_FALSE, pValue);
		}break;
	default:
		break;
	}

}

}
