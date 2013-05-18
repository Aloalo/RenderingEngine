#pragma once

#include "Shader.h"

class GeometryShader :
	public Shader
{
public:
	GeometryShader(const char *name);
	~GeometryShader(void);

	virtual const char* getExtension();
	virtual const char* getTypeString();
	virtual int getGlType();
};

