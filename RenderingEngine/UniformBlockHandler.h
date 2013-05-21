#pragma once
#include <string>
#include <map>
#include "BufferObject.h"

//works ONLY with std140 block layout
class UniformBlockHandler
{
public:
	UniformBlockHandler(void);
	~UniformBlockHandler(void);

	static void clear();
	static void createBlockBuffer(const std::string &bufferName, const void *data, unsigned int size);
	static void bindBlockToBuffer(unsigned int program, const std::string &blockName, const std::string &bufferName);
	static void fillBuffer(const std::string &bufferName, const void *data, unsigned int size);

private:
	static std::map<std::string, std::pair<BufferObject, unsigned int> > buffers;
	static unsigned int bindingPoints;
};

