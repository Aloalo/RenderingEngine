#include "Texture2D.h"
#include <GLFW/glfw3.h>

using namespace glm;

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

Texture* Texture::defaultWhite()
{
	Texture *tex = new Texture2D(GL_TEXTURE_2D);
	float data[] = {1.0f, 1.0f, 1.0f, 1.0f};

	tex->bind();
	tex->texImage(0, GL_RGBA, vec3(1, 1, 0), GL_RGBA, GL_FLOAT, data);
	return tex;
}
