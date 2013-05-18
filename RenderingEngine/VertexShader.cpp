
#include "VertexShader.h"

VertexShader::VertexShader(const char *name)
{
	init(name);
}

VertexShader::~VertexShader(void)
{
}

const char* VertexShader::getExtension()
{
	return ".vert";
}

const char* VertexShader::getTypeString()
{
	return "vertex";
}

int VertexShader::getGlType()
{
	return GL_VERTEX_SHADER;
}
