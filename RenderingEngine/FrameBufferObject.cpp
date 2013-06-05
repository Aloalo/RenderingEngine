#include "FrameBufferObject.h"

FrameBufferObject::FrameBufferObject(GLenum _target)
	: target(_target)
{
}


FrameBufferObject::~FrameBufferObject(void)
{
}

void FrameBufferObject::bind() const
{
	glBindFramebuffer(target, ID);
}

void FrameBufferObject::destroy()
{
	glDeleteFramebuffers(1, &ID);
}

void FrameBufferObject::generate()
{
	glGenFramebuffers(1, &ID);
}
