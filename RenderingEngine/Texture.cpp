#include "Texture.h"
#include "GL\glfw.h"

Texture::Texture(GLenum _target)
	: target(_target)
{
	generate();
}

Texture::Texture()
{
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

void Texture::texParami(GLenum paramName, GLuint param) const
{
	bind();
	glTexParameteri(target, paramName, param);
}

void Texture::texParamf(GLenum paramName, GLfloat param) const
{
	bind();
	glTexParameterf(target, paramName, param);
}

void Texture::texParamIuiv(GLenum paramName, const GLuint *param) const
{
	bind();
	glTexParameterIuiv(target, paramName, param);
}

void Texture::texParamIiv(GLenum paramName, const GLint *param) const
{
	bind();
	glTexParameterIiv(target, paramName, param);
}

void Texture::texParamfv(GLenum paramName, const GLfloat *param) const
{
	bind();
	glTexParameterfv(target, paramName, param);
}