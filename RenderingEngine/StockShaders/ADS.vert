// ADS Point lighting Shader
#version 330

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;

uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;

uniform mat4 mvMatrix;
uniform mat3 normalMatrix;
uniform mat4 mvpMatrix;

const int maxLights = 10;

struct Light
{
    vec3 position;
    float intensity;
};

layout(std140) uniform LightStuff
{
    Light light[maxLights];
	int lightCount;
};

smooth out vec4 vVaryingColor;

void main(void)
{
	vec3 vEyeNormal = normalMatrix * vNormal;
	vec4 vPosition3 = vec3(mvMatrix * vec4(vVertex, 1.0f));

    for(int i = 0; i < lightCount; i++)
	{
		vec3 vLightDir = normalize(light[i].position - vPosition3);
		float diff = max(0.0, dot(vEyeNormal, vLightDir));
		vVaryingColor = diff * diffuseColor;
		vec3 vReflection = normalize(reflect(-vLightDir, vEyeNormal));
		float spec = max(0.0, dot(vEyeNormal, vReflection));
		if(diff != 0)
		{
			float fSpec = pow(spec, 128.0);
			vVaryingColor.rgb += vec3(fSpec, fSpec, fSpec);
		}
	}
	
	vVaryingColor += ambientColor;
    gl_Position = mvpMatrix * vec4(vVertex, 1.0f);
}
