void VS_MAIN( float3 position : POSITION,
				  
			out float4  oPosition : POSITION,
		
			uniform matrix atp_worldViewProjMatrix
			)
{
	float4 pos = float4(position, 1);
	oPosition =  mul(pos, atp_worldViewProjMatrix);
}