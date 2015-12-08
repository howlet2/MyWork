#include "GpuProgram.h"
#include "FileDataStream.h"
#include "EngineError.h"

namespace DreamEngine
{
CGpuProgram::CGpuProgram(void):
	m_pVertexShader(MATH_NULL),
	m_pFragmentShader(MATH_NULL),
	m_pShaderParamTable(MATH_NULL)
{
}


CGpuProgram::~CGpuProgram(void)
{
}

Error CGpuProgram::initialize(const CString& vertexSource, const CString& fragmentSource)
{
	if (createShader(ST_VERTEX,		vertexSource)==MATH_NULL)
		return ERROR_CREATE_VERTEX_SHADER_FAILD;

	if(createShader(ST_FRAGMENT,	fragmentSource)==MATH_NULL)
		return ERROR_CREATE_VERTEX_SHADER_FAILD;

	CheckEngineError(onShaderCreated());
	CheckEngineError(createParamTable());

	return ERROR_OK;
}

Error CGpuProgram::initializeFromFile(const CString& vertexFile, const CString& fragmentFile)
{
	loadShader(ST_VERTEX,	vertexFile);
	loadShader(ST_FRAGMENT, fragmentFile);

	CheckEngineError(onShaderCreated());
	CheckEngineError(createParamTable());

	return ERROR_OK;
}

CShader* CGpuProgram::loadShader(ShaderType type, const CString& fileName)
{
	CFileDataStream fileStr;
	fileStr.open(fileName);
	CString strSource;
	fileStr.getAsString(strSource);
	fileStr.close();

	return createShader(type, strSource);
}

CShader* CGpuProgram::createShader(ShaderType type, const CString& strSource)
{
	switch (type)
	{
	case ST_VERTEX:
		{
			m_pVertexShader = newShader(type);
			if (m_pVertexShader->initialize(strSource))
				return MATH_NULL;

			return m_pVertexShader;
		}break;

	case ST_FRAGMENT:
		{
			m_pFragmentShader = newShader(type);
			if(m_pFragmentShader->initialize(strSource))
				return MATH_NULL;

			return m_pFragmentShader;
		}break;

	default: break;
	}

	return MATH_NULL;
}


void CGpuProgram::destory()
{
	onBeforeDestory();

	if (m_pShaderParamTable != MATH_NULL)
	{
		m_pShaderParamTable->destory();
		delete m_pShaderParamTable;
		m_pShaderParamTable = MATH_NULL;
	}

	SAFE_DELETE(m_pFragmentShader);
	SAFE_DELETE(m_pVertexShader);
}	

void CGpuProgram::update()
{
	updateAutoParams();
	updateParams();
}

}

