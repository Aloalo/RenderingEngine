#include "BufferObject.h"


BufferObject *BufferObject::boundBuffer = 0;

BufferObject::BufferObject(GLenum _target, GLenum _usage)
	: target(_target), usage(_usage)
{
	generate();
}


BufferObject::BufferObject(GLenum _target, GLenum _usage, const GLvoid *data, GLsizei size)
	: target(_target), usage(_usage)
{
	generate();
	setData(data, size);
}

BufferObject::BufferObject()
{
}

BufferObject::~BufferObject(void)
{
}

void BufferObject::destroy()
{
	glDeleteBuffers(1, &ID);
}

void BufferObject::bind() const
{
	if(boundBuffer != this)
	{
		boundBuffer = (BufferObject*) this;
		glBindBuffer(target, ID);
	}
}

void BufferObject::setData(const GLvoid *data, GLsizei size)
{
	bind();
	glBufferData(target, size, data, usage);
}

void BufferObject::reSetData(const GLvoid *data, GLuint offset, GLuint size)
{
	bind();
	glBufferSubData(target, offset, size, data);
}

void BufferObject::generate()
{
	glGenBuffers(1, &ID);
}
