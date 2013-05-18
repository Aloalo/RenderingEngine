// ADS Point lighting Shader
#version 330

in vec3 vVertex;
in vec3 vNormal;

uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;

uniform vec3 vLightPosition;
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

smooth out vec4 vVaryingColor;

void main(void)
{
    vec3 vEyeNormal = normalMatrix * vNormal;
    vec4 vPosition3 = mvMatrix * vec4(vVertex, 1.0f);
    vec3 vLightDir = normalize(vLightPosition - vPosition3);
    float diff = max(0.0, dot(vEyeNormal, vLightDir));
    vVaryingColor = diff * diffuseColor;
    vVaryingColor += ambientColor;
    vec3 vReflection = normalize(reflect(-vLightDir, vEyeNormal));
    float spec = max(0.0, dot(vEyeNormal, vReflection));
    if(diff != 0)
    {
        float fSpec = pow(spec, 128.0);
        vVaryingColor.rgb += vec3(fSpec, fSpec, fSpec);
    }
    gl_Position = mvpMatrix * vec4(vVertex, 1.0f);
}
