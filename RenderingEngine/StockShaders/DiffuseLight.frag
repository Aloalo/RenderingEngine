#version 330

in vec3 vertexNormal;
in vec2 UV;

out vec4 outputColor;

uniform vec4 diffuseColor;
uniform vec3 lightDir;
uniform mat3 normalMatrix;
uniform sampler2D textureSampler;

void main()
{
	float cosAngIncidence = dot(normalize(vertexNormal), normalize(normalMatrix * lightDir));
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);

	outputColor = diffuseColor * cosAngIncidence * texture(textureSampler, UV).rgba;
}
