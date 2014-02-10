#pragma once

#include "Shader.h"

namespace reng
{
	class VertexShader :
		public Shader
	{
	public:
		VertexShader(const char *name);
		VertexShader(int idr, const char *name);
		~VertexShader(void);

		virtual const char* getExtension();
		virtual const char* getTypeString();
		virtual int getGlType();
	};
}
