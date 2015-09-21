#pragma once
#include "HardwareBuffer.h"
#include "GLES2Define.h"
#include "GLES2/gl2.h"
#include "ShaderParam.h"
#include "Texture.h"
using namespace DreamEngine;

namespace DreamEngineGLES2
{

class _EngineGLES2Export CCommonFunction
{
public:
	CCommonFunction(void);
	~CCommonFunction(void);

	static int		HDBufTypeToGLES2PriType(HardwareBufferType HDBufType);
	static int		IdxBufTypeToElemDrawType(DreamEngine::IndexBufferType idxBufType);

	typedef std::pair<CShaderParam::ParamType, m_uint16> ParamTypeInfo ;
	static ParamTypeInfo 
					GLES2ParamDataTypeToParamType(GLenum type);

	static GLenum	ParamTypeToGLES2DataType(CShaderParam::ParamType type);

	static int		CaculateParamBufferSize(const ParamTypeInfo& paramInfo);

	static CString	UsageToGLSLAttributeName(DREAMDDECLUSAGE usage, int usageIdx=0);

	static GLint	TexFormatToGLES2Format(TEX_FORMAT texFormat);
	
};

}


