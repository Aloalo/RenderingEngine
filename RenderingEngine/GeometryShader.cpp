#include "GeometryShader.h"

namespace reng
{
	GeometryShader::GeometryShader(const char *name)
	{
		init(name);
	}

	GeometryShader::GeometryShader(int idr, const char *name)
	{
		init(idr, name);
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
}
