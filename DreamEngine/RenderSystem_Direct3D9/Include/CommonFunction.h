#pragma once
#include "D3D9Define.h"
#include "D3D9Enum.h"
#include "d3d9.h"
#include "d3dx9shader.h"
#include "HardwareBuffer.h"
#include "ShaderParam.h"
#include "Texture.h"

using namespace DreamEngine;

namespace DreamEngineD3D
{

class _EngineD3D9Export CCommonFunction
{
public:
	CCommonFunction(void);
	~CCommonFunction(void);

	static void			vertexElementToD3D9Element(
							MATH_OUT D3DVERTEXELEMENT9* pElement,
							const CVertexBuffer::ElementLst& elemLst, 
							bool isAddEndDecl=false);

	static CShaderParam::ParamType 
						D3D9ParamTypeToSPType(D3DXPARAMETER_CLASS SPClass,
							D3DXPARAMETER_TYPE SPType, m_uint8 elemCount);

	static D3DPRIMITIVETYPE 
						HDBufTypeToD3DPriType(HardwareBufferType HDBufType);

	static D3DPOOL		RSPOOLToD3DPool(RSPOOL pool);

	static D3DFORMAT	texFormatToD3DFormat(TEX_FORMAT texFormat);
	static TEX_FORMAT	D3DFormatToTexFormat(D3DFORMAT texFormat);

	static CString		profileToString(ShaderProfile profile);
	static CString		profileToEnterFun(ShaderProfile profile);
	static ShaderType	profileToType(ShaderProfile profile);
	
};

}


