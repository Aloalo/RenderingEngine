#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

#define UNIFORM_MACRO(tp,name,offset) \
	void (name(const tp &x)) \
		{ \
		setSubData(offset, x); \
		}

class UniformBuffer
{
public:
	unsigned int id;

	UniformBuffer(void);
	UniformBuffer(int size);
	UniformBuffer(int size, void *data);
	~UniformBuffer(void);

	void bind();
	void setData(int size, void *data, int usage = GL_DYNAMIC_DRAW);
	void setSubData(int offset, int size, void *data);
	template<class T>
	void setSubData(int offset, const T &data);
	void bindToPoint(int point);

private:
	static UniformBuffer *boundBuffer;
};

template<class T>
void UniformBuffer::setSubData(int offset, const T &data)
{
	setSubData(offset, sizeof data, (void*)&data);
}
