#pragma once

#include "EngineObject.h"
#include "ShaderParamTable.h"
#include "AutoShaderParam.h"

namespace DreamEngine
{

class _EngineExport CShader : public CEngineObject
{
public:

	CShader(ShaderType type);
	virtual ~CShader(void);

	virtual Error		initializeFromFile(const CString& fileName);
	virtual	Error		initialize(const CString& source);
	ShaderType			getType()const;

protected:

	ShaderType			m_type;
	CString				m_strSource;

protected:

	virtual Error		onInitializeShader()=0;
	
};



}


