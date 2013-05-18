#pragma once

#include <vector>
#include <string>
#include "BufferObject.h"

class UniformBufferList
{
public:
	UniformBufferList(void);
	~UniformBufferList(void);

	void addBuffer(const std::string &name);
	unsigned int getBindingPoint(const std::string &name);
	void setBufferData(const std::string &name);

private:
	std::vector<std::pair<std::string, BufferObject*> > uniformBuffers;
};

