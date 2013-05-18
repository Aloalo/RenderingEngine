#include "Texture.h"
#include <GL\glfw.h>


Texture::Texture(GLenum _target)
	: target(_target)
{
	glGenTextures(1, &ID);
}

Texture::~Texture(void)
{
	glDeleteTextures(1, &ID);
}

void Texture::bind()
{
	glBindTexture(target, ID);
}

void Texture::load(const char *imagepath)
{
	glfwLoadTexture2D(imagepath, 0);
}

void Texture::texParam(GLenum paramName, GLuint param)
{
	glTexParameteri(target, paramName, param);
}

void Texture::texParam(GLenum paramName, GLfloat param)
{
	glTexParameterf(target, paramName, param);
}
