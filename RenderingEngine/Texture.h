#pragma once
#include "OGLobject.h"
#include "glm/glm.hpp"

class Texture
	: public OGLobject
{
public:
	Texture(GLuint _target);
	~Texture(void);

	void bind() const;
	void destroy();

	void texParam(GLenum paramName, GLuint param) const;
	void texParam(GLenum paramName, GLfloat param) const;
	void texParam(GLenum paramName, const GLuint *param) const;
	void texParam(GLenum paramName, const GLint *param) const;
	void texParam(GLenum paramName, const GLfloat *param) const;

	virtual void texImage(GLint level, GLint internalFormat, const glm::vec3 &dimensions, GLenum format, GLenum type, const GLvoid *data) const = 0;
protected:
	void generate();
	GLenum target;
};

