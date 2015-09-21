#pragma once
#include "Engineobject.h"
#include "ShaderParam.h"

namespace DreamEngine
{

class _EngineExport CAutoShaderParam : public CEngineObject
{
public:

	enum AutoParam
	{
		atp_worldMatrix			= 1,
		atp_viewMatrix			= 2,
		atp_worldViewProjMatrix	= 3,

		atp_cameraPos			= 20,
	};

public:
	CAutoShaderParam(void);
	~CAutoShaderParam(void);

	/*typedef std::map<AutoParam, CShaderParam>	AutoParamLst;
	typedef std::map<AutoParam, CMatrix16>		MatrixLst;
	typedef std::map<AutoParam, CVector3>		VectorLst;

	

	void Initialize(void);

	protected:

	AutoParamLst		m_params;

	VectorLst			m_vectors;
	MatrixLst			m_matrixs;*/
};
}


