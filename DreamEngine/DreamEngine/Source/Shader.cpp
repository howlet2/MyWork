#include "Shader.h"
#include "FileDataStream.h"

namespace DreamEngine
{
CShader::CShader(ShaderType type):
m_type(type)
{
}


CShader::~CShader(void)
{
}

Error CShader::initializeFromFile(const CString& fileName)
{
	CFileDataStream fileStr;
	fileStr.open(fileName);
	CString strSource;
	fileStr.getAsString(strSource);
	fileStr.close();

	CheckEngineError(initialize(strSource))

	return ERROR_OK;
}

Error CShader::initialize(const CString& source)
{
	m_strSource=source;

	CheckEngineError(onInitializeShader());

	return ERROR_OK;
}


ShaderType CShader::getType()const
{
	return m_type;
}

}

