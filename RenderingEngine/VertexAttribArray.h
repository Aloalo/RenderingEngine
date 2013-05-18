#pragma once

#include <GL/glew.h>

class VertexAttribArray
{
public:
	VertexAttribArray(GLuint _index, GLint _size, GLenum _type, GLboolean _norm);
	VertexAttribArray(GLuint _index, GLint _size, GLenum _type);
	~VertexAttribArray(void);

	void enable() const;
	void disable() const;
	void attribPointer() const;
	void attribDivisor(GLuint divisor) const;

private:
	GLuint index;
	GLint size;
	GLenum type;
	int norm;
};

