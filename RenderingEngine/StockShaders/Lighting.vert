#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 UVcoord;

out vec3 vertexNormal;
out vec3 vertexPosition;
out vec2 UV;


uniform mat4 mvMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vec4 tempCamPosition = (mvMatrix * vec4(position, 1.0));
	gl_Position = projectionMatrix * tempCamPosition;

	vertexNormal = normalMatrix * normal;
	vertexPosition = vec3(tempCamPosition);
	UV = UVcoord;
}
