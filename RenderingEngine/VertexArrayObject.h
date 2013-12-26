#pragma once

#include "OGLobject.h"

class VertexArrayObject
	: public OGLobject
{
public:
	/*Also generates the VAO*/
	VertexArrayObject(void);
	~VertexArrayObject(void);

	static void unBind();

	void bind() const;
	void destroy();

protected:
	void generate();
};

