#version 330

in vec2 UV;

out vec4 outputColor;

uniform vec4 diffuseColor;
uniform sampler2D textureSampler;

void main()
{
	outputColor = diffuseColor * texture(textureSampler, UV).rgba;
}
