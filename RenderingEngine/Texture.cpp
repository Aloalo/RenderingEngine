#include "Texture.h"
#include "GL\glfw.h"

Texture::Texture(GLenum _target)
	: target(_target)
{
	generate();
}

Texture::~Texture(void)
{
}

void Texture::generate()
{
	glGenTextures(1, &ID);
}

void Texture::destroy()
{
	glDeleteTextures(1, &ID);
}

void Texture::bind() const
{
	glBindTexture(target, ID);
}

void Texture::texParam(GLenum paramName, GLuint param) const
{
	glTexParameteri(target, paramName, param);
}

void Texture::texParam(GLenum paramName, GLfloat param) const
{
	glTexParameterf(target, paramName, param);
}

void Texture::texParam(GLenum paramName, const GLuint *param) const
{
	glTexParameterIuiv(target, paramName, param);
}

void Texture::texParam(GLenum paramName, const GLint *param) const
{
	glTexParameterIiv(target, paramName, param);
}

void Texture::texParam(GLenum paramName, const GLfloat *param) const
{
	glTexParameterfv(target, paramName, param);
}
