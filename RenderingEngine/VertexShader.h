#pragma once

#include "Shader.h"

class VertexShader :
	public Shader
{
public:
	VertexShader(const char *name);
	~VertexShader(void);

	virtual const char* getExtension();
	virtual const char* getTypeString();
	virtual int getGlType();
};

