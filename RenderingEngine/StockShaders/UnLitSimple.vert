#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 UVcoord;

out vec2 UV;

uniform mat4 mvpMatrix;

void main()
{
	gl_Position = mvpMatrix * vec4(position, 1.0);
	UV = UVcoord;
}
