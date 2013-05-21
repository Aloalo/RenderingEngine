#pragma once

#include <GL/glew.h>

class VertexArrayObject
{
public:
	/*Also generates the VAO*/
	VertexArrayObject(void);
	~VertexArrayObject(void);

	static void unBind();

	void destroy();
	void bind() const;
	GLuint get() const;

private:
	GLuint ID;
};

