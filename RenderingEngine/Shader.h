#pragma once

#include "GL/glew.h"

class Shader
{
public:
	int id;

	virtual const char* getExtension() = 0;
	virtual const char* getTypeString() = 0;
	virtual int getGlType() = 0;

protected:
	void init(const char *name);
};

