#pragma once
#include "EngineObject.h"
#include "Shader.h"

namespace DreamEngine
{

class _EngineExport CGpuProgram : public CEngineObject
{
public:
	CGpuProgram(void);
	~CGpuProgram(void);

public:

	Error				initialize(const CString& vertexSource,			const CString& fragmentSource);
	Error				initializeFromFile(const CString& vertexFile,	const CString& fragmentFile);

	CShaderParamTable*	getShaderParamTable(void)const	{return m_pShaderParamTable;}
	void				update(void);

	CShader*			getVertexShader()const		{return m_pVertexShader;}
	CShader*			getFragmentShader()const	{return m_pFragmentShader;}

	void				destory(void);

protected:

	CShader*			createShader(ShaderType type,	const CString& source);
	CShader*			loadShader(ShaderType type,		const CString& fileName);

	virtual CShader*	newShader(ShaderType type)=0;

	virtual Error		createParamTable(void)=0;
	virtual void		updateAutoParams(void)=0;
	virtual void		updateParams(void)=0;
	virtual Error		onShaderCreated()=0;
	virtual void		onBeforeDestory()=0;

	CShaderParamTable*		m_pShaderParamTable;

	CShader*				m_pVertexShader;
	CShader*				m_pFragmentShader;
};

}


