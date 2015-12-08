#include "D3D9GpuTypeManager.h"

namespace DreamEngineD3D
{
CD3D9GpuTypeManager::CD3D9GpuTypeManager(void)
{
}


CD3D9GpuTypeManager::~CD3D9GpuTypeManager(void)
{
}

const char* CD3D9GpuTypeManager::defaultVertex()
{
	return																
		"void VS_MAIN( float3 position : POSITION,		\
		out float4  oPosition : POSITION,				\
		uniform matrix atp_worldViewProjMatrix			\
					)									\
		{												\
			float4 pos = float4(position, 1);			\
			oPosition =  mul(pos, atp_worldViewProjMatrix);\
		}";

}

const char* CD3D9GpuTypeManager::defaultFragment()
{
	return															
		"void PS_MAIN(					\
		uniform float red,				\
		out float4 oColor : COLOR		\
					  )					\
		{								\
			oColor = float4(red,0,0,1);	\
		} ";
}

const char* CD3D9GpuTypeManager::defaultTextureFragment()
{
	return															
		"void PS_MAIN(					\
		uniform float red,				\
		out float4 oColor : COLOR		\
		)					\
		{								\
		oColor = float4(red,0,0,1);	\
		} ";
}

}

