#type vertex
#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec2 textureCoord;

uniform mat4 u_ViewProj;
uniform mat4 transform;	

out vec2 v_textureCoord;

void main()
{
	v_textureCoord = textureCoord;
	gl_Position = u_ViewProj * transform * vec4(position, 1.0);	
}

#type fragment
#version 330 core

layout(location=0) out vec4 colour;	

in vec2 v_textureCoord;

uniform vec4 u_Colour;
uniform sampler2D u_Texture;

void main()
{
	colour = texture(u_Texture, v_textureCoord) * u_Colour;
}