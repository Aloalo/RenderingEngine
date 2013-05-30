#include "VertexAttribArray.h"

VertexAttribArray::VertexAttribArray(GLuint _index, GLint _size, GLenum _type)
	: index(_index), size(_size), type(_type)
{
	norm = -1;
}

VertexAttribArray::VertexAttribArray(GLuint _index, GLint _size, GLenum _type, GLboolean _norm)
	: index(_index), size(_size), type(_type), norm(_norm)
{
}

VertexAttribArray::~VertexAttribArray(void)
{
}

void VertexAttribArray::enable() const
{
	glEnableVertexAttribArray(index);
}

void VertexAttribArray::disable() const
{
	glDisableVertexAttribArray(index);
}

void VertexAttribArray::attribPointer() const
{
	enable();
	if(norm == -1)
	{
		if(type == GL_BYTE || type == GL_UNSIGNED_BYTE || type == GL_SHORT || 
			type == GL_UNSIGNED_SHORT || type == GL_INT || type == GL_UNSIGNED_INT)
			glVertexAttribIPointer(index, size, type, 0, 0);
		else if(type == GL_DOUBLE)
			glVertexAttribLPointer(index, size, type, 0, 0);
	}
	else
		glVertexAttribPointer(index, size, type, norm, 0, 0);
}

void VertexAttribArray::attribDivisor(GLuint divisor) const
{
	glVertexAttribDivisor(index, divisor);
}
