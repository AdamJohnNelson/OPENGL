#version 400

in vec3 vp;

uniform mat4 u_Translate;
uniform mat4 u_Scale;

void main()
{
	gl_Position = u_Translate * u_Scale * vec4(vp, 1.0);
}