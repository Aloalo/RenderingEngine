#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out VertexData
{
    vec3 normal;
} vertexData;
 
void main(void)
{
    gl_Position = vec4(position, 1.0f);
    vertexData.normal = normalize(normal);
}
