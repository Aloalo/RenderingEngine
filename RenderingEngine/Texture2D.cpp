#include "Texture2D.h"

Texture2D::Texture2D(GLenum _target)
	: Texture(_target)
{
}

Texture2D::Texture2D()
	: Texture()
{
}

Texture2D::~Texture2D(void)
{
}

void Texture2D::texImage(GLint level, GLint internalFormat, const glm::vec3 &dimensions, GLenum format, GLenum type, const GLvoid *data) const
{
	glTexImage2D(target, level, internalFormat, dimensions.x, dimensions.y, 0, format, type, data);
}
