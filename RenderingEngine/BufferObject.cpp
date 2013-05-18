#include "BufferObject.h"

BufferObject::BufferObject(GLenum _target, GLenum _usage)
	: target(_target), usage(_usage)
{
	glGenBuffers(1, &ID);
}


BufferObject::BufferObject(GLenum _target, GLenum _usage, const GLvoid *data, GLsizei size)
	: target(_target), usage(_usage)
{
	glGenBuffers(1, &ID);
	bind();
	setData(data, size);
}

BufferObject::~BufferObject(void)
{
	glDeleteBuffers(1, &ID);
}


void BufferObject::unBind() const
{
	glBindBuffer(target, 0);
}

void BufferObject::bind() const
{
	glBindBuffer(target, ID);
}

void BufferObject::setData(const GLvoid *data, GLsizei size)
{
	glBufferData(target, size, data, usage);
}

void BufferObject::reSetData(const GLvoid *data, GLuint offset, GLuint size)
{
	glBufferSubData(target, offset, size, data);
}

GLuint BufferObject::get() const
{
	return ID;
}

void BufferObject::bindBufferBase(GLuint bindingPoint) const
{
	glBindBufferBase(target, bindingPoint, ID);
}
