#pragma once

#include "OGLobject.h"

class FrameBufferObject
	: public OGLobject
{
public:
	FrameBufferObject(GLenum _target);
	~FrameBufferObject(void);

	void bind() const;
	void destroy();

protected:
	void generate();
	GLenum target;
};

