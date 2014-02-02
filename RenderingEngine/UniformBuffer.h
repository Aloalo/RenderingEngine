#pragma once

#include "BufferObject.h"

namespace reng
{
#define UNIFORM_MACRO(tp,name,offset) \
	void (name(const tp &x)) \
	{ \
	setSubData(offset, x); \
}

	class UniformBuffer
		: public BufferObject
	{
	public:
		UniformBuffer(void);
		UniformBuffer(int _size);
		UniformBuffer(int _size, void *_data);
		~UniformBuffer(void);

		template<class T>
		void setSubData(int offset, const T &data);
		void bindToPoint(int point);
	};

	template<class T>
	void UniformBuffer::setSubData(int offset, const T &data)
	{
		reSetData((void*)&data, offset, sizeof data);
	}
}
