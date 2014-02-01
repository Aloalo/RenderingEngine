#version 330

in vec2 UV;
out vec4 outputColor;

uniform vec4 ambientIntensity;
uniform vec4 diffuseColor;
uniform vec4 materialAmbientColor;
uniform sampler2D textureSampler;

void main()
{
	outputColor += ambientIntensity * diffuseColor * texture(textureSampler, UV).rgba;
}
