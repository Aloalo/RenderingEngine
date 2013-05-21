#include "UniformBlockHandler.h"
#include <GL\glew.h>


std::map<std::string, std::pair<BufferObject, unsigned int> > UniformBlockHandler::buffers;
unsigned int UniformBlockHandler::bindingPoints = 0;

UniformBlockHandler::UniformBlockHandler(void)
{
}

UniformBlockHandler::~UniformBlockHandler(void)
{
	clear();
}


void UniformBlockHandler::clear()
{
	buffers.clear();
}

void UniformBlockHandler::createBlockBuffer(const std::string &bufferName, const void *data, unsigned int size)
{
	BufferObject buffer(GL_UNIFORM_BUFFER, GL_DYNAMIC_DRAW, data, size);
	buffer.bindBufferBase(bindingPoints);
	buffers[bufferName] = std::pair<BufferObject, unsigned int>(buffer, bindingPoints);
	bindingPoints++;
}

void UniformBlockHandler::bindBlockToBuffer(unsigned int program, const std::string &blockName, const std::string &bufferName)
{
	int blockIndex = glGetUniformBlockIndex(program, blockName.c_str());
	glUniformBlockBinding(program, blockIndex, buffers[bufferName].second);
}

void UniformBlockHandler::fillBuffer(const std::string &bufferName, const void *data, unsigned int size)
{
	buffers[bufferName].first.reSetData(data, 0, size);
}
