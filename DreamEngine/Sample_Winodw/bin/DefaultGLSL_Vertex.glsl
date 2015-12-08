attribute vec3 vPosition; 
uniform mat4 atp_worldViewProjMatrix;
void main()	
{ 
	gl_Position = atp_worldViewProjMatrix *vec4(vPosition,1.0f);
}