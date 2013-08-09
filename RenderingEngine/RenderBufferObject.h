#pragma once

#include "OGLobject.h"

class RenderBufferObject :
	public OGLobject
{
public:
	RenderBufferObject(void);
	~RenderBufferObject(void);

	void bind() const;
	void destroy();
	void allocateStorage(GLenum internalformat, GLsizei width, GLsizei height) const;
	void allocateStorageMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) const;
	void query(GLenum pname, GLint *ret) const;

	static GLenum target;
private:
	void generate();
};

