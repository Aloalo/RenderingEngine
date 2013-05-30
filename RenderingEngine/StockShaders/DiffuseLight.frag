#version 330

in vec3 vertexNormal;

out vec4 outputColor;

uniform vec4 diffuseColor;
uniform vec3 lightDir;
uniform mat3 normalMatrix;

void main()
{
     
	float cosAngIncidence = dot(normalize(vertexNormal), normalize(normalMatrix * lightDir));
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);

	outputColor = diffuseColor * cosAngIncidence;
}
