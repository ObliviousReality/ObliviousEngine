#type vertex
#version 330 core

layout(location=0) in vec3 position;

uniform mat4 u_ViewProj;
uniform mat4 transform;	

out vec3 vPos;	

void main()
{
	vPos = position;
	gl_Position = u_ViewProj * transform * vec4(position, 1.0);	
}

#type fragment
#version 330 core

layout(location=0) out vec4 colour;		
in vec3 vPos;

uniform vec3 u_Colour;

void main()
{
	colour = vec4(u_Colour,1.0);
}