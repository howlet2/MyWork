#pragma once
#include "GpuProgram.h"
#include "GLES2Define.h"
#include "GLES2/gl2.h"
using namespace DreamEngine;

namespace DreamEngineGLES2
{
class _EngineGLES2Export CGLES2GLSLProgram : public CGpuProgram
{
public:
	enum PointType
	{
		PT_ATTRIBUTE	= 0,
		PT_UNIFROM		= 1,
	};
public: 

	CGLES2GLSLProgram();
	~CGLES2GLSLProgram();

	GLuint				getGLESProgram(void)const		{return m_glProgram;}
	CShaderParamTable*  getAttributeParamTable()const	{return m_pAttriParamTable;}
	GLuint				getAttributeLocal(const CString& name)const;

protected:

	virtual CShader*	newShader(ShaderType type);

	virtual Error		createParamTable(void);
	virtual void		updateAutoParams(void);
	virtual void		updateParams(void);
	virtual  Error		onShaderCreated(void);
	virtual void		onBeforeDestory(void);

	void				_addParams(void);
	void				_updateUniformParams(CShaderParam* pParam);

protected:

	GLint				m_glProgram;

	CShaderParamTable*	m_pAttriParamTable;
};
}


