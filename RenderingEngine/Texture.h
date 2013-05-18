#pragma once

#include <GL\glew.h>

class Texture
{
public:
	Texture(GLenum _target);
	~Texture(void);

	void bind();
	void load(const char *imagepath);
	void texParam(GLenum paramName, GLuint param);
	void texParam(GLenum paramName, GLfloat param);

private:
	GLuint ID;
	GLenum target;
};

