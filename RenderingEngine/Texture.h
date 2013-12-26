#pragma once
#include "OGLobject.h"
#include "glm/glm.hpp"

class Texture
	: public OGLobject
{
public:
	Texture();
	Texture(GLuint _target);
	virtual ~Texture(void);

	void bind() const;
	void destroy();

	void texParami(GLenum paramName, GLuint param) const;
	void texParamf(GLenum paramName, GLfloat param) const;
	void texParamIuiv(GLenum paramName, const GLuint *param) const;
	void texParamIiv(GLenum paramName, const GLint *param) const;
	void texParamfv(GLenum paramName, const GLfloat *param) const;

	virtual void texImage(GLint level, GLint internalFormat, const glm::vec3 &dimensions, GLenum format, GLenum type, const GLvoid *data) const = 0;
protected:
	void generate();
	GLenum target;
};

