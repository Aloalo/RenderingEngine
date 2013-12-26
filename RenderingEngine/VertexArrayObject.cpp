#include "VertexArrayObject.h"


VertexArrayObject::VertexArrayObject(void)
{
	generate();
}


VertexArrayObject::~VertexArrayObject(void)
{
}

void VertexArrayObject::bind() const
{
	glBindVertexArray(ID);
}

void VertexArrayObject::unBind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::destroy()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArrayObject::generate()
{
	glGenVertexArrays(1, &ID);
}