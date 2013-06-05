#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(void)
	: BufferObject(GL_UNIFORM_BUFFER, GL_DYNAMIC_DRAW)
{
}

UniformBuffer::UniformBuffer(int _size)
	: BufferObject(GL_UNIFORM_BUFFER, GL_DYNAMIC_DRAW, 0, _size)
{
}

UniformBuffer::UniformBuffer(int _size, void *_data)
	: BufferObject(GL_UNIFORM_BUFFER, GL_DYNAMIC_DRAW, _data, _size)
{
}

UniformBuffer::~UniformBuffer(void)
{
}

void UniformBuffer::bindToPoint(int point)
{
	glBindBufferBase(target, point, ID);
}
