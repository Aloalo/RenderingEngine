#pragma once
#include "OGLobject.h"

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

private:
	void generate();
	GLenum target;
};

