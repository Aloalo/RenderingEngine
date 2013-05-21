#include "VertexArrayObject.h"


VertexArrayObject::VertexArrayObject(void)
{
	glGenVertexArrays(1, &ID);
}


VertexArrayObject::~VertexArrayObject(void)
{
}

void VertexArrayObject::bind() const
{
	glBindVertexArray(ID);
}

GLuint VertexArrayObject::get() const
{
	return ID;
}

void VertexArrayObject::unBind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::destroy()
{
	glDeleteVertexArrays(1, &ID);
}
