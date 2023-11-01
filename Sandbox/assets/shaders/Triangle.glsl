#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;

uniform mat4 u_ViewProj;
uniform mat4 transform;

out vec3 v_Position;
out vec4 v_Color;

void main()
{
	v_Position = position;
	v_Color = colour;
	gl_Position = u_ViewProj * transform * vec4(position, 1.0);	
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;

void main()
{
	color = vec4(v_Position * 0.5 + 0.5, 1.0);
	color = v_Color;
}