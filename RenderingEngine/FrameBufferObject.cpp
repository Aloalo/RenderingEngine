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

void FrameBufferObject::attachTexture(GLenum attachment, const Texture &texture, GLint level)
{
	bind();
	glFramebufferTexture(target, attachment, texture.getID(), level);
	if(attachment != GL_DEPTH_ATTACHMENT && attachment != GL_STENCIL_ATTACHMENT && attachment != GL_DEPTH_STENCIL_ATTACHMENT)
		colorAttachments.push_back(attachment);
}

void FrameBufferObject::attachTextureLayer(GLenum attachment, const Texture &texture, GLint level, GLint layer)
{
	bind();
	glFramebufferTextureLayer(target, attachment, texture.getID(), level, layer);
	if(attachment != GL_DEPTH_ATTACHMENT && attachment != GL_STENCIL_ATTACHMENT && attachment != GL_DEPTH_STENCIL_ATTACHMENT)
		colorAttachments.push_back(attachment);
}

bool FrameBufferObject::check() const
{
	bind();
	if(glCheckFramebufferStatus(target) == GL_FRAMEBUFFER_COMPLETE)
		return 1;
	return 0;
}

void FrameBufferObject::setDrawBuffers() const
{
	glDrawBuffers(colorAttachments.size(), colorAttachments.data());
}

void FrameBufferObject::attachRenderBuffer(GLenum attachment, const RenderBufferObject &rbo)
{
	glFramebufferRenderbuffer(target, attachment, RenderBufferObject::target, rbo.getID());
}

void FrameBufferObject::unBind() const
{
	glBindFramebuffer(target, 0);
}
