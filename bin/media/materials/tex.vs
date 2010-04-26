attribute vec3 vp_Vertex;
attribute vec3 vp_MultiTexCoord0;

uniform mat4 vp_ProjectionMatrix;
uniform mat4 vp_ModelMatrix;
uniform mat4 vp_ViewMatrix;
uniform mat4 vp_ModelViewMatrix;

varying vec2 vp_TexCoord;

void main()
{
	vp_TexCoord = vp_MultiTexCoord0.st;
	gl_Position = vec4(vp_Vertex, 1.0) * vp_ModelViewMatrix * vp_ProjectionMatrix;
} 
