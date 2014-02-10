#pragma once

#include "Shader.h"

namespace reng
{
	class FragmentShader :
		public Shader
	{
	public:
		FragmentShader(const char *name);
		FragmentShader(int idr, const char *name);
		~FragmentShader(void);

		virtual const char* getExtension();
		virtual const char* getTypeString();
		virtual int getGlType();
	};
}
