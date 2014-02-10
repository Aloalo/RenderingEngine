#version 330 core
 
layout (triangles) in;
layout (line_strip, max_vertices = 8) out;
 
in VertexData
{
    vec3 normal;
} vertexData[];
 
uniform mat4 MVP;
 
smooth out vec4 color;
 
void main(void)
{
    for(int i = 0; i < gl_in.length(); ++i)
    {
        color = vec4(0.f, 1.0f, .7f, 1.f);
        gl_Position = MVP * gl_in[i].gl_Position;
        EmitVertex();
 
        color = vec4 (0.f);
        gl_Position = MVP * (gl_in[i].gl_Position + vec4(normalize(vertexData[i].normal) * 0.05f, 0.f));
        EmitVertex();
        EndPrimitive();
    }
}
