#pragma once

#include "Texture.h"

class Texture2D :
	public Texture
{
public:
	Texture2D(GLenum _target);
	~Texture2D(void);

	void texImage(GLint level, GLint internalFormat, const glm::vec3 &dimensions, GLenum format, GLenum type, const GLvoid *data) const;
};