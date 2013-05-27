#include "GL/glew.h"
#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(void)
{
	glGenBuffers(1, &id);
}

UniformBuffer::UniformBuffer(int size)
{
	glGenBuffers(1, &id);
	setData(size, 0);
}

UniformBuffer::UniformBuffer(int size, void *data)
{
	glGenBuffers(1, &id);
	setData(size, data);
}

UniformBuffer::~UniformBuffer(void)
{
}

void UniformBuffer::bind()
{
	if(boundBuffer != this)
	{
		boundBuffer = this;
		glBindBuffer(GL_UNIFORM_BUFFER, id);
	}
}

void UniformBuffer::setData(int size, void *data, int usage)
{
	bind();
	glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
}

void UniformBuffer::setSubData(int offset, int size, void *data)
{
	bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

void UniformBuffer::bindToPoint(int point)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, point, id);
}

UniformBuffer *UniformBuffer::boundBuffer = 0;
