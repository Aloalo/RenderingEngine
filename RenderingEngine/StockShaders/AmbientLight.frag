#version 330

out vec4 outputColor;

uniform vec4 ambientIntensity;
uniform vec4 materialAmbientColor;

void main()
{
	outputColor += ambientIntensity * materialAmbientColor;
}
