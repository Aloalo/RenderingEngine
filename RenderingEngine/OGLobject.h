#pragma once

#include <GL/glew.h>

/*
oglobjects must be destroyed by hand
*/
class OGLobject
{
public:
	OGLobject(void);
	virtual ~OGLobject(void);

	virtual void bind() const = 0;
	virtual void destroy() = 0;
	GLuint getID() const;

protected:
	GLuint ID;
	virtual void generate() = 0;
};

