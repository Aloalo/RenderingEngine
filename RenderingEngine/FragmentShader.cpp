
#include "FragmentShader.h"

FragmentShader::FragmentShader(const char *name)
{
	init(name);
}

FragmentShader::~FragmentShader(void)
{
}

const char* FragmentShader::getExtension()
{
	return ".frag";
}

const char* FragmentShader::getTypeString()
{
	return "fragment";
}

int FragmentShader::getGlType()
{
	return GL_FRAGMENT_SHADER;
}
