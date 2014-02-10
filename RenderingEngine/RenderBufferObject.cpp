#include "RenderBufferObject.h"

namespace reng
{
	GLenum RenderBufferObject::target = GL_RENDERBUFFER;

	RenderBufferObject::RenderBufferObject(void)
	{
		generate();
	}

	RenderBufferObject::~RenderBufferObject(void)
	{
	}

	void RenderBufferObject::bind() const
	{
		glBindRenderbuffer(target, ID);
	}

	void RenderBufferObject::destroy()
	{
		glDeleteRenderbuffers(1, &ID);
	}

	void RenderBufferObject::generate()
	{
		glGenRenderbuffers(1, &ID);
	}

	void RenderBufferObject::allocateStorage(GLenum internalformat, GLsizei width, GLsizei height) const
	{
		bind();
		glRenderbufferStorage(target, internalformat, width, height);
	}

	void RenderBufferObject::allocateStorageMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) const
	{
		bind();
		glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
	}

	void RenderBufferObject::query(GLenum pname, GLint *ret) const
	{
		bind();
		glGetRenderbufferParameteriv(target, pname, ret);
	}
}
