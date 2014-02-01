#version 330

in vec3 vertexNormal;
in vec3 vertexPosition;
in vec2 UV;

out vec4 outputColor;

uniform vec3 cameraSpaceLightPos;

uniform vec4 diffuseColor;
uniform vec4 specularColor;
uniform float shininessFactor;

uniform float lightAttenuation;
uniform vec4 lightIntensity;
uniform sampler2D textureSampler;

float CalcAttenuation(in vec3 vertexPosition, out vec3 lightDirection)
{
	vec3 lightDifference =  cameraSpaceLightPos - vertexPosition;
	float lightDistanceSqr = dot(lightDifference, lightDifference);
	lightDirection = lightDifference * inversesqrt(lightDistanceSqr);
	
	return (1 / ( 1.0 + lightAttenuation * sqrt(lightDistanceSqr)));
}

void main()
{
	vec3 lightDir = vec3(0.0);
	float atten = CalcAttenuation(vertexPosition, lightDir);
	vec4 attenIntensity = atten * lightIntensity;
	
	vec3 surfaceNormal = normalize(vertexNormal);
	float cosAngIncidence = dot(surfaceNormal, lightDir);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);
	
	vec3 viewDirection = normalize(-vertexPosition);
	vec3 reflectDir = reflect(-lightDir, surfaceNormal);
	float phongTerm = dot(viewDirection, reflectDir);
	if(phongTerm  > 0.0)
	{
		phongTerm = clamp(phongTerm, 0, 1);
		phongTerm = cosAngIncidence != 0.0 ? phongTerm : 0.0;
		phongTerm = pow(phongTerm, shininessFactor);
	}
	
	outputColor += attenIntensity * (specularColor * phongTerm + diffuseColor * cosAngIncidence * texture(textureSampler, UV).rgba);
}
