
#include "GeometryShader.h"

GeometryShader::GeometryShader(const char *name)
{
	init(name);
}

GeometryShader::~GeometryShader(void)
{
}

const char* GeometryShader::getExtension()
{
	return ".geom";
}

const char* GeometryShader::getTypeString()
{
	return "geometry";
}

int GeometryShader::getGlType()
{
	return GL_GEOMETRY_SHADER;
}
