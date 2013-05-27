#pragma once

#include <GL/glew.h>

class BufferObject
{
public:
	BufferObject();
	BufferObject(GLenum _target, GLenum _usage);
	BufferObject(GLenum _target, GLenum _usage, const GLvoid *data, GLsizei size);
	~BufferObject(void);

	void destroy();
	void bind() const;
	void setData(const GLvoid *data, GLsizei size);
	void reSetData(const GLvoid *data, GLuint offset, GLuint size);

	GLuint get() const;

protected:
	static BufferObject *boundBuffer;

	GLenum target;
	GLenum usage;

	GLuint ID;
};


